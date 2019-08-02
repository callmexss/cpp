/**
 * Handle self - assignment in operator=
 * Operator overload: exploite people's intuition and reduce their learning curve
 */

// class dog {};
// dog dd;
// dd = dd; //Looks silly
// dogs[i]=dogs[j];//looks 1ess silly

/* Implementing Assignment Operator */
class collar
{
};

/* Self Assignment */
// class dog
// {
//     collar *pCollar;
//     dog &operator=(const dog &rhs)
//     {
//         delete pCollar;
//         pCollar = new collar(*rhs.pCollar);
//         return *this;
//     }
// };

/* If Exception Throw by new collar */
// class dog
// {
//     collar *pCollar;
//     dog &operator=(const dog &rhs)
//     {
//         if (this == &rhs)
//             return *this;
//         delete pCollar;
//         pCollar = new collar(*rhs.pCollar);
//         return *this;
//     }
// };

/* Solution 1 */
class dog
{
    collar *pCollar;
    dog &operator=(const dog &rhs)
    {
        if (this == &rhs)
            return *this;
        collar *pOrigCollar = pCollar;
        pCollar = new collar(*rhs.pCollar);
        delete pOrigCollar;
        return *this;
    }
};

/* Solution 2: Delegation*/
class dog1
{
    collar *pCollar;
    dog1 &operator=(const dog1 &rhs)
    {
        *pCollar = *rhs.pCollar; //member by member copying of collars or
                                 //call collar's operator=
        return *this;
    }
};

#include <iostream>
    using namespace std;

    int main()
    {

        system("pause");
        return 0;
    }
