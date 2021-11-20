#pragma once
#include <initializer_list>
#include <stdexcept>
namespace ST
{
	template<class T>
	class Queue
	{
		struct Qelem
		{
			Qelem* next;
			T data;
		};
		Qelem* m_firstElem = nullptr, * m_lastElem = nullptr;
	public:
		Queue(){}
		Queue(const std::initializer_list<T>& input)
		{
			for (const auto& i : input)
			{
				push(i);
			}
		}
		bool isEmpty()
		{
			return m_firstElem == nullptr;
		}
		size_t size() const
		{
			Qelem* currentElem = m_firstElem;
			size_t sizeCounter = 0;
			while (currentElem != nullptr)
			{
				sizeCounter++;
				currentElem = currentElem->next;
			}
			return sizeCounter;
		}

		void push(const T& value)
		{
			Qelem* prevElem = m_lastElem;
			m_lastElem = new Qelem{ nullptr,value };
			if (isEmpty())
				m_firstElem = m_lastElem;
			else
				prevElem->next = m_lastElem;
		}
		T& getFirst()
		{
			return m_firstElem->data;
		}
		T pop()
		{
			T value = getFirst();
			voidPop();
			return value;
		}
		void voidPop()
		{
			if (isEmpty()) throw std::out_of_range("pop can't operate when queue is empty. try using isEmpty() function before call pop.");
			Qelem* beforeElem = m_firstElem;
			m_firstElem = m_firstElem->next;
			delete beforeElem;
		}
	};
}