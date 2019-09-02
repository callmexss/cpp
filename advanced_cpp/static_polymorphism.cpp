#include <iostream>
#include <vector>

using namespace std;

/*
 * Static Polymorphism
 */

// (Dynamic) Polymorphism:

struct TreeNode
{
    TreeNode *left, *right;
};

class Generic_Parser
{
public:
    void parse_preorder(TreeNode *node)
    {
        if (node)
        {
            process_node(node);
            parse_preorder(node->left);
            parse_preorder(node->right);
        }
    }

private:
    virtual void process_node(TreeNode *node) {}
};

class EmployeeChart_Parser : public Generic_Parser
{
private:
    void process_node(TreeNode *node)
    {
        cout << "Customized process_node() for EmployeeChart." << endl;
    }
};

// TMP: Template Metaprogramming
template <typename T>
class Generic_Parser_T
{
public:
    void parse_preorder(TreeNode *node)
    {
        if (node)
        {
            process_node(node);
            parse_preorder(node->left);
            parse_preorder(node->right);
        }
    }

    void process_node(TreeNode *node)
    {
        static_cast<T*>(this)->process_node(node);
    }
};

class EmployeeChart_Parser_T : public Generic_Parser_T<EmployeeChart_Parser_T>
{
public:
    void process_node(TreeNode *node)
    {
        cout << "Customized process_node() for EmployeeChart_T." << endl;
    }
};

// Tradeoff: Improve performance while increase the image size.
// The balance of the image size and performance.
class MilitaryChart_Parser_T : public Generic_Parser_T<MilitaryChart_Parser_T>
{
public:
    void parse_preorder(TreeNode *node)
    {
        if (node)
        {
            process_node(node);
            parse_preorder(node->left);
            parse_preorder(node->right);
        }
    }
    void process_node(TreeNode *node)
    {
        cout << "Customized process_node() for MilitaryChart_T." << endl;
    }

};

// Curiously recurring template pattern (static polymorphism, simulated polymorphism)

// Generalized Static Polymorphism
template <typename T>
T Max(vector<T> v)
{
    T max = v[0];
    for (typename std::vector<T>::iterator it = v.begin(); it != v.end(); ++it)
    {
        if (*it > max)
        {
            max = *it;
        }
    }
    return max;
}

int main(int argc, const char **argv)
{
    TreeNode *root = new TreeNode();
    EmployeeChart_Parser ep;
    ep.parse_preorder(root);

    EmployeeChart_Parser_T ept;
    ept.parse_preorder(root);

    MilitaryChart_Parser_T mpt;
    mpt.parse_preorder(root);
    delete root;

    vector<int> v{1, 2, 3 ,4, 5};
    cout << Max(v) << endl;

    return 0;
}

/*
 * 1. is-a relationship between base class and derived class
 * 2. Base class defines a "generic" algorithm that's used by derived class
 * 3. The "generic" algorithm is customized by the drived class
 */
