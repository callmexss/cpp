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
    std::ofstream f;
public:
    LogFile() { f.open("test.log"); }
    ~LogFile() { f.close(); }
    void shared_print(string id, int value)
    {
        std::lock_guard<mutex> locker(m_mutex);
        f << "From " << id << ": " << value << endl;
    }
    // Never return f to the outside world
    ofstream& getStream() { return f; }
    // Never pass f as an argument to user provided function
    void processf(void func(ofstream&)) { func(f); }
};

void shared_print(string msg, int id)
{
    // mu.lock();
    lock_guard<mutex> lck(mu); // RAII 
    cout << msg << id << endl;
    // mu.unlock(); // if cout throw an exception
                    // the will never be unlocked
}

void function_1()
{
    for (int i = 0; i > -100; --i)
        shared_print("From th1: ", i);
}

void function_2(LogFile& log)
{
    for (int i = 0; i > -100; i--)
        log.shared_print("th2", i);
}

int main()
{
    LogFile log;
    // thread th1(function_1);
    // th1.join();
    thread th2(function_2, std::ref(log));

    for (int i = 0; i < 100; ++i)
        log.shared_print("main", i);

    th2.join();
    
    return 0;
}



// Is this class thread safe?
class Stack
{
    int* _data;
    std::mutex _mu;
public:
    void pop(); // pops off the item on the top of the stack
    int& top(); // returns the item on top
    // ...
};

void process(int v) {}

void func(Stack& st)
{
    int v = st.top();
    st.pop();
    process(v);
}

/**
 * st = [1, 7, 3, 2]
 * 
 * A: v = st.top(); -> 1
 * B: v = st.top(); -> 1
 * A: st.pop(); -> 1
 * B: st.pop(); -> 7
 * A: process(v); -> 1
 * B: process(v); -> 1
 * 
 * 1 will be processed twice
 * while 7 will not be processed at all
 * to make stack thread safe
 * combine pop and top to one function
 * in pop();
 * but this is not exception safe
 * so the STL stack may not implement like this
 */


/**
 * Avoiding Data Race:
 * 1.Use mutex to syncrhonize data access;
 * 2.Never leak a handle of data to outside;
 * 3.Design interface appropriately.
 */

