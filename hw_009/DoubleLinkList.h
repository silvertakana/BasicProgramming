#pragma once
#include<initializer_list>
#include<stdexcept>
namespace ST
{
	template<class T>
	struct DLLE
	{
		DLLE<T>* prev;
		T data;
		DLLE<T>* next;
	};
	template<class T>
	class DLL
	{
		DLLE<T> *firstElem = nullptr, *lastElem = nullptr;
		size_t size = 0;
	public:
		DLL(const std::initializer_list<T>& input)
		{
			for (const auto& i : input)
			{
				pushBack(i);
			}
		}
		~DLL()
		{
			updatePointerElem();
			while (!isEmpty())
			{
				popFirst();
			}
		}
		bool isEmpty() const
		{
			return firstElem == nullptr;
		}
		const size_t& corectSize()
		{
			if (isEmpty()) return 0;
			DLLE<T>* checkElem = firstElem;
			size_t counter = 0;
			while (checkElem != nullptr)
			{
				checkElem = checkElem->next;
				counter++;
			}
			size = counter;
			return size;
		}
		const size_t& getSize() const
		{
			return size;
		}
		const T& popBack()
		{
			if (isEmpty()) throw std::out_of_range("can't pop when there is nothing.");
			T data = lastElem->data;
			DLLE<T>* next = lastElem->prev;
			delete lastElem->next;
			lastElem = next;
			lastElem->next = nullptr;

			size--;
			return data;
		}
		const T& popFirst()
		{
			if (isEmpty()) throw std::out_of_range("can't pop when there is nothing.");
			T data = firstElem->data;
			DLLE<T> *next = firstElem->next;
			delete firstElem;
			firstElem = next;
			firstElem->prev = nullptr;

			size--;
			return data;
		}
		void popByValue(const T& value)
		{
			for (size_t i = 0; i < size; i++)
			{
				if (operator[](i) == value)
				{
					pop(i);
					i--;
				}
			}
		}
		const T& pop(const size_t& index)
		{
			if (isEmpty()) throw std::out_of_range("can't pop when there is nothing.");
			if (index >= size) throw std::out_of_range("index must remain the the range of 0 to size - 1.");

			if (index == 0) return popFirst();
			if (index == size-1) return popBack();

			DLLE<T>* checkElem = firstElem;
			for (size_t i = 0; i < index; i++)
			{
				checkElem = checkElem->next;
			}

			const T data = checkElem->data;
			checkElem->prev->next = checkElem->next;
			checkElem->next->prev = checkElem->prev;
			delete checkElem;

			size--;
			return data;
		}
		void pushBack(const T& data)
		{
			if (isEmpty())
			{
				lastElem = new DLLE<T>{ lastElem,data,nullptr };
				firstElem = lastElem;
				return;
			}
			lastElem->next = new DLLE<T>{ lastElem,data,nullptr };
			lastElem = lastElem->next;

			size++;
		}
		void pushFirst(const T& data)
		{
			if (isEmpty())
			{
				firstElem = new DLLE<T>{ nullptr,data,lastElem };
				lastElem = firstElem;
				return;
			}
			firstElem->prev = new DLLE<T>{ nullptr,data,lastElem };
			firstElem = firstElem->prev;

			size++;
		}
		T& operator[](const size_t& index)
		{
			if (isEmpty())			throw std::out_of_range("there are nothing in this list.");
			if (index >= size)	throw std::out_of_range("index must remain the the range of 0 to size - 1.");
			if (index == 0)		return firstElem->data;
			if (index == size-1)	return lastElem->data;

			DLLE<T>* checkElem = firstElem;
			for (size_t i = 0; i < index; i++)
			{
				checkElem = checkElem->next;
			}
			return checkElem->data;
		}
		const T& operator[](const size_t& index) const
		{
			return operator[](index);
		}
		private:
			void updatePointerElem()
			{
				while (firstElem->prev != nullptr)
				{
					firstElem = firstElem->prev;
				}
				while (lastElem->next != nullptr)
				{
					lastElem = lastElem->next;
				}
			}
	};
}