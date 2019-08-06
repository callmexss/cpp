#include <iostream>
#include <string>
#include <vector>

using namespace std;


// Person owns the string through its pointer
class Person
{
public:
    Person(string name) { pName_ = new string(name); }
    ~Person() { delete pName_; }
    void printName() { cout << *pName_; }

    // Person(const Person& rhs)
    // {
    //     pName_ = new string(*(rhs.pName_));
    // }
    // Person& operator=(const Person& rhs); // Deep copying
    Person& operator=(const Person&) = delete;
    string* pName() const {return pName_; }
    Person* clone() { return (new Person(*(pName_))); }

private:
    Person(const Person &);
    string *pName_;
};

// Solution 1: Define copy constructor and copy assignment operator for deep copying
// Solution 2: Delete copy constructor and copy assignment operator

int main()
{
    // vector<Person> persons;
    // persons.push_back(Person("George"));
    // 1. "George" is constructed
    // 2. A copy of "George" is saved in the vectorf persons (shallow copy)
    // 3. "George" is destroyed.
    // persons.back().printName();

    vector<Person*> persons;
    persons.push_back(new Person("George"));
    persons.back()->printName();

    cout << " Goodbye" << endl;
    for (auto &p : persons)
        delete p;
    return 0;
}