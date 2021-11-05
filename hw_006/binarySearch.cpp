#include <iostream>
#include <sstream>
size_t Bsearch(int y, int *x, size_t start, size_t end)
{
	size_t middle = (start + end) >> 1;

	if (y == x[middle])
		return middle;
	else if (end == start)
		return -1;
	else if (y < x[middle])
		return Bsearch(y, x, start, middle - 1);
	else
		return Bsearch(y, x, middle + 1, end);
}
template <typename T>
std::string toStringArray(T arr, size_t size)
{
	std::stringstream s;
	s << "[ ";
	for (size_t i = 0; i < size; i++)
	{
		s << arr[i] << ", ";
	}
	s << "\b\b ]";
	return s.str();
}
int main()
{
	std::cout << "-------------------findable item case-------------------\n";
	{ //findable item case
		int x[] = {0, 1, 3, 5, 7, 9, 10, 11, 15, 17};
		std::cout << toStringArray(x, sizeof(x) / sizeof(int)) << "\n";
		auto foundPos = Bsearch(10, x, 0, sizeof(x) / sizeof(int) - 1);
		std::cout << foundPos << std::endl;
	}
	std::cout << "------------------unfindable item case------------------\n";
	{ //unfindable item case
		int x[] = {0, 1, 3, 5, 7, 9, 11, 15, 17};
		std::cout << toStringArray(x, sizeof(x) / sizeof(int)) << "\n";
		auto foundPos = Bsearch(10, x, 0, sizeof(x) / sizeof(int) - 1);
		std::cout << foundPos << std::endl;
	}
}