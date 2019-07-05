/**
 * 9. override (for virtual function)
 * 
 * To avoid inadvertently create new function in derived classes.
 */

class Dog
{
public:
    virtual void A(int) {}
    virtual void B() const {}
    void C() {}
};

// C++ 03
class YellowDog : public Dog
{
public:
    virtual void A(float) {} // Created a new function.
    virtual void B() {}      // Created a new function.
};

// C++ 11
class RedDog : public Dog
{
public:
    virtual void A(float) override {} // Error: no function to override
    virtual void B() override {} // Error: no function to override
    void C() override {} // Error: no function to override
};

int main(int argc, char const *argv[])
{
    YellowDog yd1;
    yd1.A(3.14);
    yd1.B();

    return 0;
}
