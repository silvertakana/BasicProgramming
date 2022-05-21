#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include "LinklistGraph.h"
#include "MatrixGraph.h"
#include "EdgeListGraph.h"

int main()
{
	{
		LLGraphDemo();
	}
	std::cout << "==================" << std::endl;
	{
		MatrixGraphDemo();
	}
	std::cout << "==================" << std::endl;
	{
		ELGraphDemo();
	}
}