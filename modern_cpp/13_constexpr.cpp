/**
 * 13. constexpr
 */

int arr[6];
int A() { return 3; }
int arr2[A() + 3]; // Compiler Error

// C++ 11
constexpr int B() { return 3; } // Forces the compution to happen
                                // at compile time.

int arr[B() + 3]; // create an array of size 6

// Write faster program with constexpr 
constexpr int cubed(int x) { return x * x * x; }

int y = cubed(1789); // computed at compile time
