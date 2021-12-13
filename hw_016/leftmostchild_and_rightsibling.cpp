#include <iostream>

namespace ST
{
	namespace Tree
	{
		template <class T>
		struct Node
		{
			T data;
			Node *leftmostchild;
			Node *rightsibling;
			~Node()
			{
				delete leftmostchild;
				delete rightsibling;
			}
			void preOrder(void (*f)(T &, Node<T> &))
			{
				f(data, *this);
				if (leftmostchild != NULL)
				{
					leftmostchild->preOrder(f);
					Node *temp = leftmostchild->rightsibling;
					while (temp != NULL)
					{
						temp->preOrder(f);
						temp = temp->rightsibling;
					}
				}
			}

			void inOrder(void (*f)(T &, Node<T> &))
			{
				if (leftmostchild == NULL)
				{
					f(data, *this);
				}
				else
				{
					leftmostchild->inOrder(f);
					f(data, *this);
					Node *temp = leftmostchild->rightsibling;
					while (temp != NULL)
					{
						temp->inOrder(f);
						temp = temp->rightsibling;
					}
				}
			}

			void postOrder(void (*f)(T &, Node<T> &))
			{
				if (leftmostchild != NULL)
				{
					leftmostchild->postOrder(f);
					Node *temp = leftmostchild->rightsibling;
					while (temp != NULL)
					{
						temp->postOrder(f);
						temp = temp->rightsibling;
					}
				}
				f(data, *this);
			}
		};
	}
}

int main()
{
	using namespace ST::Tree;
	Node<int> tree{2};
	(((tree.leftmostchild = new Node<int>{7})->rightsibling = new Node<int>{5})->leftmostchild = new Node<int>{9})->leftmostchild = new Node<int>{4};
	((((tree.leftmostchild->leftmostchild = new Node<int>{2})->rightsibling = new Node<int>{10})->rightsibling = new Node<int>{6})->leftmostchild = new Node<int>{5})->rightsibling = new Node<int>{11};
	(tree.leftmostchild->rightsibling->rightsibling = new Node<int>{8})->leftmostchild = new Node<int>{3};
	tree.preOrder([](int &data, Node<int> &node) //					pre_order
					  { std::cout << data << std::endl; });
	std::cout << "---------------------" << std::endl;
	tree.postOrder([](int &data, Node<int> &node) //					post_order
						{ std::cout << data << std::endl; });
	std::cout << "---------------------" << std::endl;
	tree.inOrder([](int &data, Node<int> &node) //					post_order
					 { std::cout << data << std::endl; });
}