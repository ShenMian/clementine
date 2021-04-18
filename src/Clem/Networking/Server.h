// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Connection.h"
#include "asio.hpp"
#include <cstdint>
#include <memory>
#include <vector>

class Server
{
public:
	Server();
	virtual ~Server();

	bool start(std::uint16_t port);
	void stop();

private:
	void acceptAsync();

	asio::io_context        context;
	asio::ip::tcp::socket   socket;
	asio::ip::tcp::acceptor acceptor;
	std::thread             thread;

	std::vector<std::shared_ptr<Connection>> connections;
};
