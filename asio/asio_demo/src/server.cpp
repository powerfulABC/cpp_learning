#include "server.h"
#include "session.h"
#include <iostream>

Server::Server(boost::asio::io_context &ioc, short port)
    : ioc_(ioc), acceptor_(ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), port_(port)
{
}

void Server::Start()
{
    std::shared_ptr<Session> new_session = std::make_shared<Session>(ioc_, this);
    acceptor_.async_accept(
        new_session->socket(),
        std::bind(&Server::HandleAccept, this, std::placeholders::_1, new_session)
    );
}

void Server::ClearSession(const std::string &session_id)
{
    sessions_.erase(session_id);
}

void Server::HandleAccept(boost::system::error_code &ec, std::shared_ptr<Session> session)
{
    if (!ec)
    {
        session->Start();
        sessions_.insert({session->uuid(), session});
    }
    else{
        log_error_message(ec, "Server accept listenning..");
    }
}
