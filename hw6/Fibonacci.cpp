#include <iostream>
#include <chrono>
#include <functional>
size_t turnCount = 0; 
int Fibonacci(int n) {
	if (n <= 1) return 1;
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}
int Fibonacci2(int n)
{
	int current = 1,prev2 = 0, prev = 0;
	for (size_t i = 0; i <= n; i++)
	{
		current += prev2;
		prev2 = prev;
		prev = current;
	}
	return current;
}
using namespace std;
using namespace std::chrono;
void Timing(const std::function<int()> f)
{
	auto timer = high_resolution_clock::now();
	int num = f();
	auto duration = high_resolution_clock::now() - timer;
	std::cout << "calculated Fibonacci: " << num << " in " << std::fixed << duration_cast<microseconds>(duration).count() / 1000000.f << "second" << "\n";
}
int main()
{
	int n = 45;
	std::cout << "loop-----------------------------""\n";
	Timing([&]()
		{
			return Fibonacci2(n);
		});
	std::cout << "recursion------------------------""\n";
	Timing([&]()
		{
			return Fibonacci(n);
		});
}