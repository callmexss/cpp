/**
 * 12. delete
 */

class Dog
{
public:
    Dog(int age) {}
};

void c03()
{
    Dog a(2);
    Dog b(3.0); // 3.0 is converted from double to int
    a = b;      // Compiler generated assignment operator
}

// C++ 11
class Dog2
{
public:
    Dog2(int age) {}
    Dog2(double) = delete;
    Dog2& operator=(const Dog2&) = delete;
};

void c11()
{
    Dog2 a(2);
    Dog2 b(3.0);
    a = b;
}
