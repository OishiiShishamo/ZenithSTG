#include "Main.h"

#include "Time.h"

void
Time::StartTimer() {
	startTime = std::chrono::high_resolution_clock::now();
	frontFrameTime = std::chrono::nanoseconds(0);
}

void
Time::StopTimer() {
	elapsedus += Timer();
}

void
Time::ResetTimer() {
	StartTimer();
	elapsedus = std::chrono::nanoseconds(0);
}

double
Time::NSec2Double(std::chrono::nanoseconds ns) {
	return std::chrono::duration<double>(ns).count();
}

std::chrono::nanoseconds
Time::Timer() {
	return elapsedus + std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startTime);
}

std::chrono::nanoseconds
Time::ElapsedTime() {
	std::chrono::nanoseconds tmp = frontFrameTime;
	frontFrameTime = Timer();
	framedayo = static_cast<double>(Timer().count()) / std::chrono::nanoseconds(1000000000 / fps).count();
	return Timer() - tmp;
}

Time timeMng;