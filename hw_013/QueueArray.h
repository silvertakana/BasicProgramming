#pragma once
#include <initializer_list>
#include <stdexcept>
template<class T, size_t maxSize>
class QueueArray
{
	T arr[maxSize];
	size_t currentSize = 0;
public:
	QueueArray(){}
	QueueArray(const std::initializer_list<T>& IL)
	{
		for (const auto& i : IL)
		{
			push(i);
		}
	}
	bool isEmpty()
	{
		return currentSize == 0;
	}
	bool isOverflow()
	{
		return currentSize >= maxSize;
	}
	const size_t& size() const
	{
		return currentSize;
	}
	void push(const T& elem)
	{
		if (isOverflow()) throw std::overflow_error("too much elements are in this queue");
		arr[currentSize++] = elem;
	}
	const T& pop()
	{
		if (isEmpty()) throw std::underflow_error("pop can't operate when there is nothing in the queue");
		T returnVal = arr[0];
		for (int i = 0; i < currentSize; i++)
		{
			arr[i] = arr[i + 1];
		}
		currentSize--;
		return returnVal;
	}
};