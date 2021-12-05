#include <iostream>
#include <tuple>
#include <math.h>
namespace TreeArray
{
	template <class T>
	void pre_order(void (*f)(T &data), T treeArray[], size_t size, size_t index = 0)
	{
		f(treeArray[index]);
		if (2 * index + 1 < size)
			pre_order(f, treeArray, size, 2 * index + 1);
		if (2 * index + 2 < size)
			pre_order(f, treeArray, size, 2 * index + 2);
	}
	template <class T>
	void post_order(void (*f)(T &data), T treeArray[], size_t size, size_t index = 0)
	{
		if (2 * index + 1 < size)
			post_order(f, treeArray, size, 2 * index + 1);
		if (2 * index + 2 < size)
			post_order(f, treeArray, size, 2 * index + 2);
		f(treeArray[index]);
	}
	template <class T>
	void in_order(void (*f)(T &data), T treeArray[], size_t size, size_t index = 0)
	{
		if (2 * index + 1 < size)
			in_order(f, treeArray, size, 2 * index + 1);
		f(treeArray[index]);
		if (2 * index + 2 < size)
			in_order(f, treeArray, size, 2 * index + 2);
	}

	template <class T>
	std::tuple<T *, size_t> getLeafs(T treeArray[], size_t size)
	{
		auto a = size / 2.f;
		return {&treeArray[(size_t)(a)], (size_t)ceil(a)};
	}

	float depth(size_t size)
	{
		return ceil(log2(size + 1));
	}
}

int main()
{
	char tree[] = "*+-abac";

	TreeArray::in_order<char>([](char &data)
									  { std::cout << data << std::endl; },
									  tree, sizeof(tree) - 1);
	std::cout << "------------------------------" << std::endl;
	auto [resultArray, size] = TreeArray::getLeafs(tree, sizeof(tree) - 1);
	for (size_t i = 0; i < size; i++)
	{
		std::cout << resultArray[i] << std::endl;
	}
	std::cout << "------------------------------" << std::endl;
	std::cout << TreeArray::depth(100) << std::endl;
}