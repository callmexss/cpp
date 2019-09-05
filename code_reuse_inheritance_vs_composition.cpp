#include <iostream>
using namespace std;

/**
 * Code Reuse: Inheritance Vs. Composition
 */

// Code Reuse with inheritance
class BaseDog
{
    // common activities
};

class BullDog : public BaseDog
{
    // Call the common activities to perform more tasks.
};

class shepherdDog : public BaseDog
{
    // Call the common activities to perform more tasks.
};

// Code Reuse with composition
class ActivityManager
{
    // common activities
};

class Dog
{
    // ...
};

class BullDog : public Dog
{
    ActivityManager* pActMngr;
    // Call the common activities through pActMngr
};

class ShepherdDog : public Dog
{
    ActivityManager* pActMngr;
    // Call the common activities through pActMngr
};

/*
 * Code Reuse : composition is better than inheritance
 * 
 * 1. Less code coupling between reused code and reuser of the codel
 *    a. Child class automatically inherits ALL parent class's public members.
 *    b. Child class can access parent's protected members.
 *       - Inheritance breaks encapsulation
 * 
 */
 
/*
 * 2. Dynamic Binding
 *    a. Inheritance is bound at compile time
 *    b. Composition can be bound at either compile time or at run time
 */

class OutdoorActivityManager : public ActivityManager {};
class IndoorActivityManager : public ActivityManager {};

/*
 * 3. Flexible Code Construct
 * 
 *    Dog                  ActivityManager
 * 
 *    Bul1Dog              OutdlorActivityManager
 *    ShepherdDog          IndoorActivityManager
 *    ...
 */

int main()
{

    return 0;
}
