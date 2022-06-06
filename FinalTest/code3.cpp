#include <string>
#include <iostream>
#include <string_view>
bool isSingleNumber(std::string_view equation)
{
	return !equation.contains('(') &&
		!equation.contains(')') &&
		equation.find('+', (int)(equation[0] == '+')) == -1 &&
		equation.find('-', (int)(equation[0] == '-')) == -1;
}
int calFromString(std::string_view equation)
{
	if(isSingleNumber(equation))
		return std::stoi((std::string)equation);
	std::string num1, num2;
	int start = equation[0] == '-';
	int operatorIndex = std::min(equation.find_first_of('+', start), equation.find_first_of('-', start));
	int end = std::min(equation.find_first_of('+', operatorIndex+1), equation.find_first_of('-', operatorIndex+1));
	if (end == -1) end = equation.size();
	num1 = equation.substr(0, operatorIndex);
	num2 = equation.substr(operatorIndex, end - operatorIndex);
	return calFromString(std::to_string(std::stoi(num1) + std::stoi(num2)) + (std::string)equation.substr(end, equation.size()-end));
}
std::string SolveEquation(std::string equation)
{
	int openBracketIndex = equation.find_last_of('(');
	int closeBracketIndex;
	if (openBracketIndex == -1)
	{
		openBracketIndex = -1;
		closeBracketIndex = equation.size();
	}
	else
	{
		closeBracketIndex = equation.find_first_of(')', openBracketIndex+1);
	}
	std::string_view subEquation(equation.begin() + (openBracketIndex +1), equation.begin() + (closeBracketIndex));
	std::cout << subEquation << std::endl;
	std::string insertString = std::to_string(calFromString(subEquation));
	equation.insert(std::max(openBracketIndex,0), insertString);
	equation.erase(equation.begin() + (std::max(openBracketIndex, 0) + insertString.size()), equation.begin() + (std::min(closeBracketIndex + 1 + insertString.size(), equation.size())));
	int index = 0;
	do
	{
		index = equation.find_first_of('-', index+1);
		if (index != -1 && equation[index+1] == '-')
		{
			equation.erase(index, 2);
			equation.insert(equation.begin() + index, '+');
		}
	}
	while(index != -1);
	if(isSingleNumber(equation))
		return equation;
	return SolveEquation(equation);
}

int main()
{
	std::string equation = "-(3+(2-1))";
	std::cout << SolveEquation(equation);
}