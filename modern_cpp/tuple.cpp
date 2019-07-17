#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>


using namespace std;

int main()
{
    std::pair<int, string> p = make_pair(23, "hello");
    cout << p.first << " " << p.second << endl;

    tuple<int, string, char> t(32, "Penny wise", 'a');
    cout << get<0>(t) << endl;
    cout << get<1>(t) << endl;
    cout << get<2>(t) << endl;

    get<1>(t) = "Pound follish";
    cout << get<1>(t) << endl;
    string &s = get<1>(t);
    s = "Patience is virtue"; // returns a reference, changes t.
    cout << get<1>(t) << endl;

    // get<3>(t); // out of range
    vector<int> v(3);
    v[1] = 3; // returns a reference, changes v[1]'s value.

    // int i = 1; // invalid, copile error, i must be compile time constant.
    constexpr int i = 1;
    get<i>(t);
    
    tuple<int, string, char> t2; // every element will call its default constructor
    t2 = tuple<int, string, char>(12, "Curiosity kills the cat", 'd');
    t2 = make_tuple(12, "Curiosity kills the cat", 'd');

    if (t > t2) // lexicographical comparison
    {
        cout << "t is larger than t2" << endl; 
        t = t2; // member by member copying
    }

    // Tuple can store references
    string st = "In for a penny";
    tuple<string&> t3(st);
    t3 = make_tuple(ref(st));
    get<0>(t3) = "In for a pound"; // st contains "In for a pound"
    t2 = make_tuple(12, "Curiosity kills a cat", 'd');
    int x;
    string y;
    char z;
    make_tuple(ref(x), ref(y), ref(z)) = t2;
    x = 0;
    cout << get<0>(t2) << endl;
    cout << get<1>(t2) << endl;
    cout << get<2>(t2) << endl;


    std::tie(x, y, z) = t2; // Doing the same thing
    std::tie(x, std::ignore, z) = t2;

    auto t4 = std::tuple_cat(t2, t3); // t4 is a tuple<int, string, char, string>

    // type traits
    cout << std::tuple_size<decltype(t4)>::value << endl; // 4
    std::tuple_element<1, decltype(t4)>::type d; // d is a string
    
    return 0;
}
