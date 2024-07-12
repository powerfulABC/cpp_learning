#include <iostream>
#include <typeinfo>
void func()
{

}

class Base { 
public:
	virtual void func1(){}
};

class Derived : public Base{
public:
	void func1() {}
	void func2(){}
};


class Base1 {
public:
	void func1(){}
};

class Derived1 : public Base1
{
	void func1() {}
	void func2() {}
};

int main()
{
	// 获取值类型的基本信息 : int
	int a = 10;
	const std::type_info& a_info = typeid(a);
	std::cout << a_info.name() << std::endl;

	// 获取类类型的基本信息 : class Derived
	Derived derived;
	const std::type_info& derived_info = typeid(derived);
	std::cout << derived_info.name() << std::endl;

	// 获取值类型指针的基本信息 : int * __ptr64
	int* b = new int(10);
	const std::type_info& b_info = typeid(b);
	std::cout << b_info.name() << std::endl;

	// 获取类类型指针的基本信息 : class Derived * __ptr64
	Derived* derivedptr = new Derived;
	const std::type_info& derivedptr_info = typeid(derivedptr);
	std::cout << derivedptr_info.name() << std::endl;

	// 获取全局函数的基本信息 : void __cdecl(void)
	const std::type_info& func_info = typeid(func);
	std::cout << func_info.name() << std::endl;

	// 基类指针指向派生类对象
	// 未使用虚函数的结果: class Base1
	Base1* base1ptr = new Derived1;
	const std::type_info& base1ptr_info = typeid(*base1ptr);
	std::cout << base1ptr_info.name() << std::endl;

	// 基类指针指向派生类对象
	// 使用虚函数的结果: class Derived
	Base* baseptr = new Derived;
	const std::type_info& baseptr_info = typeid(*baseptr);
	std::cout << baseptr_info.name() << std::endl;
}