#include <iostream>
using namespace std;

// class Dog{}; // 1, 2, 3, 4, 5, 6

/*
 * C++ 03:
 * 1. default constructor (generated only if no constructor is declared by user)
 * 2. copy constructor (generated only if no 5, 6 declared by user)
 * 3. copy assignment operator (generated only if 5, 6 not declared by user)
 * 4. destructor
 * 
 * C++ 11:
 * 5. move constructor (generated only if 2, 3, 4, 6 not declared by user)
 * 6. move assignment operator (generated only 2, 3, 4, 5 not declared by user)
 */

class Dog
{
    // C++ 03:
    Dog(); // default constructor 
    Dog(const Dog&); //copy constructor 
    Dog& operator=(const Dog&); // copy assignment operator
    ~Dog(); // destructor

    //C++11:
    Dog(Dog&&); // move constructor 
    Dog& operator=(Dog&&); // move assignment operator
};

// 3, 4
class Cat
{
    Cat(const Cat&) {} // copy constructor
};

// 4
// represents a pretty useful case 
// if an object can only be move constructed, can not be copied
// in real life application, things like mutex or socket,
// which should only be moved not copied.
// 
class Duck
{
    Duck(Duck&&) {} // move constructor
};

// 4
class Frog
{
    Frog(Frog&&, int=0) {} // move constructor
    Frog(int = 0) {} // default constructor
    Frog(const Frog&, int=0) {} // copy constructor
};

// 1, 2, 3
class Fish
{
    ~Fish() {}
};

// 1, 2, 3
class Cow
{
    // though deleted, it still can be seen as user defined one
    Cow& operator=(const Cow&) = delete;
};

int main()
{
    return 0;
}
