#include "math_tool.h"

#include <cmath>

namespace zenithstg {
	std::array<double, 360> sin_table;
	std::array<double, 360> cos_table;

	void MathInit() {
		sin_table.fill(10.0);
		cos_table.fill(10.0);
	}

	double FastSin(int x) {
		if (SafeAccess(sin_table, x % 360) == 10.0) {
			SafeAccess(sin_table, x % 360) = std::sin(Rad(x));
		}
		return SafeAccess(sin_table, x % 360);
	}

	double FastCos(int x) {
		if (SafeAccess(cos_table, x % 360) == 10.0) {
			SafeAccess(cos_table, x % 360) = std::cos(Rad(x));
		}
		return SafeAccess(cos_table, x % 360);
	}

	double FastSqrt(double x, double epsilon) {
		if (x < 0) return -1;
		if (x == 0) return 0;

		double guess = x;
		while (std::abs(guess * guess - x) > epsilon) {
			guess = (guess + x / guess) / 2;
		}
		return guess;
	}
}