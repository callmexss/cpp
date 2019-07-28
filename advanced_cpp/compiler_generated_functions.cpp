/**
 *  C++ Advanced: Session 1
 */
#include <string>
#include <iostream>

using namespace std;

/**
 * 
 * Compiler silently writes 4 functions if they are not explicitly declared:
 * 1. Copy constructor.
 * 2. Copy Assignment Operator.
 * 3. Destructor.
 * 4. Default constructor(only if there is no constructor declared).
 */


class dog {};
/* equivalent to*/
class dog1
{
public:
    dog1(const dog1& rhs) {}; //Member by member initialization 
    dog1& operator=(const dog1& rhs){}; //Member by member copying 
    dog1(){};    // 1. Call base class's default constructor;
                 // 2. Call data member's default constructor.
    ~dog1(){};   // 1. call base class's destructor;
                 // 2. Call data member's destructor.
};

/**
 * Note:
 * 1. They are public and inline.
 * 2. They are generated only if they are needed.
 */

/* Example:
 * 1. Copy Constructor. -no
 * 2. Copy Assignment Operator. -yes
 * 3. Destructor. -no
 * 4. Default Constructor. -no
 */
class dog2
{
public: 
    string m_name;
    dog2(string name="Bob") { m_name = name; cout << name <<"is born." << endl; }
    ~dog2(){ cout << m_name << " is destroyed.\n" << endl; }
};

/* Example 2：*/
class collar
{
public:
    collar(string color) { std::cout << "collar is born.\n"; }
};

class dog3
{
    collar m_collar;
};


int main()
{
    dog2 d1("Henry");
    dog2 d2;
    d2=d1;

    // dog3 d3; // will not be compiler
}