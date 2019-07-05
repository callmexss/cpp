#include <string>
#include <iostream>

using namespace std;
/**
 * 14. New String Literals
 */

int main(int argc, char const *argv[])
{
    /* code */
    // C++ 03
    char *a = "string";

    // C++ 11
    char *b = u8"string";          // to define a UTF-8 string. 
    char16_t *c = u"string";       // to define a UTF-16 string.
    char32_t *d = U"string";       // to define a UTF-32 string.
    char *e = R"(string \\)";      // to define a raw string. `()` is needed else will raise a compile error
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << d << endl;
    cout << e << endl;
    return 0;
}

