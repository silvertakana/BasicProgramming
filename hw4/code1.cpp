#include <iostream>

int main()
{
	int a, b;
	std::cout << "a>>";
	std::cin >> a;
	std::cout << "b>>";
	std::cin >> b;

	while (a != b)
	{
		if (a < b)
		{
			b = b - a;
		}else
		{
			a = a - b;
		}
	}
	std::cout << a << std::endl;
}