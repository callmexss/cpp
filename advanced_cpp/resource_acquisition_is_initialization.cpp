/**
 * Resource Acquisition is Initialization (RAII)
 * Use objects to manage resources:
 * memory, hardware device, network handle, etc.
 */

// Mutex_t mu = MUTEX INITIALIZER;

// void functionA()
// {
//     Mutex_lock(&mu);
//     //Do a bunch of things
//     Mutex_unlock(& mu); //Will this line always be executed?
// }

/*
 * Solution:
 */

// class Lock
// {
// private:
//     Mutex_t *m_pm;

// public:
//     explicit Lock(Mutex_t *pm)
//     {
//         Mutex_lock(pm);
//         m_pm = pm;
//     };
//     ~Lock() { Mutex_unlock(m_pm); }
// };

// void functionA()
//     Lock mylock(&mu);
// ... 7 / Do a bunch of things
// } // The mutex will always be released when mylock is destroied from stack

/**
 * Conclusion:
 * The only code that can be guaranteed to be executed after exception is
 * thrown are the destructor of objects residing on the stack.
 * Resource management therefore needs to be tied to the lifespan of
 * suitable objects in order to gain automatic deallocation and reclamation.
 */

/**
 * Note 1:
 * Another good example of RAII: trl: shared ptr
 */

// int function_A()
// {
//     std::tr1::shared_ptr<dog> pd(new dog());
//     ...
// } // The dog is destructed when pd goes out of scope (no more pointer
//   // points to pd).

// Another example:
// class dog;
// class Trick;
// void train(tr1::shared ptr<dog> pd, Trick dogtrick);
// Trick getTrick();
// int main()
// {
//     train(tr1::shared ptr<dog> pd(new dog()), getTrick());
//     return 0;
// }

// Question: What's the problem with above code:

// What happens in train()'s parameter passing:
// 1. new dog();
// 2. getTrick()}
// 3. construct tr1:: shared ptr<dog>.
// The order of these operations are determined by compiler.

/**
 *  Note3: what happens when resource management object is copied?
 */

// Lock L1(&mu);
// Lock L2(L1);

/**
 * Solution 1:
 * Prohibit copying. To see how to disallow copy constructor and copy
 * assignment operator from being used, watch my another session:
 * Disallow Compiler Generated Functions.
 */

/**
 * Solution 2:
 * Reference-count the underlying resource by using trl:: shared ptr
 */
// template<class other, class D> shared_ptr(other * ptr,D deleter);

//The default value for D is "delete",e.g.:
// std::tr1::shared_ptr<dog> pd(new dog());

// class Lock
// {
// private:
//     std::tr1::shared_ptr<Mutex_t> pMutex;
// public:
//     explicit Lock(Mutex_t *pm) : pMutex(pm, Mutex_unlock)
//     {
//         Mutex_lock(pm);
//         //The second parameter of shared ptr constructor is "deleter"function.
//     };

// int main(int argc, char const *argv[])
// {
//     /* code */
//     Lock L1(&mu);
//     Lock L2(L1);
//     return 0;
// }

#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

class Mutex
{
private:
    std::mutex m_mutex;

public:
    void lock() { m_mutex.lock(); }
    void unlock() { m_mutex.unlock(); }

};

class LockGuard
{
private:
    Mutex& m_mu;

public:
    LockGuard(Mutex &mu) : m_mu(mu) { m_mu.lock(); }
    ~LockGuard() { m_mu.unlock(); }
    LockGuard(const Mutex&) = delete;
};

int main()
{
    int i = 0;
    Mutex mu;

    // auto f_without_lock_guard = [&i]() { while (i < 100) { i++; cout << i << endl; } };
    // std::thread th1(f_without_lock_guard);
    // std::thread th2(f_without_lock_guard);

    // th1.join();
    // th2.join();
    

    auto f_with_lock_guard = [&i, &mu]() { while (i < 100) { LockGuard locker = LockGuard(mu); i++; cout << i << endl; } };
    std::thread th3(f_with_lock_guard);
    std::thread th4(f_with_lock_guard);

    th3.join();
    th4.join();

    return 0;
}
