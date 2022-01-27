#include <cmath>
#include <iostream>

struct TreeNode
{
    int info;
    TreeNode* left;
    TreeNode* right;
    bool search(int target)
    {
        TreeNode* crntNode = this;
        while (crntNode != nullptr)
        {
            if (crntNode->info == target)
                return true;
            else if (crntNode->info > target)
                crntNode = crntNode->left;
            else if (crntNode->info < target)
                crntNode = crntNode->right;
        }
        return false;
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
    std::cout << std::boolalpha << tree.search(0) << std::endl;
}