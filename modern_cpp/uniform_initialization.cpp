#include <string>
#include <iostream>
#include <initializer_list>

using namespace std;

/**
 * 2. Uniform Initialization
 */

/**
 * C++ 03
 */
class Dog03 // Aggregate class or struct
{
public:
    int age;
    string name;
};

Dog03 d1 = {5, "Henry"}; // Aggregate initialization

/**
 * C++ 11
 * extend the scope of curly brace initialization
 */
class Dog11
{
public:
    Dog11(int age, string name) {}
};

Dog11 d2 = {5, "Henry"};

/* Uniform Initialization Search Order:
 * 1.Initializer list constructor
 * 2.Regular constructor that takes the appropriete parameters.
 * 3.Aggregate initializer.
 */

class Dog11New
{
public:
    int age; // 3rd choice

    Dog11New(int age) { cout << "2nd choice" << endl; } // 2nd choice

    Dog11New(const initializer_list<int> &vec) // 1st choice
    {
        cout << "1st choice" << endl;
        age = *(vec.begin());
    }
};


int main(int argc, char const *argv[])
{
    /* code */
    Dog11New d{3};
    return 0;
}
