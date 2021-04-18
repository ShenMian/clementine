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
							 readBody<T>();
						 });
}

template <typename T>
void Connection::readBody()
{
	async_read(socket, asio::buffer(&((Message<T>*)buffer)->header, ((Message<T>*)buffer)->header.size),
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
