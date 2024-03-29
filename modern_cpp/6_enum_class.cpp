#include <iostream>

using namespace std;
/**
 * 6. enum class
 */

// C++ 03
void c03()
{

    enum apple
    {
        green_a,
        red_a
    };

    enum orange
    {
        big_o,
        small_o
    };
    apple a = green_a;
    orange o = big_o;

    if (a == o)
        cout << "green apple and big orange are the same\n";
    else
        cout << "green apple and big orange are not the same\n";

}

// C++ 11
void c11()
{

    enum class apple
    {
        green,
        red
    };

    enum class orange
    {
        big,
        small
    };
    apple a = apple::green;
    orange o = orange::big;

    if (a == o)
        cout << "green apple and big orange are the same\n";
    else
        cout << "green apple and big orange are not the same\n";

    // Compile fails because we haven't define==(apple,orange)
}

int main(int argc, char const *argv[])
{
    c03();
    return 0;
}
