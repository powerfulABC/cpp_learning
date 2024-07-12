// 用函数重载的方法实现多态
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


// 使用函数重载实现多态
void draw(Line* shape)
{
    shape->Draw();
}

void draw(Circle* shape)
{
    shape->Draw();
}

int main()
{
    draw(new Line);     // output: Draw Line.
    draw(new Circle);   // output: Draw Circle.
}