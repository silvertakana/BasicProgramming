#include <iostream>
#include <format>
#include <stack>
#include "Timer.h"
void HanoiTower(const size_t& n, const char* a, const char* b, const char* c)
{
	if (n == 1)
	{
		std::cout << a << " to " << c << "\n";
	}
	else
	{
		HanoiTower(n - 1, a, c, b);
		HanoiTower(1, a, b, c);
		HanoiTower(n - 1, b, a, c);
	}
}
void HanoiTowerCheatNoRecur(const size_t& n, const char* a, const char* b, const char* c)
{
	size_t looptime = (pow(2, n) - 1) / 3;
	for (size_t i = 0; i < looptime; i++)
	{
		if (n % 2)
		{
			if (i%2)
				std::cout << std::format("{0} to {2}\n{1} to {0}\n{1} to {2}\n", a, b, c);
			else
				std::cout << std::format("{0} to {2}\n{0} to {1}\n{2} to {1}\n", a, b, c);
		}
		else
		{
			if (i % 2)
				std::cout << std::format("{0} to {1}\n{2} to {0}\n{2} to {1}\n", a, b, c);
			else
				std::cout << std::format("{0} to {1}\n{0} to {2}\n{1} to {2}\n", a, b, c);
		}
	}
	if (n % 2)
		std::cout << a << " to " << c <<"\n";
}
void HanoiTowerNoRecur(const size_t& n1, const char* a1, const char* b1, const char* c1)
{
	std::stack<size_t> diskes;
	std::stack<const char*> names;
	diskes.push(n1);
	names.push(a1);
	names.push(b1);
	names.push(c1);
	while (diskes.size())
	{
		const char* a, *b, *c;
		size_t n;

		c = names.top(); names.pop();
		b = names.top(); names.pop();
		a = names.top(); names.pop();
		n = diskes.top(); diskes.pop();

		if (n == 1)
		{
			std::cout << a << " to " << c << "\n";
		}
		else
		{
			diskes.push(n - 1);
			names.push(b);
			names.push(a);
			names.push(c);
			diskes.push(1);
			names.push(a);
			names.push(b);
			names.push(c);
			diskes.push(n - 1);
			names.push(a);
			names.push(c);
			names.push(b);
		}
	}
}
int main()
{
	size_t diskcount = 5;
	float times[3];
	Timer::start();
	HanoiTowerCheatNoRecur(diskcount, "A", "B", "C");
	times[0] = Timer::end().count();
	
	printf("\n");

	Timer::start();
	HanoiTowerNoRecur(diskcount, "A", "B", "C");
	times[1] = Timer::end().count();

	printf("\n");

	Timer::start();
	HanoiTower(diskcount, "A", "B", "C");
	times[2] = Timer::end().count();

	std::cout << "\ntime1: " << times[0] << " seconds\n";
	std::cout << "time2: " << times[1] << " seconds\n";
	std::cout << "time3: " << times[2] << " seconds\n";

}