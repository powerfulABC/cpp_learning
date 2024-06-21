#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <memory>
#include <mutex>

template<class T>
class Singleton{
protected:
    static std::shared_ptr<T> instance_;
    static std::mutex mtx_;
protected:
    Singleton() = default;
    ~Singleton() = default;
    Singleton(const Singleton<T>&) = delete;
    Singleton<T>& operator=(const Singleton<T>) = delete;

    class SingletonSafeDeleter{
        void operator()(T* ptr)
        {
            delete ptr;
        }
    };

public:
    static std::shared_ptr<T> instance()
    {
        if (instance_ != nullptr)
        {
            return instance_;
        }

        {
            std::lock_guard<std::mutex> lock(mtx_);
            if (instance_ == nullptr)
            {
                instance_ = std::shared_ptr<T>(new T, SingletonSafeDeleter());
            }
        }
        return instance_;
    }
};

#endif