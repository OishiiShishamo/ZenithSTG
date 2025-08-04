#include "easing.h"

namespace zenithstg {
	//ラッパ関数
	double Easing(int ease_type, double t, double start, double end) {
		switch (ease_type) {
		case kLinear: return Linear(t, start, end);

		case kEaseInSine: return EaseInSine(t, start, end);
		case kEaseOutSine: return EaseOutSine(t, start, end);
		case kEaseInOutSine: return EaseInOutSine(t, start, end);

		case kEaseInQuad: return EaseInQuad(t, start, end);
		case kEaseOutQuad: return EaseOutQuad(t, start, end);
		case kEaseInOutQuad: return EaseInOutQuad(t, start, end);

		case kEaseInCubic: return EaseInCubic(t, start, end);
		case kEaseOutCubic: return EaseOutCubic(t, start, end);
		case kEaseInOutCubic: return EaseInOutCubic(t, start, end);

		case kEaseInQuart: return EaseInQuart(t, start, end);
		case kEaseOutQuart: return EaseOutQuart(t, start, end);
		case kEaseInOutQuart: return EaseInOutQuart(t, start, end);

		case kEaseInQuint: return EaseInQuint(t, start, end);
		case kEaseOutQuint: return EaseOutQuint(t, start, end);
		case kEaseInOutQuint: return EaseInOutQuint(t, start, end);

		case kEaseInExpo: return EaseInExpo(t, start, end);
		case kEaseOutExpo: return EaseOutExpo(t, start, end);
		case kEaseInOutExpo: return EaseInOutExpo(t, start, end);

		case kEaseInCirc: return EaseInCirc(t, start, end);
		case kEaseOutCirc: return EaseOutCirc(t, start, end);
		case kEaseInOutCirc: return EaseInOutCirc(t, start, end);

		case kEaseInBack: return EaseInBack(t, start, end);
		case kEaseOutBack: return EaseOutBack(t, start, end);
		case kEaseInOutBack: return EaseInOutBack(t, start, end);

		case kEaseInElastic: return EaseInElastic(t, start, end);
		case kEaseOutElastic: return EaseOutElastic(t, start, end);
		case kEaseInOutElastic: return EaseInOutElastic(t, start, end);

		case kEaseInBounce: return EaseInBounce(t, start, end);
		case kEaseOutBounce: return EaseOutBounce(t, start, end);
		case kEaseInOutBounce: return EaseInOutBounce(t, start, end);

		default:
			Logger("存在しないイージングタイプを選択しています。 / You have selected an easing type that does not exist.", LogType::kLogWarning);
			return Linear(t, start, end);
		}
	}

	// イージング時間計算関数
	double EasingTimeCalc(double now_time, double start_time, double end_time) {
		double result = (static_cast<double>(now_time) - static_cast<double>(start_time)) / (static_cast<double>(end_time) - static_cast<double>(start_time));
		if (result > 1) result = 1;
		return result;
	}

	double Linear(double t, double start, double end) {
		return start + (end - start) * t;
	}

	// Sine
	double EaseInSine(double t, double start, double end) {
		return start + (end - start) * (1 - std::cos((t * kPi) / 2));
	}
	double EaseOutSine(double t, double start, double end) {
		return start + (end - start) * std::sin((t * kPi) / 2);
	}
	double EaseInOutSine(double t, double start, double end) {
		return start + (end - start) * (-0.5 * (std::cos(kPi * t) - 1));
	}

	// Quad
	double EaseInQuad(double t, double start, double end) {
		return start + (end - start) * (t * t);
	}
	double EaseOutQuad(double t, double start, double end) {
		return start + (end - start) * (t * (2 - t));
	}
	double EaseInOutQuad(double t, double start, double end) {
		if (t < 0.5f) return start + (end - start) * (2 * t * t);
		return start + (end - start) * (-1 + (4 - 2 * t) * t);
	}

	// Cubic
	double EaseInCubic(double t, double start, double end) {
		return start + (end - start) * (t * t * t);
	}
	double EaseOutCubic(double t, double start, double end) {
		t -= 1;
		return start + (end - start) * (t * t * t + 1);
	}
	double EaseInOutCubic(double t, double start, double end) {
		if (t < 0.5f) return start + (end - start) * (4 * t * t * t);
		t -= 1;
		return start + (end - start) * (t * t * t * 4 + 1);
	}

	// Quart
	double EaseInQuart(double t, double start, double end) {
		return start + (end - start) * (t * t * t * t);
	}
	double EaseOutQuart(double t, double start, double end) {
		t -= 1;
		return start + (end - start) * (1 - t * t * t * t);
	}
	double EaseInOutQuart(double t, double start, double end) {
		if (t < 0.5) return start + (end - start) * (8 * t * t * t * t);
		t -= 1;
		return start + (end - start) * (1 - 8 * t * t * t * t);
	}

	// Quint
	double EaseInQuint(double t, double start, double end) {
		return start + (end - start) * (t * t * t * t * t);
	}
	double EaseOutQuint(double t, double start, double end) {
		t -= 1;
		return start + (end - start) * (t * t * t * t * t + 1);
	}
	double EaseInOutQuint(double t, double start, double end) {
		if (t < 0.5) return start + (end - start) * (16 * t * t * t * t * t);
		t -= 1;
		return start + (end - start) * (16 * t * t * t * t * t + 1);
	}

	// Expo
	double EaseInExpo(double t, double start, double end) {
		return start + (end - start) * (t == 0 ? 0 : std::pow(2, 10 * (t - 1)));
	}
	double EaseOutExpo(double t, double start, double end) {
		return start + (end - start) * (t == 1 ? 1 : 1 - std::pow(2, -10 * t));
	}
	double EaseInOutExpo(double t, double start, double end) {
		if (t == 0) return start;
		if (t == 1) return end;
		if (t < 0.5) return start + (end - start) * (std::pow(2, 20 * t - 10) / 2);
		else return start + (end - start) * ((2 - std::pow(2, -20 * t + 10)) / 2);
	}

	// Circ
	double EaseInCirc(double t, double start, double end) {
		return start + (end - start) * (1 - FastSqrt(1 - t * t));
	}
	double EaseOutCirc(double t, double start, double end) {
		t -= 1;
		return start + (end - start) * FastSqrt(1 - t * t);
	}
	double EaseInOutCirc(double t, double start, double end) {
		if (t < 0.5)
			return start + (end - start) * (0.5 * (1 - FastSqrt(1 - 4 * t * t)));
		t = t * 2 - 1;
		return start + (end - start) * (0.5 * (FastSqrt(1 - t * t) + 1));
	}

	// Back
	double EaseInBack(double t, double start, double end) {
		const double c1 = 1.70158;
		const double c3 = c1 + 1;
		return start + (end - start) * (c3 * t * t * t - c1 * t * t);
	}
	double EaseOutBack(double t, double start, double end) {
		const double c1 = 1.70158;
		const double c3 = c1 + 1;
		t -= 1;
		return start + (end - start) * (1 + c3 * t * t * t + c1 * t * t);
	}
	double EaseInOutBack(double t, double start, double end) {
		const double c1 = 1.70158;
		const double c2 = c1 * 1.525;
		if (t < 0.5) return start + (end - start) * (0.5 * (((2 * t) * (2 * t)) * ((c2 + 1) * 2 * t - c2)));
		t = 2 * t - 2;
		return start + (end - start) * (0.5 * ((t * t) * ((c2 + 1) * t + c2) + 2));
	}

	// Elastic
	double EaseInElastic(double t, double start, double end) {
		if (t == 0) return start;
		if (t == 1) return end;
		double c = (end - start);
		const double p = 0.3;
		const double s = p / 4;
		t -= 1;
		return start - c * std::pow(2, 10 * t) * std::sin((t - s) * (2 * kPi) / p);
	}
	double EaseOutElastic(double t, double start, double end) {
		if (t == 0) return start;
		if (t == 1) return end;
		double c = (end - start);
		const double p = 0.3;
		const double s = p / 4;
		return start + c * std::pow(2, -10 * t) * std::sin((t - s) * (2 * kPi) / p) + c;
	}
	double EaseInOutElastic(double t, double start, double end) {
		if (t == 0) return start;
		if (t == 1) return end;
		double c = (end - start);
		const double p = 0.45;
		const double s = p / 4;
		if (t < 0.5) {
			t = t * 2 - 1;
			return start - 0.5 * c * std::pow(2, 10 * t) * std::sin((t - s) * (2 * kPi) / p);
		}
		t = t * 2 - 1;
		return start + 0.5 * c * std::pow(2, -10 * t) * std::sin((t - s) * (2 * kPi) / p) + c * 0.5;
	}

	// Bounce
	double EaseOutBounce(double t, double start, double end) {
		double c = end - start;
		if (t < (1 / 2.75)) {
			return c * (7.5625 * t * t) + start;
		}
		else if (t < (2 / 2.75)) {
			t -= (1.5 / 2.75);
			return c * (7.5625 * t * t + 0.75) + start;
		}
		else if (t < (2.5 / 2.75)) {
			t -= (2.25 / 2.75);
			return c * (7.5625 * t * t + 0.9375) + start;
		}
		else {
			t -= (2.625 / 2.75);
			return c * (7.5625 * t * t + 0.984375) + start;
		}
	}
	double EaseInBounce(double t, double start, double end) {
		return end - EaseOutBounce(1 - t, 0, end - start);
	}
	double EaseInOutBounce(double t, double start, double end) {
		if (t < 0.5) return EaseInBounce(t * 2, 0, end - start) * 0.5 + start;
		else return EaseOutBounce(t * 2 - 1, 0, end - start) * 0.5 + (end + start) * 0.5;
	}
}