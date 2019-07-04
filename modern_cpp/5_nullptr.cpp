#include <iostream>

using namespace std;

/**
 * 5. nullptr
 * 
 * To replace NULL in c++ 03
 */

void foo(int i) { cout << "foo_int" << endl; }
void foo(char *pc) { cout << "foo_char *" << endl; }

int main(int argc, char const *argv[])
{
    // foo(NULL); // Ambiguity

    // C++ 11
    foo(nullptr); // call foo(char *)
    return 0;
}
