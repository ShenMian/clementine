// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Platform.h"
#include "Connection.h"
#include "asio.hpp"
#include <cstdint>
#include <string>

/**
 * @addtogroup Networking
 * @{
 */

/**
 * @brief 网络客户端, TCP 协议.
 */
class Client
{
public:
	Client();
	virtual ~Client();

	bool connect(const std::string_view& host, std::uint16_t port);
	void disconnect();

	bool isConnected() const;

	template <typename T>
	void write(const Message<T>& msg)
	{
		connection.write(msg);
	}

private:
	asio::io_context context;
	Connection       connection;
	std::thread      thread;
};

/**
 * end of Networking group
 * @}
 */
