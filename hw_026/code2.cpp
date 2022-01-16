#include <ctime>
#include <vector>
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

void checking(int* first, int* last)
{
	for (int* i = first; i <= last; i++)
	{
		for (int* j = first; j <= last; j++)
		{
			if (*j > *i && i != j)
			{
				int index = linearSearch(first, last, 2 * *j - *i);
				if (index != -1)
				{
					printf("%i %i %i\n", *i, *j, first[index]);
				}
			}
		}
	}
}
void checking2(int* first, int* last)
{
	std::vector<std::pair<int*, int*>> pairOf_ca;
	for (int* i = first; i <= last; i++)
	{
		for (int* j = first; j <= last; j++)
		{
			if (*j > *i)
			{
				pairOf_ca.push_back({i,j});
			}
		}
	}

	for (const auto& i : pairOf_ca)
	{
		float elemToFind = (*i.first + *i.second) / 2.f;
		if ((int)elemToFind == elemToFind)
		{
			size_t findElem = linearSearch(first, last, elemToFind);
			if (findElem != -1)
			{
				printf("%i %i %i\n", *i.first, first[findElem], *i.second);
			}
		}
	}

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