// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Connection.h"
#include "asio.hpp"
#include <cstdint>
#include <string>

class Client
{
public:
	Client();
	virtual ~Client();

	bool connect(const std::string_view& host, std::uint16_t port);
	void disconnect();

	bool isConnected() const;

private:
	asio::io_context context;
	std::thread      thread;
	Connection       connection;
};
