#include <future>
#include <iostream>


using namespace std;

int factorial(int N)
{
    cout << std::this_thread::get_id() << endl;
    int res = 1;
    for (int i = N; i > 1; i--)
    {
        res *= i;
    }
    return res;
}

int factorial2(std::future<int>& f)
{
    int res = 1;
    int N = f.get(); // if not p.set_value() -> exception: std::future_errc::broken_promise
    for (int i = N; i > 1; i--)
    {
        res *= i;
    }
    return res;
}

int factorial3(std::shared_future<int> sf)
{
    int res = 1;
    int N = sf.get(); // if not p.set_value() -> exception: std::future_errc::broken_promise
    for (int i = N; i > 1; i--)
    {
        res *= i;
    }
    return res;
}

int main(int argc, char const *argv[])
{
    /* code */
    int x;
    cout << std::this_thread::get_id() << endl;
    
    // this may or may not create a new thread
    // std::future<int> fu = std::async(factorial, 4);
    // Equals to
    // std::future<int> fu = std::async(std::launch::async | std::launch::deferred,
    //                                  factorial, 4);
    // whether this will launch a thread depends on the implementation.

    // deferred will not launch a new thread,
    // it will deferred the factorail function
    // until fu.get() is called.
    // std::future<int> fu = std::async(std::launch::deferred, factorial, 4);

    // And this will launch a new thread
    std::future<int> fu = std::async(std::launch::async, factorial, 4);

    x = fu.get();
    cout << x << endl;
    // fu.get(); // if fu.get() be called twice, the program will be crashed

    std::promise<int> p;
    std::future<int> f = p.get_future();

    fu = std::async(std::launch::async, factorial2, std::ref(f));

    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    p.set_value(4);
    x = fu.get();
    cout << "Get from child: " << x << endl;

    // broke promise
    // p.set_exception(std::make_exception_ptr(std::runtime_error("Too err is human.")));

    std::promise<int> p2;
    std::future<int> f2 = p2.get_future();
    std::shared_future<int> sf = f2.share(); // can be copied
    
    std::future<int> fu1 = std::async(std::launch::async, factorial3, sf);
    std::future<int> fu2 = std::async(std::launch::async, factorial3, sf);
    std::future<int> fu3 = std::async(std::launch::async, factorial3, sf);

    p2.set_value(4);

    cout << fu1.get() << endl;
    cout << fu2.get() << endl;
    cout << fu3.get() << endl;

    return 0;
}
