#include <iostream>

namespace ST {
	namespace Tree {
		template<class T>
		struct Node
		{
			T data;
			Node* leftmostchild;
			Node* rightsibling;
			~Node()
			{
				delete leftmostchild;
				delete rightsibling;
			}
			void preOrder(void(*f)(T&, Node<T>&))
			{
				f(this->data, *this);
				if (leftmostchild)leftmostchild->preOrder(f);
				if (rightsibling)rightsibling->preOrder(f);
			}
			void postOrder(void(*f)(T&, Node<T>&))
			{
				if (leftmostchild)leftmostchild->postOrder(f);
				f(this->data, *this);
				if (rightsibling)rightsibling->postOrder(f);
			}
		};
	}
}

int main()
{
	using namespace ST::Tree;
	Node<int> tree{ 2 };
	(((tree.leftmostchild = new Node<int>{ 7 })->rightsibling = new Node<int>{ 5 })->leftmostchild = new Node<int>{ 9 })->leftmostchild = new Node<int>{ 4 };
	((((tree.leftmostchild->leftmostchild = new Node<int>{ 2 })->rightsibling = new Node<int>{ 10 })->rightsibling = new Node<int>{ 6 })->leftmostchild = new Node<int>{ 5 })->rightsibling = new Node<int>{ 11 };

	tree.preOrder([](int& data, Node<int>& node)	//					pre_order
					  {
						  std::cout << data << std::endl;
					  });
	std::cout << "---------------------" << std::endl;
	tree.postOrder([](int& data, Node<int>& node)//					post_order
						{
							std::cout << data << std::endl;
						});
}