#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int binarySearch(int* firstPtr, int* secondPtr, int target)
{
	int* first, * last;
	if (firstPtr < secondPtr)
	{
		first = firstPtr;
		last = secondPtr;
	}
	else if (firstPtr > secondPtr)
	{
		last = firstPtr;
		first = secondPtr;
	}
	else if (target == *firstPtr) return 0;
	else return -1;


	int* mid;
	while (first <= last)
	{
		mid = first + (last - first) / 2;
		if (*mid > target)
			last = mid - 1;
		else if (*mid < target)
			first = mid + 1;
		else return mid - firstPtr;
	}
	return -1;
}
int binarySearchRecur(int* first, int* last, int target)
{
	if(first > last) return -1;
	if(first == last) if(*first == target)return 0; else return -1;

	int* mid = first + (last - first) / 2;
	if (*mid == target) return mid - first;
	else if (*mid > target) return binarySearchRecur(first, mid - 1, target);
	else if (*mid < target) {
		int result = binarySearchRecur(mid + 1, last, target);
		if (result == -1) return -1;
		else return (mid - first + 1) + result;
	}
	else return -1;
}

int compare(const void* first, const void* second)
{
	return *(int*)second - *(int*)first;
}

int main()
{
	// srand(time(0));
	int arr[10];
	for (size_t i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
		arr[i] = rand()/(float)RAND_MAX * 1998 - 999;
	}
	// int findElem = rand() / (float)RAND_MAX * 1998 - 999;
	int findElem = 11;
	arr[7] = 11;
    
    qsort(arr, sizeof(arr)/sizeof(int), sizeof(int), compare);

	printf("arr: ");
    for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++)
		printf("%i ", arr[i]);

	printf("\nelement %i is at index number %i\n", findElem, binarySearchRecur(arr, arr + sizeof(arr) / sizeof(int) - 1, findElem));
	printf("\nelement %i is at index number %i\n", findElem, binarySearch(arr, arr + sizeof(arr) / sizeof(int) - 1, findElem));

}