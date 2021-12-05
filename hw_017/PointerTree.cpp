#include <iostream>

namespace ST
{
	namespace BinaryTree
	{
		template <class T>
		struct Node
		{
			T data;
			Node *left = nullptr, *right = nullptr;
			Node(const T &data)
			{
				this->data = data;
			}
			size_t countNode()
			{
				static size_t nodeCounts = 1; //node counts strart from 0 to account for the root node.
				if (left)
				{
					nodeCounts++; //test if the left node exist, if so then increment nodeCounts by 1.
					left->countNode();
				} //using recursion to get left node
				if (right)
				{
					nodeCounts++; //test if the right node exist, if so then increment nodeCounts by 1.
					right->countNode();
				} //using recursion to get left node
				return nodeCounts;
			}

		private:
			size_t m_depth_recursion(size_t d) //using recursion to find the max depth
			{
				static size_t maxDepth = 1;
				if (d > maxDepth) //check if current depth is greater than max depth, if so then update it
					maxDepth = d;
				if (left)
				{
					left->m_depth_recursion(d + 1);
				}
				if (right)
				{
					right->m_depth_recursion(d + 1);
				}
				return maxDepth;
			}

		public:
			size_t depth() // calcualte how many layer does this tree have.
			{
				return m_depth_recursion(1);
			}
			bool isLeaf()
			{
				return !left && !right; //check if the left node and right node both don't exist
			}
			void preOrder(void (*f)(T &, Node<T> &))
			{
				f(data, *this);
				if (left)
					left->preOrder(f);
				if (right)
					right->preOrder(f);
			}
			void postOrder(void (*f)(T &, Node<T> &))
			{
				if (left)
					left->postOrder(f);
				if (right)
					right->postOrder(f);
				f(data, *this);
			}
			void inOrder(void (*f)(T &, Node<T> &))
			{
				if (left)
					left->inOrder(f);
				f(data, *this);
				if (right)
					right->inOrder(f);
			}
		};
	}
}

int main()
{
	ST::BinaryTree::Node<int> tree{0};
	auto *currentNode = &tree;
	for (size_t i = 1; i < 10; i++)
	{
		auto n = new ST::BinaryTree::Node<int>{(int)i};
		while (currentNode->right && currentNode->left)
		{
			if (rand() > RAND_MAX / 2)
			{
				currentNode = currentNode->right;
			}
			else
			{
				currentNode = currentNode->left;
			}
		}
		if (!(currentNode->right || currentNode->left))
		{
			if (rand() > RAND_MAX / 2)
			{
				currentNode->right = n;
			}
			else
			{
				currentNode->left = n;
			}
		}
		else if (currentNode->right)
		{
			currentNode->left = n;
		}
		else if (currentNode->left)
		{
			currentNode->right = n;
		}
		currentNode = &tree;
	}
	tree.preOrder([](int &data, ST::BinaryTree::Node<int> &node)
					  { std::cout << data << std::endl; });
	std::cout << "-----------------------\n";
	std::cout << tree.countNode() << std::endl;

	std::cout << "-----------------------\n";
	std::cout << tree.depth() << std::endl;
}