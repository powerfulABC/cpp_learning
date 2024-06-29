#include "session.h"
#include "server.h"
#include "message.h"
#include "const.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <cstring>
#include "logicsystem.h"

Session::Session(boost::asio::io_context &ioc, Server *server)
    : ioc_(ioc), server_(server), socket_closed_(false), socket_(ioc)
{
    uuid_ = boost::uuids::to_string(boost::uuids::random_generator()());
    log_message("session " + uuid() + " created.");
    recv_header_ = std::make_shared<Message>(HEADER_LENGTH);
}

void Session::Start()
{
    log_message("session " + uuid() + " started.");
    boost::asio::async_read(
        socket_,
        boost::asio::buffer(recv_header_->data_, HEADER_LENGTH),
        std::bind(&Session::HandleReadHeader, this, std::placeholders::_1, std::placeholders::_2, shared_from_this())
    );
}

void Session::Send(const std::string &message, short message_id)
{
    Send(message.c_str(), message.size(), message_id);
}

void Session::Send(const char *message, short length, short message_id)
{
    std::lock_guard<std::mutex> lock(send_mutex_);
    int send_message_queue_size = send_message_queue_.size();

    // 发送队列已满
    if (send_message_queue_size > MAX_SEND_QUEUE_SIZE)
    {
        log_message("session " + uuid() + ": send queue is full.");
        return;
    }

    send_message_queue_.push(std::make_shared<SendMessage>(message, length, message_id));

    // 还有未发送完的消息，入队后结束
    if (send_message_queue_size > 0)
    {
        return;
    }
    
    std::shared_ptr<SendMessage> msg = send_message_queue_.front();
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(msg->data_, msg->max_length_),
        std::bind(&Session::HandleWrite, this, std::placeholders::_1, shared_from_this())
    );
}

void Session::Close()
{
    socket_.close();
    socket_closed_ = true;
}

void Session::HandleReadHeader(const boost::system::error_code &ec, size_t bytes_transferred, std::shared_ptr<Session> self_shared)
{
    if (!ec)
    {
        if (bytes_transferred < HEADER_LENGTH)
        {
            log_error_message("session " + uuid() + ": wrong header length. received header length: " + std::to_string(bytes_transferred) + ". expected header length: " + std::to_string(HEADER_LENGTH));
            server_->ClearSession(uuid());
        }

        short message_id_net, message_size_net;
        ::memcpy(&message_id_net, recv_header_->data_, MESSAGE_ID_LENGTH);
        ::memcpy(&message_size_net, recv_header_->data_ + MESSAGE_ID_LENGTH, MESSAGE_SIZE_LENGTH);
        short message_id_host = boost::asio::detail::socket_ops::network_to_host_short(message_id_net);
        short message_size_host = boost::asio::detail::socket_ops::network_to_host_short(message_size_net);

        log_message("session " + uuid() + " has received message header. message id: [" + std::to_string(message_id_host) + "], message size: [" + std::to_string(message_size_host) + "]");

        recv_message_ = std::make_shared<RecvMessage>(message_size_host, message_id_host);
        boost::asio::async_read(
            socket_,
            boost::asio::buffer(recv_message_->data_, message_size_host),
            std::bind(&Session::HandleReadData, this, std::placeholders::_1, std::placeholders::_2, self_shared)
        );
    }
    else{
        log_error_message(ec, "session " + uuid() + ": reading message header.");
        HandleErrror();
    }
}

void Session::HandleReadData(const boost::system::error_code &ec, size_t bytes_transferred, std::shared_ptr<Session> self_shared)
{
    if (ec)
    {
        log_error_message(ec, "session " + uuid() + ": reading message.");
        HandleErrror();
        return;
    }

    if (bytes_transferred < recv_message_->max_length_)
    {
        log_error_message("session " + uuid() + ": wrong data length. received header length: " + std::to_string(bytes_transferred) + ". expected data length: " + std::to_string(recv_message_->max_length_));
        server_->ClearSession(uuid());
        return;
    }

    recv_message_->data_[recv_message_->max_length_] = '\0';
    
    // 将消息放入logic queue
    log_message("session " + uuid() + " has received message data. message: [" + std::string(recv_message_->data_, recv_message_->max_length_) + "]");
    std::shared_ptr<LogicNode> logic_node = std::make_shared<LogicNode>(shared_from_this(), recv_message_); 
    LogicSystem::instance()->PostMessageToQueue(logic_node);
    
    recv_header_->Clear();
    boost::asio::async_read(
        socket_,
        boost::asio::buffer(recv_header_->data_, HEADER_LENGTH),
        std::bind(&Session::HandleReadHeader, this, std::placeholders::_1, std::placeholders::_2, self_shared)
    );
    
}

void Session::HandleWrite(const boost::system::error_code & ec, std::shared_ptr<Session> self_shared)
{
    if (ec)
    {
        log_error_message(ec, "session " + uuid() + ": reading message.");
        HandleErrror();
        return;
    }

    std::lock_guard<std::mutex> lock(send_mutex_);
    // 队列首端message发送成功，出队
    send_message_queue_.pop();
    
    // 队列中仍有message，继续发送
    if (!send_message_queue_.empty())
    {
        std::shared_ptr<SendMessage> msg = send_message_queue_.front();
        boost::asio::async_write(
            socket_,
            boost::asio::buffer(msg->data_, msg->max_length_),
            std::bind(&Session::HandleWrite, this, std::placeholders::_1, self_shared)
        );
    }
}

void Session::HandleErrror()
{
    server_->ClearSession(uuid());
    Close();
}
