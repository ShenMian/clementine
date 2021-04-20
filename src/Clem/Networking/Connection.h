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

	/**
	 * @brief 与指定主机建立连接.
	 * 
	 * @param host   主机, IP 或 Domain.
	 * @param port   端口号.
	 * @return true  连接成功
	 * @return false 连接失败
	 */
	bool connect(const std::string_view& host, std::uint16_t port);

	/**
	 * @brief 断开已建立的连接.
	 */
	void disconnect();

	/**
	 * @brief 判断是否已建立连接.
	 * 
	 * @return true  连接已建立.
	 * @return false 连接未建立.
	 */
	bool isConnected() const;

	template <typename T>
	void write(const Message<T>& msg);

	template <typename T>
	void read();

	template <typename T>
	const Message<T>& getMessage();

	std::function<void()> onConnect = nullptr;
	std::function<void()> onMessage = nullptr;

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
	asio::async_write(socket, asio::buffer(&msg.header, sizeof(msg.header)),
										[this](std::error_code ec, size_t size) {
											assert(!ec);
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
	async_read(socket, asio::buffer(&((Message<T>*)buffer)->header, sizeof(Message<T>::header)),
						 [this](std::error_code ec, size_t size) {
							 assert(!ec);
							 if(((Message<T>*)buffer)->header.size == 0)
							 {
								 if(onMessage)
									 onMessage();
								 return;
							 }
							 readBody<T>();
						 });
}

template <typename T>
void Connection::readBody()
{
	async_read(socket, asio::buffer(&((Message<T>*)buffer)->body.data(), ((Message<T>*)buffer)->header.size),
						 [this](std::error_code ec, size_t size) {
							 assert(!ec);
							 readHeader<T>();
							 if(onMessage)
								 onMessage();
						 });
}

template <typename T>
const Message<T>& Connection::getMessage()
{
	return *(Message<T>*)buffer;
}
