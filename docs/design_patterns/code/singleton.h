#ifndef SINGLETON_H_
#define SINGLETON_H_

/*
 * 描述: 单例模板类
 * 创建时间: 2024/06/20
*/

// 1、返回对象引用
// 依据: c++11之后内部静态变量是线程安全的

template<class T>
class Singleton{
protected:
    Singleton() = default;
    Singleton(const Singleton<T>&) = delete;
    Singleton<T>& operator = (const Singleton<T>&) = delete;

public:
    static T& instance(){
        static T inst;
        return inst;
    }
};


// 2、 返回对象指针
// 使用智能指针管理对象生命周期
#include <memory>
#include <mutex>

template<class T>
class Singleton{
protected:
    std::shared_ptr<T> instance_;
    std::mutex mutex_;

protected:
    Singleton() = default;
    Singleton(const Singleton<T>&) = delete;
    Singleton<T>& operator = (const Singleton<T>&) = delete;
    ~Singleton() = default;

    class SingletonDeleter{
    public:
        void operator()(T* ptr)
        {
            delete ptr;
        }
    };

public:
    std::shared_ptr<T> instance()
    {
        // 实例已经被初始化，直接返回实例
        if (instance_ != nullptr)
        {
            return _instance;
        }

        // 实例还没有被初始化
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (instance == nullptr)
            {
                _instance = new std::shared_ptr<T>(T, SingletonDeleter());
            }
        }

        return _instance;
    }
};

#endif