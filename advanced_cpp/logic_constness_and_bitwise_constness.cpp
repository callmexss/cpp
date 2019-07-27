#include <vector>

using namespace std;

class BigArray
{
    vector<int> v; // huge vector
    // int accessCounger;
    mutable int accessCounger; // can be changed in a const function

    int* v2; // another int array

public:
    int getItem(int index) const
    {
        accessCounger++;
        // Another way if mutable not support by some compile
        // use this only when you have to
        // const_cast<BigArray*>(this)->accessCounger++;
        return v[index];
    }

    // v2 was not directly changed
    void setV2Item(int index, int x) // const
    {
        *(v2+index) = x;
    }

    // Quic
    const int* const func(const int* const& p) const;
};

int main(int argc, char const *argv[])
{
    BigArray b;
    return 0;
}
