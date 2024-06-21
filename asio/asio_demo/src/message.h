#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "const.h"
#include "session.h"

class Message{
    friend class Session;
public:
    Message(short max_length);
    virtual ~Message();
    void Clear();

protected:
    short cur_length_;
    short max_length_;
    char* data_;
};

class SendMessage : public Message{
public:
    SendMessage(char* message, short length, short message_id);
    ~SendMessage() = default;

private:
    short message_id_;
};

class RecvMessage : public Message{
public:
    RecvMessage(short length, short message_id);
    ~RecvMessage() = default;

private:
    short message_id_;
};


class LogicNode{
public:
    LogicNode(std::shared_ptr<Session>, std::shared_ptr<RecvMessage>);
    ~LogicNode() = default;
    
private:
    std::shared_ptr<RecvMessage> recv_message_;
    std::shared_ptr<Session> session_;
};

#endif