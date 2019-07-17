#include <iostream>
#include <chrono>
#include <random>

using namespace std;

int main()
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    cout << e << endl; // range: [e.min(), e.max()]

    // range: [0, 5]
    cout << e() % 6 << endl;
    // 1. Bad quality of randomness
    // 2. Can only provide uniform distribution

    std::uniform_int_distribution<int> distr(0, 5); // range: [0, 5]
    cout << distr(e) << endl;

    std::uniform_real_distribution<double> distrR(0, 5); // range: [0, 5)
    cout << distrR(e) << endl;

    std::poisson_distribution<int> distrP(1.0); // mean
    cout << distrP(e) << endl;

    cout << "normal_distribution:" << endl;
    std::normal_distribution<double>distrN(10.0, 3.0); //mean and standard deviation 
    vector<int>v(20);
    for(int i = 0; i < 800; i++)
    {
        int num = distrN(e); // convert double to int 
        if(num >= 0 && num < 20)
            v[num]++; // E.g., v[10] records number of times 10 appeared
    }

    for (int i = 0; i < 20; i++)
    {
        cout << i << ": " << std::string(v[i], '*') << endl;
    }
    cout << endl;
    
    return 0;
}
