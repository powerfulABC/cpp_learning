## C++的 Static

### 1、两个基本语义（C语言static的作用）
- 静态存储，在固定的内存分配一次空间，延长变量生命周期
- 可见性，static修饰的变量或函数只在文件内部可见

建议： 除了函数和类内部外，不要使用static

### 2、C++ “static”的用法

| | |
|----|----|
|Static free functions |~~Internal linkage~~ deprecated|
|Static global variables | ~~Internal linkage~~ deprecated|
|Static local variables | Persistent storage|
|Static member variables | Shared by all instances|
|Static member function| Shared by all instances, can only access static member variables|


### 静态成员变量
- 静态成员变量的可见性由private等访问控制符决定
- 静态成员变量是属于类的 


### 静态成员函数
- 静态成员函数没有隐藏的this参数，所以静态成员函数只能访问静态成员变量，无法访问非静态成员变量
- 静态成员函数可以通过对象和类名访问

