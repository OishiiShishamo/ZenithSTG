#pragma once
#ifndef ZENITHSTG_SRC_TIMEUTL_H_
#define ZENITHSTG_SRC_TIMEUTL_H_

namespace zenithstg {
	class TimeUtl {
	public:
		long long target_t_ = 0;
		std::chrono::nanoseconds last_frame_time_;
		std::chrono::nanoseconds elapsedus_ = std::chrono::nanoseconds(0);
		std::chrono::high_resolution_clock::time_point start_time_;
		void StartTimer();
		void StopTimer();
		void ResetTimer();
		std::chrono::milliseconds NSec2MSec(std::chrono::nanoseconds ns);
		double NSec2Double(std::chrono::nanoseconds);
		std::chrono::nanoseconds Timer();
		std::chrono::nanoseconds ElapsedTime();
		void FrameWait();
	};

	extern TimeUtl time_mng_;
}

#endif
