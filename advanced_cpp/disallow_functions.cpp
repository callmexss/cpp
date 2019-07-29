#include <iostream>
#include <string>

using namespace std;

class OpenFile
{
public:
    OpenFile(string filename){ cout << "open a file" << filename << endl; }
    OpenFile(const OpenFile& rhs) = delete;
    void destroyMe() { delete this; }

private:
    // OpenFile(const OpenFile& rhs);
    OpenFile& operator=(const OpenFile& rhs);
    ~OpenFile() { cout << "OpenFile destructed." << endl; }
};

int main()
{
    // OpenFile f(string("Bo file"));
    OpenFile *f = new OpenFile(string("Bo_file"));
    f->destroyMe();

    // OpenFile f2(f);
    return 0;
}


/* Summary of Disallowing Functions
 * 1. C++11: f()=delete;
 * 2. C++ 03: Declare the function to be private, and not define it.
 * 3. Private destructor: stay out of stack.
 */