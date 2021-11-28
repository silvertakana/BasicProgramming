#include "SinglyLinkedList.h"
#include "Stack.h"

bool checkPalindrome(ST::SLL<char> sll)
{
	ST::Stack<char> palinstack;
	for (const auto& i : sll)
	{
		palinstack.push(i);
	}
	for (const auto& i : sll)
	{
		if (i != palinstack.pop()) return false;
	}
	return true;
}
int main()
{
	ST::SLL<char> sll = "ohello";
	std::cout << std::boolalpha << checkPalindrome(sll) << std::endl;
}