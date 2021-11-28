#include <iostream>
#include "SinglyLinkedList.h"
template<class T>
T BackfindSLL(ST::SLL<T> sll, T index)
{
	return sll[sll.size() - index];
}
int main()
{
	ST::SLL<int> sll = { 4,0,9,6 };
	std::cout << BackfindSLL(sll, 2) << std::endl;
}