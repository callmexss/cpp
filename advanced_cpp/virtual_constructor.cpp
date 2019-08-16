#include <iostream>
using namespace std;

class Dog
{
public:
    virtual Dog* clone() { return (new Dog(*this)); } // co-variant return type
};

class Yellowdog: public Dog
{
    virtual Yellowdog* clone() { return (new Yellowdog(*this)); }
};

void foo(Dog* d) // d is a Yellowdog
{
    // Dog* c = new Dog(*d); // while c is a Dog
    Dog* c = d->clone();
    // ...
    // play with dog c
    delete c;
}

int main()
{
    Yellowdog d;
    foo(&d);
    
    return 0;
}
