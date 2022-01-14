#include <cstdio>
#include <climits>

int* CountSort(int* input,int n, int k)
{
	int i, * temp = new int[k], * output = new int[n];
	for(i=0;i<k;i++) temp[i]=0; 
	for(i=0;i<n;i++) temp[input[i]]++;
	for(i=1;i<k;i++) temp[i]+=temp[i-1];
	for(i=n-1;i>=0;i--)
	{
		output[temp[input[i]]-1]=input[i];
		temp[input[i]]-=1;
	}
	return output;
}

int main()
{
	int a[] = { 1,6,3,5,6,3,2,5,6,8,3 };
	for (size_t i = 0; i < sizeof(a) / sizeof(int); i++)
	{
		printf("%i ", a[i]);
	}
	printf("\n");
	int maxValue = INT_MIN;
	for (size_t i = 0; i < sizeof(a) / sizeof(int); i++)
	{
		if (a[i] > maxValue) maxValue = a[i];
	}

	int* b = CountSort(a, sizeof(a) / sizeof(int), maxValue+1);

	for (size_t i = 0; i < sizeof(a) / sizeof(int); i++)
	{
		printf("%i ", b[i]);
	}
	printf("\n");
}