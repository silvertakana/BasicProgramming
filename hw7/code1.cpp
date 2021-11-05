#include <iostream>
#include <chrono>

double pow2A(uint64_t n)
{
	return n == 0 ? 1 : (2 * pow2A(n - 1));
}
double pow2B(uint64_t n)
{
	return n == 0 ? 1 : (pow2B(n - 1) + pow2B(n - 1));
}
int main()
{
	uint64_t n = 30;
	{
		auto startTime = std::chrono::high_resolution_clock::now();
		std::cout << std::fixed << pow2A(n);
		auto duraion = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startTime);
		std::cout << " in " << std::fixed << duraion.count() / 1000000.f << "\n";
	}
	{
		auto startTime = std::chrono::high_resolution_clock::now();
		std::cout << pow2B(n);
		auto duraion = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startTime);
		std::cout << " in " << std::fixed << duraion.count() / 1000000.f << "\n";
	}
}