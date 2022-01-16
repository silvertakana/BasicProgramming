#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int linearSearch(int* firstPtr, int* secondPtr, int target)
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

	for (int* i = first; i <= last; i++)
	{
		if (*i == target) return i - first;
	}
	return -1;
}

int main()
{
	srand(time(0));
	int arr[100];
	printf("arr: ");
	for (size_t i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
		arr[i] = rand()/(float)RAND_MAX * 1998 - 999;
		printf("%i ", arr[i]);
	}
	int findElem = rand() / (float)RAND_MAX * 1998 - 999;


	printf("\n\nelement %i is at index number %i\n", findElem, linearSearch(arr, arr + sizeof(arr) / sizeof(int) - 1, findElem));
}