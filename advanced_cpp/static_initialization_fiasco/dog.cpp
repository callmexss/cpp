#include <iostream>
#include "dog.h"
#include "cat.h"

// Cat c("Smokey");

void Dog::bark()
{
    std::cout << "Dog rules! My name is " << _name << std::endl;
}

Dog::Dog(std::string name)
{
    std::cout << "Constructing Dog " << name << std::endl;
    _name = name;
    // c.meow();
}