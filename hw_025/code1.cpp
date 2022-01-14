#include <vector>
#include <iostream>
#include <functional>
int myArr[] = {15, 4, 1, 3, 13, 2, 16, 9, 10, 14, 8, 7, 0, 20, 5};
//int myArr[] = {0,2,3,1};
void Min_Heapify(int arr[],const size_t& size, const int& i)
{
	const auto left_child = [](const int& i) ->int { return 2 * i + 1; };
	const auto right_child = [](const int& i) ->int { return 2 * i + 2; };
	const auto parent = [](const int& i) ->int { return (i - 1) / 2; };

	int left = left_child(i), right = right_child(i), largest = i;
	if (left < size and arr[left] < arr[i])
		largest = left;
	if (right < size and arr[right] < arr[largest])
		largest = right;
	if (largest != i)
	{
		std::swap(arr[i], arr[largest]);
		Min_Heapify(arr, size, largest);
	}
};
void Build_Min_Heap(int arr[],size_t size)
{
	int n = size;
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		Min_Heapify(arr,size, i);
	}
}
void Heap_Sort(int arr[],size_t size)
{
	Build_Min_Heap(arr,size);
	for (int i = size - 1; i >= 1; i--)
	{
		std::swap(arr[0], arr[i]);
		Min_Heapify(arr,i,0);
	}
}

int main()
{
	for (auto& i : myArr)
	{
		printf("%i ", i);
	}
	printf("\n");
	Heap_Sort(myArr,sizeof(myArr)/sizeof(int));
	for (auto& i : myArr)
	{
		printf("%i ", i);
	}
	printf("\n");
}