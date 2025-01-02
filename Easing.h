#pragma once
#ifndef EASING_H
#define EASING_H

#define LINEAR 0
#define EASEINQUAD 1
#define EASEOUTQUAD 2
#define EASEINOUTQUAD 3
#define EASEINCUBIC 4
#define EASEOUTCUBIC 5
#define EASEINOUTCUBIC 6

#include "main.h"

// 線形補間
double Linear(double t, double start, double end);

// イージイン (加速) - 二次曲線
double EaseInQuad(double t, double start, double end);

// イージアウト (減速) - 二次曲線
double EaseOutQuad(double t, double start, double end);

// イージインアウト (加速と減速) - 二次曲線
double EaseInOutQuad(double t, double start, double end);

// イージイン (加速) - 三次曲線
double EaseInCubic(double t, double start, double end);

// イージアウト (減速) - 三次曲線
double EaseOutCubic(double t, double start, double end);

// イージインアウト (加速と減速) - 三次曲線
double EaseInOutCubic(double t, double start, double end);

#endif