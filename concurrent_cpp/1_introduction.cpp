#include <iostream>
#include <thread>

using namespace std;

void function_1()
{
    cout << "Beauty is only skin-deep" << endl;
}

int main()
{
    std::thread th1(function_1); // t1 starts running
    // th1.join(); // main thrad waits for t1 to finish
    th1.detach(); // th1 will freely on its own -- daemon process 

    // ...

    if (th1.joinable())
        th1.join(); // if not check, program will crash
    return 0;
}
