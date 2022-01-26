#include <iostream>
#include <cmath>

struct TreeNode
{
	int key;
	TreeNode* left = nullptr, * right = nullptr;
	int height = 0;
	void printInorder()
	{
		if (left) left->printInorder();
		printf("%i ", key);
		if (right) right->printInorder();
	}
	void printMirrorInorder()
	{
		if (right) right->printInorder();
		printf("%i ", key);
		if (left) left->printInorder();
	}
	bool search(const int& target)
	{
		if (target > key && right)
		{
			return right->search(target);
		}
		else if (target < key && left)
		{
			return left->search(target);
		}
		else if (target == key) return true;
		else					return false;
	}
	TreeNode* findMin()
	{
		if (left) return left->findMin();
		else return this;
	}
	TreeNode* findMax()
	{
		if (right) return right->findMax();
		else return this;
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
		if (node->key < key)
		{
			if (left) left = left->insert(node);
			else left = node;
		}
		else if (node->key > key)
		{
			if (right) right = right->insert(node);
			else right = node;
		}
		
		return makeBalance();
	}
	TreeNode* insert(const int& newKey)
	{
		return insert( new TreeNode{ newKey } );
	}

};
TreeNode* del(TreeNode* T, float x)
{
	TreeNode* tmp;
	if (T == nullptr) printf("not found");
	else if (x < T->key) T->left = T->left? del(T->left, x) : nullptr;
	else if (x > T->key) T->right = T->right ? del(T->right, x) : nullptr;
	else 
		if (T->left && T->right)
		{
			tmp = T->right->findMin();
			T->key = tmp->key;
			T->right = del(T->right, T->key);
		}
		else
		{
			tmp = T;
			if (T->left == nullptr)
				T = T->right;
			else 
				T = T->left;
			free(tmp);
		}

	return T? T->makeBalance() : nullptr;
}
int main()
{
	int test[] = { 1,8,3,6,5,4,7,2,0,-5,-10 };

	TreeNode* tree = new TreeNode { test[0] };

	for (size_t i = 1;i < sizeof(test)/sizeof(int);i++)
	{
		tree = tree->insert(test[i]);
	}
	tree->printInorder();
	tree = del(tree, -5);
	printf("\n");
	tree->printInorder();
}