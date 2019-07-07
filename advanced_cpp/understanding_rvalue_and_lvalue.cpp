/*
 * Understanding Rvalue and Lvalue
 * 
 * 
 * Why do I care?
 * 1. Understand C++ construct,and decypher compiler errors or warnings.
 * 2. C++11 introduced rvalue reference.
 * 
 * 
 */

/*
 * Simplified Definition:
 * 
 * lvalue - An object that occupies some identifiable location in memory
 * rvalue - Any object that is not a lvalue
 */

class Dog
{
public:
    void bark() {}
};

int sum(int x, int y) { return x + y; }
int square(int &x) { return x * x; }
// Workaround
int square2(const int &x) { return x * x; }

/**
 * Misconception 1: function or operator always yields rvalues.
 */
int myglobal;
int &foo() { return myglobal; }

int main(int argc, char const *argv[])
{
    /* Lvalue Example */
    int i;       // i is a lvalue
    int *p = &i; // i's address is identifiable
    i = 2;       // Memory content is modified

    Dog d1; // lvalue of user defined type (class)

    /* Most variables in C++ code are lvalues */

    /* Rvalue Example */
    int x = 2;         // 2 is an rvalue
    x = i + 2;         // i + 2 is an rvalue
    int *p = &(i + 2); // Error
    i + 2 = 4;         // Error
    2 = i;             // Error

    Dog d2;
    d2 = Dog(); // Dog() is an rvalue of user defined type (class)

    i = sum(3, 4); // sum(3, 4) is an rvalue

    // Rvalues: 2, i + 2, Dog(), sum(3, 4), x + y
    // Lvalues: x, i, p, d1

    // Reference (or lvalue reference):
    int j;
    int &r = j;

    int &r1 = 5; // Error

    // Exception: Constant lvalue reference can be assign a rvalue
    const int &r2 = 5; // step 1: a temporary lvalue is created with 5;
                       // step 2: the reference was initialized with this temporary lvalue.

    square(r);  // OK
    square(40); // Error

    square2(i);
    square2(40);

    /**
     *  lvalue can be used to crate an rvalue
     */
    i = 1;
    x = i + 2;

    x = i; // i is implicitly transformed to an rvalue
           // however, the other way around is not valid
           // an rvalue should explicitly used to crate a lvalue

    /**
     * rvalue can be used to create a lvalue
     */
    int v[3];
    *(v + 2) = 4; // `v + 2` is an rvalue, *(v + 2) is a lvalue

    foo() = 50;

    // A more common example:
    int array[5];
    array[3] = 50; // Operator [] almost always generates lvalue

    /*
    * Misconception 2: lvalues are modifiable.
    * 
    * C language: lvalue means "value suitable for left-hand-side of assignment"
    */
    const int c = 1; //c is a lvalue
    c = 2;           // Error, c is not modifiable.

    /**
     * Misconception 3: rvalues are not modifiable
     * 
     * For built-in types this is True
     * For user defined types this may not
     */
    i + 3 = 6;     // Error
    sum(3, 4) = 7; // Error

    Dog dog;
    dog.bark(); // bark() may change the state of the dog object

    return 0;
}

/*
 * Summary
 * 1. Every C++ expression yield either an rvalue or a lvalue.
 * 2. If the expression has an identifiable memory address, it's lvalue;
 *    otherwise, rvalue.
 */