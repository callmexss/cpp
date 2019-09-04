#include <iostream>
using namespace std;

/*
 * The Duality of Public Inheritance
 * 
 * - Inheritance of Interface
 * - Inheritance of Implementation
 */

class Dog
{
public:
    virtual void bark() = 0;
    void run() { std::cout << "I am running." << std::endl; }
    virtual void eat() { std::cout << "I am eating." << std::endl; }

protected:
    void sleep() { std::cout << "I am sleeping." << std::endl; }
};

class Yellowdog : public Dog
{
public:
    virtual void bark() { std::cout << "I am a yellow dog." << std::endl; }
    void iSleep() { sleep(); }
};


/*
 * Types of Inheritance in C++:
 * 1. Pure virtual public function - inherit interface only.
 * 2. Non-virtual public function - inherit both interface and implementation.
 * 3. Impure virtual public function-inherit interface and default implementation.
 * 4. Protected function-inherit implementation only.
 * 
 * As a software designer, it is very important to separate the concepts of
 * interface and implementation.
 */

/*
 * Interface Inheritance
 * 
 * 1. Subtyping
 * 2. Polymorphism
 */

class A
{
    virtual void bark()=0;
};

/*
 * Pitfalls:
 * 
 * -- Be careful of interface bloat.
 * -- Interfaces do not reveal implementation.
 */

/*
 * Implementation Inheritance
 *     - Increase code complexity
 *     - Not encouraged
 */

class B
{
public:
    void run() { cout <<"I am running." << endl; }
    virtual void eat() { cout << "I am eating."<< endl; }

protected:
    void sleep(){ cout << "I am sleeping."<< endl; }
};

/* Guidelines for Implementation Inheritance:
 * 1. Do not use inheritance for code reuse, use composition.
 * 2. Minimize the implementation in base classes. Base classes should be thin.
 * 3. Minimize the level of hierarchies in implementation inheritance.
 */

/*
 * "Inheritance is evil"    ???
 * "Inheritance is often useful, but more often overused(abused)."
 */
 
int main()
{
    Yellowdog yd;
    yd.bark();
    yd.eat();
    yd.run();
    yd.iSleep();
    
    return 0;
}
