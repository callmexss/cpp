#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <forward_list>

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
    void memberFunc() override
    {
        std::cout << *m_vec.begin() << std::endl;
        std::cout << *m_vec.end() << std::endl;
        std::cout << m_vec.size() << std::endl;
    }

private:
    std::vector<int> m_vec = {1, 2, 3, 4};

};

class DequeTest : public Run
{
public:
    void memberFunc() override
    {
        m_deque.push_front(1);
        std::cout << m_deque.front() << std::endl;
        std::cout << m_deque.back() << std::endl;
        std::cout << m_deque.size() << std::endl;
        std::cout << m_deque.empty() << std::endl;
    }

private:
    std::deque<int> m_deque{1, 2, 3, 4, 5};

};

class ListTest : public Run
{
public:
    void memberFunc() override
    {
        std::list<int> new_list{4, 3, 2, 1};
        m_list.merge(new_list);
        m_list.sort();
        while (!m_list.empty())
        {
            std::cout << m_list.front() << std::endl;
            m_list.pop_front();
        }
    }

private:
    std::list<int> m_list{1, 2, 3, 4};
};

class ForwardListTest : public Run
{
public:
    void display() override { std::cout << m_flist << std::endl; }
    void memberFunc() override
    {
        std::forward_list<int> new_list{3, 2, 1};
        m_flist.merge(new_list);
        m_flist.push_front(5);
        m_flist.sort();
        display();
    }

private:
    std::forward_list<int> m_flist{1, 2, 3, 4};
};

class QueueTest : public Run
{
public:
    void memberFunc() override
    {
        for (int i = 0; i < 10; ++i)
        {
            m_queue.push(i);
        }

        while (!m_queue.empty())
        {
            std::cout << m_queue.front() << std::endl;
            m_queue.pop();
        }

    }

private:
    std::queue<int> m_queue;

};

class StackTest : public Run
{
public:
    void memberFunc() override
    {
        for (int i = 0; i < 10; ++i)
        {
            m_stack.push(i);
        }

        while (!m_stack.empty())
        {
            std::cout << m_stack.top() << std::endl;
            m_stack.pop();
        }

    }

private:
    std::stack<int> m_stack;

};


int main(int argc, char const *argv[])
{
    Run* st = new StringTest;
    Run* vt = new VectorTest;
    Run* dt = new DequeTest;
    Run* lt = new ListTest;
    Run* ft = new ForwardListTest;
    Run* qt = new QueueTest;
    Run* sat = new StackTest;
    st->run();
    vt->run();
    dt->run();
    lt->run();
    ft->run();
    qt->run();
    sat->run();

    delete st;
    delete vt;
    delete dt;
    delete lt;
    delete ft;
    delete qt;
    delete sat;
    return 0;
}
