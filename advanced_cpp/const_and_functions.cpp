#include <string>
#include <iostream>

using namespace std;

// const used with functions
class Dog
{
    int age;
    string name;
public:
    Dog() { age = 3; name="dummy"; }

    // const parameters
    // reference parameter and const reference parameter
    // can also be overloaded
    void setAge(const int& a) { age = a; cout << "const" << endl; /* a++; */ }
    void setAge(int& a) { age = a; cout << "non-const" << endl; } 
    void setAge2(const int a) { age = a; /* a++; */ } // this is useless

    // const return value
    const string& getName() { return name; }
    const string getName2() { return name; } // useless too

    // const function
    // will be invoked when dog is const
    void printDogName() const 
    { 
        cout << name << "const" << endl; 
        // age++; // will not compile
        // getName(); // also will not compile
        // A const function can only call another const function
        // in order to maintain the const correctness
    }

    // const can be used to overload functions 
    // will be invoked when dog is not const
    void printDogName() { cout << getName() << "non-const" << endl; }


};

int main(int argc, char const *argv[])
{
    Dog d;
    int i = 9;
    d.setAge(i);
    cout << i << endl;

    const string &n = d.getName();
    cout << n << endl;

    d.printDogName();

    // d2 can only invoke const functions
    const Dog d2;
    d2.printDogName();

    const int &a = 3;
    d.setAge(a);
    int &b = i;
    d.setAge(b);
    return 0;
}
