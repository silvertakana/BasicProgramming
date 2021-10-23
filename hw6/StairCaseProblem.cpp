#include <iostream>
#include <string>
static size_t solutionCounts = 0;
void StairCaseCase(size_t steps, std::string solution = "")
{
	switch(steps){
	case 1:
		std::cout << solution << "1\n";
		solutionCounts += 1;
		break;
	case 2:
		std::cout << solution << "11\n" << solution << "2\n";
		solutionCounts += 2;
		break;
	default:
		StairCaseCase(steps - 1, solution + "1");
		StairCaseCase(steps - 2, solution + "2");
		break;
	}
}
int main()
{
	size_t steps;
	std::cout << "enter your stair case steps: ";
	std::cin >> steps;

	StairCaseCase(steps);
	std::cout << "there are a total of " << solutionCounts << " ways to go up your stair";
}