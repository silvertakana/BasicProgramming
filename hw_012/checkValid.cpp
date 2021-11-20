#include <string>
#include "Stack.h"

bool checkValidBrackets(const std::string &expression)
{
	std::string OpenBrackets = "{[(", CloseBrackets = "}])";
	ST::Stack<char> brackets;
	for (const auto &i : expression)
	{
		if (OpenBrackets.find(i) != std::string::npos)
			brackets.push(i);
		else if (CloseBrackets.find(i) != std::string::npos)
			if (brackets.isEmpty() || CloseBrackets.find(i) != OpenBrackets.find(brackets.pop()))
				return false;
	}
	if (brackets.size() == 0)
		return true;
	return false;
}

int main()
{
	std::cout << std::boolalpha << checkValidBrackets("(){}[]({[]})") << std::endl;
}