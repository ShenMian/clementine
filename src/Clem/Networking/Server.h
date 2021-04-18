// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Platform.h"
#include "Connection.h"
#include "asio.hpp"
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

class Server
{
public:
	Server();
	virtual ~Server();

	bool start(std::uint16_t port);
	void stop();

	void write(std::shared_ptr<Connection> conn);
	void read(std::shared_ptr<Connection> conn);

private:
	void acceptAsync();

	asio::io_context        context;
	asio::ip::tcp::socket   socket;
	asio::ip::tcp::acceptor acceptor;
	std::thread             thread;

	std::function<bool(std::shared_ptr<Connection>)> onConnect    = nullptr;
	std::function<void(std::shared_ptr<Connection>)> onDisconnect = nullptr;
	std::function<void(std::shared_ptr<Connection>)> onMessage    = nullptr;

	std::vector<std::shared_ptr<Connection>> connections;
};
