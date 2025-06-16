#include "Main.h"

#include "timeUtl.h"

long long t = 0;
long long fps = 60;

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

std::chrono::milliseconds
Time::NSec2MSec(std::chrono::nanoseconds ns) {
	return duration_cast<std::chrono::milliseconds>(ns);
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
	std::chrono::nanoseconds frameElapsed = Timer() - frontFrameTime + (std::chrono::nanoseconds)(rnd() / 32768);

	if (frameElapsed < FrameDuration - std::chrono::milliseconds(2)) {
		std::this_thread::sleep_for((FrameDuration - frameElapsed) - std::chrono::milliseconds(2));
	}
}

Time timeMng;
