#include <iostream>
using namespace std;

/**
 * User Defined Literals
 */

/*
 * Literals are constants.
 *
 * C++ has 4 kinds of literals:
 *     integer        ---   45
 *     floating point ---   4.5
 *     character      ---   'z'
 *     string         ---   "Dog"
 */

// 45; int literal
// 45u; unsigned int (suffix specifies type)
// 45l; long

// C++ 99
long double height = 3.4; // Metres? Centimeters? Inches?

// Ideally, always attach units to the values: 
// height = 3.4cm;
// ratio = 3.4cm / 2.1mm;
// ratio = -3.4 * 10 / 2.1

// User Defined Literals
// long double operator"" _cm(long double x) { return x * 10; }
// long double operator"" _m(long double x) { return x * 1000; }
// long double operator"" _mm(long double x) { return x; }
constexpr long double operator"" _cm(long double x) { return x * 10; }
constexpr long double operator"" _m(long double x) { return x * 1000; }
constexpr long double operator"" _mm(long double x) { return x; }

// Example
int operator"" _bin(const char* str, size_t l)
{
    int ret = 0;
    for (int i = 0; i < l; ++i)
    {
        ret = ret << 1;
        if (str[i] == '1')
            ret += 1;
    }
    return ret;
}

int main()
{
    long double height = 3.4_cm;
    cout << height << endl;
    cout << (height + 13.0_m) << endl;
    cout << (130.0_mm / 13.0_m) << endl;

    cout << "110"_bin << endl;
    cout << "1100110"_bin << endl;
    cout << "110100010001001110001"_bin << endl;
    
    return 0;
}

// C++ went a long way to make user defined types (classes) to behave same as build-in types.
// User defined literals pushes this effort even further

/**
 * Restriction: it can only work with following parameters:
 * 
 * char const*
 * unsigned long long 
 * long double
 * char const*, std::size_t
 * wchar t const*, std::size_t
 * charl6t const*, std::size_t
 * char32t const*, std::size_t
 * 
 * Note: return value can be of any types.
 */
