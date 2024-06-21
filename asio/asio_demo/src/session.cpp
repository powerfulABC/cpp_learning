#include "session.h"
#include "server.h"
#include "message.h"
#include "const.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <cstring>

Session::Session(boost::asio::io_context &ioc, Server *server)
    : ioc_(ioc), server_(server)
{
    uuid_ = boost::uuids::to_string(boost::uuids::random_generator()());
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

void Session::HandleReadHeader(boost::system::error_code &ec, std::size_t bytes_transferred, std::shared_ptr<Session> self_shared)
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

        recv_message_ = std::make_shared<RecvMessage>(message_size_host, message_id_host);
        boost::asio::async_read(
            socket_,
            boost::asio::buffer(recv_message_->data_, message_size_host),
            std::bind(&Session::HandleReadData, this, std::placeholders::_1, std::placeholders::_2, self_shared)
        );
    }
    else{
        log_error_message(ec, "session " + uuid() + ": reading message header.");
        server_->ClearSession(uuid());
    }
}

void Session::HandleReadData(boost::system::error_code &ec, std::size_t bytes_transferred, std::shared_ptr<Session> self_shared)
{
    if (ec)
    {
        log_error_message(ec, "session " + uuid() + ": reading message.");
        server_->ClearSession(uuid());
        return;
    }

    if (bytes_transferred < recv_message_->max_length_)
    {
        log_error_message("session " + uuid() + ": wrong data length. received header length: " + std::to_string(bytes_transferred) + ". expected data length: " + std::to_string(recv_message_->max_length_));
        server_->ClearSession(uuid());
        return;
    }

    recv_message_->data_[recv_message_->max_length_] = '\0';

    recv_header_->Clear();
    boost::asio::async_read(
        socket_,
        boost::asio::buffer(recv_header_->data_, HEADER_LENGTH),
        std::bind(&Session::HandleReadHeader, this, std::placeholders::_1, std::placeholders::_2, shared_from_this())
    );
    
}
