#pragma once
#include <iostream>
#include <initializer_list>

namespace ST
{
	template <typename T>
	struct StackElem
	{
		StackElem<T> *next;
		T data;
	};

	template <typename T>
	class Stack
	{
	private:
		StackElem<T> *top = nullptr;

	public:
		Stack() {}
		virtual ~Stack()
		{
			makeEmpty();
		}
		void makeEmpty()
		{
			if (isEmpty())
				return;
			StackElem<T> *thisElem = top;
			while (thisElem != nullptr)
			{
				StackElem<T> *prev = thisElem;
				thisElem = thisElem->next;
				delete prev;
			}
			top = nullptr;
		}

		template <class... Args>
		void emplaceFirst(Args... args)
		{
			top = new StackElem<T>{top, {args...}};
		}
		void push(const T &elem)
		{
			top = new StackElem<T>{top, elem};
		}
		T pop()
		{
			if (isEmpty())
				throw std::underflow_error("popBack can't operate when array is empty.");

			T returnVal = top->data;
			auto *nextElem = top->next;
			delete top;
			top = nextElem;
			return returnVal;
		}
		bool isEmpty() const
		{
			return top == nullptr;
		}
		size_t size() const
		{
			if (isEmpty())
				return 0;
			else
			{
				size_t counter = 0;
				StackElem<T> *thisElem = top;
				while (thisElem != nullptr)
				{
					thisElem = thisElem->next;
					counter++;
				}
				return counter;
			}
		}
	};
}