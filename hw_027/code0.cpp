#include <iostream>

struct TreeNode
{
	int key;
	TreeNode* left = nullptr, * right = nullptr;
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
	void insert(const int& newKey)
	{
		if (newKey < key)
		{
			if (left) left->insert(newKey);
			else left = new TreeNode { newKey };
		}
		else if (newKey > key)
		{
			if (right) right->insert(newKey);
			else right = new TreeNode { newKey };
		}
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
};
TreeNode* del(TreeNode* T, float x)
{
	TreeNode* tmp;
	if (T == NULL) printf("not found");
	else if (x < T->key) T->left = del(T->left, x);
	else if (x > T->key) T->right = del(T->right, x);
	else /*Tìm được phần tử cần xóa */
		if (T->left && T->right)
		{/* Tình huống 4 */
			tmp = T->right->findMin();
			T->key = tmp->key;
			T->right = del(T->right, T->key);
		}
		else
		{/* có một con hoặc không có con*/
			tmp = T;
			if (T->left == NULL)/* chỉ có con phải */
				T = T->right;
			else /* chỉ có con trái */
				T = T->left;
			free(tmp);
		}
	return(T);
}
int main()
{
	int test[] = { 1,8,3,6,5,4,7,2,0,-5,-10 };

	TreeNode tree{test[0]};

	for (size_t i = 1;i < sizeof(test)/sizeof(int);i++)
	{
		tree.insert(test[i]);
	}
	tree.printInorder();
	printf("\n");
	std::cout << std::boolalpha << tree.search(5) << "\n";
	std::cout << std::boolalpha << tree.search(13) << "\n";
	std::cout << std::boolalpha << tree.findMin()->key << "\n";
	std::cout << std::boolalpha << tree.findMax()->key << "\n";
	del(&tree, 6);
	printf("\n");
	tree.printInorder();

}