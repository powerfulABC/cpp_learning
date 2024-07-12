#include "MessageNode.h"
#include <string>
#include <cstring>

MessageNode::MessageNode(short max_length)
    : max_length_(max_length), 
      cur_length_(0)
{
    data_ = new char[max_length + 1];
    std::memset(data_, 0, max_length_ + 1);
}

void MessageNode::Clear()
{
    std::memset(data_, 0, max_length_ + 1);
    cur_length_ = 0;
}

MessageNode::~MessageNode()
{
    if (data_ != nullptr)
    {
        delete []data_;
        data_ = nullptr;
    }
}

RecvMessageNode::RecvMessageNode(short max_length, short message_id)
    : MessageNode(max_length),
      message_id_(message_id)
{
}

SendMessageNode::SendMessageNode(const char *send_data, int max_length, short message_id)
    : MessageNode(max_length),
      message_id_(message_id)
{
    
}
