#include "utilities/Core.h"

#include <chrono>

namespace eb
{
	PerformanceMonitor::PerformanceMonitor()
		: _startTime{ 0 },
		_performanceProfiler{ nullptr }
	{
	}

	void PerformanceMonitor::StartMeasurement()
	{
		_startTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	}

	void PerformanceMonitor::EndMeasurement(const char* label)
	{
		double endTIme = std::chrono::high_resolution_clock::now().time_since_epoch().count();

		// 1e-6 = convert nanoseconds to miliseconds.
		double duration = (endTIme - _startTime) * 1e-6;

		PRINT_COLOR(YELLOW, "%s: %.4fms", label, duration);
	}
}