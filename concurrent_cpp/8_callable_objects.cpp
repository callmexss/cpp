#include <future>
#include <mutex>
#include <thread>
#include <iostream>
#include <functional>


using namespace std;

class A
{
public:
    void f(int x, char c) {}
    long g(double x) { return 0; }
    int operator()(int N) { return 0; }
};

void foo(int x) {}

int main(int argc, char const *argv[])
{
    std::once_flag flag;
    A a;
    std::thread th1(a, 6); // copy_of_a() in a different thread
    std::thread th2(std::ref(a), 6); // a() in a different thread
    std::thread th3(A(), 6); // temp A
    std::thread th4([](int x) { return x * x; }, 6); // with lambda function
    std::thread th5(foo, 7); // with function
    std::thread th6(&A::f, a, 7, 'w'); // with member function, copy_of_a.f(8, 'w') in a different thread
    std::thread th7(&A::f, &a, 7, 'w'); // with member function, a.f(8, 'w') in a different thread
    std::thread th8(std::move(a), 6); // a() in a different thread, a is no longer usable in main thread

    // std::bind; std::async; std::call_once;
    std::async(std::launch::async, a, 6);
    std::bind(a, 6);
    std::call_once(flag, a, 6);

    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
    th6.join();
    th7.join();
    th8.join();
    return 0;
}
