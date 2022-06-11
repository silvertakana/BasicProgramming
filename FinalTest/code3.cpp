#include <string>
#include <iostream>
#include <stack>

char getOperator(char c)
{
	if(c == '+' || c == '-' || c == '(' || c == ')')
		return c;
	if (c == ' ')
		return 1;
	return 0;
}
std::string infixToPostfix(std::string equation)
{
	//remove space for easier parsing
	for (int i = 0; i < equation.length(); i++)
	{
		if (equation[i] == ' ')
		{
			equation.erase(i, 1);
			i--;
		}
	}
	std::string postfix;
	std::stack<char> stack;
	for(char c : equation)
	{
		if(getOperator(c))
		{
			if(stack.empty())
				stack.push(c);
			else
			{
				if(c == '(')
					stack.push(c);
				else if(c == ')')
				{
					while(stack.top() != '(')
					{
						postfix += stack.top();
						postfix += ' ';
						stack.pop();
					}
					stack.pop();
				}
				else
				{
					while(!stack.empty() && stack.top() != '(' && getOperator(stack.top()) && getOperator(c) && getOperator(stack.top()) <= getOperator(c))
					{
						postfix += stack.top();
						postfix += ' ';
						stack.pop();
					}
					stack.push(c);
				}
			}
		}
		else
		{
			postfix += c;
			postfix += ' ';
		}
	}
	while(!stack.empty())
	{
		postfix += stack.top();
		postfix += ' ';
		stack.pop();
	}
	return postfix;
}
int solve(std::string pfequa)
{
	std::stack<int> operandStack;
	std::string operand;
	for (size_t i = 0; i < pfequa.size(); i++)
	{
		if (!getOperator(pfequa[i]))
		{
			operand += pfequa[i];
		}
		else
		{
			if (operand.size() > 0)
			{
				operandStack.push(std::stoi(operand));
				operand.clear();
			}
			int a, b;
			a = b = 0;
			if (pfequa[i] == '+' || pfequa[i] == '-')
			{
				if (!operandStack.empty())
				{
					b = operandStack.top();
					operandStack.pop();
				}
				
				if (!operandStack.empty())
				{
					a = operandStack.top();
					operandStack.pop();
				}
			}
			switch (pfequa[i])
			{
			case '+':
				{
					operandStack.push(a + b);
				}
				break;
			case '-':
				{
					operandStack.push(a - b);
				}
				break;
			default:
				break;
			}
		}
	}
	return operandStack.top();
}

int main()
{
	std::string equation = "";
	std::cout << "Enter equation: " << equation;
	std::getline(std::cin, equation);
	
	int result = solve(infixToPostfix(equation));
	std::cout << "\nResult: " << result << std::endl;
	system("pause");
}