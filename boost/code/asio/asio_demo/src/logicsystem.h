#ifndef LOGICSYSTEM_H_
#define LOGICSYSTEM_H_

#include "singleton.h"
#include <queue>
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <functional>
#include <unordered_map>


class LogicNode;
class Session;

typedef std::function<void(std::shared_ptr<Session>, const short&, const std::string&)> CallBackFunc;

class LogicSystem : public Singleton<LogicSystem>
{
    friend class Singleton<LogicSystem>;
public:
    void PostMessageToQueue(std::shared_ptr<LogicNode> logic_message);
    ~LogicSystem() = default;
    
private:
    LogicSystem();
    
    void RegisterCallBackFunction();

    // 运行逻辑处理系统
    void Run();

    // call back functions
    
    // 将接收的数据原样返回 
    void HelloWorldCallBack(std::shared_ptr<Session> session, const short& message_id, const std::string& message);

private:
    std::queue<std::shared_ptr<LogicNode>> logic_message_queue_;
    std::mutex logic_mutex_;
    std::condition_variable consume_;
    std::unordered_map<short, CallBackFunc> call_back_functions_;
    std::thread worker;
};

#endif