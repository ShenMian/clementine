// Copyright 2021 SMS
// License(Apache-2.0)

#include "Client.h"

using namespace asio;

Client::Client()
		: connection(context, ip::tcp::socket(context))
{
}

Client::~Client()
{
	disconnect();
}

bool Client::connect(const std::string_view& host, std::uint16_t port)
{
	try
	{
		connection.connect(host, port);

		thread = std::thread([this]() { context.run(); });
	}
	catch(std::exception&)
	{
		return false;
	}
	return true;
}

void Client::disconnect()
{
	connection.disconnect();
	context.stop();
	if(thread.joinable())
		thread.join();
}

bool Client::isConnected() const
{
	return connection.isConnected();
}