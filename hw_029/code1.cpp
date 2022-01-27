#include <cmath>
#include <iostream>

struct TreeNode
{
    int info;
    TreeNode* left;
    TreeNode* right;
	int height = 0;
    bool isAVL()
    {
		auto getHeight = [](TreeNode* node) { return node ? node->height : -1; };

		return abs(getHeight(left) - getHeight(right)) <= 1;
    }
	TreeNode* rightRotate()
	{
		auto getHeight = [](TreeNode* node) { return node ? node->height : -1; };

		TreeNode* k2 = left;
		TreeNode* B = k2->right;

		//rotate
		k2->right = this;
		left = B;

		//update height;
		height = std::max(getHeight(left), getHeight(right)) + 1;
		k2->height = std::max(getHeight(k2->left), getHeight(k2->right)) + 1;
		return k2;
	}
	TreeNode* leftRotate()
	{
		auto getHeight = [](TreeNode* node) { return node ? node->height : -1; };

		TreeNode* k1 = right;
		TreeNode* B = k1->left;

		//rotate
		k1->left = this;
		right = B;

		//update height;
		height = std::max(getHeight(left), getHeight(right)) + 1;
		k1->height = std::max(getHeight(k1->left), getHeight(k1->right)) + 1;
		return k1;
	}
	TreeNode* makeBalance()
	{
		auto getHeight = [](TreeNode* node) { return node ? node->height : -1; };
		auto getBalance = [getHeight](TreeNode* node) { return std::max(getHeight(node->left), getHeight(node->right)) + 1; };
		height = getBalance(this);
		int heightDiff = getHeight(left) - getHeight(right);

		if (heightDiff > 1 and getBalance(left) >= 0)
		{
			return rightRotate();
		}

		else if (heightDiff > 1 and getBalance(left) < 0)
		{
			left = left->leftRotate();
			return rightRotate();
		}
		else if (heightDiff < -1 and getBalance(right) <= 0)
		{
			return leftRotate();
		}
		else if (heightDiff < -1 and getBalance(right) > 0)
		{
			right = right->rightRotate();
			return leftRotate();
		}
		return this;
	}
	TreeNode* insert(TreeNode* node)
	{
		if (node->info < info)
		{
			if (left) left = left->insert(node);
			else left = node;
		}
		else if (node->info > info)
		{
			if (right) right = right->insert(node);
			else right = node;
		}
		height++;
		return this;
	}
	TreeNode* insert(const int& newinfo)
	{
		return insert(new TreeNode { newinfo });
	}
};

int main()
{
    int test[] = { 1,8,3,6,5,4,7,2,0,-5,-10,11 };

    TreeNode* tree = new TreeNode{ test[0] };

    for (size_t i = 1; i < sizeof(test) / sizeof(int); i++)
    {
        tree->insert(test[i]);
    }
	std::cout << std::boolalpha << tree->isAVL() << std::endl;
	tree = tree->makeBalance();
	std::cout << std::boolalpha << tree->isAVL() << std::endl;
}