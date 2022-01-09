#include <cstdio>
#include <cstring>

template<class T>
void MergeSort(T* first, T* last)
{
	const auto Merge = [](T* first, T* mid, T* last)
	{
		T* i = first, * j = mid + 1, * newArr = new T[last - first + 1];
		while (i != mid + 1 && j != last + 1)
		{
			T& a = newArr[i - first + j - (mid + 1)];
			if (*i < *j)
			{
				a = *i;
				i++;
			}
			else
			{
				a = *j;
				j++;
			}
		}
		if (i < mid + 1)
		{
			memcpy(&newArr[i - first + j - (mid + 1)], i, ((mid + 1) - i) * sizeof(T));
		}
		else if (j < last + 1)
		{
			memcpy(&newArr[i - first + j - (mid + 1)], j, ((last + 1) - j) * sizeof(T));
		}
		memcpy(first, newArr, (last - first + 1) * sizeof(T));
	};
	if (first < last)
	{
		T* mid = (last - first) / 2 + first;
		MergeSort(first, mid);
		MergeSort(mid + 1, last);
		Merge(first, mid, last);
	}
}


int main()
{
	int myArray[] = { 8, 2, 9, 4, 5, 3, 1, 6 };
	for (auto& i : myArray)
	{
		printf("%i ", i);
	}
	printf("\n");

	MergeSort(myArray, myArray + sizeof(myArray) / sizeof(int) - 1);

	for (auto& i : myArray)
	{
		printf("%i ", i);
	}
	printf("\n");
}