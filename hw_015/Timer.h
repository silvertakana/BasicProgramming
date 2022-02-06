#pragma once
#include <stack>
#include <chrono>

namespace Timer {
	using namespace std::chrono;
	static std::stack<steady_clock::time_point> timeStack;

	void start()
	{
		timeStack.push(high_resolution_clock::now());
	}
	duration<float> end()
	{
		auto duration = high_resolution_clock::now() - timeStack.top();
		timeStack.pop();
		return duration;
	}
	float getTime(duration<float> dura)
	{
		return dura.count();
	}
}