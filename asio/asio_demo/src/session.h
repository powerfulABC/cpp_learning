#ifndef SESSION_H_
#define SESSION_H_

#include <boost/asio.hpp>
#include <memory>
#include <queue>
class Server;
class Message;

class Session : public std::enable_shared_from_this<Session>{
public:
    Session(boost::asio::io_context& ioc, Server *server);
    void Start();
    boost::asio::ip::tcp::socket& socket() { return socket_; }
    const std::string& uuid() { return uuid_; } 

private:
    void HandleReadHeader(boost::system::error_code& ec, std::size_t bytes_transferred, std::shared_ptr<Session>);
    void HandleReadData(boost::system::error_code& ec, std::size_t bytes_transferred, std::shared_ptr<Session>);

private:
    Server *server_;
    boost::asio::io_context& ioc_;
    boost::asio::ip::tcp::socket socket_;
    std::string uuid_;
    std::shared_ptr<Message> recv_header_;
    std::shared_ptr<RecvMessage> recv_message_;
};

#endif