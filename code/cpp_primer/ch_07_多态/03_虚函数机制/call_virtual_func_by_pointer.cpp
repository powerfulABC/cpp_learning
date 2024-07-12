#include <iostream>

class Shape {
public:
    virtual void Draw() {
        std::cout << "Draw Shape." << std::endl;
    }
};

class Line : public Shape {
public:
    void Draw() {
        std::cout << "Draw Line." << std::endl;
    }
};

class Circle : public Shape {
public:
    void Draw() {
        std::cout << "Draw Circle." << std::endl;
    }
};


int main()
{
    Shape* shape = new Line;

    // 取出虚函数指针
    // vfptr指向虚函数表，虚函数表又指向函数定义，所以vfptr是二级指针
    // shape指向vfptr，所以shape是三级指针
    void** vfptr = *(void***)shape;

    // vfptr指向虚函数表的首地址，将虚函数表存储的第一个指针重新解释为函数函数
    void(*draw_line_ptr)() = reinterpret_cast<void(*)()>(vfptr[0]);

    // 执行函数
    draw_line_ptr();    // output: Draw Line.
}