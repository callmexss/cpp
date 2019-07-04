#include <iostream>

using namespace std;
/**
 * 8. Delegating Constructor
 */

class Dog1
{
public:
    Dog1() { cout << "do some common things.\n"; }
    Dog1(int a)
    {
        Dog1();
        cout << "dootherThings(a);" << endl;
    }
};

// c++ 03:
class Dog2
{
    void init() { cout << "do some common things.\n"; }

public:
    Dog2() { init(); }
    Dog2(int a)
    {
        init();
        cout << "dootherThings(a);" << endl;
    }
};

/* Cons：
*  1. Cumbersome code.
*  2. init() could be invoked by other functions.
*/

// C++ 11
class Dog3
{
    int age = 9; // if do this, age will be initialized at any constructor.
    public:
    Dog3() { cout << "do some common things.\n"; }
    Dog3(int a): Dog3()
    {
        cout << "dootherThings(a);" << endl;
    }
};
// Limitation: Dog3() has to be called first.

int main(int argc, char const *argv[])
{
    Dog1 d1(1);
    Dog2 d2(2);
    Dog3 d3(3);
    return 0;
}
