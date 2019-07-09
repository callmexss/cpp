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
#include <typeinfo>

using namespace std;

/**
 * Usage 1: Moving Semantics
 */

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

/**
 * Note 1：the most useful place for rvalue reference is ouerloading copy 
 * constructor and copy assignment operator, to achieve move semantics.
 */
class X
{
public:
    X &operator=(X const &rhs);
    X &operator=(X &&rhs);
};

X &X::operator=(X const &rhs) {}
X &X::operator=(X &&rhs) {}

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

/**
 * Usage 2: Perfect Forwarding
 */

// XuVector has both move constructor and copy constructor
void foo_new(XuVector arg) { cout << &arg << endl; }

template <typename T>
void relay1(T arg)
{
    foo_new(arg);
}

/*
 * 1. No costly and unnecessary copy construction of boVector is made;
 * 2. rvalue is forwarded as rvalue, and lvalue is forwarded as lvalue.
 */

// Solution
template <typename T>
void relay2(T &&arg)
{
    foo_new(std::forward<T>(arg));
}

// Note: this will work because type T is a template type.

/*
 * Reference Collapsing Rules (C++11):
 * 1.   T& &   ==>  T&
 * 2.   T& &&  ==>  T&
 * 3.   T&& &  ==>  T&
 * 4.   T&& && ==>  T&&
 */

// template <class T>
// struct remove_reference; // It removes reference on type T

// T is int&
remove_reference<int &>::type i; // int i;

// T is int
remove_reference<int>::type i1; // int i;

template <typename T>
void relay3(T &&arg)
{
    cout << arg << endl;
    // cout << typeid(arg).name << endl;
}

// T&& is called universal reference

// T&& is Universal Reference: rvalue, lvalue, const, non-const, etc...
// Conditions:
// 1. T is a template type.
// 2. Type deduction (reference collasing) happens to T.
//    -T is a function template type, not class template type.

//Implementation of std::forward()
// template <class T>
// T &&forward(typename remove_reference<T>::type &arg)
// {
//     return static_cast<T &&>(arg);
// }

template <typename T>
void relay4(T &&arg)
{
    foo_new(forward<T>(arg));
}

// std::move()vs std::forward()
// std::move<T>(arg); // Turn arg into an rvalue type 
// std::forward<T>(arg); // Turn arg to type of T&&


int main(int argc, char const *argv[])
{
    cout << "----------Move Semantics----------" << endl;
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
    cout << "-------End of Move Semantics------" << endl;

    cout << "--------Perfect Forwarding--------" << endl;
    cout << "XuVector reusable_new = createXuVector(n);" << endl;
    XuVector reusable_new = createXuVector(n);
    cout << "relay(reusable_new);" << endl;
    relay1(reusable_new);
    cout << "relay(createXuVector(n));" << endl;
    relay2(createXuVector(n));

    /*
    * rvalue reference is specified with type&.
    *
    * type&& is rvalue reference?
    */

    // T&& variable is intialized with rvalue => rvalue reference
    relay3(9); // T = int && -> T && = int && && = int &&

    // T&& variable is intialized with lvalue =>lvalue reference
    relay3(n); // T = int&   -> T && = int& &&   = int&

    cout << "------End Perfect Forwarding------" << endl;

    return 0;
}