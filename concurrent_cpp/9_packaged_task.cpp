#include <iostream>
#include <future>
#include <functional>
#include <deque>
#include <mutex>

using namespace std;

int factorail(int n)
{
    int res = 1;
    for (int i = n; i > 1; i--)
        res *= i;
    cout << "Result is: " << res << endl;
    return res;
}

std::deque<std::packaged_task<int()>> task_q;
std::mutex mu;
std::condition_variable cond;

void thread1()
{
    std::packaged_task<int()> t;
    {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [](){ return !task_q.empty(); });
        t = std::move(task_q.front());
        task_q.pop_front();
    }
    t();
}

int main(int argc, char const *argv[])
{
    std::packaged_task<int(int)> t(factorail);

    /// ...

    t(6); // In a different context
    int x = t.get_future().get();

    std::thread th1(factorail, 6);
    th1.join();

    // can link a callable object to a future
    std::packaged_task<int()> t2(std::bind(factorail, 6));

    t2(); // DON'T FORGET DO THIS
    int x2 = t2.get_future().get();

    std::packaged_task<int()> t3(bind(factorail, 6));
    std::future<int> fu = t3.get_future();

    {
        std::lock_guard<std::mutex> locker(mu);
        task_q.push_back(std::move(t3));
    }
    cond.notify_one();

    std::thread th2(thread1);
    // cout << fu.get() << endl;
    th2.join();

    return 0;
}

/* Summary
 * 3 ways to get a future:
 * - promise::get_future()
 * - packaged_task::get_future()
 * - async() returns a future
 */