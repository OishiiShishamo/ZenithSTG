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

//ÉâÉbÉpä÷êî
double Easing(int easeType, double t, double start, double end);

double Linear(double t, double start, double end);

double EaseInQuad(double t, double start, double end);

double EaseOutQuad(double t, double start, double end);

double EaseInOutQuad(double t, double start, double end);

double EaseInCubic(double t, double start, double end);

double EaseOutCubic(double t, double start, double end);

double EaseInOutCubic(double t, double start, double end);

#endif