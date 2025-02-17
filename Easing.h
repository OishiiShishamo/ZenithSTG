#pragma once
#ifndef EASING_H
#define EASING_H

#include "Main.h"

//ラッパ関数
double Easing(int easeType, double t, double start, double end);

double Linear(double t, double start, double end);

double EaseInQuad(double t, double start, double end);

double EaseOutQuad(double t, double start, double end);

double EaseInOutQuad(double t, double start, double end);

double EaseInCubic(double t, double start, double end);

double EaseOutCubic(double t, double start, double end);

double EaseInOutCubic(double t, double start, double end);

#endif