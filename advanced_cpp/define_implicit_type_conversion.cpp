#include <iostream>
#include <string>

using namespace std;

/**
 * User Defined Implicit Type Conversion
 * 
 * Categories of Type Conversion:
 *                                  Implicit             Explicit
 * Standard Type Conversion            A                    B
 * User Defined Type Conversion        C                    D
 *                                                       (casting)
 * 
 * Category A: Implicit Standard Type Conversion
 */

char c = 'A';
int i = c; // Integral promotion

char* pc = 0; // int->Null pointer 

void f(int i) {}

/**
 *  Category C: Implicit User Defined Type Conversion
 * 
 *  Defined inside class (user defined type)
 * 
 *  There are 2 methods to define implicit user defined type conversion:
 *  Method 1: Use constructor that can accept a single parameter.
 *      - convert other types of object into your class
 *  Method 2: Use the type conversion function
 *      - convert an object of your class into other types
 */

class dog
{
public:
    // constructor with one parameter is not only a constructor
    // but also a type convertor.
    dog(string name) { m_name = name; } // No explicit
    // If you only want to define a constructor, and no implicit type
    // conversion, always put "explicit" before the constructor to
    // avoid inadvertent type conversion.
    string getName() { return m_name; }
    operator string () const { return m_name; }

private:
    string m_name;
};

// dog *pd = new yellowdog(); // pointer type conversion 

/**
 * Implicit type conversion is useful when creating numerical types of class,
 * such as a rational class.
 */
class Rational
{
public:
    Rational(int numerator=0, int dennominator=1):
             num(numerator), den(dennominator) {}
    int num; // Demo only, public data members are not recommended
    int den;

    // const Rational operator*(const Rational& rhs)
    // {
    //     return Rational(num * rhs.num, den * rhs.den);
    // }

    // operator int () const { return num / den; }
};

const Rational operator* (const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.num * rhs.num, lhs.den * rhs.den);
}

int main(int argc, char const *argv[])
{
    f(c);
    string dogname = "Bob";
    dog dog1 = dogname;
    string dog2 = dog1;
    cout << dog2 << endl;
    // printf("My name is %s.\n", dog1.getName());
    printf("My name is %s.\n", dog1);

    Rational r1 = 23;
    Rational r2 = r1 * 2;
    Rational r3 = 3 * r1;
    return 0;
}

/**
 * PRINCIPLE: make interface easy to use correctly and hard to use incorrectly.
 * How hard is enough? Ideally, uncompilable.
 * 
 * General quideline:
 *     1. Avoid defining seemingly unexpected conversion.
 *     2. Avoid defining two-way implicit conversion.
 */
