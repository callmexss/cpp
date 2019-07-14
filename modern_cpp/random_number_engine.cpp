#include <random>
#include <iostream>
#include <sstream>
#include <chrono>
#include <vector>
#include <algorithm>


using namespace std;

/* Random Engine:
 *    Stateful generator that generates random values within predefined min and max.
 *    Not truely random--pseudorandom
 */

void printRandom(default_random_engine e)
{
    for (int i = 0; i < 10; i++)
    {
        cout << e() << " ";
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    std::default_random_engine eng;
    cout << "Min: " << eng.min() << endl;
    cout << "Max: " << eng.max() << endl;

    cout << eng() << endl;
    cout << eng() << endl;

    std::stringstream state;
    state << eng; // Save the current state

    cout << eng() << endl;
    cout << eng() << endl;

    state >> eng; // Restore the state

    cout << eng() << endl;
    cout << eng() << endl;

    std::default_random_engine e;
    std::default_random_engine e2;

    printRandom(e);
    printRandom(e2);

    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine e3(seed);
    printRandom(e3);

    e.seed();
    e.seed(109);
    e2.seed(109);
    if (e == e2)
        cout << "e and e2 have the same state" << endl;

    vector<int> d{1, 2, 3 ,4, 5, 6, 7, 8, 9};
    std::shuffle(d.begin(), d.end(), std::default_random_engine());
    for (int i : d)
        cout << i << " ";
    cout << endl;
    return 0;
}
