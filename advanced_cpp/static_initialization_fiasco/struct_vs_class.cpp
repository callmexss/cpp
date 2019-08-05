#include <iostream>
#include <string>

using namespace std;

// Small passive objects that carry public data
// and have no or few basic member functions.
// Data container
struct Person_t
{
    string name;  // public default
    unsigned age;
};

// Bigger active objects that carry private data,
// interfaced through public member functions.
// Complex Data Structure 
class Person
{
    string name_; // private default
    unsigned age_;

public:
    unsigned age() const { return age_; } // getter / accessor
    void set_age(unsigned a) { age_ = a; } // setter / mutator
};

int main()
{
    Person_t PT;
    cout << PT.age << endl;

    Person P;
    // cout << P.age_ << endl; // will not compile
    cout << P.age() << endl;
    P.set_age(3);
    
    return 0;
}

// Summary:
// 1. Use struct for passive objects with public data, use class for active objects with private data.
// 2. Use setter/getter to access class's data
// 3. Avoid making setter/getter if possible