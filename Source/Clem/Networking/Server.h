// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Assert.h"
#include "Clem/Platform.h"
#include "Connection.h"
#include "asio.hpp"
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

namespace clem
{

/**
 * @addtogroup Networking
 * @{
 */

/**
 * @brief 异步网络服务器, TCP 协议.
 */
class Server
{
public:
	Server();
	virtual ~Server();

	/**
	 * @brief 启动服务器并开始监听指定端口.
	 * 
	 * @param port 要监听的端口.
	 * 
	 * @return true  启动成功.
	 * @return false 启动失败.
	 */
	bool start(uint16_t port);

	/**
	 * @brief 停止服务器.
	 */
	void stop();

	/**
	 * @brief 向指定客户端发送消息.
	 */
	template <typename T>
	void write(std::shared_ptr<Connection> conn, const Message<T>& msg);

	/**
	 * @brief 向全部客户端发送消息.
	 */
	template <typename T>
	void write(const Message<T>& msg);

	/**
	 * @brief 持续接收任何消息并转换为特定类型.
	 */
	template <typename T>
	void read(std::shared_ptr<Connection> conn);

	const std::vector<std::shared_ptr<Connection>>& getConnections() const;

	std::function<bool(std::shared_ptr<Connection>)>                  onAccept;
	std::function<void(std::shared_ptr<Connection>)>                  onDisconnect;
	std::function<void(std::shared_ptr<Connection>)>                  onReceived;
	std::function<void(std::shared_ptr<Connection>, std::error_code)> onError;

private:
	void accept();

	asio::io_context        context;
	asio::ip::tcp::socket   socket;
	asio::ip::tcp::acceptor acceptor;
	std::thread             thread;

	std::vector<std::shared_ptr<Connection>> connections;
};

template <typename T>
void Server::write(std::shared_ptr<Connection> conn, const Message<T>& msg)
{
	ASSERT_NOT_NULL(conn, "connection doesn't exist");

	if(!conn->isConnected())
	{
		if(onDisconnect)
			onDisconnect(conn);
		connections.erase(std::find(connections.begin(), connections.end(), conn));
		return;
	}

	conn->write<T>(msg);
}

template <typename T>
void Server::Server::write(const Message<T>& msg)
{
	for(auto& conn : connections)
		write<T>(conn, msg);
}

template <typename T>
void Server::read(std::shared_ptr<Connection> conn)
{
	ASSERT_NOT_NULL(conn, "connection doesn't exist");

	if(!conn->isConnected())
	{
		if(onDisconnect)
			onDisconnect(conn);
		connections.erase(std::find(connections.begin(), connections.end(), conn));
		return;
	}

	conn->read<T>();
}

/**
 * end of Networking group
 * @}
 */

} // namespace clem
