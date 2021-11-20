#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "Stack.h"
int PostfixCalculator(const std::string &expression)
{
	const std::string &operators = "+-*/%^";
	ST::Stack<int> stack;
	std::string curentNumber;
	for (size_t i = 0; i <= expression.size(); i++)
	{
		if (expression[i] == ' ' || i == expression.size())
		{
			bool foundExpresion = false;
			for (const auto &i : operators)
			{
				if (i == curentNumber[0])
				{
					//calculate
					int val2 = stack.pop(), val1 = stack.pop(), val3;
					switch (i)
					{
					case '+':
						val3 = val1 + val2;
						break;
					case '-':
					{
						val3 = val1 - val2;
					}
					break;

					case '*':
					{
						val3 = val1 * val2;
					}
					break;

					case '/':
					{
						val3 = val1 / val2;
					}
					break;

					case '^':
					{
						val3 = std::pow(val1, val2);
					}
					break;

					default:
						stack.pop();
						break;
					}
					stack.push(val3);
					foundExpresion = true;
					break;
				}
			}
			if (!foundExpresion)
				stack.push(std::stoi(curentNumber));
			curentNumber = "";
		}
		else
		{
			curentNumber += expression[i];
		}
	}
	return stack.pop();
}
std::string infixConverter(const std::string &input)
{
	struct op
	{
		char name;
		uint8_t importancy;
		bool operator>(const op &op2)
		{
			return importancy > op2.importancy;
		}
		bool operator>=(const op &op2)
		{
			return importancy >= op2.importancy;
		}
		bool operator<(const op &op2)
		{
			return importancy < op2.importancy;
		}
		bool operator<=(const op &op2)
		{
			return importancy <= op2.importancy;
		}
	};

	op operators[]{{'+', 0}, {'-', 0}, {'*', 1}, {'/', 1}, {'^', 2}};

	std::stringstream postfix, curentData;

	auto findOperator = [&](const char &ch)
	{
		for (const auto &i : operators)
		{
			if (i.name == ch)
				return i;
		}
		return op{0, 255ui8};
	};
	auto isGreaterOperator = [&](const char &ch1, const char &ch2)
	{
		if (ch1 == '^')
			return findOperator(ch1) > findOperator(ch2);
		return findOperator(ch1) >= findOperator(ch2);
	};

	ST::Stack<char> myStack;
	for (const auto &i : input)
	{
		if (findOperator(i).importancy != 255ui8) //check if it is an operator
		{
			if (!curentData.str().empty())
			{
				postfix << curentData.str() << " ";
				curentData.str("");
			}
			if (!myStack.isEmpty())
			{
				while (true) // take care of operators
				{
					const char top = myStack.getTopVal();
					if (isGreaterOperator(top, i) && top != '(')
					{
						postfix << myStack.pop() << " ";
					}
					else
						break;
					if (myStack.isEmpty())
						break;
				}
			}
			myStack.push(i);
		}
		else if (i == '(')
		{
			myStack.push(i);
		}
		else if (i == ')')
		{
			if (!curentData.str().empty())
			{
				postfix << curentData.str() << " ";
				curentData.str("");
			}
			while (true)
			{
				const char top = myStack.pop();
				if (top == '(')
					break;
				else
					postfix << top << " ";
			}
		}
		else if (i != ' ')
			curentData << i;
	}
	if (!curentData.str().empty())
	{
		postfix << curentData.str() << " ";
		curentData.str("");
	}
	while (!myStack.isEmpty())
	{
		postfix << myStack.pop() << " ";
	}
	return postfix.str();
}

int main()
{
	while (true)
	{
		std::string expression;
		std::cout << ">> ";
		getline(std::cin, expression);
		auto postfix = infixConverter(expression);
		std::cout << postfix << "\n";
	}
}
// 3 * 6 + ( 4 * ( 3 + 8 ) + 7 )
// 32 * 42 + (61*(3+5)+39) = 1871