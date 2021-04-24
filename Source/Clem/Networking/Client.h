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
 * @brief 异步网络客户端, TCP 协议.
 */
class Client
{
public:
	Client();
	virtual ~Client();

	/**
	 * @brief 启动客户端并与指定主机(服务器)的端口建立连接.
	 * 
	 * @param host 主机, IP 或域名.
	 * @param port 端口号.
	 * 
	 * @return true  启动成功.
	 * @return false 启动失败.
	 */
	bool connect(const std::string_view& host, uint16_t port);

	/**
	 * @brief 断开连接.
	 */
	void disconnect();

	/**
	 * @brief 判断是否已建立连接.
	 * 
	 * @return true  连接已建立.
	 * @return false 连接未建立.
	 */
	bool isConnected() const;

	/**
	 * @brief 发送消息.
	 */
	template <typename T>
	void write(const Message<T>& msg);

	/**
	 * @brief 持续接收任何消息并转换为特定类型.
	 */
	template <typename T>
	void read();

	std::function<void()>                onConnected;
	std::function<void()>                onDisconnect;
	std::function<void()>                onReceived;
	std::function<void(std::error_code)> onError;

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
