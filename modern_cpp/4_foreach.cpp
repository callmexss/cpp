#include <vector>
#include <iostream>
#include <string>

#include "../myfunc.h"

using namespace std;

/**
 * 4. foreach
 */

// C++03:
void c03()
{
    vector<int> v{1, 2, 3 ,4};
    for (vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr)
        cout << (*itr) << " ";
    cout << endl;
}

// C++11
void c11()
{
    vector<int> v{1, 2, 3 ,4};
    for (int i: v) // works on any class that has begin and end
    {
        cout << i << " "; // readonly access
    }
    cout << endl;


    for (int &i : v)
    {
        i++; // changes the values in v
    }

    Myfunc::pringVec(v);
}

int main(int argc, char const *argv[])
{
    c03();
    c11();
    return 0;
}
