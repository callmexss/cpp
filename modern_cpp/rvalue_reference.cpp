/**
 * Rvalue Reference
 * 
 *      1. Moving Semantics
 *      2. Perfect Forwarding
 * 
 *  Prerequisite: understanding rvalue and lvalue
 */

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

// lvalue reference and rvalue reference can be used to overload function
void printInt(int &i) { cout << "&i: " << i << endl; }
void printInt(int &&i) { cout << "&&i: " << i << endl; }
// void printInt(int i) {} // Uncomment this line to see compile error message

class XuVector
{
public:
    XuVector(int n) : m_size(n)
    {
        m_arr = new double[n]; // if not initialize what will happen?
                               // will be initialize to an array of zeros (g++).
    }

    ~XuVector()
    {
        delete[] m_arr;
    }

    XuVector(const XuVector &rhs) // Copy constructor
    {
        cout << "Copy Constructor" << endl;
        m_size = rhs.m_size;
        m_arr = new double[m_size];
        for (int i = 0; i < m_size; ++i)
        {
            m_arr[i] = rhs.m_arr[i];
        }
    }

    XuVector(XuVector &&rhs) // Move constructor
    {
        cout << "Move Constructor" << endl;
        m_size = rhs.m_size;
        m_arr = rhs.m_arr;
        rhs.m_arr = nullptr;
    }

    int size() { return m_size; }

    // double operator[](const int& i) // without `&` this method will be readonly
    double &operator[](const int &i)
    {
        assert(i < m_size);
        return m_arr[i]; // return a lvalue reference
    }

private:
    int m_size;
    double *m_arr; // a big array
};

void foo(XuVector v, bool print = false)
{
    if (print)
    {
        for (int i = 0; i < v.size(); ++i)
        {
            cout << v[i] << " ";
        }
        cout << endl;
    }
}

void fooByRef(XuVector &v, bool print = false)
{
    if (print)
    {
        for (int i = 0; i < v.size(); ++i)
        {
            cout << v[i] << " ";
        }
        cout << endl;
    }
}

XuVector createXuVector(int size) // create a XuVector
{
    XuVector v(size);
    srand(time(NULL));
    for (int i = 0; i < v.size(); ++i)
    {
        v[i] = rand() % 100;
    }
    cout << "inner address: " << &v << endl;
    return v;
}

class Dog
{
public:
    Dog() {}
    ~Dog() {}
};

Dog createDog()
{
    Dog d;
    cout << "inner address: " << &d << endl;
    return d;
}

Dog &createDogByRef()
{
    Dog d;
    cout << "inner address: " << &d << endl;
    return d;
}

int main(int argc, char const *argv[])
{
    // What is rvalue reference
    int a = 5;   // a is a lvalue
    int &b = a;  // b is a lvalue reference
    int &&c = 5; // c is a rvalue reference

    printInt(a); // call printInt(int &);
    printInt(c); // call printInt(int &); Why ?
    printInt(5); // call printInt(int &&);

    int n = 10;
    XuVector v = createXuVector(n);
    cout << "outer address: " << &v << endl;
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;

    cout << "---------------Dog----------------" << endl;
    Dog d = createDog();
    cout << "outer address: " << &d << endl;
    Dog d2 = createDogByRef();
    cout << "outer address: " << &d2 << endl;
    cout << "-------------End  Dog-------------" << endl;

    XuVector reusable = createXuVector(n);
    cout << "outer address: " << &reusable << endl;
    fooByRef(reusable, true);       // call no constructor
    foo(reusable, true);            // call copy constructor
    foo(std::move(reusable), true); // call move constructor. reusable.m_arr == nullptr;
    // reusable is distroyed here

    foo(createXuVector(n), true);

    return 0;
}

/**
 * Note 1：the most useful place for rvalue reference is ouerloading copy 
 * constructor and copy assignment operator, to achieve move semantics.
 */
class X
{
public:
    X &X::operator=(X const &rhs);
    X &X::operator=(X &&rhs);
};

/**
 *  Note 2: Move semantics is implemented for all STL containers, which means:
 *      a. Move to C++ 11, Your code will be faster without changing a thing.
 *      b. Passing-By-Value can be used for STL containers.
 */

vector<int> foo()
{
    vector<int> myvector;
    //…
    return myvector;
}

void hoo(string s);

bool goo(vector<int> &arg); //Pass by reference if you use arg to carry
                            //data back from goo（）

/* Move Constructor / Move Assignment Operator:
 * Purpose: conveniently auoid costly and unnecessary deep copying.
 * 
 * 1. They are particularly powerful where passing by reference and
 *    passing by ualue are both used.
 * 
 * 2. They give you finer control of which part of your object to
 *    be moved.
 */