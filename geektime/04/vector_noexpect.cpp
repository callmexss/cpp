#include <iostream>
#include <vector>

using namespace std;

class Obj1
{
public:
    Obj1() { cout << "Obj1()" << endl; }
    Obj1(const Obj1&) { cout << "Obj1(const Obj1&)" << endl; }
    Obj1(Obj1&&) { cout << "Obj1(Obj1&&)" << endl; }
};

class Obj2
{
public:
    Obj2() { cout << "Obj2()" << endl; }
    Obj2(const Obj1&) { cout << "Obj2(const Obj2&)" << endl; }
    Obj2(Obj2&&) noexcept { cout <<  "Obj2(Obj2&&)" << endl; }
};

int main()
{
    vector<Obj1> v1;
    v1.reserve(2);
    // v1.emplace_back();
    // v1.emplace_back();
    // v1.emplace_back();
    v1.push_back({});
    v1.push_back({});
    v1.push_back({});

    vector<Obj2> v2;
    v2.reserve(2);
    // v2.emplace_back();
    // v2.emplace_back();
    // v2.emplace_back();
    v2.push_back({});
    v2.push_back({});
    v2.push_back({});


    return 0;
}
