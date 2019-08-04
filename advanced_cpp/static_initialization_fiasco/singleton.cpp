#include "singleton.h"
#include "cat.h"
#include "dog.h"

Dog* Singleton::pd = nullptr;
Cat* Singleton::pc = nullptr;

Dog* Singleton::getDog()
{
    if (!pd)
        pd = new Dog("Gunner"); // Initialize Upon First Usage Idiom
    return pd;
}

Cat* Singleton::getCat()
{
    if (!pc)
        pc = new Cat("Smokey");
    return pc;
}

Singleton::~Singleton()
{
    if (pd) delete pd;
    if (pc) delete pc;

    pd = nullptr;
    pc = nullptr;
}