/**
 *  Initialization Fiasco
 *      -A subtle problem that can crash your program
 */

#include <iostream>

#include "cat.h"
#include "dog.h"
#include "singleton.h"

using namespace std;

// Dog d("Gunner");

int main()
{
    Singleton s; // delete cat or dog or both when out of scope
    // d.bark();
    Singleton::getCat()->meow();
    
    return 0;
}
