#include <iostream>
#include <algorithm>
#include <functional>
template<class T>
void insertionSort(T arr[], size_t size, bool(*key)(const T&, const T&))
{
	for (size_t i = 1; i < size; i++)
	{
		T last = arr[i];
		size_t j = i;
		while (j > 0 && key(arr[j-1], last) )
		{
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = last;
		for (size_t k = 0; k < size; k++)
		{
			std::cout << arr[k] << " ";
		}
		std::cout << std::endl;
	}
}
template <class T>
void bubbleSort(T arr[], size_t size, bool(*key)(const T&, const T&))
{
	for (int i = size - 1; i > 0; i--)
	{
		for (size_t j = 1; j <= i; j++)
		{
			if (!key(arr[j - 1], arr[j]))
				std::swap(arr[j - 1], arr[j]);
		}
		for (size_t k = 0; k < size; k++)
		{
			std::cout << arr[k] << " ";
		}
		std::cout << std::endl;
	}
}
template	<class T>
void selectionSort(T arr[], size_t size, bool(*key)(const T&, const T&))
{
	for (size_t i = 0; i < size-1; i++)
	{
		T best = i;
		for (size_t j = i + 1; j < size; j++)
		{
			if (key(arr[j], arr[best]))
				best = j;
		}
		if(i != best) std::swap(arr[i], arr[best]);
		for (size_t k = 0; k < size; k++)
		{
			std::cout << arr[k] << " ";
		}
		std::cout << std::endl;
	}
}
bool key(const int& a, const int& b)
{
	return a < b;
}
int main()
{
	int arr[]{42,20,17,13,28,14,23,15};

	bubbleSort(arr, sizeof(arr)/sizeof(int) , key);
}