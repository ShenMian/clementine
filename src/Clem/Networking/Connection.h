// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "asio.hpp"

class Connection
{
public:
	Connection(asio::io_context&, asio::ip::tcp::socket);
	virtual ~Connection();

	bool connect(const asio::ip::tcp::endpoint& endpoint);
	void disconnect();

	bool isConnected() const;

	void write();
	void read();

private:
	asio::ip::tcp::socket socket;
	asio::io_context&     context;
};
