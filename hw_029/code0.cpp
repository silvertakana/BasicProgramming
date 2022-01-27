#include <cmath>
#include <cstdio>

struct TreeNode
{
    int info;
    TreeNode* left;
    TreeNode* right;
    int max_odd()
    {
        if (!this) return INT_MIN;
        int maxOdd;
        if (info % 2)
        {
            maxOdd = std::fmax(info, right->max_odd());
        }
        else
        {
            maxOdd = std::fmax(INT_MIN, right->max_odd());
            if(maxOdd == INT_MIN) maxOdd = std::fmax(maxOdd, left->max_odd());
        }
        return maxOdd;
    }
    void insert(TreeNode* node)
    {
        if (node->info < info)
        {
            if (left) left->insert(node);
            else left = node;
        }
        else if (node->info > info)
        {
            if (right) right->insert(node);
            else right = node;
        }
    }
    void insert(const int& newKey)
    {
        insert(new TreeNode { newKey });
    }
};

int main()
{
    int test[] = { 1,8,3,6,5,4,7,2,0,-5,-10,11 };

    TreeNode tree { test[0] };

    for (size_t i = 1; i < sizeof(test) / sizeof(int); i++)
    {
        tree.insert(test[i]);
    }
    printf("%i", tree.max_odd());
}