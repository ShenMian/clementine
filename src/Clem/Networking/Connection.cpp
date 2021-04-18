// Copyright 2021 SMS
// License(Apache-2.0)

#include "Connection.h"

using namespace asio;

Connection::Connection(io_context& c, ip::tcp::socket s)
		: context(c), socket(std::move(s))
{
	onConnect = [](std::error_code, ip::tcp::endpoint) {};
}

Connection::~Connection()
{
	disconnect();
}

bool Connection::connect(const std::string_view& host, std::uint16_t port)
{
	try
	{
		ip::tcp::resolver resolver(context);
		auto              endpoints = resolver.resolve(std::string(host), std::to_string(port));

		async_connect(socket, endpoints, Connection::onConnect);
	}
	catch(std::exception&)
	{
		return false;
	}
	return true;
}

void Connection::disconnect()
{
	socket.close();
}

bool Connection::isConnected() const
{
	return socket.is_open();
}