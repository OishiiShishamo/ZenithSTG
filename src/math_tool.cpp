#include "math_tool.h"

double
FastSqrt(double x, double epsilon = 1e-3) {
	if (x < 0) return -1;
	if (x == 0) return 0;

	double guess = x;
	while (std::abs(guess * guess - x) > epsilon) {
		guess = (guess + x / guess) / 2;
	}
	return guess;
}
