/**
 * 10. final (for virtual function and for class)
 */

class Dog final // no class can be derived from dog
{

};

class Dog2
{
    virtual void bark() final; // no class can override bark()
};

class YellowDog: public Dog
{

};

class RedDog: public Dog2
{
    void bark() override;
};