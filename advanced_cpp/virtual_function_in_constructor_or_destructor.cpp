/* Calling Virtual Function in Constructor or Destructor */

#include <iostream>

using namespace std;

class Dog
{
public:
    Dog()
    {
        cout << "Dog born." << endl;
        // bark(); // do not invoke virtual functions in constructor or destructor
    }
    virtual void bark() { cout << "I am a just a dog" << endl; }
    void seeCat() { bark(); }
};
class Yellowdog : public Dog
{

public:
    Yellowdog()
    {
        cout << "Yellow dog born." << endl;
    }
    virtual void bark() { cout << "I am a yellow dog" << endl; }
};

int main()
{
    Yellowdog d;
    d.seeCat();
    return 0;
}