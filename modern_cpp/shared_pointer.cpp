#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Dog
{
public:
    Dog(string name) : m_name(name) { cout << "Dog " << m_name << " is created." << endl; }
    Dog() : m_name("nameless") { cout << "Dog " << m_name << " is created." << endl; }
    ~Dog() { cout << "Dog " << m_name << " is destroyed." << endl; }
    void bark() { cout << "Dog " << m_name << " rules!" << endl; }

private:
    string m_name;
};

// use bare pointer
void foo()
{
    Dog *p = new Dog("Gunner");
    // ...
    // delete p;
    // ...
    p->bark(); // if delete p before,
               // p is a dangling pointer - undefined behavior
} // if forget delete p, memory leak

// use_count
void foo1() // use shared pointer
{
    shared_ptr<Dog> p(new Dog("Gunner")); // count = 1
    // 1. "Gunner" is created; 2. p is created.
    cout << p.use_count() << endl;

    p->bark();
    {
        shared_ptr<Dog> p2 = p;
        p2->bark(); // count = 2
        cout << p.use_count() << endl;
    }
    cout << p.use_count() << endl;
    // count = 1
} // count = 0

// reset a shared_ptr
void foo2()
{
    shared_ptr<Dog> p1 = make_shared<Dog>("Gunner");
    shared_ptr<Dog> p2 = make_shared<Dog>("Tank");
    p1 = p2; // Gunner is deleted
    p1 = nullptr;
    p1.reset();
}

// User defined deleter
void foo3()
{
    shared_ptr<Dog> p1 = make_shared<Dog>("Gunner"); // using default deleter: operator delete
    shared_ptr<Dog> p2 = shared_ptr<Dog>(new Dog("Tank"),
                                         [](Dog *p) { cout << "custum deleting." << endl; delete p; });
    // shared_ptr<Dog> p3(new Dog[3]); // dog[1] and dog[2] have memory leaks.
    shared_ptr<Dog> p4(new Dog[3], [](Dog *p) { delete[] p; }); // All 3 dogs will be deleted
                                                                // when p4 goes out of scope.
}

// get
void foo4()
{
    shared_ptr<Dog> p1 = make_shared<Dog>("Gunner");
    Dog *d = p1.get(); // returns the raw pointer

    // delete d; // when out of scope, p1's destructor will delete d again,
                 // which will cause undefined behavior.

    // shared_ptr<Dog> p2(p1);
    // dogHouse.saveDog(d); // when p1 out of scope, dog "Gunner" will be deleted.
                            // dogHouse will holding a dangling pointer.

    // WARN: when use raw pointer again, know exactly what you are doing and with extra care.
}

int main(int argc, char const *argv[])
{
    foo1();

    // this will cause undefined behavior
    // {
    //     Dog *d = new Dog("Tank"); // Bad idea
    //     shared_ptr<Dog> p(d); // p.use_count() == 1
    //     shared_ptr<Dog> p2(d); // p2.use_count() == 1
    // }
    // when out of scope, p will be destroyed, which means d is deleted.
    // p2 will also be destroyed, then it will delete a deleted pointer d.
    // which will cause undefined behavior.
    // An object should be assigned to a smart pointer as soon as it created.
    // Raw pointer should not be used.

    shared_ptr<Dog> p = make_shared<Dog>("Tank"); // faster and safer

    (*p).bark();
    // static_pointer_cast
    // dynamic_pointer_cast
    // const_pointer_cast

    foo2();

    foo3();

    foo4();

    return 0;
}
