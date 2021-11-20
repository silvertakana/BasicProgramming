#include "Queue.h"
#include <iostream>
uint64_t stringToInt(const char* str)
{
	ST::Queue<char> myQueue;
	for (size_t i = 0; i < strlen(str);i++)
	{
		const char& currentchar = str[i];
		if (!(currentchar <= 57ui8 && currentchar >= 48ui8)) throw std::exception("input string isn't a number-string");

		myQueue.push(currentchar - 48ui8);
	}
	uint64_t returnVal = 0ui64;
	while (!myQueue.isEmpty())
	{
		returnVal = returnVal * 10ui8 + myQueue.pop();
	}
	return returnVal;
}

int main()
{
	std::cout << stringToInt("2048")+5 << "\n";
}