#pragma once
#ifndef ZENITHSTG_SRC_EASING_H_
#define ZENITHSTG_SRC_EASING_H_

namespace zenithstg {
	//ラッパ関数
	double Easing(int ease_type, double t, double start, double end);

	// イージング時間計算関数
	double EasingTimeCalc(double now_time, double start_time, double end_time);

	double Linear(double t, double start, double end);

	double EaseInQuad(double t, double start, double end);

	double EaseOutQuad(double t, double start, double end);

	double EaseInOutQuad(double t, double start, double end);

	double EaseInCubic(double t, double start, double end);

	double EaseOutCubic(double t, double start, double end);

	double EaseInOutCubic(double t, double start, double end);
}

#endif