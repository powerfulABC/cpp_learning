#include <iostream>

class Base1 {
public:
	virtual void func1() {}
};

class Base2 {
public:
	virtual void func2(){}
};

class Derived : public Base1, public Base2 {};
class Animal {};
class Dog : public Animal{};

class Test{};
int main()
{

	// 编译期类型转换
	Animal* a = new Animal; 
	Dog* dog = new Dog;

	// d -> a: 转换成功 
	Animal* a_1 = dynamic_cast<Animal*>(dog);
	std::cout << a_1 << std::endl;	// 0x000001C539A11960 

	// a -> d: 编译失败: the operand of a runtime dynamic_cast must have a polymorphic class type
	// Dog* dog_1 = dynamic_cast<Dog*>(a);
	// std::cout << dog_1 << std::endl;


	// 运行期类型转换
	Derived* d = new Derived;
	Base1* b1 = new Base1;
	Base2* b2 = new Base2;

	std::cout << d << std::endl;	// 0x000001E10C994880
	std::cout << b1 << std::endl;	// 0x000001E10C994C40
	std::cout << b2 << std::endl;	// 0x000001E10C994600
	
	// b1 -> b2: 转换失败 
	Base2* b2_1 = dynamic_cast<Base2*>(b1);
	std::cout << b2_1 << std::endl;	// 0x0000000000000000

	// b2 -> b1: 转换失败
	Base1* b1_1 = dynamic_cast<Base1*>(b2);
	std::cout << b1_1 << std::endl;	// 0x0000000000000000

	// b1 -> d: 转换失败
	Derived* d_1 = dynamic_cast<Derived*>(b1);
	std::cout << d_1 << std::endl;	// 0x0000000000000000

	// d -> b1: 转换成功
	Base1* b1_2 = dynamic_cast<Base1*>(d);
	std::cout << b1_2 << std::endl;	// 0x000001E10C994880

	// b2 -> d: 转换失败
	Derived* d_2 = dynamic_cast<Derived*>(b2);
	std::cout << d_2 << std::endl;	// 0x0000000000000000

	// d -> b2: 转换成功
	Base2* b2_2 = dynamic_cast<Base2*>(d);
	std::cout << b2_2 << std::endl;	// 0x000001E10C994888

	// d -> b2 -> b1
	Base1* b1_3 = dynamic_cast<Base1*>(b2_2);
	std::cout << b1_3 << std::endl;	// 0x000001E10C994880

}