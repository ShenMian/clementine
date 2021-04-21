// Copyright 2021 SMS
// License(Apache-2.0)

#include "Server.h"
#include "Clem/Logger.h"
#include "Connection.h"

using namespace asio;

namespace clem
{

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
	catch(std::exception& e)
	{
		CLEM_LOG_ERROR("networking", e.what());
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

void Server::acceptAsync()
{
	acceptor.async_accept([this](std::error_code ec, ip::tcp::socket sock) {
		if(ec)
			abort();

		auto conn = std::make_shared<Connection>(context, std::move(sock));
		if(!onConnect || onConnect(conn))
		{
			conn->onMessage = [this, conn]() { onMessage(conn); };
			connections.push_back(conn);
		}

		acceptAsync();
	});
}

} // namespace clem