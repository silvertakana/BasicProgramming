#include <iostream>

struct Node
{
	int data;
	Node *next;
};
size_t count(Node *ptr)
{
	size_t counter = 0;
	Node *checkPtr = ptr;
	while (checkPtr->next != ptr)
	{
		checkPtr = checkPtr->next;
		counter++;
	}
	return counter + 1;
}
int main()
{
	Node *firstNode = new Node{0, nullptr};
	Node *beforeNode = firstNode;
	for (size_t i = 1; i < 10; i++)
	{
		Node *n = new Node{(int)i, beforeNode};
		beforeNode = n;
	}
	firstNode->next = beforeNode;

	Node *checkNode = firstNode;
	for (size_t i = 0; i < count(firstNode); i++)
	{
		std::cout << checkNode->data << "\n";
		checkNode = checkNode->next;
	}
}