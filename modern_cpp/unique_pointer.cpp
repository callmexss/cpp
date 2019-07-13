#include <iostream>
#include <memory>

using namespace std;

/**
 * Unique Pointer
 * 
 * exclusive ownership, light weight smart pointer.
 */

class Bone
{
public:
    Bone() { cout << "Bone is created." << endl; }
    ~Bone() { cout << "Bone is destroyed." << endl; }
};

class Dog
{
    unique_ptr<Bone> pB;

public:
    string m_name;
    void bark() { cout << "Dog " << m_name << " rules!" << endl; }
    Dog() : m_name("nameless"), pB(new Bone()) { cout << "Nameless dog created." << endl; }
    Dog(string name) : m_name(name)
    {
        cout << "Dog is created: " << m_name << endl;
    }
    ~Dog() { cout << "dog is destroyed: " << m_name << endl; }
};

void test()
{
    Dog *pD = new Dog("Gunner");
    pD->bark();
    delete pD;
}

void test1()
{
    unique_ptr<Dog> pD = make_unique<Dog>("Gunner");
    pD->bark();

    /**
     * Unique Pointer release method
     */
    // Dog *p = pD.release(); // Gunner will not automatically be deleted if released.
    // if (!pD)
    // {
    //     cout << "pD is empty." << endl;
    // }
    // delete p;

    /**
     * Unique Pointer get method
     */
    pD.reset(new Dog("Smokey")); // once reset invoked, Dog Gunner will be deleted automically
                                 // when create new Dog Smonkey.
    pD.reset();                  // pD = nullptr;
    if (pD)
    {
        cout << "pD is not empty." << endl;
    }
    else
    {
        cout << "pD is empty." << endl;
    }
} // when out of scope, Smokey will be deleted automically.

void test2()
{
    unique_ptr<Dog> pD = make_unique<Dog>("Gunner");
    unique_ptr<Dog> pD2 = make_unique<Dog>("Smokey");
    pD2->bark();
    pD2 = move(pD);
    // 1. Somokey is destroyed.
    // 2. pD becomes empty.
    // 3. pD2 owns Gunner.
    if (pD)
    {
        cout << "pD is not empty." << endl;
    }
    else
    {
        cout << "pD is empty." << endl;
    }
    pD2->bark();
}

void f(unique_ptr<Dog> &p)
{
    cout << "pass by reference." << endl;
    p->bark();
} // p will be deleted when reach out of its origin scope but not in function f.

void f1(unique_ptr<Dog> p)
{
    cout << "pass by move semantic." << endl;
    p->bark();
} // p will be deleted when reach out of function f1.

void test3()
{
    unique_ptr<Dog> pD = make_unique<Dog>("Gunner");
    f(pD);
    if (pD)
    {
        cout << "pD is not empty." << endl;
    }
    else
    {
        cout << "pD is empty." << endl;
    }

    f1(move(pD));
    if (pD)
    {
        cout << "pD is not empty." << endl;
    }
    else
    {
        cout << "pD is empty." << endl;
    }
}

unique_ptr<Dog> getDog()
{
    unique_ptr<Dog> pD = make_unique<Dog>("Smokey");
    return pD;
}

void test4()
{
    unique_ptr<Dog> pD = getDog();
}

void test5()
{
    unique_ptr<Dog[]> dogs(new Dog[3]);
}

int main()
{
    cout << "-----------------------------------" << endl;
    test();
    cout << "-----------------------------------" << endl;
    test1();
    cout << "-----------------------------------" << endl;
    test2();
    cout << "-----------------------------------" << endl;
    test3();
    cout << "-----------------------------------" << endl;
    test4();
    cout << "-----------------------------------" << endl;
    test5();
    cout << "-----------------------------------" << endl;

    return 0;
}
