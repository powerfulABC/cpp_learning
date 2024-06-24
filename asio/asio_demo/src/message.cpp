#include "message.h"
#include <cstring>
#include <boost/asio.hpp>

Message::Message(short max_length)
    :max_length_(max_length), cur_length_(0)
{
    data_ = new char[max_length_ + 1];
    ::memset(data_, 0, max_length + 1);
}

Message::~Message()
{
    delete[] data_;
}

void Message::Clear()
{
    ::memset(data_, 0, max_length_ + 1);
    cur_length_ = 0;
}

SendMessage::SendMessage(const char *message, short length, short message_id)
    : Message(length + HEADER_LENGTH), message_id_(message_id)
{
    short message_id_net = boost::asio::detail::socket_ops::host_to_network_short(message_id_);
    short length_net = boost::asio::detail::socket_ops::host_to_network_short(max_length_);

    // fill message id
    ::memcpy(data_, &message_id_, MESSAGE_ID_LENGTH);
    // fill data size 
    ::memcpy(data_ + MESSAGE_ID_LENGTH, &length_net, MESSAGE_SIZE_LENGTH);
    // fill data
    ::memcpy(data_ + HEADER_LENGTH, message, max_length_);
}

RecvMessage::RecvMessage(short length, short message_id)
    : Message(length), message_id_(message_id)
{
}

LogicNode::LogicNode(std::shared_ptr<Session> session, std::shared_ptr<RecvMessage> recv_message)
    : session_(session), recv_message_(recv_message)
{
}
