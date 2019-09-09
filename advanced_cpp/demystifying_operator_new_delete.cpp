#include <iostream>
using namespace std;

/**
 * Demystifying Operator new/delete
 * 
 * What happens when following code is executed?
 */

/**
 * Member Operator new
 */
class dog
{
public:
    static void* operator new(std::size_t size) // throw(std::bad_alloc)
    {
        if (size == sizeof(dog))
            // customNewForDog(size);
            ;
        else
            ::operator new(size);
    }
};

class yellowdog : public dog
{
    int age;
public:
    static void* operator new(std::size_t size) // throw(std::bad_alloc)
    {
        // ...
    }
};

void f()
{
    dog* pd = new dog();
    /**
     * Step 1. operator new is called to allocate memory.
     * Step 2. dog's constructor is called to create dog.
     * Step 3. if step 2 throws an exception, call operator delete to free the
     *         memory allocated in step 1.
     */

    delete pd;
    /**
     * Step 1. dog's destructor is called.
     * Step 2. operator delete is called to free memory.
     */
}

/**
 * Note: new handler is a function invoked when operator new failed to allocate
 * memory.
 *     set_new_handler() installs a new handler and returns current new handler.
 */
void* operator new(std::size_t size) //throw(std::std::bad_alloc)
{
    while (true)
    {
        void* pMem = malloc(size); // Allocate memory
        if (pMem)
            return pMem;           // Return the memory if successful

        std::new_handler Handler = std::set_new_handler(0); // Get new handler
        std::set_new_handler(Handler);

        if (Handler)
            (*Handler)();          // Invoke new handler 
        else
            throw bad_alloc();     // If new handler is null, throw exception
    }
}

/* Similarly for operator delete */
class cat
{
    static void operator delete(void* pMemory) throw()
    {
        std::cout << "Bo is deleting a dog" << std::endl;
        // customNewDeleteDog();
        free(pMemory);
    }
    ~cat() {}
};

class yellowcat : public cat
{
    static void operator delete(void* pMemory) throw()
    {
        std::cout << "Bo is deleting a yellowcat" << std::endl;
        // customNewDeleteYellowCat();
        free(pMemory);
    }
};

int main()
{
    // yellowdog* py = new yellowdog();
    return 0;
}

/**
 * Why do we want to customize new/delete
 * 
 * 1. Usage error detection:
 *    - Memory leak detection/garbage collection.
 *    - Array index overrun/underrun.
 * 2. Improve efficiency:
 *    a. Clustering related objects to reduce page fault.
 *    b. Fixed size allocation (good for application with many small objects).
 *    c. Align similar size objects to same places to reduce fragmentation.
 * 3. Perform additional tasks:
 *    a. Fill the deallocated memory with 0's-security.
 *    b. Collect usage statistics.
 */

/**
 * Writing a GOOD memory manager is HARD!
 * 
 * Before writing your own version of new/delete,consider:
 * 
 * 1. Tweak your compiler toward your needs;
 * 2. Search for memory management library, E.g.Pool library from Boost.
 */