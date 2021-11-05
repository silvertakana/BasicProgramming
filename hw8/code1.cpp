#include "LinkedList.h"
int main()
{
	ST::LinkedList<int> ll;
	
	for (size_t i = 5; i > 0; i--)
	{
		ll.pushFirst(i);
	}
	for (const auto& i : ll)
	{
		std::cout << i << "\n";
	}
	
	for (size_t i = 0; i < 5; i++)
	{
		ll.popFirst();
	}
	for (const auto &i : ll)
	{
		std::cout << i << "\n";
	}
}