// Copyright 2021 SMS
// License(Apache-2.0)

#include "Server.h"
#include "Connection.h"

using namespace asio;

Server::Server()
		: socket(context), acceptor(context)
{
}

Server::~Server()
{
	stop();
}

bool Server::start(std::uint16_t port)
{
	try
	{
		ip::tcp::endpoint endpoint(ip::tcp::v4(), port);
		acceptor.open(endpoint.protocol());
		acceptor.bind(endpoint);
		acceptor.listen();

		acceptAsync();

		thread = std::thread([this]() { context.run(); });
	}
	catch(std::exception&)
	{
		return false;
	}

	return true;
}

void Server::stop()
{
	for(auto& conn : connections)
		conn->disconnect();
	context.stop();
	if(thread.joinable())
		thread.join();
}

void Server::write(std::shared_ptr<Connection> conn)
{
	assert(conn);

	if(!conn->isConnected())
	{
		if(onDisconnect)
			onDisconnect(conn);
		connections.erase(std::find(connections.begin(), connections.end(), conn));
	}
}

void Server::read(std::shared_ptr<Connection> conn)
{
	assert(conn);

	if(!conn->isConnected())
	{
		if(onDisconnect)
			onDisconnect(conn);
		connections.erase(std::find(connections.begin(), connections.end(), conn));
	}
}

void Server::acceptAsync()
{
	acceptor.async_accept([this](std::error_code ec, ip::tcp::socket sock) {
		if(ec)
		{
			acceptAsync();
		}

		auto ptr = std::make_shared<Connection>(context, std::move(sock));
		if(!onConnect || onConnect(ptr))
			connections.push_back(ptr);

		acceptAsync();
	});
}