# 单例模式(Singleton)
单例模式是一种常用的设计模式，主要目的是确保进程运行过程中全局只有一个实例对象。常用于线程池类，Logger类等<br/>
按照实例对象初始化的时机不同，单例模式又可分为懒汉式和饿汉式

## 动机
设计一个具有以下特征的类
- 类内保存一个全局唯一的实例对象
- 提供一个统一接口用来获取类内保存的实例对象，不允许用户去实例化这个类
- 保证实例对象始终全局唯一，不允许拷贝和复制
- 实例的生命周期由类去管理，外部用户只能使用

## 饿汉式
实例对象在程序开始运行时就进行初始化
<br>

```cpp
    class SingletonHungry{
    private:
        static SingletonHungry instance_;

    private:
        SingletonHungry() = default;
        SingletonHungry(const SingletonHungry&) = delete;
        SingletonHungry& operator=(const SingletonHungry&) = delete;
    
    public:
        ~SingletonHungry();
        static SingletonHungry& instance()
        {
            return instance_;
        }
    };

    SingletonHungry SingletonHungry::instance_;
```
即使实例对象没被用到,饿汉式也会在程序启动时初始化实例对象,造成了资源的浪费。

## 懒汉式
实例对象在第一次被用户使用时才被实例化, 经常使用
<br>
### 返回指针的懒汉式
- 线程不安全的单例模式

> 当对象没有被实例化，并且两个线程都同时走到了代码①处，会产生两次初始化

```cpp
    #include <memory>
    class Singleton{
    private:
        std::shared_ptr<Singleton> instance_;

    private:
        Singleton() = default;
        Singleton(const Singleton&) = delete;
        Singleton& operator = (const Singleton&) = delete;

    public:
        ~Singleton() = default;
        std::shared_ptr<Singleton> instance()
        {
            // 实例已经被初始化，直接返回实例
            if (instance_ != nullptr)
            {
                return _instance;
            }
            _instance = std::make_shared<Singleton>();  // ①
            return _instance;
        }
    };
```

- 添加锁保证线程安全

```cpp
    #include <memory>
    #include <mutex>

    class Singleton{
    private:
        std::shared_ptr<Singleton> instance_;
        std::mutex mutex_;

    private:
        Singleton() = default;
        Singleton(const Singleton&) = delete;
        Singleton& operator = (const Singleton&) = delete;

    public:
        ~Singleton() = default;
        std::shared_ptr<Singleton> instance()
        {
            // 实例已经被初始化，直接返回实例
            if (instance_ != nullptr)
            {
                return _instance;
            }

            // 实例还没有被初始化，加锁进行初始化
            {
                std::lock_guard<std::mutex> lock(mutex_);
                if (instance == nullptr)
                {
                    _instance = std::make_shared<Singleton>();
                }
            }

            return _instance;
        }
    };
```

> 依然存在的问题: 析构函数是公有的，意味着用户可以在外部将资源释放,导致程序结束时智能指针二次释放资源，程序崩溃。虽然基本不可能有人这么做，但是仍然不能将这个风险暴露给用户

```cpp
    auto sptr = Singleton::instance();
    delete sptr.get();
```

- 隐藏析构函数，添加自定义析构函数来释放资源

```cpp
    class Singleton{
    private:
        std::shared_ptr<Singleton> instance_;
        std::mutex mutex_;

    private:
        Singleton() = default;
        Singleton(const Singleton&) = delete;
        Singleton& operator = (const Singleton&) = delete;
        
        // 隐藏析构函数
        ~Singleton() = default;

        // 定义仿函数析构资源
        class SingletonDeleter{
        public:
            void operator()(Singleton* ptr)
            {
                delete ptr;
            }
        };

    public:
        std::shared_ptr<Singleton> instance()
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
                    // share_ptr的第二个参数指定自定义析构函数
                    _instance = new std::shared_ptr<Singleton>(Singleton, SingletonDeleter());
                }
            }

            return _instance;
        }
    };
```


### 返回引用的极简饿汉式

c++11之后保证了内部静态变量是线程安全的，基于内部静态变量在第一次使用时才进行初始化的特性，可以设计出不带锁的单例模式类

```cpp
    class Singleton{
    private:
        Singleton() = default;
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

    public:
        static Singleton& instance(){
            static Singleton inst;
            return inst;
        } 
    };
```


## 单例模式模板基类

单例模式是一种通用的设计结构，因此可以设计一个基类，让基类实现单例模式的所有需求，具体的单例类只需要继承基类就可以拥有单例类的所有特性
[单例模板类.cpp](./code/singleton.h)

```cpp
    // 单例基类
    template <class T>
    class Singleton;


    // 具体单例类
    class SingletonSpecific : Singleton<SingletonSpecific> {
    public:
        void do_something();
    };
```

