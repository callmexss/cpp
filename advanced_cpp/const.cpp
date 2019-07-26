// const
//   - A compile time constraint that an object can not be modified


int main(int argc, char const *argv[])
{
    const int i = 9;
    // i = 8; // can not compile
    
    const int *p1 = &i; // data is const, pointer is not
    // *pi = 5; // can not compile
    p1++; // p1 is not const

    int j = 0;
    int * const p2 = &j; // pointer is const, data is not

    const int* const p3 = &i; // data and pointer are both const

    int const *p4 = &i; // data is const, pointer is not

    const int k = 9;
    const_cast<int&>(i) = 6;

    static_cast<const int&>(j);
    j = 3;

    return 0;
}

// If const is on the left of *, data is const
// If const is on the right of *, pointer is const

/*
    Why use const
        a.) Guards against inadvertent write to the variable.
        b.) Self documenting 
        c.) Enabless compiler to do more optimiztion, making code tighter.
        d.) const means the variable can be put in ROM.
*/