#include <iostream>
#include <string>
#include <vector>
#include <map>

template <class T>
void promt(std::string text, T &input)
{
	std::cout << text;
	std::cin >> input;
}
int main()
{
	size_t arraySize;
	promt("Enter array size: ", arraySize);
	std::cout << "enter array elements: " << std::endl;
	std::vector<int> array(arraySize);
	for (size_t i = 0; i < arraySize; i++)
	{
		int element;
		promt("", element);
		array[i] = element;
	}
	std::cout << "array: " << std::endl;
	for (size_t i = 0; i < arraySize; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << "\nresult: " << std::endl;
	std::map<int, bool> m;
	for (size_t i = 0; i < arraySize; i++)
	{
		if (m.find(array[i]) != m.end())
			m[array[i]] = true;
		m[array[i]];
	}
	for (auto i : m)
	{
		if (i.second == false)
		{
			std::cout << i.first << " ";
		}
	}
}