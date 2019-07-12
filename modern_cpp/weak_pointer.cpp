#include <iostream>
#include <memory>
#include <string>

using namespace std;

// weak_ptr has no ownership of the pointed object.
// can only access the object, provides safer access to the pointer.

class Dog
{
    // shared_ptr<Dog> m_pFriend; // cyclic reference
    weak_ptr<Dog> m_pFriend; // work as a raw pointer but provide protection that no one can delete it.
    string m_name;

public:
    Dog(string name) : m_name(name) { cout << "Dog is created: " << m_name << endl; }
    ~Dog() { cout << "Dog is destroyed: " << m_name << endl; }
    string showName() { return m_name; }
    void bark() { cout << "Dog " << m_name << "rules!" << endl; }
    void makeFriend(shared_ptr<Dog> f) { m_pFriend = f; }
    void showFriend()
    {
        // check whether the pointer is still valid
        // if m_pFriend is a nullptr, m_pFriend will throw an exception.
        if (!m_pFriend.expired())
        {
            // lock() create a shared_ptr out of weak_ptr to make two things:
            // 1. checks if the weak_ptr is still pointing a valid object;
            // 2. it makes sure that while is access an object, that object will not be deleted. 
            // an object should be deleted only when there is no share_ptrs pointing to it.
            cout << "My friend is: " << m_pFriend.lock()->showName() << endl;
        }
        cout << "He is owned by " << m_pFriend.use_count() << " pointers" << endl;
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    shared_ptr<Dog> pD = make_shared<Dog>("Gunner");
    shared_ptr<Dog> pD2 = make_shared<Dog>("Smokey");
    pD->makeFriend(pD2);
    pD2->makeFriend(pD);
    pD->showFriend();
    return 0;
}
