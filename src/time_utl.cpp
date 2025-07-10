#include "main.h"

#include "time_utl.h"

namespace zenithstg {
	long long t = 0;
	long long fps = 60;

	void TimeUtl::StartTimer() {
		start_time_ = std::chrono::high_resolution_clock::now();
		front_frame_time_ = std::chrono::nanoseconds(0);
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
		std::chrono::nanoseconds tmp = front_frame_time_;
		front_frame_time_ = Timer();
		target_frame_ = static_cast<double>(Timer().count()) / std::chrono::nanoseconds(1000000000 / fps).count();
		return Timer() - tmp;
	}

	void TimeUtl::FrameWait() {
		std::chrono::nanoseconds frame_duration(1000000000 / fps);
		std::chrono::nanoseconds frame_elapsed = Timer() - front_frame_time_ + (std::chrono::nanoseconds)((rng() % 65535) / 32768);

		if (frame_elapsed < frame_duration - std::chrono::milliseconds(2)) {
			std::this_thread::sleep_for((frame_duration - frame_elapsed) - std::chrono::milliseconds(2));
		}
	}

	TimeUtl time_mng_;
}