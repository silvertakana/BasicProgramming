#include "QueueArray.h"
#include <iostream>
int main()
{
	QueueArray<int,10>a{1,2,3,4,5,6,7,8,9,10};
	
	std::cout << "\n";
	while (!a.isEmpty())
		std::cout << a.pop() << "\n";
}