#include <iostream>

/**
 * C++ Keyword: using
 * 1. using directive: to bring all namespace members into current scope.
 *    Example:
 */
using namespace std; // case 1, global scope

/* 2. using declaration
 *    a. Bring one specific namespace member to current scope.
 *    b. Bring a member from base class to current class's scope.
 *    Example:
 */
using std::cout; // case 2.a, global scope
void func()
{
    cout << "Hello world.\n";
}

class B
{
public:
    void f(int a) {}
};

class D : private B
{
public:
    void g()
    {
        using namespace std; // case 1, local scope
        cout << "From D: \n";
    }
    void h()
    {
        using std::cout; // case 2.a, local scope
        cout << "From D: \n";
    }
    using B::f; // case 2.b, class scope
    // using std::cout; // illegal
    // using namespace std; // illegal
};

// using B::f; // illegal

class DD : public B
{
public:
    using B::f; // without this, code will not compile
    void f() {}
};

/*
 * Anonymous Namespace
 */
void g() { std::cout << "out namespace" << std::endl; }
namespace
{
    // access in same file
    void g() { std::cout << "in namespace" << std::endl; }
    void h() { std::cout << "h()" << std::endl; g(); }
}

int main()
{
    DD d;
    d.f(8);
    h();
    return 0;
}
