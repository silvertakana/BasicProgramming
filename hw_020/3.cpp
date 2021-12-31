#include <iostream>
struct Tnode
{
	int key;
	Tnode* left = nullptr, * right = nullptr;
	size_t Diam()
	{
		size_t leftDepth = 0, rightDepth = 0, leftDiam = 0, rightDiam = 0;
		if (left)
		{
			leftDepth = left->depth();
			leftDiam = left->Diam();
		}
		if (right)
		{
			rightDepth = right->depth();
			rightDiam = right->Diam();
		}
		return std::max(1 + leftDepth + rightDepth, std::max(leftDiam, rightDiam));
	}
	size_t depth()
	{
		size_t leftDepth = 0, rightDepth = 0;
		if (left) leftDepth = left->depth();
		if (right) rightDepth = right->depth();
		return 1 + std::max(leftDepth, rightDepth);
	}
};
int main()
{
	Tnode* root = new Tnode{1};
	{
		root->left = new Tnode{ 2 };
		{
			root->left->left = new Tnode{ 4 };
			{
				root->left->left->right = new Tnode{ 6 };
			}
		}
		root->right = new Tnode{ 3 };
		{
			root->right->left = new Tnode{ 5 };
			{
				root->right->left->right = new Tnode{ 7 };
			}
		}
	}
	std::cout << std::boolalpha << root->Diam() << std::endl;
}