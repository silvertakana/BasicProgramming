#include <vector>
#include <iostream>
#include <functional>
void Build_Max_Heap(std::vector<int>& arr)
{
	std::function<void(std::vector<int>&,const int&)> Max_Heapify = [&Max_Heapify](std::vector<int>& arr, const int& i)->void
	{
		const auto left_child = [](const int& i) ->int { return 2 * i + 1; };
		const auto right_child = [](const int& i) ->int { return 2 * i + 2; };
		const auto parent = [](const int& i) ->int { return (i - 1) / 2; };

		int left = left_child(i), right = right_child(i), largest = i;
		if (left < arr.size() and arr[left] > arr[i])
			largest = left;
		if (right < arr.size() and arr[right] > arr[largest])
			largest = right;
		if (largest != i)
		{
			std::swap(arr[i], arr[largest]);
			Max_Heapify(arr, largest);
		}
	};

	int n = arr.size();
	for (int i = n/2 - 1; i >= 0; i--)
	{
		Max_Heapify(arr, i);
	}
}


int main()
{
	std::vector<int> arr = { 15, 4, 1, 3, 13, 2, 16, 9, 10, 14, 8, 7, 0, 20, 5 };
	for (auto& i : arr)
	{
		printf("%i, ", i);
	}

	Build_Max_Heap(arr);
	printf("\n");
	for (auto& i : arr)
	{
		printf("%i, ", i);
	}
	printf("\n");
	system("pause");
} 