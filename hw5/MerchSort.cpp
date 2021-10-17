#include <iostream>
#include <vector>

//print out array function
template <typename T>
std::ostream &operator<<(std::ostream &output, const std::vector<T> list)
{

	if (list.empty())
	{
		output << "[empty]";
	}
	else
	{
		output << "[";
		for (const auto &i : list)
			output << i << ", ";
		output << "\b\b]";
	}
	return output;
}

static void Merch(std::vector<int> &A, const size_t &p, const size_t &q, const size_t &r)
{
	size_t i = 0, j = 0;
	std::vector<int> L(&A[p], &A[q]);
	std::vector<int> R(&A[q], (&A[r - 1]) + 1);

	//merching!
	for (size_t k = p; k < r; k++)
	{
		if (i >= L.size())
		{
			A[k] = R[j];
			j++;
		}
		else if (j >= R.size())
		{
			A[k] = L[i];
			i++;
		}
		else if (L[i] <= R[j])
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;
		}
	}
}
static void MerchSort(std::vector<int> &A, const size_t &p, const size_t &r)
{
	if (p < r - 1)
	{
		auto q = (p + r) >> 1;

		//funny recursions
		MerchSort(A, p, q);
		MerchSort(A, q, r);

		//merch the two half together
		Merch(A, p, q, r);
		return;
	}
}
/*
8
5 2 4 7 1 3 2 6

*/
int main()
{
	//getting input from user

	std::vector<int> MerchSortArray;
	{
		size_t arraySize;
		std::cout << "List size: ";
		std::cin >> arraySize;
		MerchSortArray.resize(arraySize);
	}

	std::cout << "enter your elements here: ";
	for (size_t i = 0; i < MerchSortArray.size(); i++)
	{
		std::cin >> MerchSortArray[i];
	}

	//merch sorting
	MerchSort(MerchSortArray, 0, MerchSortArray.size());

	//printing the array
	std::cout << "\n"
				 << MerchSortArray;
}