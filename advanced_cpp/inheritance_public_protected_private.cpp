#include <iostream>
using namespace std;

/**
 * Public, Protected, Private
 */

class B {};

class D_priv : private B {};
class D_prot: protected B {};
class D_pub : public B {};

/* Detail Example */

class C
{
public:
    void f_pub() { std::cout << "f_pub is called." << std::endl;}
protected:
    void f_prot() { std::cout << "f_prot is called." << std::endl;}
private:
    void f_priv() { std::cout << "f_priv is called." << std::endl;}
};

class E_pub : public C
{
public:
    void f()
    {
        f_pub();  // OK. E_pub's public function
        f_prot(); // OK. E_pub's protected function
        f_priv(); // Error. C's private function
    }
};

class E_prot : protected C
{
public:
    using C::f_pub;
    void f()
    {
        f_pub();  // OK. E_prot's public function
        f_prot(); // OK. E_prot's protected function
        f_priv(); // Error. C's private function
    }
};

class E_priv: private C
{
public:
    void f()
    {
        f_pub();  // OK. E_priv's public function
        f_prot(); // OK. E_priv's protected function
        f_priv(); // Error. C's private function
    }
};

/**
 * public inheritance: is-a relation, eg., D_pub is-a kind of a B.
 * 
 * private inheritance: similar to has-a relation.
 */
class ring
{
public:
    void tinkle() {}
};

/* Composition */
class dog
{
    ring m_ring;
public:
    void tinkle() { m_ring.tinkle(); } // call forwarding
};

/* Private Inheritance */
class dog2 : private ring
{
public:
    using ring::tinkle;
};

int main(int argc, const char** argv)
{
    E_pub E1;
    E1.f_pub(); // OK. f_pub() is D_prot's public function.
    E_prot E2;
    E2.f_pub(); // Error. f_pub() is D_prot's protected function.
                // unless add a using C::f_pub() statement in class D_prot's public scope

    C* pC = &E1; // OK
    pC = &D2; // Error

    return 0;
}

/**
 * They specifies different access control from the drived class to the base class.
 * 
 * Access Control:
 * 1. None of the derived classes can access anything that is private in B.
 * 2. D_pub inherits public members of B as public and the protected members of B as protected
 * 3. D_priv inherits the public and protected members of B as private.
 * 4. D_prot inherits the public and protected members of B as protected.
 * 
 * Casting:
 * 1. Anyone can cast a D_pub* to B*. D_pub is a special kind of B.
 * 2. D_priv's members and friends can cast a D_priv* to B*.
 * 3. D_prot's members, friends, and children can cast a D_prot* to B*.
 */