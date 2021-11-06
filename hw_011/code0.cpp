﻿#include <iostream>
#include <string>
#include <math.h>
#include "Stack.h"
int PostfixCalculator(const std::string& expresstion)
{
	const std::string& operators = "+-*/%^";
	ST::Stack<int> stack;
	std::string curentNumber;
	for (size_t i = 0; i < expresstion.size(); i++)
	{
		if (expresstion[i] == ' ' || i == expresstion.size())
		{
			bool foundExpresion = false;
			for (const auto& i : operators)
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
						}break;


						case '*':
						{
							val3 = val1 * val2;
						}break;

						case '/':
						{
							val3 = val1 / val2;
						}break;

						case '^':
						{
							val3 = pow(val1, val2);
						}break;

						default:
							stack.pop();
							break;
					}
					stack.push(val3);
					foundExpresion = true;
					break;
				}
			}
			if (!foundExpresion)stack.push(std::stoi(curentNumber));
			curentNumber = "";
		}
		else
		{
			curentNumber += expresstion[i];
		}
	}
	return stack.pop();
}
int main()
{
	std::cout << PostfixCalculator("") << "\n";
}