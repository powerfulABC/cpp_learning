##命名空间

#### 1、双冒号运算符::
域运算符前面什么都不加表示访问全局资源

    int atk = 200;
    void test01()
    {
        int atk = 10;
        std::cout << "local variable atk: " << atk << std::endl;      // 打印局部变量atk， 10
        std::cout << "global variable atk: " << ::atk << std::endl;  // 打印全局变量atk, 200
    }

#### 2、使用命名空间可以访问命名冲突
不同的功能模块，采用命名空间隔离各自的命名，防止命名冲突

    namespace KingGlory{
        void goAttack(){
            std::cout << "attack in KingGlory" << std::endl;
        }
    }

    namespace LOL{
        void goAttack(){
            std::cout << "attack in LOL" << std::endl;
        }
    }

    void test02()
    {
        KingGlory::goAttack(); // attack in KingGlory

        LOL::goAttack();       //  attack in LOL
    }

####3、命名空间可以里放变量，函数，结构体，类。。。
    namespace A{
        int m_A = 3;
        void func();
        struct Person{};
        class Animal{};
    };

####4、命名空间必须声明在全局作用域下

声明在局部作用域下会报错

    void test03()
    {
        // namespace B{    // 报错 error: 'namespace' definition is not allowed here

    //  };
    }

####5、命名空间可以嵌套
    namespace TA{
        namespace TB{
            int testVal = 1;
        };
    };

    void test04()
    {
        std::cout << TA::TB::testVal << std::endl;
    }

####6、命名空间是开放的

    namespace A{
        int m_B = 4;
    }

    void test05()
    {
        std::cout << A::m_A << std::endl;
        std::cout << A::m_B << std::endl;
    }

####7、匿名命名空间

    namespace{
        int m_C = 1000; // 相当于static int m_C = 1000
        int m_D = 2000; // 相当于static int m_D = 2000
    }


####8、命名空间的别名

    namespace veryLongName
    {
        int m_E = 1000;
    }


    void test06()
    {
    namespace veryShortName = veryLongName;
    std::cout << veryShortName::m_E << std::endl;
    }

    // int main()
    // {
        //test01();
        //test02();
        //test04();
        //test05();
    //    test06();
    //   return 0;
    //}
