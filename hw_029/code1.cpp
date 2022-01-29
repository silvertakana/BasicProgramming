#include <cmath>
#include <iostream>

struct TreeNode
{
	int info;
	TreeNode* left;
	TreeNode* right;
	int height = 0;
	size_t getHeight()
	{
		if (!this) return 0;
		size_t h = 1;
		if (left) h = left->getHeight() + 1;
		if (right) h = std::max(right->getHeight() + 1, h);
		return h;
	}
	bool isAVL()
	{
		if (left ? left->isAVL() : true && right ? right->isAVL() : true)
			if (left ? left->info < info : true && right ? right->info > info : true)
				if(std::abs((int)left->getHeight() - (int)right->getHeight()) <= 1 )
					return true;
		return false;
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
	void printInorder()
	{
		if (left) left->printInorder();
		printf("%i ", info);
		if (right) right->printInorder();
	}
};

int main()
{
	{
		int test[] = { 1,2,5,-1,3,4 };

		TreeNode* tree = new TreeNode { test[0] };

		for (size_t i = 1; i < sizeof(test) / sizeof(int); i++)
		{
			tree->insert(test[i]);
		}
		std::cout << std::boolalpha << tree->isAVL() << std::endl;
	}
	{
		int test[] = { 2,1,3,4,5,-1 };

		TreeNode* tree = new TreeNode { test[0] };

		for (size_t i = 1; i < sizeof(test) / sizeof(int); i++)
		{
			tree->insert(test[i]);
		}

		std::cout << std::boolalpha << tree->isAVL() << std::endl;
	}
}
