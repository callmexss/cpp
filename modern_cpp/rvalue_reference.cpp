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

void foo(XuVector v, bool print=false)
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

Dog& createDogByRef()
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
    foo(reusable, true);

    foo(createXuVector(n), true);

    return 0;
}
