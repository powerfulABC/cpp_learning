#include <iostream>

// 内置类型要做手动初始化
void test01()
{
    int x = 0;
    const char* text = "A C-style string";

    double d;
    std::cin >> d;
}

class PhoneNumber{
public:
    PhoneNumber(){std::cout << "PhoneNumber()" << std::endl;}
    PhoneNumber(std::string& phonenumber){ m_phoneNumber = phonenumber; std::cout << "PhoneNumber(std::string& phonenumber)" << std::endl;}

    PhoneNumber& operator=(const PhoneNumber& pn)
    {
        this->m_phoneNumber = pn.m_phoneNumber;
        return *this;
    }
private:
    std::string m_phoneNumber;
};

// 类的初始化，初始化列表和赋值
#include <list>
class ABEntry
{
public:
    ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>&phones);

private:
    std::string m_theName;
    std::string m_theAddress;
    std::list<PhoneNumber> m_thePhones;
    int m_numTimeConsulted;
};

ABEntry::ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phones)
{
    m_theName = name;
    m_theAddress = address;
    m_thePhones = phones;
    m_numTimeConsulted = 0;
}

void test02()
{
    std::list<PhoneNumber> phones;
    for (int i = 0; i < 3; ++i)
    {

    }
}

int main()
{
    
}