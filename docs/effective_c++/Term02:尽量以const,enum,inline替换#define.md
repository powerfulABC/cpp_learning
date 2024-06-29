# 条款2: 尽量以const,enum,inline替换#define
也叫做使用编译器代替预处理器
- 对于单纯常量，最好使用const或enum代替\#define
- 对于宏函数，最好改用inline代替 \#define

## 2.1、 使用const代替\#define定义常量
2.1.1、优劣对比
||\#define|const|
|:----|:----|:----|
|类型检查|预编译期做文本替换，没有类型检查|定义时需要指定类型，编译期进行类型检查|
|错误追踪|宏替换导致编译错误时，由于宏已经展开，很难定位具体宏名|const常量会被编译器看到，并将其记录到记号表中
|作用域|宏没有作用域概念|const常量跟本地变量一样具有作用域|
||

2.1.2、 使用const替换\#define的特殊情况： 定义常量指针<br>
> 定义常量指针有必要将指针声明为const<br/>表示指针指向不可更改，指针指向对象不可通过该指针更改

        const int char* const authorName = "Scott Meyers";

2.1.3、 使用const替换\#define的特殊情况： class专属常量<br>
> 为了将常量的作用域限制在class内，必须将常量作为成员变量，并且为了保证只有一份常量，他必须时static成员

    // Gameplayer.h
    class Gameplayer{
    private:
        static const int NumTurns = 5; // 常量声明式
        int scores[NumTurns];
    };

    //Gameplayer.cpp
    const int Gameplayer::NumTurns; // 常量定义，声明和定义只能有一个地方給初值


## 2.2、 使用enum hack代替\#define定义常量
> 如果编译器不允许在类内对static const常量进行初始化(2.1.3)，可以改用enum hack。<br/>理论基础: 枚举类型的数值可以被当作int使用

    class Gameplayer{
    private:
        enum{NumTurns = 5}; // enum hack -- 让NumTurn成为5的记号名称
        int scores[NumTurns];
    };

## 2.2、 使用inline函数替换\#define定义宏函数
宏函数可能造成多个语义

    #define CALL_WITH_MAX(a,b) f((a) > (b) > (a) : (b))

    int a = 5, b = 0;
    CALL_WITH_MAX(++a, b);  // a累加一次
    CALL_WITH_MAX(++a, b + 10); // a累加两次 

使用template inline提供函数特性

    template<typename T>
    inline void callWithMax(const T& a, const T& b)
    {
        f(a > b ? a : b);
    }