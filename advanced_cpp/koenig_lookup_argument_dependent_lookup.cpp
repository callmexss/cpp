#include <iostream>
using namespace std;

/**
 * Koenig Lookup
 */

// Example 1
namespace A
{
    struct X {};
    void g(X) { std::cout << "calling A::g()" << std::endl; }
}

// will not compile, because there are two g visible in current scope
// void g(x) { std::cout << "calling A::g()" << std::endl; }

// Example 2
class C
{
public:
    struct Y {};
    static void h(Y) { std::cout << "calling C::h()" << std::endl; }
};

// Example 3
// namespace D
class D
{
public:
    void g(A::X) { std::cout << "calling D::g()" << std::endl; }
    void j() { A::X x; g(x); }
};

// Name hiding:
namespace A
{
    // struct X {};
    // void g(X) { std::cout << "calling A::g(X)" << std::endl; }
    void g(int) { std::cout << "calling A::g(int)" << std::endl; }
    namespace C
    {
        void g() { std::cout << "calling C::g()" << std::endl; }
        void j()
        { 
            // using A::g;
            // g(8);
            X x;
            g(x);
         }
    }
}

int main()
{
    A::X x1;
    g(x1); // Koenig Lookup, or Argument Dependent Lookup (ADL)

    C::Y y;
    // h(y); // Koenig Lookup only works for namespace

    D d;
    d.j();
    
    return 0;
}

/*
 * Name Lookup Sequence
 * 
 * With namespaces:
 * current scope => next enclosed scopel=> ... => global scope
 * 
 * To override the sequence:
 * 1. Qualifier or using declaration
 * 2. Koenig lookup
 * 
 * With classes:
 * current class scope => parent scope => ... => global scope
 * 
 * To override the sequence:
 * - Qualifier or using declaration
 * 
 * Name hiding
 */