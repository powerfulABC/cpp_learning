#ifndef MESSAGENODE_H_
#define MESSAGENODE_H_

#include <string>

class MessageNode{
public:
    MessageNode(short max_length);
    void Clear();
    virtual ~MessageNode();

protected:
    char *data_;
    short max_length_;
    short cur_length_;
};


class RecvMessageNode:public MessageNode{
public:
    RecvMessageNode(short max_length, short message_id);
    ~RecvMessageNode() = default;

private:
    short message_id_;
};


class SendMessageNode : public MessageNode{
public:
    SendMessageNode(const char *send_data, int max_length, short message_id);
    SendMessageNode(const std::string& message, short message_id);
    ~SendMessageNode() = default;
private:
    short message_id_;
};

#endif