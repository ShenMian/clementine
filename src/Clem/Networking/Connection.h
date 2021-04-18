// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Platform.h"
#include "Message.h"
#include "asio.hpp"
#include <functional>

class Connection
{
public:
	Connection(asio::io_context&, asio::ip::tcp::socket);
	virtual ~Connection();

	bool connect(const std::string_view& host, std::uint16_t port);
	void disconnect();

	bool isConnected() const;

	template <typename T>
	void write(const Message<T>& msg)
	{
		asio::async_write(socket, asio::buffer(&msg.header, sizeof(msg.header)), [this](std::error_code ec, size_t size) {
			assert(!ec);
		});
	}

private:
	asio::io_context&     context;
	asio::ip::tcp::socket socket;

	std::function<void(std::error_code, asio::ip::tcp::endpoint)> onConnect;
};
