// 静态绑定
// 在编译时期确定函数入口地址
#include <iostream>
#include <string>
#include <cstdio>

// 1、全局函数
void do_logic(){};


// 2、重载函数
void func(){}
void func(int a){}
void func(int a, std::string b){}

// 3、 成员函数
class myclass {
public:
    void do_something(){}
};


// 函数模板
template <class T>
void foo(T val){}

int main()
{

    do_logic();

    func();
    func(100);
    
    foo(1);
    foo("test");

    myclass mc1;
    mc1.do_something();

    myclass *mc2 = new myclass;
    mc2->do_something();
    return 0;
}