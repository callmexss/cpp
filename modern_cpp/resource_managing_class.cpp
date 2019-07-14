#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Person
{
public:
    Person(string name) : m_pName(new string(name)) {}
    // Person(const Person&) = delete; // the copy constructor is deleted
    // ~Person() { delete m_pName; }
    ~Person() { }
    void printName() { cout << *m_pName; }

private:
    // string* m_pName;
    // shared_ptr<string> m_pName;
    unique_ptr<string> m_pName;
};

int main(int argc, const char *argv[])
{
    vector<Person> persons;
    // persons.push_back(Person("George"));
    // persons.emplace_back(Person("George")); // construct the object in place,
                                               // (in the space allocated to the vector)
    Person p("George");
    persons.push_back(move(p));
    persons.front().printName(); // will crashed

    /**
     * C++ 03 solution:
     * 1. define copy constructor and copy assignment operator
     * 2. delete copy constructor and copy assignment operator
     * 
     * C++11:
     * 1. keyword "delete"
     * 2. emplace_back()
     * 3. shared_ptr
     * 4. unique_str
     * 5. move
     */
    
    return 0;
}
