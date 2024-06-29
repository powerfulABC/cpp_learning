#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <memory>
#include <mutex>

template<class T>
class Singleton{
protected:
    static std::shared_ptr<T> instance_;

protected:
    Singleton() = default;
    Singleton(const Singleton<T>&) = delete;
    Singleton<T>& operator=(const Singleton<T>) = delete;

public:
    ~Singleton() = default;
    static std::shared_ptr<T> instance()
    {
        std::once_flag created_flag;
        std::call_once(created_flag, [&](){
            instance_ = std::shared_ptr<T>(new T);
        });
        return instance_;
    }
};


template<class T>
std::shared_ptr<T> Singleton<T>::instance_ = nullptr;

#endif