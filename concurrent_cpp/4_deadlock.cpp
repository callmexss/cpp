#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <mutex>

using namespace std;

mutex mu;

class LogFile
{
    std::mutex m_mutex;
    std::mutex m_mutex2;
    std::ofstream f;
public:
    LogFile() { f.open("test.log"); }
    ~LogFile() { f.close(); }
    void shared_print(string id, int value)
    {
        std::lock_guard<mutex> locker(m_mutex);
        std::lock_guard<mutex> locker2(m_mutex2);
        cout << "From " << id << ": " << value << endl;
    }

    void shared_print2(string id, int value)
    {
        // std::lock_guard<mutex> locker(m_mutex);
        std::lock_guard<mutex> locker2(m_mutex2);
        std::lock_guard<mutex> locker(m_mutex); // lock the mutex in the same order
        cout << "From " << id << ": " << value << endl;
    }
    // Never return f to the outside world
    // ofstream& getStream() { return f; }
    // Never pass f as an argument to user provided function
    // void processf(void func(ofstream&)) { func(f); }
};

class LogFile2
{
    std::mutex m_mutex;
    std::mutex m_mutex2;
    std::ofstream f;
public:
    LogFile2() { f.open("test.log"); }
    ~LogFile2() { f.close(); }
    void shared_print(string id, int value)
    {
        std::lock(m_mutex, m_mutex2);
        std::lock_guard<mutex> locker(m_mutex, std::adopt_lock);
        std::lock_guard<mutex> locker2(m_mutex2, std::adopt_lock);
        cout << "From " << id << ": " << value << endl;
    }

    void shared_print2(string id, int value)
    {
        std::lock(m_mutex, m_mutex2);
        std::lock_guard<mutex> locker(m_mutex, std::adopt_lock);
        std::lock_guard<mutex> locker2(m_mutex2, std::adopt_lock);
        cout << "From " << id << ": " << value << endl;
    }
    // Never return f to the outside world
    // ofstream& getStream() { return f; }
    // Never pass f as an argument to user provided function
    // void processf(void func(ofstream&)) { func(f); }
};

void function_1(LogFile2& log)
{
    for (int i = 0; i > -100; i--)
    {
        log.shared_print("th2", i);
    }
}

int main()
{
    LogFile log;
    // LogFile2 log;

    // remember change the argument in function_1
    thread th1(function_1, std::ref(log));

    for (int i = 0; i < 100; ++i)
        log.shared_print2("main", i);

    th1.join();
    
    return 0;
}


/**
 * Avoiding deadlock
 * 1. Prefer locking single mutex.
 * 2. Avoid locking a mutex and then calling a user provided function.
 * 3. Use std::lock()to lock more than one mutex.
 * 4. Lock the mutex in same order.
 * 
 * Locking Granularity:
 * -Fine-grained lock:protects small amount of data
 * -Coarse-grained lock:protects big amount of datlI
 */