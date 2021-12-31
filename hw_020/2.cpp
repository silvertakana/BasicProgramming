#include <iostream>
#include <string>
struct Tnode
{
	int key;
	Tnode* left = nullptr, * right = nullptr;
	~Tnode() {
		delete left ;
		delete right;
	}
	bool isOmetric() const 
	{
		std::cout << left->Structure(0) << std::endl;
		std::cout << right->Structure(0) << std::endl;
		return left->Structure(0) == right->Structure(0);
	}
private:
	std::string Structure(const size_t& depth) const
	{
		std::string code = "";
		if (left ) { code += std::to_string(2 * depth)     + left ->Structure(depth + 1); }
		if (right) { code += std::to_string(2 * depth + 1) + right->Structure(depth + 1); }
		return code;
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
	std::cout << std::boolalpha << root->isOmetric() << std::endl;
}