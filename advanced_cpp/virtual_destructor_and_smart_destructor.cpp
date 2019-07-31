#include <iostream>
#include <memory>

using namespace std;

/* Use virtual destructors in polymorphic base classes */

class Dog
{
public:
    // derive class will not be destroied if this is not virtual
    // ~Dog() { cout << "Dog destroyed" << endl; }
    virtual ~Dog() { cout << "Dog destroyed" << endl; }

    // if has some virtual functions
    // this class highly will be used as polymorphism
    // so should have a virtual destructor
    virtual void bark() {}
};

class Yellowdog : public Dog
{
public:
    ~Yellowdog() { cout << "Yellow dog destroyed." << endl; }
};

class DogFactory
{
public:
    static Dog *createYellowDog() { return (new Yellowdog()); }
    static shared_ptr<Dog> createYellowDogSmart()
    {
        return shared_ptr<Yellowdog>(new Yellowdog());
    }
    //... create other dogs
};

int main()
{
    Dog *pd = DogFactory::createYellowDog();
    //.. Db something with pd 
    delete pd; // base class's destructor will be called first, then derive class

    // unique_ptr will not do the job, it will only invoke the Dog's destructor
    shared_ptr<Dog> spd = DogFactory::createYellowDogSmart();
    return 0;
}

/**
 * Note: All classes in STL have no virtual destructor,
 * so be careful inheriting from them.
 */