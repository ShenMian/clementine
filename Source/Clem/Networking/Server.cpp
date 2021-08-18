// Copyright 2021 SMS
// License(Apache-2.0)

#include "Server.h"
#include "Connection.h"
#include "Logging/Logging.h"

using namespace asio;

namespace clem
{

Server::Server()
    : socket(context), acceptor(context)
{
}

Server::~Server()
{
    stop();
}

bool Server::start(uint16_t port)
{
    try
    {
        ip::tcp::endpoint endpoint(ip::tcp::v4(), port);
        acceptor.open(endpoint.protocol());
        acceptor.bind(endpoint);
        acceptor.listen();

        accept();

        thread = std::thread([this]()
                             { context.run(); });
    }
    catch(std::exception& e)
    {
        CLEM_LOG_ERROR("networking", e.what());
        return false;
    }

    return true;
}

void Server::stop()
{
    for(auto& conn : connections)
        conn->disconnect();
    context.stop();
    if(thread.joinable())
        thread.join();
}

const std::vector<std::shared_ptr<Connection>>& Server::getConnections() const
{
    return connections;
}

void Server::accept()
{
    acceptor.async_accept([this](std::error_code ec, ip::tcp::socket sock)
                          {
                              if(ec)
                                  abort();

                              auto conn = std::make_shared<Connection>(context, std::move(sock));
                              if(onAccept && onAccept(conn))
                              {
                                  conn->onDisconnect = [this, conn]()
                                  {
                                      if(onDisconnect)
                                          onDisconnect(conn);
                                  };
                                  conn->onMessage = [this, conn]()
                                  {
                                      if(onMessage)
                                          onMessage(conn);
                                  };
                                  conn->onError = [this, conn](auto ec)
                                  {
                                      if(onError)
                                          onError(conn, ec);
                                  };
                                  connections.push_back(conn);
                              }

                              accept();
                          });
}

} // namespace clem