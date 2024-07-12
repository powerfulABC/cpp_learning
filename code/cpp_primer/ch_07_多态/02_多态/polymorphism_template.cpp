#include <iostream>

class Shape {
public:
    void Draw() {
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

// 使用函数模板实现多态
template <class T>
void draw(T* t)
{
    t->Draw();
}

int main()
{
    draw(new Line);     // output: Draw Line.
    draw(new Circle);   // output: Draw Circle.
}