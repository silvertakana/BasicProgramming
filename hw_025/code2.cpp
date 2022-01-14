#include <vector>
#include <iostream>
#include <functional>
void Max_Heapify(int arr[], const size_t& size, const int& i)
{
	const auto left_child = [](const int& i) ->int { return 2 * i + 1; };
	const auto right_child = [](const int& i) ->int { return 2 * i + 2; };
	const auto parent = [](const int& i) ->int { return (i - 1) / 2; };

	int left = left_child(i), right = right_child(i), largest = i;
	if (left < size and arr[left] > arr[i])
		largest = left;
	if (right < size and arr[right] > arr[largest])
		largest = right;
	if (largest != i)
	{
		std::swap(arr[i], arr[largest]);
		Max_Heapify(arr, size, largest);
	}
};

void Build_Max_Heap(int arr[], size_t size)
{
	int n = size;
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		Max_Heapify(arr, size, i);
	}
}
void Heap_Sort(int arr[], size_t size)
{
	Build_Max_Heap(arr, size);
	for (int i = size - 1; i >= 1; i--)
	{
		std::swap(arr[0], arr[i]);
		Max_Heapify(arr, i, 0);
	}
}

int Heap_max(int arr[]) { return arr[0]; }
int Heap_Extract_Max(int arr[], size_t& size)
{
	if (size < 1) throw std::invalid_argument("size cannot be 0");
	int max = arr[0];
	arr[0] = arr[size - 1];
	Max_Heapify(arr, size - 1, 0);
	size--;
	return max;
}
int Heap_Increase_Key(int arr[], size_t i, int key)
{
	if (key < arr[i]) throw std::invalid_argument("new key is smaller than current key");

	const auto parent = [](const int& i) ->int { return (i - 1) / 2; };

	arr[i] = key;
	while (i > 0 && arr[parent(i)] < arr[i])
	{
		std::swap(arr[i], arr[parent(i)]);
		i = parent(i);
	}
	return arr[i];
}
int* Heap_Max_Insert(int oldArr[], size_t& size, const int& key)
{
	int* newArray = new int[size + 1];
	memcpy(newArray, oldArr, size * sizeof(int));
	newArray[size] = INT_MIN;
	Heap_Increase_Key(newArray, size, key);
	size++;
	delete[] oldArr;
	return newArray;

}
int main()
{
	int* myArr;
	size_t arraySize;
	{
		int tempArray[] = { 15, 4, 1, 3, 13, 2, 16, 9, 10, 14, 8, 7, 0, 20, 5 };
		arraySize = sizeof(tempArray) / sizeof(int);
		myArr = new int[arraySize];
		memcpy(myArr, tempArray, arraySize * sizeof(int));
	}
	printf("original array: ");
	for (size_t i = 0; i < arraySize; i++)
	{
		printf("%i ", myArr[i]);
	}
	printf("\n");
	Build_Max_Heap(myArr, arraySize);
	printf("array after Build_Max_Heap: ");
	for (size_t i = 0; i < arraySize; i++)
	{
		printf("%i ", myArr[i]);
	}

	printf("\nresult of Heap_Max: %i\n", Heap_max(myArr));
	printf("result of Heap_Extract_Max: %i\n", Heap_Extract_Max(myArr,arraySize));
	printf("array after Heap_Extract_Max: ");
	for (size_t i = 0; i < arraySize;i++)
	{
		printf("%i ", myArr[i]);
	}
	printf("\nresult of Heap_Increase_Key: %i\n", Heap_Increase_Key(myArr, 7, 11));
	printf("array after Heap_Increase_Key: ");
	for (size_t i = 0; i < arraySize; i++)
	{
		printf("%i ", myArr[i]);
	}
	printf("\n");
	myArr = Heap_Max_Insert(myArr, arraySize, 6);
	printf("array after Heap_Max_Insert: ");
	for (size_t i = 0; i < arraySize; i++)
	{
		printf("%i ", myArr[i]);
	}
	printf("\n");
	Heap_Sort(myArr, arraySize);
	printf("array after Heap_Sort: ");
	for (size_t i = 0; i < arraySize; i++)
	{
		printf("%i ", myArr[i]);
	}
	delete[] myArr;
}