#include <iostream>
#include <string>
using namespace std;

/**
 * Public inheritance => "is-a" relation
 * 
 * A Derived class should be able to do everything the base class can do.
 */

class bird
{
};

class flyablebird : public bird
{
public:
    void fly();
};

class penguin : public bird {};

class dog
{
public:
    // void bark() { cout << "I am just a dog." << endl;}
    void bark(int age) { std::cout << "I am " << age << " years old" << std::endl;}
    virtual void bark(string msg="just a")
    {
        std::cout << "Whoof, I am " << msg << " dog." << std::endl;
    }
};

class yellowdog : public dog
{
public:
    // void bark() { cout << "I am a yellow dog." << endl; }
    using dog::bark;
    virtual void bark(string msg="a yellow")
    {
        std::cout << "Whoof, I am " << msg << " dog." << std::endl;
    }
};

int main()
{
    yellowdog* py = new yellowdog();
    py->bark(5);
    dog* pd = py;
    // the default parameter is bound at compile time
    // so when virtual function called
    // it will invoke the virtual function of yellow dog but
    // use the default parameter of dog
    // so the output is:
    //     Whoof, I am a yellow dog.
    //     Whoof, I am just a dog.
    // never override the default value for virtual function
    pd->bark();
    
    delete pd;
    return 0;
}

/**
 * Summary:
 * 1. Precise definition of classes;
 * 2. Don't override non-virtual functions;
 * 3. Don't override default parameter values for virtual function;
 * 4. Force inheritance of shadowed functions.
 */
