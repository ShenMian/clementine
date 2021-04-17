// Copyright 2021 SMS
// License(Apache-2.0)

#include "Network.h"
#include "asio.hpp"
#include <thread>

static asio::io_context context;
static std::thread      thread;

void Network::init()
{
	thread = std::thread([]() { context.run(); });

	asio::error_code        ec;
	asio::io_context        context;
	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("59.36.232.4", ec), 80);
	asio::ip::tcp::socket   socket(context);
	socket.connect(endpoint, ec);
	//assert(!ec && socket.is_open());
}

void Network::deinit()
{
	assert(!context.stopped() && thread.joinable());

	context.stop();
	if(thread.joinable())
		thread.join();
}
