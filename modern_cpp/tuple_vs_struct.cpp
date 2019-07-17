#include <iostream>
#include <string>
#include <tuple>
#include <map>
#include <unordered_map>

using namespace std;


tuple<string, int> getNameAge()
{
    // ...
    return make_tuple("Jobs", 32);
}

long long fib(int n)
{
    if (n <= 1)
        return n;

    int a = 1; // 1
    int b = 0; // 0

    // start from 2 .. n
    for (int i = 2; i <= n; i++)
    {
        tie(a, b) = make_tuple(a + b, a);
    }
    return a;
}

int main()
{
    // Structure is more readable.
    // tuple is more convenient.
    struct Person { string name; int age; };
    tuple<string, int> t{"John", 18};

    Person bob = {"Bob", 32};

    cout << bob.name << " " << bob.age << endl;
    cout << get<0>(t) << " " << get<1>(t) << endl;

    // As a one-time only structure to transfer a group of data.
    string name;
    int age;
    tie(name, age) = getNameAge();

    // Comparison of tuples
    tuple<int, int, int> time1{0, 0, 1}, time2{0, 2, 1}; // hours, minutes, seconds
    if (time1 < time2)
        cout << "time2 is a later time" << endl;

    map<tuple<int, char, float>, string> m;
    m[make_tuple(2, 'a', 2.3)] = "Faith will move the mountains.";
    // unordered_map<tuple<int, char, float>, string> hashtable;
    
    int a = 1, b = 2, c = 3;
    tie(b, c, a) = make_tuple(a, b, c);
    cout << a << b << c << endl;

    cout << a << b << endl;
    tie(a, b) = make_tuple(b, a);
    cout << a << b << endl;

    for (int i = 0; i < 20; i++)
        cout << fib(i) << " ";
    cout << endl;

    return 0;
}
