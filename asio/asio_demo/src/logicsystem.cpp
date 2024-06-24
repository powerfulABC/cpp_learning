#include "logicsystem.h"
#include <json/value.h>
#include <json/json.h>
#include <json/reader.h>
#include "message.h"
#include "session.h"
#include "const.h"

void LogicSystem::PostMessageToQueue(std::shared_ptr<LogicNode> logic_message)
{
    std::unique_lock<std::mutex> lock(logic_mutex_);
    logic_message_queue_.push(logic_message);
    if (logic_message_queue_.size() == 1)
    {
        lock.unlock();
        consume_.notify_one();
    }
}

LogicSystem::LogicSystem()
{
    RegisterCallBackFunction();
    worker = std::thread(&LogicSystem::Run, this);
}

void LogicSystem::RegisterCallBackFunction()
{
    call_back_functions_[MESSAGE_IDS::HELLO_WORLD] = std::bind(
        &LogicSystem::HelloWorldCallBack,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    );
}

void LogicSystem::Run()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(logic_mutex_);
        if (logic_message_queue_.empty())
        {
            consume_.wait(lock);
        }

        auto& logic_node = logic_message_queue_.front();
        auto call_back_function = call_back_functions_.find(logic_node->recv_message_->message_id_);
        if (call_back_function == call_back_functions_.end())
        {
            log_error_message("message id(" + std::to_string(logic_node->recv_message_->message_id_) +") is illeagal." );
            logic_message_queue_.pop();
            continue;
        }

        // 调用message id对应的处理函数
        call_back_function->second(
            logic_node->session_, 
            logic_node->recv_message_->message_id_, 
            std::string(logic_node->recv_message_->data_, logic_node->recv_message_->max_length_)
        );

        // logic node 出队
        logic_message_queue_.pop();
    }
}

void LogicSystem::HelloWorldCallBack(std::shared_ptr<Session> session, const short &message_id, const std::string &message)
{
    Json::Reader json_reader;
    Json::Value root;
    json_reader.parse(message, root);
    log_message("session(" + session->uuid() + ") received: " + root.toStyledString());

    // 回复client
    std::string response = "hello client, this is server.";
    session->Send(response, root["id"].asInt());
}
