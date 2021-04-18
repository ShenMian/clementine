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

	template <typename T>
	void write(std::shared_ptr<Connection> conn, const Message<T>& msg);

	template <typename T>
	void read(std::shared_ptr<Connection> conn);

	std::function<bool(std::shared_ptr<Connection>)> onConnect    = nullptr;
	std::function<void(std::shared_ptr<Connection>)> onDisconnect = nullptr;
	std::function<void(std::shared_ptr<Connection>)> onMessage    = nullptr;

private:
	void acceptAsync();

	asio::io_context        context;
	asio::ip::tcp::socket   socket;
	asio::ip::tcp::acceptor acceptor;
	std::thread             thread;

	std::vector<std::shared_ptr<Connection>> connections;
};

template <typename T>
void Server::write(std::shared_ptr<Connection> conn, const Message<T>& msg)
{
	assert(conn);

	if(!conn->isConnected())
	{
		if(onDisconnect)
			onDisconnect(conn);
		connections.erase(std::find(connections.begin(), connections.end(), conn));
	}

	conn->write<T>(msg);
}

template <typename T>
void Server::read(std::shared_ptr<Connection> conn)
{
	assert(conn);

	if(!conn->isConnected())
	{
		if(onDisconnect)
			onDisconnect(conn);
		connections.erase(std::find(connections.begin(), connections.end(), conn));
	}

	conn->read<T>();
}
