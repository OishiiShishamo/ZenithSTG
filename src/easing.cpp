#include "easing.h"

namespace zenithstg {
	//ラッパ関数
	double Easing(int ease_type, double t, double start, double end) {
		switch (ease_type) {
		case kLinear:
			return Linear(t, start, end);
			break;
		case kEaseInQuad:
			return EaseInQuad(t, start, end);
			break;
		case kEaseOutQuad:
			return EaseOutQuad(t, start, end);
			break;
		case kEaseInOutQuad:
			return EaseInOutQuad(t, start, end);
			break;
		case kEaseInCubic:
			return EaseInCubic(t, start, end);
			break;
		case kEaseOutCubic:
			return EaseOutCubic(t, start, end);
			break;
		case kEaseInOutCubic:
			return EaseInOutCubic(t, start, end);
			break;
		default:
			Logger("存在しないイージングタイプを選択しています。 / You have selected an easing type that does not exist.", LogType::kLogWarning);
			return Linear(t, start, end);
			break;
		}
	}

	// イージング時間計算関数
	double EasingTimeCalc(double now_time, double start_time, double end_time) {
		double result = (static_cast<double>(now_time) - static_cast<double>(start_time)) / (static_cast<double>(end_time) - static_cast<double>(start_time));
		if (result > 1) result = 1;
		return result;
	}

	// 線形補間
	double Linear(double t, double start, double end) {
		return start + (end - start) * t;
	}

	// イージイン (加速) - 二次曲線
	double EaseInQuad(double t, double start, double end) {
		return start + (end - start) * (t * t);
	}

	// イージアウト (減速) - 二次曲線
	double EaseOutQuad(double t, double start, double end) {
		return start + (end - start) * (t * (2 - t));
	}

	// イージインアウト (加速と減速) - 二次曲線
	double EaseInOutQuad(double t, double start, double end) {
		if (t < 0.5f) return start + (end - start) * (2 * t * t);
		return start + (end - start) * (-1 + (4 - 2 * t) * t);
	}

	// イージイン (加速) - 三次曲線
	double EaseInCubic(double t, double start, double end) {
		return start + (end - start) * (t * t * t);
	}

	// イージアウト (減速) - 三次曲線
	double EaseOutCubic(double t, double start, double end) {
		t -= 1;
		return start + (end - start) * (t * t * t + 1);
	}

	// イージインアウト (加速と減速) - 三次曲線
	double EaseInOutCubic(double t, double start, double end) {
		if (t < 0.5f) return start + (end - start) * (4 * t * t * t);
		t -= 1;
		return start + (end - start) * (t * t * t * 4 + 1);
	}
}