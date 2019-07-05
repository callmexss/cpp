/**
 * 11. Compiler Generated Default Constructor
 */

class Dog
{
    Dog(int age) {}
};

Dog d1; // Error: compiler will not generate the default constructor

// C++ 11
class Dog2
{
public:
    Dog2(int age);
    Dog2() = default; // Force compiler to generate the default constructor
};

int main(int argc, char const *argv[])
{
    /* code */
    Dog2 d2;
    return 0;
}
