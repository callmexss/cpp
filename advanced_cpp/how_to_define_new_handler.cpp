#include <iostream>
#include <new>
using namespace std;

/**
 * Define Your Own New-handler
 * 
 * 1. What is new-handler
 * 
 * New handler is a function invoked when operator new failed to allocate
 * memory. It's purpose is to help memory allocation to succeed.
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

/**
 * So the new-handler must do one of following things:
 * 1). Make more memory available.
 * 2). Install a different new-handler.
 * 3). Uninstall the new-handler (passing a null pointer).
 * 4). Throw an exception bad_alloc or its descendant.
 * 5). Terminate the program.
 */

void NoMoreMem()
{
    cerr << "Unable to allocate memory." << endl;
    abort();
}

/**
 * 2. Class specific new-handler
 */

class dog
{
    int hair[10000000000L];
    static std::new_handler origHandler;
public:
    static void NoMemForDog()
    {
        cerr << "No more memory for doggy." << endl;
        throw std::bad_alloc();
    }

    static void* operator new(std::size_t size)
    {
        origHandler = std::set_new_handler(NoMemForDog);
        void* pV = ::operator new(size);   // Call global operator new
        std::set_new_handler(origHandler); // Restore old handler
        return pV;
    }
};

int main()
{
    std::set_new_handler(NoMoreMem);
    int *pGiant = new int[100000000000L];
    delete [] pGiant;

    // dog* pd = new dog();
    
    return 0;
}
