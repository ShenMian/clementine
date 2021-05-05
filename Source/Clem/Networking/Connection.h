// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Logger.h"
#include "Clem/Platform.h"
#include "Message.h"
#include "asio.hpp"
#include <functional>

namespace clem
{
/**
 * @addtogroup Networking
 * @{
 */

/**
 * @brief 网络连接, TCP 协议.
 */
class Connection
{
public:
	Connection(asio::io_context&, asio::ip::tcp::socket);
	virtual ~Connection();

	/**
	 * @brief 与指定主机的端口建立连接.
	 * 异步, 完成后回调 onConnect.
	 *
	 * @param host 主机, IP 或域名.
	 * @param port 端口号.
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

	template <typename T>
	Message<T>& getMessage();

	std::function<void()>                onConnected;
	std::function<void()>                onDisconnect;
	std::function<void()>                onMessage;
	std::function<void(std::error_code)> onError;

private:
	asio::io_context&     context;
	asio::ip::tcp::socket socket;

	void* buffer = nullptr;

	template <typename T>
	void readHeader();

	template <typename T>
	void readBody();
};

template <typename T>
void Connection::write(const Message<T>& msg)
{
	CLEM_ASSERT_TRUE(msg.header.size == msg.body.size(), "");

	asio::async_write(socket, asio::buffer(&msg.header, sizeof(msg.header)),
										[this](std::error_code ec, size_t size) {
											if(ec)
											{
												if(onError)
													onError(ec);
												CLEM_LOG_ERROR("networking", ec.message());
												return;
											}
										});
	asio::async_write(socket, asio::buffer(msg.body.data(), msg.header.size),
										[this](std::error_code ec, size_t size) {
											if(ec)
											{
												if(onError)
													onError(ec);
												CLEM_LOG_ERROR("networking", ec.message());
												return;
											}
										});
}

template <typename T>
void Connection::read()
{
	if(buffer)
		delete buffer;
	buffer = new Message<T>();

	readHeader<T>();
}

template <typename T>
void Connection::readHeader()
{
	Message<T>& msg = *static_cast<Message<T>*>(buffer);
	async_read(socket, asio::buffer(&msg.header, sizeof(Message<T>::header)),
						 [&, this](std::error_code ec, size_t size) {
							 if(ec)
							 {
								 if(onError)
									 onError(ec);
								 CLEM_LOG_ERROR("networking", ec.message());
								 return;
							 }

							 if(msg.header.size == 0)
							 {
								 if(onMessage)
									 onMessage();
								 readHeader<T>();
								 return;
							 }

							 msg.body.resize(msg.header.size);
							 readBody<T>();
						 });
}

template <typename T>
void Connection::readBody()
{
	Message<T>& msg = *static_cast<Message<T>*>(buffer);
	async_read(socket, asio::buffer(msg.body.data(), msg.header.size),
						 [this](std::error_code ec, size_t size) {
							 if(ec)
							 {
								 if(onError)
									 onError(ec);
								 CLEM_LOG_ERROR("networking", ec.message());
								 return;
							 }

							 if(onMessage)
								 onMessage();

							 readHeader<T>();
						 });
}

template <typename T>
Message<T>& Connection::getMessage()
{
	return *(Message<T>*)buffer;
}

/**
 * end of Networking group
 * @}
 */
} // namespace clem
