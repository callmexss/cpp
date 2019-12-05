#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>

#include "../output_container.h"


class Run
{
public:
    virtual void run()
    {
        display();
        randomAccess();
        memberFunc();
        std::cout << std::endl;
    }

private:
    virtual void display() {}
    virtual void randomAccess() {}
    virtual void memberFunc() {}
};

class StringTest : public Run
{
private:
    void display() override { std::cout << m_str << std::endl;}
    void randomAccess() override { std::cout << m_str[1] << std::endl; }
    void memberFunc() override
    {
        std::cout << *m_str.begin() << std::endl;
        std::cout << "end() points to \'\\0\'? " << (*m_str.end() == '\0' ? "True" : "False") << std::endl;
        std::cout << "m_str\'s size: " << m_str.size() << std::endl;
        std::cout << "m_str is empty? " << (m_str.empty() ? "True" : "False") << std::endl;
        std::string new_str = "new string.";
        m_str.swap(new_str);
        m_str.front() = 'N';
        m_str.back() = '!';
        display();
        auto data = m_str.data();
        data[0] = 'f';
        std::cout << m_str.data() << std::endl;
        m_str = "Eat an apple a day.";
        std::cout << m_str.size() << std::endl;
        std::cout << m_str.capacity() << std::endl;
        m_str.reserve(40);
        std::cout << m_str.capacity() << std::endl;
        display();
        m_str.resize(4);
        display();
        m_str.pop_back();
        display();
        m_str.push_back('?');
        display();
        m_str.insert(m_str.begin(), '-');
        display();
        m_str.erase(m_str.begin() + 1, m_str.end());
        display();
        m_str.append("Show");
        display();
    }


private:
    std::string m_str = "default string.";
};

class VectorTest : public Run
{
private:
    void display() override { std::cout << m_vec << std::endl; }
    void randomAccess() override { std::cout << m_vec[1] << std::endl; }

private:
    std::vector<int> m_vec = {1, 2, 3, 4};

};


int main(int argc, char const *argv[])
{
    Run* st = new StringTest;
    Run* vt = new VectorTest;
    st->run();
    vt->run();

    delete st;
    delete vt;
    return 0;
}
