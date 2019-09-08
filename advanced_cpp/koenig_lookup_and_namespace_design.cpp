#include <iostream>
using namespace std;

/**
 * Why Koenig lookup?
 */

// Example 1:
namespace A
{
    struct X {};
    void g(X) { std::cout << "calling A::g()" << std::endl; }
}

/**
 * 1. The Practical Reason
 */
void f()
{
    std::cout << "Hi."; // calls std::operator<<
    // std::cout std::<< "Hi.\n"; // calls std::operator<<
    // std::operator<<(std::cout, "Hi.\n");
}

/**
 * 2. Theoretical Reason:
 *     -- What is the interface of a class?
 */ 
namespace A
{
    class C
    {
    public:
        void f() {}
        void g() {}
    };
    void h(C) {}
    // ostream& operator<<(ostream&, const C&);
}

/**
 * Definition of class:
 *     A class describes a set of data, along with the functions that operate
 *     on that data.
 */

/**
 * Engineering Principle:
 * 1. Functions that operate on class C and in a same namespace with C are
 *    part of C's interface.
 * 2. Functions that are part of C's interface should be in the same namespace
 *    as C.
 */

void f2()
{
    A::C c;
    c.f();
    h(c);
}
 

int main()
{
    A::X x1;
    g(x1); // Koenig Lookup, or Argument Dependent Lookup (ADL)
    // g(); // Error
    
    
    return 0;
}
