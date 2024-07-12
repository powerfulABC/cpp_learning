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


void draw(Shape* shape)
{
    shape->Draw();
}

int main()
{
    draw(new Line);     // output: Draw Shape.
    draw(new Circle);   // output: Draw Shape.
}