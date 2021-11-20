#include "Stack.h"
#include <iostream>

bool isPalindrome(const char* input)
{
	ST::Stack<char> palindromeStack;

	for (size_t i = 0; i < strlen(input); i++)
		palindromeStack.push(input[i]);
	for (size_t i = 0; i < strlen(input); i++)
		if(input[i] != palindromeStack.pop()) return false;
	return true;
}

int main()
{
	std::cout <<std::boolalpha<< isPalindrome("able was i ere i saw elba") << std::endl;
}