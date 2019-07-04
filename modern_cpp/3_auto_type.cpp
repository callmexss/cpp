#include <vector>

#include "../myfunc.h"

using namespace std;

/**
 * 3. auto type
 */
vector<int> vec = {2, 3, 4, 5};

// C++ 03
void c03()
{
    vector<int> m_vec;
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        m_vec.push_back(*it);
    }
    Myfunc::pringVec(m_vec);
}

// C++ 11
void c11()
{
    vector<int> m_vec;
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        m_vec.push_back(*it);
    }
    Myfunc::pringVec(m_vec);

    auto a = 6;
    auto b = 9.6;
    auto c = a;
    // TODO: type info ?
    // IDE becomes more important
}


int main(int argc, char const *argv[])
{
    c03();
    c11();
    return 0;
}
