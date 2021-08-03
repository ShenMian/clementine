// Copyright 2021 SMS
// License(Apache-2.0)

#include "Client.h"

using namespace asio;

namespace clem
{

Client::Client()
    : connection(context, ip::tcp::socket(context))
{
}

Client::~Client()
{
    disconnect();
}

bool Client::connect(const std::string_view& host, uint16_t port)
{
    connection.connect(host, port);
    connection.onConnected  = [this]() { if(onConnected) onConnected(); };
    connection.onDisconnect = [this]() { if(onDisconnect) onDisconnect(); };
    connection.onMessage    = [this]() { if(onMessage) onMessage(); };
    connection.onError      = [this](auto ec) { if(onError) onError(ec); };

    thread = std::thread([this]() { context.run(); });

    return true;
}

void Client::disconnect()
{
    connection.disconnect();
    context.stop();
    if(thread.joinable())
        thread.join();
}

bool Client::isConnected() const
{
    return connection.isConnected();
}

} // namespace clem