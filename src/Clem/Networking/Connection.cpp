// Copyright 2021 SMS
// License(Apache-2.0)

#include "Connection.h"

using namespace asio;

Connection::Connection(io_context& c, ip::tcp::socket s)
		: context(c), socket(std::move(s))
{
}

Connection::~Connection()
{
	disconnect();
}

bool Connection::connect(const asio::ip::tcp::endpoint& endpoint)
{
	error_code ec;
	socket.connect(endpoint, ec);
	return ec ? false : true;
}

void Connection::disconnect()
{
	socket.close();
}

bool Connection::isConnected() const
{
	return socket.is_open();
}