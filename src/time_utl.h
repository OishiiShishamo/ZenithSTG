#pragma once
#ifndef ZENITHSTG_SRC_TIMEUTL_H_
#define ZENITHSTG_SRC_TIMEUTL_H_

class timeUtl {
public:
	long long target_frame = 0;
	std::chrono::nanoseconds front_frame_time;
	std::chrono::nanoseconds elapsedus = std::chrono::nanoseconds(0);
	void StartTimer();
	void StopTimer();
	void ResetTimer();
	std::chrono::milliseconds NSec2MSec(std::chrono::nanoseconds ns);
	double NSec2Double(std::chrono::nanoseconds);
	std::chrono::nanoseconds Timer();
	std::chrono::high_resolution_clock::time_point start_time;
	std::chrono::nanoseconds ElapsedTime();
	void FrameWait();
};

extern timeUtl timeMng;

#endif
