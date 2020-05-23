#ifndef II887522_CALCULATOR_CONTROL_FLOW_H
#define II887522_CALCULATOR_CONTROL_FLOW_H

#include <functional>

using std::function;

namespace ii887522::Calculator
{
	void loop(const unsigned int times, const function<void()>& run)
	{
		for (auto i{ 0u }; i != times; ++i) run();
	}
}

#endif