#include <mutex>
#include <fstream>
#include <string>

using namespace std;

class LogFile
{
    std::mutex _mu;
    std::mutex _mu_open;
    std::once_flag _flag;
    std::ofstream _f;
public:
    LogFile() { /*  _f.open("log.txt"); */ }
    ~LogFile() { _f.close(); }

    void shared_print(string id, int value)
    {
        std::unique_lock<mutex> locker(_mu);
        _f << "From " << id << ": " << value << endl;
        locker.unlock();
    }

    void shared_print2(string id, int value)
    {
        // unique_lock can only be transfered but not copied
        // heavy than lock_guard, which will compromise the performance
        std::unique_lock<mutex> locker(_mu, std::defer_lock);
        locker.lock();
        _f << "From " << id << ": " << value << endl;
        locker.unlock();

        // ...
        locker.lock(); 

        std::unique_lock<mutex> locker2 = std::move(locker);
        locker2.unlock();
    }

    void shared_print3(string id, int value)
    {
        if (!_f.is_open()) // Lazy Initailization or Initialization Upon First Use Idiom
        {
            // This is not thread safe.
            // suppose thread A enters the scope and gets the lock
            // then before A opens the file, thread B also enters the scope
            // now thread is Blocked until thread A opens file
            // and Thread B will gain the lock and open the file again
            // which is not thread safe.
            std::unique_lock<mutex> locker2(_mu_open);
            _f.open("log.txt");
        }
        std::unique_lock<mutex> locker(_mu);
        _f << "From " << id << ": " << value << endl;
    }

    // To handle the problem before
    void shared_print4(string id, int value)
    {
        {
            // This will do many times each time this function is called
            // which is very bad to performance.
            std::unique_lock<mutex> locker2(_mu_open);
            if (!_f.is_open())
                _f.open("log.txt");
        }
        std::unique_lock<mutex> locker(_mu);
        _f << "From " << id << ": " << value << endl;
    }

    // Both efficient and safe
    void shared_print5(string id, int value)
    {
        // file will be opened only once by one thread
        std::call_once(_flag, [&](){ _f.open("log.txt"); });

        std::unique_lock<mutex> locker(_mu);
        _f << "From " << id << ": " << value << endl;
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
