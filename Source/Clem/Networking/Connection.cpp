// Copyright 2021 SMS
// License(Apache-2.0)

#include "Connection.h"

using namespace asio;

namespace clem
{

Connection::Connection(io_context& c, ip::tcp::socket s)
    : context(c), socket(std::move(s))
{
}

Connection::~Connection()
{
    disconnect();
}

bool Connection::connect(const std::string_view& host, uint16_t port)
{
    try
    {
        ip::tcp::resolver resolver(context);
        auto              endpoints = resolver.resolve(std::string(host), std::to_string(port));

        async_connect(socket, endpoints, [this](std::error_code ec, ip::tcp::endpoint)
                      {
                          if(ec)
                          {
                              CLEM_LOG_ERROR("networking", ec.message());
                              if(onError)
                                  onError(ec);
                              return;
                          }

                          if(onConnected)
                              onConnected();
                      });
    }
    catch(std::exception& e)
    {
        CLEM_LOG_ERROR("networking", e.what());
        return false;
    }
    return true;
}

void Connection::disconnect()
{
    if(!socket.is_open())
        return;

    if(onDisconnect)
        onDisconnect();
    post(context, [this]()
         { socket.close(); });
}

bool Connection::isConnected() const
{
    return socket.is_open();
}

} // namespace clem