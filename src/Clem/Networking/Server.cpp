// Copyright 2021 SMS
// License(Apache-2.0)

#include "Server.h"

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
	for(auto& con : connections)
		con->disconnect();
	context.stop();
	if(thread.joinable())
		thread.join();
}

void Server::acceptAsync()
{
	acceptor.async_accept([this](std::error_code ec, ip::tcp::socket sock) {
		assert(!ec);

		connections.push_back(std::make_shared<Connection>(context, std::move(sock)));
		acceptAsync();
	});
}