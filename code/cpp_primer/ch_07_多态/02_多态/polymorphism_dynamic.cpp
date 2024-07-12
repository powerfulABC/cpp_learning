#include <iostream>

class Shape {
public:
    // 添加virtual关键字，调用该函数及子类重新函数将在运行时进行动态绑定
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


// 动态绑定通过虚函数机制实现的多态
void draw(Shape* shape)
{
    shape->Draw();
}

int main()
{
    draw(new Line);     // output: Draw Line.
    draw(new Circle);   // output: Draw Circle.
}