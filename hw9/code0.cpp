#include <iostream>
#include <thread>
#include <chrono>
template <class T>
struct DLL_elem
{
	T data;
	DLL_elem<T> *next;
	DLL_elem<T> *prev;
};
template <class T>
class DLL
{
public:
	DLL_elem<T> *firstElem = nullptr;
	DLL_elem<T> *lastElem = nullptr;
	size_t size() const
	{
		size_t counter = 0;
		auto *checker = firstElem;
		while (checker != lastElem->next)
		{
			checker = checker->next;
			counter++;
		}
		return counter;
	}
	void insert(const T &data)
	{
		lastElem = new DLL_elem<T>{data, nullptr, lastElem};
		if (lastElem->prev)
			lastElem->prev->next = lastElem;
		else
			firstElem = lastElem;
	}
	void del(const DLL_elem<T> *chosen)
	{
		if (chosen->prev)
			chosen->prev->next = chosen->next;
		else
		{
			firstElem = chosen->next;
			if (firstElem)
				firstElem->prev = nullptr;
		}
		if (chosen->next)
			chosen->next->prev = chosen->prev;
		else
		{
			lastElem = chosen->prev;
			if (lastElem)
				lastElem->next = nullptr;
		}

		delete chosen;
	}
};
int main()
{
	size_t n = 100;
	std::cout << "enter you customers here: ";
	std::cin >> n;
	std::cout << std::endl;

	srand(time(nullptr));

	DLL<int> customers;
	for (size_t i = 1; i <= n; i++)
	{
		customers.insert(i);
	}
	size_t stepSize = (rand() / (float)RAND_MAX) * (customers.size() - 1) + 1;
	std::cout << "the step size is " << stepSize << "\n";
	DLL_elem<int> *deadGuy = customers.firstElem;
	while (customers.firstElem != customers.lastElem)
	{
		for (size_t i = 0; i < stepSize; i++)
		{
			deadGuy = deadGuy->next;
			if (deadGuy == nullptr)
				deadGuy = customers.firstElem;
		}
		{
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(0.1s);
		}
		std::cout << "player " << deadGuy->data << "\tis eliminated!"
					 << "\n";
		{
			auto nextGuy = deadGuy->next;
			customers.del(deadGuy);
			deadGuy = nextGuy;
			if (deadGuy == nullptr)
				deadGuy = customers.firstElem;
		}
	}
	std::cout << "\n==================================\n\nthe winer is ";
	{
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(2s);
	}
	std::cout << "player number " << customers.firstElem->data << "!";
}