#pragma once
#ifndef TIME_H
#define TIME_H

class Time {
public:
	long long targetFrame = 0;
	std::chrono::nanoseconds frontFrameTime;
	std::chrono::nanoseconds elapsedus = std::chrono::nanoseconds(0);
	void StartTimer();
	void StopTimer();
	void ResetTimer();
	std::chrono::milliseconds NSec2MSec(std::chrono::nanoseconds ns);
	double NSec2Double(std::chrono::nanoseconds);
	std::chrono::nanoseconds Timer();
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::nanoseconds ElapsedTime();
	void FrameWait();
};

extern Time timeMng;

#endif