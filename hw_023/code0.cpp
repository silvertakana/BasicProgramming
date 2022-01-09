#include <iostream>
#include <ctime>
#include <algorithm>
template <class T>
void quickSortRand(T *left, T *right)
{
	const auto Partition = [](T *left, T *right)
	{
		T *i = left, *j = right, pivot = *left + rand() / (float)RAND_MAX * ((right + 1) - left);
		while (i < j)
		{
			while (i <= right && *i <= pivot)
				i++;
			while (j >= left && *j > pivot)
				j--;
			if (i < j)
			{
				std::swap(*i, *j);
			}
		}
		std::swap(*left, *i);
		return j;
	};

	const T *p = Partition(left, right);

	if (left < p - 1)
		quickSortRand((T *)left, (T *)(p - 1));
	if (p + 1 < right)
		quickSortRand((T *)(p + 1), (T *)right);
}
template <class T>
void quickSortLeft(T *left, T *right)
{
	const auto Partition = [](T *left, T *right)
	{
		T *i = left, *j = right, pivot = *left;
		while (i < j)
		{
			while (i <= right && *i <= pivot)
				i++;
			while (j >= left && *j > pivot)
				j--;
			if (i < j)
			{
				std::swap(*i, *j);
			}
		}
		std::swap(*left, *j);
		return j;
	};

	const T *p = Partition(left, right);

	if (left < p - 1)
		quickSortLeft((T *)left, (T *)(p - 1));
	if (p + 1 < right)
		quickSortLeft((T *)(p + 1), (T *)right);
}
template <class T>
void quickSortMin(T *left, T *right)
{
	const auto Partition = [](T *left, T *right)
	{
		T *i = left, *j = right, pivot = *std::min_element(left, right);
		while (i < j)
		{
			while (i <= right && *i <= pivot)
				i++;
			while (j >= left && *j > pivot)
				j--;
			if (i < j)
			{
				std::swap(*i, *j);
			}
		}
		std::swap(*right, *i);
		return j;
	};

	const T *p = Partition(left, right);

	if (left < p - 1)
		quickSortMin((T *)left, (T *)(p - 1));
	if (p + 1 < right)
		quickSortMin((T *)(p + 1), (T *)right);
}
int main()
{
	{
		int arr[] = {30, 19, 24, 28, 41, 34, 15, 43, 20, 12, 36};
		quickSortLeft((int *)arr, (int *)(arr + sizeof(arr) / sizeof(int) - 1));
		for (const auto &i : arr)
		{
			printf("%i ", i);
		}
		printf("\n");
	}
	{
		int arr[] = {30, 19, 24, 28, 41, 34, 15, 43, 20, 12, 36};
		quickSortMin((int *)arr, (int *)(arr + sizeof(arr) / sizeof(int) - 1));
		for (const auto &i : arr)
		{
			printf("%i ", i);
		}
		printf("\n");
	}
	{
		srand(time(0));
		int arr[] = {30, 19, 24, 28, 41, 34, 15, 43, 20, 12, 36};
		quickSortRand((int *)arr, (int *)(arr + sizeof(arr) / sizeof(int) - 1));
		for (const auto &i : arr)
		{
			printf("%i ", i);
		}
		printf("\n");
	}
	system("pause");
};