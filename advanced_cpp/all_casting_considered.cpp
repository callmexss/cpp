#include <iostream>
#include <string>

/**
 * 
 * A11 Castings Considered
 *
 * Type Conversion:
 *     1. Implicit Type Conversion
 *     2. Explicit Type Conversion-Casting
 */

using namespace std;

class dog
{
public:
    dog(string name="Bob") { m_name = name;}
    virtual void bark() { cout << m_name << endl; }

protected:
    string m_name;
};

class yellowdog: public dog {};

/*
 * 1. static cast
 */
void statisCast()
{
    int i = 9;
    float f = static_cast<float>(i); // convert object from one type to another
    dog d1 = static_cast<dog>(string("Bob")); // Type Conversion needs to be defined
    dog* pd = static_cast<dog*>(new yellowdog()); // convert pointer/reference from one type
                                                  // to a related type (down/up cast)
}

/**
 * 2. dynamic_cast
 */
void dynamicCast()
{
    dog* pd = new yellowdog();
    yellowdog* py = dynamic_cast<yellowdog*>(pd);
    // a. It convert pointer/reference from one type to a related type (down cast)
    // b. run-time type check. If succeed, py==pd; if fail, py==0;
    // c. It requires the 2 types to be polymorphic (have virtual function).   
}

/**
 * const_cast
 */
void constCast()
{
    const char* str = "Hello World.";           // only works on pointer/reference
    char* modifiable = const_cast<char*>(str);  // only works on same type
                                                // cast away constness of the object
                                                // being pointed to
}

/**
 * 4. reinterpret_cast
 */
void reinterpretCast()
{
    long p = 51110980;
    dog* dd = reinterpret_cast<dog*>(p); // re-interpret the bits of the object pointed to
                                         // The ultimate cast that can cast one pointer to any other type of pointer
}

/**
 * C-Style Casting
 */
void cstyleCasting()
{
    short a = 2000;
    int i = (int)a; // c-like cast notation
    int j = int(a); // functional notation
    // A mixture of static_cast, const_cast and reinterpret_cast
}

int main(int argc, const char** argv)
{
    statisCast();
    dynamicCast();
    constCast();
    reinterpretCast();
    cstyleCasting();
    return 0;
}