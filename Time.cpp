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
	targetFrame = static_cast<double>(Timer().count()) / std::chrono::nanoseconds(1000000000 / fps).count();
	return Timer() - tmp;
}

void
Time::FrameWait() {
	std::chrono::nanoseconds FrameDuration(1000000000 / fps);
	std::chrono::nanoseconds frameElapsed = Timer() - frontFrameTime;

	if (frameElapsed < FrameDuration - std::chrono::milliseconds(2)) {
		std::this_thread::sleep_for(FrameDuration - frameElapsed - std::chrono::milliseconds(2));
	}
}

Time timeMng;