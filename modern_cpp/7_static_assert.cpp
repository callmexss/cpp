#include <cassert>
#include <stddef.h>

using namespace std;

/**
 * 7. static_assert
 */

void asserts()
{

    // run-time assert
    int a = 3;
    int *myPointer;
    myPointer = &a;
    assert(myPointer != NULL);
    // ref: https://stackoverflow.com/questions/924664/why-is-null-undeclared

    // compile time assert (C++ 11)
    static_assert(sizeof(int) == 4);
}

int main(int argc, char const *argv[])
{
    asserts();
    return 0;
}
