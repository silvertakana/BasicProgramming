#include <iostream>
int main()
{
	//get input from user
	size_t listSize;
	std::cout << "list size:";
	std::cin >> listSize;

	float *List = new float[listSize];
	std::cout << "enter your Elements:";
	for (size_t i = 0; i < listSize; i++)
	{
		std::cin >> List[i];
	}

	//find the min value of the list
	float ans = List[0];
	for (size_t i = 1; i < listSize; i++)
	{
		if (List[i] < ans)
			ans = List[i];
	}
	std::cout << ans << "\n";
}