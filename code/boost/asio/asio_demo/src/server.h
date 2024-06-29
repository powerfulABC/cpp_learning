#ifndef SERVER_H_
#define SERVER_H_

#include <boost/asio.hpp>
#include <unordered_map>
#include <memory>
#include "const.h"

class Session;

class Server{
public:
    Server() = default;
    Server(boost::asio::io_context& ioc, short port);
    ~Server() = default;
    void Start();
    void ClearSession(const std::string& session_id);

private:
    void HandleAccept(const boost::system::error_code& ec, std::shared_ptr<Session> session);

private:
    boost::asio::io_context& ioc_;
    short port_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::unordered_map<std::string, std::shared_ptr<Session>> sessions_;
};

#endif