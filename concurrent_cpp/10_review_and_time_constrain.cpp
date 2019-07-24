#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>
#include <functional>
#include <chrono>

using namespace std;

int factorial(int N)
{
    int res = 1;
    for (int i = 1; i <= N; i++)
        res *= i;
    return res;
}

int main()
{
    /* Thread */
    std::thread th1(factorial, 6);
    std::this_thread::sleep_for(chrono::milliseconds(3));
    th1.join();
    chrono::steady_clock::time_point tp = chrono::steady_clock::now() + 
                                          chrono::microseconds(4);
    std::this_thread::sleep_until(tp);

    /* Mutex */
    std::mutex mu;
    std::timed_mutex tmu;
    // std::lock_guard<mutex> locker(mu); // both open will cause deadlock
    std::unique_lock<mutex> ulocker(mu);
    // std::unique_lock<std::timed_mutex> ulocker1(tmu);
    // ulocker.try_lock();
    // ulocker1.try_lock_for(chrono::nanoseconds(500));
    // ulocker.try_lock_until(tp);

    /* Condition Variable */
    std::condition_variable cond;
    cond.wait_for(ulocker, chrono::microseconds(2));
    cond.wait_until(ulocker, tp);


    /* Future and Promise */
    std::promise<int> p;
    std::future<int> f = p.get_future();
    f.get();
    f.wait();
    f.wait_for(std::chrono::milliseconds(2));
    f.wait_until(tp);

    /* Async */
    std::future<int> fu = async(factorial, 6);

    /* Packaged Task */
    std::packaged_task<int(int)> t(factorial);
    t(6);
    std::future<int> fu2 = t.get_future();
    
    return 0;
}
