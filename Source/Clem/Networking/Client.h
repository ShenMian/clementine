// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Platform.h"
#include "Connection.h"
#include "asio.hpp"
#include <cstdint>
#include <string>

namespace clem
{

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
	void write(const Message<T>& msg);

	template <typename T>
	void read();

	std::function<void()> onDisconnect;
	std::function<void()> onMessage;

private:
	asio::io_context context;
	Connection       connection;
	std::thread      thread;
};

template <typename T>
void Client::write(const Message<T>& msg)
{
	if(!connection.isConnected())
	{
		if(onDisconnect)
			onDisconnect();
		return;
	}

	connection.write(msg);
}

template <typename T>
void Client::read()
{
	if(!connection.isConnected())
	{
		if(onDisconnect)
			onDisconnect();
		return;
	}

	connection.read<T>();
}

/**
 * end of Networking group
 * @}
 */

} // namespace clem
