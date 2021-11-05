#pragma once
#include <iostream>
namespace ST
{
	template <typename T>
	struct LinkedListElement
	{
		LinkedListElement<T> *next;
		T data;
	};

	template <typename Base, typename T>
	inline bool instanceof (const T *)
	{
		return std::is_base_of<Base, T>::value;
	}

	template <typename T>
	class LinkedList
	{
	private:
		LinkedListElement<T> *firstElem = nullptr;

	public:
		virtual ~LinkedList()
		{
			LinkedListElement<T> *thisElem = firstElem;
			LinkedListElement<T> *lastElem = nullptr;
			if (thisElem != nullptr)
				while (thisElem->next != nullptr)
				{
					lastElem = thisElem;
					thisElem = thisElem->next;
					delete lastElem;
				}
			delete thisElem;
			firstElem = nullptr;
		}
		void makeEmpty()
		{
			LinkedListElement<T> *thisElem = firstElem;
			LinkedListElement<T> *lastElem = nullptr;
			if (thisElem != nullptr)
				while (thisElem->next != nullptr)
				{
					lastElem = thisElem;
					thisElem = thisElem->next;
					delete lastElem;
				}
			delete thisElem;
			firstElem = nullptr;
		}
		template <class... Args>
		void emplaceBack(Args... args)
		{
			LinkedListElement<T> **thisElem;
			if (isEmpty())
				thisElem = &firstElem;
			else
				thisElem = &(getLastElem()->next);

			*thisElem = new LinkedListElement<T>{nullptr, {args...}};
		}
		void fill(const T &elem)
		{
			for (auto &i : *this)
			{
				i = elem; // copy!
			}
		}
		void fill(const T &elem, const size_t &size)
		{
			const auto s = this->size();
			for (size_t i = 0; i < size; i++)
			{
				if (i < s)
					(*this)[i] = elem; // copy!
				else
					this->pushBack(elem);
			}
		}
		template <class... Args>
		void emplaceFill(const size_t &size, Args... args)
		{
			const auto s = this->size();
			for (size_t i = 0; i < size; i++)
			{
				if (i < s)
					(*this)[i] = T{args...}; // copy!
				else
					this->emplaceBack(args...);
			}
		}
		void pushBack(const T &elem)
		{
			LinkedListElement<T> **thisElem;
			if (isEmpty())
				thisElem = &firstElem;
			else
				thisElem = &(getLastElem()->next);

			*thisElem = new LinkedListElement<T>{nullptr, elem};
		}
		void popBack()
		{
			if (isEmpty())
				throw std::underflow_error("popBack can't operate when array is empty.");
			auto *thisElem = this->gotoElem(size() - 1);
			delete thisElem->next;
			thisElem->next = nullptr;
		}
		void pushFirst(const T &elem)
		{
			firstElem = new LinkedListElement<T>{firstElem, elem};
		}
		void popFirst()
		{
			if (isEmpty())
				throw std::underflow_error("popBack can't operate when array is empty.");
			auto *nextElem = firstElem->next;
			delete firstElem;
			firstElem = nextElem;
		}

		void push(const T &value, const size_t &index)
		{
			auto lastElem = gotoElem(index - 1);
			auto newElem = new LinkedListElement<T>{lastElem->next, value};
			lastElem->next = newElem;
		}
		void pop(const size_t &index)
		{
			if (isEmpty())
				throw std::underflow_error("pop can't operate when array is empty.");
			if (index == 0)
			{
				auto lastElem = firstElem->next;
				firstElem->next = firstElem->next->next;
				delete lastElem;
				return;
			}
			auto Elem = gotoElem(index - 1);
			auto lastElem = Elem->next;
			Elem->next = Elem->next->next;
			delete lastElem;
		}
		bool isEmpty() const
		{
			return firstElem == nullptr;
		}
		size_t size() const
		{
			size_t counter = 1;
			LinkedListElement<T> *thisElem = firstElem;
			if (thisElem != nullptr)
				while (thisElem->next != nullptr)
				{
					thisElem = thisElem->next;
					counter++;
				}
			else
				return 0;
			return counter;
		}

		T &operator[](const size_t &index) const
		{
			if (index > size())
				throw std::out_of_range("index value for LinkedList is too big");
			return gotoElem(index)->data;
		}

	private:
		LinkedListElement<T> *gotoElem(const size_t &index) const
		{
			LinkedListElement<T> *thisElem = firstElem;
			if (thisElem != nullptr)
				for (size_t i = 0; i < index; i++)
				{
					thisElem = thisElem->next;
				}

			return thisElem;
		}
		LinkedListElement<T> *getLastElem() const
		{
			LinkedListElement<T> *thisElem = firstElem;

			if (thisElem != nullptr)
				while (thisElem->next != nullptr)
				{
					thisElem = thisElem->next;
				}
			return thisElem;
		}

	public:
		struct Iterator
		{
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = LinkedListElement<T>;
			using pointer = LinkedListElement<T> *;
			using reference = LinkedListElement<T> &;

			Iterator(pointer ptr) : m_ptr(ptr) {}

			T &operator*() const { return m_ptr->data; }
			T *operator->() { return &(m_ptr->data); }

			Iterator &operator++()
			{
				m_ptr = m_ptr->next;
				return *this;
			}
			Iterator operator++(int)
			{
				Iterator tmp = *this;
				++(*this);
				return tmp;
			}

			friend bool operator==(const Iterator &a, const Iterator &b) { return a.m_ptr == b.m_ptr; };
			friend bool operator!=(const Iterator &a, const Iterator &b) { return a.m_ptr != b.m_ptr; };

		private:
			pointer m_ptr;
		};
		Iterator begin() { return Iterator(firstElem); }
		Iterator end() { return Iterator(nullptr); }
	};
}