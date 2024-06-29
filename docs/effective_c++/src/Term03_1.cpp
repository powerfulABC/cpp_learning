#include <iostream>
#include <cstdio>

// const * 常量指针(被指对象不可变)
// * const 常指针(指向不可变)
void test01()
{
    // 1、定义指针指向常量区的地址，不能用指针进行更改，因为常量区是只读的
    char *greeting1 = "hello world!";   // 警告: ISO C++ forbids converting a string constant to ‘char*’
    //greeting1[0] = 'b';                 // 报错: Segmentation fault

    char greeting[] = "hello world!";
    
    // 2、非const 可以改变内容，和指向
    char *p = greeting;     
    p[0] = 'b';
    printf("%s\n", p);  // hello world!
    p = p + 1;
    printf("%s\n", p);  // ello world!
 
    // 3、常量指针的被指对象不可变更 (const *p代表 *p是只读的)
    const char *p1 = greeting;
    char const *p2 = greeting;
    // p1[0] = 'b';    // 报错: assignment of read-only location ‘* p1’
    // p2[0] = 'c';    // 报错: assignment of read-only location ‘* p2’

    // 4、常指针的指向不可变更(*const p代表 p是只读的)
    char * const p3 = greeting;
    p3[0] = 'd';
    printf("%s\n", p3);  // dello world!
}

#include <vector>
// STL迭代器和const迭代器
// 迭代器: T*
// const迭代器:T const*
void test02()
{
    std::vector<int> vec(10, 0);
    
    // const std::vector<int>::iterator 类似于 int* const 迭代器值不可变
    const std::vector<int>::iterator ite = vec.begin();
    *ite = 1;   // okay, 迭代器所指对象可变
    std::cout << *ite << std::endl;
    // ite++;      // ng: passing ‘const iterator’ as ‘this’ argument discards qualifiers

    // const_iterator类似于 const int*, 迭代器指向的值不可变
    std::vector<int>::const_iterator cite = vec.begin();
    // *cite = 2;   // ng: const_iterator指向的值不可变
                    // assignment of read-only location ‘ite1.__gnu_cxx::__normal_iterator<const int*, std::vector<int> >::operator*()’
    ++cite;         // okay
    std::cout << *cite << std::endl;
}

// const返回常量值，避免意外操作
class Rational{
public:
    Rational():m_value(0){}
    Rational(int value):m_value(value){}
    void setValue(int value){this->m_value = value;}
    double getValue()const{return this->m_value;}
    ~Rational(){}

    friend const Rational operator*(const Rational& lhs, const Rational& rhs)
    {
        return Rational(lhs.m_value * rhs.m_value);
    }

    Rational& operator= (const Rational& rhs){
        if (this == &rhs)
        {

        }
        this->setValue(rhs.m_value);
        return *this;
    };

    friend std::ostream& operator<<(std::ostream& os, const Rational& rhs)
    {
        os << rhs.getValue() ;
        return os;
    }

private:
    double m_value;
};

// 返回const常量值，避免意外操作修改返回值对象
void test03()
{
    // 添加const防止出现与内置类型不一致的行为 (a*b)=3;
    Rational a(1), b(2), c;
    std::cout << (a*b) << std::endl;
    // (a*b) = c; // 拷贝赋值函数返回const对象避免了这种误操作
}

// 成员函数与const
#include <string>
class IndexOutOfBound{
public:
    IndexOutOfBound(std::size_t index):m_badIndex(index){}
    ~IndexOutOfBound(){}
    void diagnostic() const
    {
        std::cerr << "Index: " << m_badIndex << " out of bound!";
    }
private:
    std::size_t m_badIndex;
};

class TextBlock{
public:
    TextBlock(const std::string& text):m_text(text){}
    ~TextBlock(){}

    const char& operator[](std::size_t index) const{
        std::cout << "operator[] const\n";
        if (index < 0 || index >= m_text.size())
        {
            throw IndexOutOfBound(index);
        }
        return m_text[index];
    }

    char& operator[](std::size_t index){
         std::cout << "operator[]\n";
        if (index < 0 || index >= m_text.size())
        {
            throw IndexOutOfBound(index);
        }
        return m_text[index];
    }

private:
    std::string m_text;
};

// 两个函数如果只是常量性不同，可以被重载
void test04()
{
    const TextBlock tb1("123");
    TextBlock tb2("234");
    try{
        std::cout << tb1[0] << std::endl;   // 调用operator[] const
        tb2[0] = 5;                         // 调用operator[]
        std::cout << tb2[0] << std::endl;
        std::cout << tb1[20] << std::endl;
    }
    catch(IndexOutOfBound& e)
    {
        e.diagnostic();
        std::cout << std::endl;
    }
    std::cout << "ok\n";
}


// bitwise constness: 认为不更改对象内的任一个bit，是c++对于常量性(constness)的定义
// bitwise会造成反直觉的例外: 修改对象中指针指向的区域是合法的
class CTextBlock
{
public:
    CTextBlock(char* text, std::size_t size):m_pText(text), m_size(size){}
    
    //成员函数是const的，说明对象的任一bit都不可更改 
    char& operator[](std::size_t index) const {
        if (index < 0 || index >= m_size){
            throw IndexOutOfBound(index);
        }
        return m_pText[index];
    }

    friend std::ostream& operator<<(std::ostream& os, const CTextBlock& rhs)
    {
        os << rhs.m_pText;
        return os;
    }

private:
    char* m_pText;
    std::size_t m_size;
};
void test05()
{
    char p[] = "123";
    CTextBlock cb1(p, 3);
    cb1[0] = '4';           // 调用const成员函数，但修改了成员变量指向的区域
    std::cout << cb1 << std::endl;
}

// logical constness: const成员函数可以修改它所处理的对象内某些bit，但只有客户端侦测不出才可以
// 由于c++在机制上支持bitwise constness， 所以要借助关键字mutable实现logical constness
// mutable释放non-static成员变量的bitwise constness约束
#include <cstring>
class CTextBlock1
{
public:
    CTextBlock1(char* text, std::size_t size, bool sizeIsValid):m_pText(text), m_size(size),m_sizeIsValid(false){}
    
    std::size_t length() const{
        if (!m_sizeIsValid)
        {
            m_size = std::strlen(m_pText);  // 只有m_size是mutable的，才允许在const函数改变m_size
            m_sizeIsValid =true;            // 只有m_sizeIsValid是mutable的，才允许在const函数改变m_sizeIsValid
        }
        return m_size;
    }

    //成员函数是const的，说明对象的任一bit都不可更改 
    char& operator[](std::size_t index) const {
        if (index < 0 || index >= m_size){
            throw IndexOutOfBound(index);
        }
        return m_pText[index];
    }

    friend std::ostream& operator<<(std::ostream& os, const CTextBlock1& rhs)
    {
        os << rhs.m_pText;
        return os;
    }

private:
    char* m_pText;
    mutable std::size_t m_size;
    mutable bool m_sizeIsValid;
};

void test06()
{
    char p[] = "123";
    CTextBlock1 cb1(p, 5, false);
    std::cout << cb1.length() << std::endl;
}


// const和non-const成员函数中避免重复
// const和non-const实现功能一致，可以通过non-const调用const函数减少non-const的代码定义
// non-const函数可能会改变对象,const调用non-const是有风险的
class Text{
public:
    Text(char* text):m_pText(text){}
    const char& operator[](std::size_t index) const
    {
        std::cout << "operator[] const" << std::endl;
        // 边界检查
        // 日志记录
        // 检验数据完整性
        return m_pText[index];
    }

    char& operator[](std::size_t index)
    {
        std::cout << "operator[]" << std::endl;
        // 第一次转型 static_cast<const Text&>(*this)[index]
        // 将*this转为const调用operator[]const

        // 第二次转型 const_cast<char&>(static_cast<const Text&>(*this)[index])
        // 将const char&转为char &

        return const_cast<char&>(static_cast<const Text&>(*this)[index]);
    }
private:
    char *m_pText;
};

void test07()
{
    char p[] = "123";
    Text t(p);
    std::cout << t[0] << std::endl;
}

#include <string>
int main(int argc, const char** argv)
{
    
    if (argc == 2)
    {
        std::string args2(argv[1]);
        if (args2 == "test01")
        {
            test01();
        }
        else if (args2 == "test02")
        {
            test02();
        }
        else if (args2 == "test03")
        {
            test03();
        }
        else if (args2 == "test04")
        {
            test04();
        }
        else if (args2 == "test05")
        {
            test05();
        }
        else if (args2 == "test06")
        {
            test06();
        }
        else if (args2 == "test07")
        {
            test07();
        }
    }
    
    
}