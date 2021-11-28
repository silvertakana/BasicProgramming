#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include "SinglyLinkedList.h"
template<class T>
class stack
{
	struct Elem
	{
		Elem* next;
		T data;
	};
	Elem* top = nullptr;
	ST::SLL<T*> onceMinPtr{ new T{INT32_MAX} };
public:
	stack() {};
	stack(const std::initializer_list<T>& input)
	{
		for (const auto& i : input)
		{
			push(i);
		}
	}
	size_t size()
	{
		Elem* checkElem = top;
		size_t counter;
		while (checkElem != nullptr)
		{
			checkElem = checkElem->next;
			counter++;
		}
		return counter;
	}
	bool isEmpty()
	{
		return top == nullptr;
	}
	void push(const T& input)
	{
		top = new Elem{ top, input };
		if (!(onceMinPtr[0]) || input < *(onceMinPtr[0]))
		{
			onceMinPtr.pushFirst(&top->data);
		}
	}
	T pop()
	{
		if (isEmpty()) throw std::underflow_error("there are nothing to pop.");
		if (&(top->data) == (onceMinPtr[0]))
		{
			onceMinPtr.popFirst();
		}
		Elem* next = top->next;
		T data = top->data;
		delete top;
		top = next;
	}
		return data;
	T& min()
	{
		if (isEmpty()) throw std::exception("there are nothing to find min.");
		return *(onceMinPtr[0]);
	}
};

int main()
{
	stack<int> s;
	srand(time(nullptr));

	for (size_t i = 0; i < 5; i++)
	{
		s.push((int)(rand()/(float)RAND_MAX*10));
	}


	while (!s.isEmpty())
	{
		std::cout << s.min() << "\t";
		std::cout << s.pop() << std::endl;
	}
}