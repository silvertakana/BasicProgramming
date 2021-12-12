#include <iostream>

template<class T>
struct TreeNode
{
	T data;
	TreeNode* left = nullptr, * right = nullptr;
	void miror()
	{
		if (left) left->miror();
		if (right) right->miror();
		std::swap(left, right);
	}
	TreeNode* clone() const
	{
		TreeNode* newTree = new TreeNode{ *this };
		if(left)newTree->left = left->clone();
		if(right)newTree->right = right->clone();
		return newTree;
	}
};

int main()
{
	TreeNode<int> root{2};
	((root.left = new TreeNode<int>{7})->left = new TreeNode<int>{ 2 });
	((root.left->right = new TreeNode<int>{ 6 })->left = new TreeNode<int>{ 5 });
	root.left->right->right = new TreeNode<int>{ 11 };
	((root.right = new TreeNode<int>{ 5 })->right = new TreeNode<int>{ 9 })->left = new TreeNode<int>{ 4 };

	TreeNode<int>* newTree = root.clone();
	newTree->miror();
}