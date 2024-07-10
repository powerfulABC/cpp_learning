#include <stdio.h>

// 初始化的全局变量
int count = 10;
// 未初始化的全局变量
int value;
// 初始化为0的全局变量
int var = 0;

// 全局函数
void func(int sum)
{
    printf("sum is %d\n", sum);
}

// 全局函数
int main()
{
    // 初始化的局部静态变量
    static int a = 1;
    // 初始化为0的局部静态变量
    static int b = 0;
    // 局部变量
    int x = 1;
    func(a + b + x);
    return 0;
}