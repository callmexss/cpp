#include <iostream>
#include <thread>
#include <string>

using namespace std;

void function_1()
{
    cout << "Beauty is only skin-deep" << endl;
}

class Functor
{
public:
    void operator()()
    {
        for (int i = 0; i > -2; --i)
            cout << "From th1: " << i << endl;
    }

private:
};

void function_2(string msg)
{
    cout << "t2 says: " << msg << endl;
}

void function_3(string msg)
{
    cout << "t3 says: " << msg << endl;
    msg = "Trust is the mother of deceit";
}

int main()
{
    cout << "main: " << this_thread::get_id() << endl;

    // thread th1(function_1); // t1 starts running
    // using RAII
    // Wrapper w(t1);
    Functor fct;
    thread th1(fct);
    cout << "th1: " << th1.get_id() << endl;

    // thread th1(Functor()); // this won't work as expected
                              // actually it defined a function takes a single
                              // parameter which is a pointer to another function
                              // and this function `Functor()` takes no parameter
                              // and returns a functor while the function th1
                              // returns a thread

    // thread th1((Functor()));  // solution, add an extra parenthesis

    try
    {
        for (int i = 0; i < 2; ++i)
            cout << "From main: " << i << endl;
    }
    catch (...)
    {
        th1.join();
        throw;
    }

    th1.join();

    string msg = "Where there is no trust, there is no love";

    // thread th2(function_2, msg);
    thread th2([](string msg){ cout << "t2 says: " << msg << endl; }, msg);
    cout << "th2: " << th2.get_id() << endl;
    th2.join();

    // thread th3(function_3, msg); // parameter to a thread will always be value
    // thread th3(function_3, std::ref(msg)); // in order to pass by reference, 
                                              // use std::ref
                                              // good old pointer is also ok
                                              // share memory may cause race competition

    thread th3(function_3, std::move(msg)); // both efficient and safe
                                            // thread can only be moved
                                            // function_3's parameter can not be reference
    cout << "th3: " << th3.get_id() << endl;


    // thread t4 = t3; // this will not be compiled, 
                       // because thread can not be copied.

    thread th4 = std::move(th3);
    cout << "th4: " << th4.get_id() << endl;

    // th3.join(); // th3 can not join because it has moved to th4

    cout << msg << endl; // suppose will not use msg (then can use move)
    th4.join();

    // Oversubscription
    cout << std::thread::hardware_concurrency() << endl; // Indication

    return 0;
}
