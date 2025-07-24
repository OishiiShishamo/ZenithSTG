#include "time_utl.h"

namespace zenithstg {
	long long t = 0;
	long long fps = 60;

	void TimeUtl::StartTimer() {
		start_time_ = std::chrono::high_resolution_clock::now();
		last_frame_time_ = std::chrono::nanoseconds(0);
		target_t_ = 0;
		t = 0;
	}

	void TimeUtl::StopTimer() {
		elapsedus_ += Timer();
	}

	void TimeUtl::ResetTimer() {
		StartTimer();
		elapsedus_ = std::chrono::nanoseconds(0);
	}

	std::chrono::milliseconds TimeUtl::NSec2MSec(std::chrono::nanoseconds ns) {
		return duration_cast<std::chrono::milliseconds>(ns);
	}

	double TimeUtl::NSec2Double(std::chrono::nanoseconds ns) {
		return std::chrono::duration<double>(ns).count();
	}

	std::chrono::nanoseconds TimeUtl::Timer() {
		return elapsedus_ + std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start_time_);
	}

	std::chrono::nanoseconds TimeUtl::ElapsedTime() {
		std::chrono::nanoseconds tmp = last_frame_time_;
		last_frame_time_ = Timer();
		target_t_ = static_cast<double>(Timer().count()) / std::chrono::nanoseconds(1000000000 / fps).count();
		return Timer() - tmp;
	}

	void TimeUtl::FrameWait() {
		std::chrono::nanoseconds frame_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(1.0 / fps));
		std::chrono::nanoseconds frame_elapsed = Timer() - last_frame_time_;

		if (frame_elapsed < frame_duration - std::chrono::milliseconds(4)) {
			std::this_thread::sleep_for((frame_duration - frame_elapsed) - std::chrono::milliseconds(4));
		}

		// 微調整 / fine tuning.
		while (Timer() - last_frame_time_ < frame_duration) {
			std::this_thread::yield();
		}
	}

	TimeUtl time_mng_;
}