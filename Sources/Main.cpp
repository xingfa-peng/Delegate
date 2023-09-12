#include "Action.h"
#include <iostream>
using namespace std;

using namespace Inking;

#define ACTION0() printf("() : %s\n", __FUNCSIG__);

void Action0()
{
    ACTION0();
}

#define ACTION3(param0, param1, param2) \
{ \
    param0++; \
    printf("param0 = [%d], param1 = [%s], param2 = [%s] : %s \n", param0, param1.c_str(), param2, __FUNCSIG__); \
}

void Action3(int& param0, const std::string& param1, const char* param2)
{
    ACTION3(param0, param1, param2);
}

class MyClass
{
public:
    void Action0()
    {
        ACTION0();
    }

    void Action3(int& param0, const std::string& param1, const char* param2)
    {
        ACTION3(param0, param1, param2);
    }
};

class MyClass2
{
public:
    MyClass2()
    {
        printf("%s\n", __FUNCSIG__);
    }
    
    MyClass2(const MyClass2& myClass2)
    {
        printf("%s\n", __FUNCSIG__);
    }
   
    ~MyClass2()
    {
        printf("%s\n", __FUNCSIG__);
    }
};
void Test_Action0()
{
    MyClass test;

    Action<> action0;

    // global function
    action0 += Action0;

    // class member function
    action0 += { &test, & MyClass::Action0 };

    // lambda
    auto lambda0 = []()
    {
        ACTION0();
    };

    action0 += lambda0;

    // invoke
    if (action0)
        action0();

    // remove methods
    action0 -= lambda0;
    action0 -= { &test, & MyClass::Action0 };
    action0 -= Action0;
}

void Test_Action3()
{
    MyClass test;
    // Action<int param0, const std::string& param1, const char* param2>
    Action<int&, std::string, char*> action3;

    // global function
    action3 += Action3;

    // class member function
    action3 += { &test, & MyClass::Action3 };

    auto lambda3 = [](int& param0, const std::string& param1, const char* param2)
    {
        ACTION3(param0, param1, param2);
    };
    // lambda
    action3 += lambda3;

    int param0 = 0;
    if (action3)
    {
        action3(param0, "param1", "param2");
    }

    // remove lambda
    action3 -= lambda3;
    if (action3)
    {
        action3(param0, "param1", "param2");
    }

    // remove class member function
    action3 -= {&test, & MyClass::Action3};

    if (action3)
    {
        action3(param0, "param1", "param2");
    }

}

void Test_Delegate0()
{
    MyClass2 myClass2;

    Delegate<const MyClass2&> onDelegate;

    onDelegate += [&myClass2]()->const MyClass2&
    {
        return myClass2;
    };

    if (onDelegate)
    {
        onDelegate();
    }
}
void Test_Delegate1()
{
    MyClass2 myClass2;

    Delegate<MyClass2> onDelegate;

    onDelegate += [&myClass2]()
    {
        return myClass2;
    };

    if (onDelegate)
    {
        onDelegate();
    }
}
void Test_Delegate3()
{
    Delegate<int, int, int> onDelegate;

    onDelegate += [](int a, int b)
    {
        return a + b;
    };

    if (onDelegate)
    {
        printf("%s = %d\n", __FUNCSIG__, onDelegate(2, 3));
    }
}

int main()
{
    printf("---------------------------\n");
    Test_Action0();

    printf("---------------------------\n");
    Test_Action3();

    printf("---------------------------\n");
    Test_Delegate0();
    
    printf("---------------------------\n");
    Test_Delegate1();

    printf("---------------------------\n");
    Test_Delegate3();

    return 0;
}