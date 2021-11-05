#include <initializer_list>
#include <iostream>
namespace ST
{
	template <class T, size_t maxSize>
	class Array
	{
	private:
		T *start, size;

	public:
		Array(std::initializer_list<T> list)
		{
			size = list.size();
			start = new T[maxSize];
			for (size_t i = 0; i < std::min<size_t>(maxSize, size); i++)
			{
				start[i] = list.begin()[i];
			}
		}
		void Insert(const T &x, const size_t &index)
		{
			if (index > size || index >= maxSize)
				throw std::overflow_error("index value is too large for this array");
			for (size_t i = size; i >= index; i--)
			{
				start[i + 1] = start[i];
			}
			size++;
			start[index] = x;
		}
		void Delete(const size_t &index)
		{
			if (index > size)
				throw std::overflow_error("index value is too large for this array");

			for (size_t i = index; i < size; i++)
			{
				start[i] = start[i + 1];
			}
			size--;
		}
		size_t getSize() const
		{
			return size;
		}
		T &operator[](const size_t &index)
		{
			return start[index];
		}
		T operator[](const size_t &index) const
		{
			return start[index];
		}
	};
}

int main()
{
	ST::Array<int, 10> arr = {1, 2, 3, 4, 5};
	arr.Insert(100, 3);

	for (size_t i = 0; i < arr.getSize(); i++)
	{
		std::cout << arr[i] << '\n';
	}
	std::cout << "=========================\n";
	arr.Delete(3);

	for (size_t i = 0; i < arr.getSize(); i++)
	{
		std::cout << arr[i] << '\n';
	}
}