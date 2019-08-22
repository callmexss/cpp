#include <iostream>
using namespace std;

/**
 * Example with dynamic_cast:
 */
class dog
{
public:
    virtual ~dog() {}
    virtual void bark() {}
};

/* casting could be a handy hack tool */
class dog1
{
public:
    std::string m_name;
    dog1(): m_name("Bob") {}
    void bark() const
    {
        std::cout << "My name is " << m_name << std::endl;
        // const_cast<dog*>(this)->m_name = "Henry"; // not work...
    }
};

class yellowdog : public dog
{
    int age;
public:
    void bark() override { cout << "woof" << endl; }
    void bark2() { cout << "Dog " << age << endl; }
};

int main()
{
    dog* pd = new yellowdog();
    // dog* pd = new dog();
    // yellowdog* py = dynamic_cast<yellowdog*>(pd); // this will fail, py points to 0
    // yellowdog* py = static_cast<yellowdog*>(pd); // this will always success
                                                    // which can cause nasty bugs
    // if (py) // good practice 
    //     py->bark(); // try to interpret py->bark() as a static function and success
    // py->bark2(); // this will crashed, because it try to access a member variable
                    // which is not exists.
    
    pd->bark();
    // cout << "py = " << py << endl;
    cout << "pd = " << pd << endl;
    delete pd;
    
    return 0;
}

/**
 * ============================ C++ Style Casting ================================
 *                    Generate_Code   Generate_data   Risky     Data_Type
 * Object Casting:
 *   static_cast         yes             yes            2       any types
 *                                                            (as long as type
 *                                                          conversion is defined)
 * Pointer/Reference
 * Casting:
 *     static cast       no              no             4      related types
 *     dynamic cast      yes             no             3  related types(down-cast)
 *     const cast        no              no             1        same type
 *     reinterpret_cast  no              no             5        any types
 * 
 * 
 * ============================ C++ Style Casting ================================
 *                    Generate_Code   Generate_data   Risky     Data_Type
 * Object Castring       yes             yes            5        any types 
 *                                                            (as long as type
 *                                                          conversion is defined)
 * 
 * Pointer/Reference
 * Casting:              no              no             5        any types
 * 
 * Notes can be downloaded at this website: boqian.weebly.com
 */