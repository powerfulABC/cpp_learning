#ifndef SESSION_H_
#define SESSION_H_

#include <boost/asio.hpp>
#include <memory>
#include <queue>
#include <mutex>

class Server;
class Message;
class RecvMessage;
class SendMessage;

class Session : public std::enable_shared_from_this<Session>{
public:
    Session(boost::asio::io_context& ioc, Server *server);
    void Start();
    boost::asio::ip::tcp::socket& socket() { return socket_; }
    const std::string& uuid() { return uuid_; } 
    void Send(const std::string& message, short message_id);
    void Send(const char* message, short length, short message_id);
    void Close();

private:
    void HandleReadHeader(const boost::system::error_code& ec, size_t bytes_transferred, std::shared_ptr<Session>);
    void HandleReadData(const boost::system::error_code& ec, size_t bytes_transferred, std::shared_ptr<Session>);
    void HandleWrite(const boost::system::error_code& ec, std::shared_ptr<Session>);
    void HandleErrror();

private:
    Server *server_;
    boost::asio::io_context& ioc_;
    boost::asio::ip::tcp::socket socket_;
    bool socket_closed_;
    std::string uuid_;
    std::shared_ptr<Message> recv_header_;
    std::shared_ptr<RecvMessage> recv_message_;
    std::queue<std::shared_ptr<SendMessage>> send_message_queue_;
    std::mutex send_mutex_;
};

#endif