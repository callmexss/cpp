#include <iostream>

#include "cat.h"
#include "dog.h"
#include "singleton.h"

// extern Dog d;

void Cat::meow()
{
    std::cout << "Cat rules! My name is " << _name << std::endl;
}

Cat::Cat(std::string name)
{
    std::cout << "Constructing Cat " << name << std::endl;
    _name = name;
    // d.bark();
    Singleton::getDog()->bark();
}