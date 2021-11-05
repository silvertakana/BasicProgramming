#include <iostream>
size_t turnCount = 0;
void HanoiTower(const size_t &n, const char *a, const char *b, const char *c)
{

	if (n == 1)
	{
		turnCount++;
		std::cout << "take from " << a << " and put it on " << c << "\n";
	}
	else
	{
		HanoiTower(n - 1, a, c, b);
		HanoiTower(1, a, b, c);
		HanoiTower(n - 1, b, a, c);
	}
}
int main()
{
	turnCount = 0;
	HanoiTower(5, "A", "B", "C");
	std::cout << "\n" << turnCount;
}