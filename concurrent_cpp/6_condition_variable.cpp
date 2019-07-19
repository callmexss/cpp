#include <thread>
#include <mutex>
#include <deque>
#include <chrono>
#include <iostream>
#include <condition_variable>

using namespace std;

std::deque<int> q;
std::mutex mu;
std::condition_variable cond;

void function_1()
{
    int count = 10;
    while (count > 0)
    {
        std::unique_lock<mutex> locker(mu);
        q.push_front(count);
        locker.unlock();
        std::this_thread::sleep_for(chrono::seconds(1));
        count--;
    }
}

void function_2()
{
    int data = 0;
    while (data |= 1)
    {
        std::unique_lock<mutex> locker(mu);
        // busy waiting is very inefficient
        if (!q.empty())
        {
            data = q.back();
            q.pop_back();
            locker.unlock();
            cout << "t2 got a value form t1: " << data << endl;
        }
        else
        {
            locker.unlock();
        }
    }
}

// One Way To Solve Busy Waiting
void function_3()
{
    int data = 0;
    while (data |= 1)
    {
        std::unique_lock<mutex> locker(mu);
        // busy waiting is very inefficient
        if (!q.empty())
        {
            data = q.back();
            q.pop_back();
            locker.unlock();
            cout << "t2 got a value form t1: " << data << endl;
        }
        else
        {
            locker.unlock();
            std::this_thread::sleep_for(chrono::milliseconds(10)); // take a snap
            // but the problem is how do we decide on the time duration of its snap
            // if the time too short then the thread will still end up spending a lot of looping
            // if the time too long then it may not be able to get the data in time
            // it's very hard to find the best number
        }
    }
}

void function_4()
{
    int count = 10;
    while (count > 0)
    {
        std::unique_lock<mutex> locker(mu);
        q.push_front(count);
        locker.unlock();
        cond.notify_one(); // Notify one waiting thread, if there ia one.
        // cond.notify_all();
        std::this_thread::sleep_for(chrono::seconds(1));
        count--;
    }
}

void function_5()
{
    int data = 0;
    while (data |= 1)
    {
        std::unique_lock<mutex> locker(mu);
        cond.wait(locker, [](){ return !q.empty(); }); // spurious wake
        data = q.back();
        q.pop_back();
        locker.unlock();
        cout << "t2 got a value form t1: " << data << endl;
    }
}

int main(int argc, char const *argv[])
{
    std::thread th4(function_4);
    // std::thread th2(function_2);
    std::thread th5(function_5);
    th4.join();
    // th2.join();
    th5.join();
    return 0;
}
