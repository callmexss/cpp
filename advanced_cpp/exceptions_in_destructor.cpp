/**
 * Prevent Exceptions from Leaving Destructors.
 */

#include <iostream>
#include <string>
#include <exception>

using namespace std;

class MYEXCEPTION: public exception
{
public:
    MYEXCEPTION(){}
};

class dog
{
public:
    string m_name;
    dog(string name)
    {
        m_name = name;
        cout << name << "is born." << endl;
    }

    // ~dog() { cout << m_name << "is distroied.\n" << endl; }
    // ~dog()
    // {
    //     cout << m_name << "is distroied.\n" << endl;
    //     throw 20;
    // }

    /*
     * Solution 1:Destructor swallow the exception.
     */

    ~dog() // for dog use this way
    {
        try
        {
            //Enclose all the exception prone code here
            cout << m_name << "is distroied.\n" << endl;
        }
        catch (MYEXCEPTION e)
        {
            //Catch exception I
        }
        catch(...)
        {
        }
    }

    /**
     * Solution 2:Move the exception-prone code to a different function.
     */
    void prepareToDestr() { throw 20; } // for dog client use this manner

    void bark() {}
};

int main()
{
    try
    {
        dog dog1("Henry");
        dog dog2("Bob");
        // Bob is destroied first, because Henry and Bob are stored at stack.
        // Stack is first in last out
        // throw 20; // exception will be caught after all the local virables
        // have been destroied.
        dog1.bark();
        dog2.bark();
        // If exception is thrown in the destructor,
        // then when the local variables are destroied,
        // there will be two exceptions thrown which
        // c++ do not like multi exceptions pending at the same time.
        // So the program will be crashed.
        dog1.prepareToDestr();
        dog2.prepareToDestr();
    }
    catch (int e)
    {
        cout << e << " is caught" << endl;
    }
}