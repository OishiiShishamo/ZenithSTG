#pragma once
#ifndef ZENITHSTG_SRC_TIMEUTL_H_
#define ZENITHSTG_SRC_TIMEUTL_H_

#include <chrono>
#include <string>
#include <thread>
#include <windows.h>
#include <mmsystem.h>

#include "logging.h"
#include "main.h"

namespace zenithstg {
	extern long long t;
	extern long long fps;

	class TimeUtl {
	public:
		long long target_t_ = 0;

		void StartTimer();
		void StopTimer();
		void ResetTimer();
		std::chrono::milliseconds NSec2MSec(std::chrono::nanoseconds ns);
		double NSec2Double(std::chrono::nanoseconds);
		std::chrono::nanoseconds Timer();
		void ElapsedTime();
		void FrameWait();
	private:
		std::chrono::nanoseconds last_frame_time_ = std::chrono::nanoseconds(0);
		std::chrono::nanoseconds elapsedus_ = std::chrono::nanoseconds(0);
		std::chrono::high_resolution_clock::time_point start_time_;
		std::chrono::nanoseconds frame_duration_ = std::chrono::nanoseconds(1000000000 / fps);
	};

	extern TimeUtl time_mng_;
}

#endif
