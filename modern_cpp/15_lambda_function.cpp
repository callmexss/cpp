#include <iostream>
#include <vector>
using namespace std;

/**
 * 15. lambda function
 */

template <typename func>
void filter(func f, vector<int> arr)
{
    for (auto i : arr)
    {
        if (f(i))
        {
            cout << i << endl;
        }
    }
}

int main()
{
    cout << [](int x, int y) { return x + y; }(3, 4) << endl; // output: 7
    auto f = [](int x, int y) { return x + y; };
    f(3, 4); // output: 7

    vector<int> vec{1, 4, 1, 4, 7, 3, 2};
    filter([](int i) { return i & 1; }, vec);

    vector<int> v = {1, 2, 3, 4, 5, 6};

    filter([](int x) { return (x > 3); }, v);          // output:456
    filter([](int x) { return (x > 2 && x < 5); }, v); //output:3 4

    int y = 4;
    filter([&](int x) { return (x > y); }, v); // output:56
                                               //Note:[&] tells compiler that we want variable capture

    return 0;
}
