#pragma once
#include <iostream>
#include <cstring>
#include <initializer_list>

namespace ST
{
	template <typename T>
	struct SLLE
	{
		SLLE<T>* next;
		T data;
	};

	template <typename T>
	class SLL
	{
	private:
		SLLE<T>* firstElem = nullptr;

	public:
		SLL(){}
		SLL(const char* txt)
		{
			for (int i = strlen(txt) - 1; i >= 0; i--)
			{
				this->pushFirst(txt[i]);
			}
		}
		SLL(std::initializer_list<T> inputs)
		{
			for (int i = inputs.size() - 1; i >= 0; i--)
			{
				this->pushFirst(inputs.begin()[i]);
			}
		}
		SLL(const SLL<T>& list2)
		{
			(*this) = list2;
		}
		const SLL<T>& operator=(const SLL<T>& list2)
		{
			SLLE<T>** updateElem = &firstElem;
			for (const auto& i : list2)
			{
				if (*updateElem == nullptr)
				{
					*updateElem = new SLLE<T>{nullptr,i};
				}
				else
				{
					(*updateElem)->data = i;
				}
				updateElem = &((* updateElem)->next);
			}
			return *this;
		}
		SLL<T>& join(const SLL<T>& list2)
		{
			SLLE<T>* lastElem = getLastElem();
			for (const auto& i : list2)
			{
				lastElem->next = new SLLE<T>{nullptr,i};
				lastElem = lastElem->next;
			}
			return *this;
		}
		virtual ~SLL()
		{
			makeEmpty();
		}
		void makeEmpty()
		{
			if (isEmpty()) return;
			SLLE<T>* thisElem = firstElem;
			while (thisElem != nullptr)
			{
				SLLE<T>* prev = thisElem;
				thisElem = thisElem->next;
				delete prev;
			}
			firstElem = nullptr;
		}

		void fill(const T& elem)
		{
			for (auto& i : *this)
			{
				i = elem; // copy!
			}
		}
		void fill(const size_t& size, const T& elem)
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
		void emplaceFill(const size_t& size, Args... args)
		{
			const auto s = this->size();
			for (size_t i = 0; i < size; i++)
			{
				if (i < s)
					(*this)[i] = T{ args... }; // copy!
				else
					this->emplaceBack(args...);
			}
		}
		template <class... Args>
		void emplaceBack(Args... args)
		{
			SLLE<T>** thisElem;
			if (isEmpty())
				thisElem = &firstElem;
			else
				thisElem = &(getLastElem()->next);

			*thisElem = new SLLE<T>{ nullptr, {args...} };
		}
		void pushBack(const T& elem)
		{
			SLLE<T>** thisElem;
			if (isEmpty())
				thisElem = &firstElem;
			else
				thisElem = &(getLastElem()->next);

			*thisElem = new SLLE<T>{ nullptr, elem };
		}
		T popBack()
		{
			if (isEmpty())
				throw std::underflow_error("popBack can't operate when array is empty.");
			const size_t s = size();
			if (s == 1)
			{
				T a = firstElem->data;
				delete firstElem;
				firstElem = nullptr;
				return a;
			}
			auto* thisElem = gotoElem(s - 2);
			T a = thisElem->next->data;
			delete thisElem->next;
			thisElem->next = nullptr;
			return a;
		}

		template <class... Args>
		void emplaceFirst(Args... args)
		{
			firstElem = new SLLE<T>{firstElem, {args...} };
		}
		void pushFirst(const T& elem)
		{
			firstElem = new SLLE<T>{ firstElem, elem };
		}
		T popFirst()
		{
			if (isEmpty())
				throw std::underflow_error("popBack can't operate when array is empty.");
			auto* nextElem = firstElem->next;
			T a = firstElem->data;
			delete firstElem;
			firstElem = nextElem;
			return a;
		}

		template <class... Args>
		void emplace(const size_t& index, Args... args)
		{
			if (index == 0)
			{
				emplaceFirst(args...);
				return;
			}
			auto lastElem = gotoElem(index - 1);
			auto newElem = new SLLE<T>{ lastElem->next, {args...} };
			lastElem->next = newElem;
		}
		void push(const size_t& index, const T& value)
		{
			if (index == 0)
			{
				pushFirst(value);
				return;
			}
			auto lastElem = gotoElem(index - 1);
			auto newElem = new SLLE<T>{ lastElem->next, value };
			lastElem->next = newElem;
		}
		T pop(const size_t& index)
		{
			if (isEmpty())
				throw std::underflow_error("pop can't operate when list is empty.");
			if (index == 0)
			{
				return popFirst();
			}
			auto Elem = gotoElem(index - 1);
			auto lastElem = Elem->next;
			Elem->next = Elem->next->next;
			T a = lastElem->data;
			delete lastElem;
			return a;
		}
		bool isEmpty() const
		{
			return firstElem == nullptr;
		}
		size_t size() const
		{
			if (isEmpty())
				return 0;
			else
			{
				size_t counter = 0;
				SLLE<T>* thisElem = firstElem;
				while (thisElem != nullptr)
				{
					thisElem = thisElem->next;
					counter++;
				}
				return counter;
			}

		}

		T& operator[](const size_t& index) 
		{
			if (index > size())
				throw std::out_of_range("index value for LinkedList is too big");
			return gotoElem(index)->data;
		}
		const T operator[](const size_t& index) const
		{
			return (*this)[index];
		}

	private:
		SLLE<T>* gotoElem(const size_t& index) const
		{
			if (index < 0) throw std::underflow_error("index must be greater or equal to 0");
			if (index >= size()) throw std::overflow_error("index must be smaller than size");

			SLLE<T>* thisElem = firstElem;
			for (size_t i = 0; i < index; i++)
			{
				thisElem = thisElem->next;
			}

			return thisElem;
		}
		SLLE<T>* getLastElem() const
		{
			SLLE<T>* thisElem = firstElem;

			if (!isEmpty())
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
			using value_type = SLLE<T>;
			using pointer = SLLE<T>*;
			using reference = SLLE<T>&;

			Iterator(pointer ptr) : m_ptr(ptr) {}

			T& operator*() const { return m_ptr->data; }
			T* operator->() { return &(m_ptr->data); }

			Iterator& operator++()
			{
				m_ptr = m_ptr->next;
				return *this;
			}
			Iterator operator++(int) const
			{
				Iterator tmp = *this;
				++(*this);
				return tmp;
			}

			friend bool operator==(const Iterator& a, const Iterator& b)  { return a.m_ptr == b.m_ptr; };
			friend bool operator!=(const Iterator& a, const Iterator& b)  { return a.m_ptr != b.m_ptr; };

		private:
			pointer m_ptr;
		};
		Iterator begin() const { return Iterator{ firstElem };}
		Iterator end() const { return Iterator{ nullptr }; }
	};
	template<class T>
	SLL<T> join(SLL<T> l1, const SLL<T> l2)
	{
		return l1.join(l2);
	}
}