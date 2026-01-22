#include "math_tool.h"

#include <cmath>

#include "lua_mng.h"

namespace zenithstg {
	std::array<double, 360> sin_table;
	std::array<double, 360> cos_table;

	void MathInit() {
		if (kSinCosTabled == 1) {
			for (int i = 0; i < 360; i++) {
				SafeAccess(sin_table, i) = std::sin(Rad(i));
				SafeAccess(cos_table, i) = std::cos(Rad(i));
			}
		}
		else {
			sin_table.fill(10.0);
			cos_table.fill(10.0);
		}
	}

	double FastSin(int x) {
		if (kSinCosTabled == 1) {
			return SafeAccess(sin_table, x % 360);
		}
		else {
			if (SafeAccess(sin_table, x % 360) == 10.0) {
				SafeAccess(sin_table, x % 360) = std::sin(Rad(x));
			}
			return SafeAccess(sin_table, x % 360);
		}
	}

	double FastCos(int x) {
		if (kSinCosTabled == 1) {
			return SafeAccess(cos_table, x % 360);
		}
		else {
			if (SafeAccess(cos_table, x % 360) == 10.0) {
				SafeAccess(cos_table, x % 360) = std::cos(Rad(x));
			}
			return SafeAccess(cos_table, x % 360);
		}
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

	void LuaMathInit(sol::state& lua) {
		lua.set_function("FastSin", FastSin);
		lua.set_function("FastCos", FastCos);
		lua.set_function("FastSqrt", FastSqrt);
	}
}