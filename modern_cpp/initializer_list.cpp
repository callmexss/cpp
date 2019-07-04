#include <vector>
#include <iostream>
#include <initializer_list> // Define your own initializer_list constructor

#include "../myfunc.h"
/**
 * 1. Initializer List
 */

using namespace std;

/**
 * C++ 03
 */
void c03()
{
    // C++ 03 initializer list
    int arr[4] = {3, 4, 2, 5};

    vector<int> v;
    v.push_back(3);
    v.push_back(4);
    v.push_back(2);
    v.push_back(5);
}

/**
 * C++ 11
 */
void c11()
{
    // C++ 11 extended the support
    vector<int> v2 = {3, 4, 2, 5}; // Calling initializer_list constructor
    // All the relevent STL containers have heen updated to accept initializer_list
}


class XuVector
{
public:
    XuVector(const initializer_list<int> &v)
    {
        for (initializer_list<int>::iterator iter = v.begin(); iter != v.end(); ++iter)
        {
            m_vec.push_back(*iter);
        }
    }

    int size() const
    {
        return m_vec.size();
    }

    int operator[](const int& i) const
    {
        return m_vec[i];
    }

private:
    vector<int> m_vec;
};

void printXuVec(const XuVector& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}


int main(int argc, char const *argv[])
{
    /* code */
    XuVector v = {0, 2, 3, 4};
    printXuVec(v);
    XuVector v1{0, 2, 3, 4}; // effectively the same
    printXuVec(v1);
    return 0;
}
