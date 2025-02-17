#include "Easing.h"

//ラッパ関数
double
Easing(int easeType, double t, double start, double end) {
	switch (easeType) {
	case 0:
		return Linear(t, start, end) * 1.0f;
		break;
	case 1:
		return EaseInQuad(t, start, end) * 1.0f;
		break;
	case 2:
		return EaseOutQuad(t, start, end) * 1.0f;
		break;
	case 3:
		return EaseInOutQuad(t, start, end) * 1.0f;
		break;
	case 4:
		return EaseInCubic(t, start, end) * 1.0f;
		break;
	case 5:
		return EaseOutCubic(t, start, end) * 1.0f;
		break;
	case 6:
		return EaseInOutCubic(t, start, end) * 1.0f;
		break;
	default:
		return Linear(t, start, end) * 1.0f;
		break;
	}
}

// 線形補間
double
Linear(double t, double start, double end) {
	return start + (end - start) * t;
}

// イージイン (加速) - 二次曲線
double
EaseInQuad(double t, double start, double end) {
	return start + (end - start) * (t * t);
}

// イージアウト (減速) - 二次曲線
double
EaseOutQuad(double t, double start, double end) {
	return start + (end - start) * (t * (2 - t));
}

// イージインアウト (加速と減速) - 二次曲線
double
EaseInOutQuad(double t, double start, double end) {
	if (t < 0.5f) return start + (end - start) * (2 * t * t);
	return start + (end - start) * (-1 + (4 - 2 * t) * t);
}

// イージイン (加速) - 三次曲線
double
EaseInCubic(double t, double start, double end) {
	return start + (end - start) * (t * t * t);
}

// イージアウト (減速) - 三次曲線
double
EaseOutCubic(double t, double start, double end) {
	t -= 1;
	return start + (end - start) * (t * t * t + 1);
}

// イージインアウト (加速と減速) - 三次曲線
double
EaseInOutCubic(double t, double start, double end) {
	if (t < 0.5f) return start + (end - start) * (4 * t * t * t);
	t -= 1;
	return start + (end - start) * (t * t * t * 4 + 1);
}