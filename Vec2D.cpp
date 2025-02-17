#include "Vec2D.h"

#include <cmath>

Vec2D
sumVec2D(Vec2D v1, Vec2D v2) {
	return Vec2D(v1.x + v2.x, v1.y + v2.y);
}

Vec2D
subVec2D(Vec2D v1, Vec2D v2) {
	return Vec2D(v1.x - v2.x, v1.y - v2.y);
}

Vec2D
mulVec2D(Vec2D v1, double num) {
	return Vec2D(v1.x * num, v1.y * num);
}

double
crossProduct(Vec2D v1, Vec2D v2, Vec2D v3) {
	return (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);
}

double
Range(Vec2D v1, Vec2D v2) {
	return std::sqrt(std::pow((v1.y - v2.y), 2) + std::pow((v1.x - v2.x), 2));
}

Vec2D
VecNorm(Vec2D v) {
	if (v.x + v.y == 0) return v;
	v.x *= 1 / std::sqrt(v.x * v.x + v.y * v.y);
	v.y *= 1 / std::sqrt(v.x * v.x + v.y * v.y);
	return v;
}