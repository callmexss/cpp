#include <iostream>
#include <vector>

namespace Myfunc
{

template <typename T>
void pringVec(const std::vector<T> &v)
{
    for (auto const &val : v)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

} // namespace Myfunc
