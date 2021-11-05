#include <iostream>
#include <initializer_list>
#include <string>

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
			if (isEmpty())
				return;
			StackElem<T> *thisElem = top;
			StackElem<T> *lastElem = nullptr;
			while (thisElem != nullptr)
			{
				lastElem = thisElem;
				thisElem = thisElem->next;
				delete lastElem;
			}
			top = nullptr;
		}
		void clear()
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

namespace ST
{
	char valToChar(const uint32_t val)
	{
		if (val <= 9)
			return 48 + val;
		if (val <= 35)
			return 65 + val - 10;
		return 63;
	}
	std::string baseConverter(uint32_t num, const uint32_t &base)
	{
		if (base < 2)
			throw std::domain_error("there are no such base as that");
		ST::Stack<uint8_t> a;
		while (num != 0)
		{
			a.push(num % base);
			num /= base;
		}
		std::string result;
		result.reserve(a.size());

		while (!a.isEmpty())
		{
			result += valToChar(a.pop());
		}

		return result;
	}
}

int main()
{
	std::cout << ST::baseConverter(2021, 2) << "\n";
}