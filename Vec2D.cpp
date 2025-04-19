#include "Vec2D.h"
#include "MathTool.h"
#include <cmath>

void
Vec2D::VecNorm() {
	if (x + y == 0) return;
	Vec2D v = Vec2D(x, y);
	v.x *= 1 / fastSqrt(v.x * v.x + v.y * v.y);
	v.y *= 1 / fastSqrt(v.x * v.x + v.y * v.y);
	*this = v;
}

double
crossProduct(const Vec2D& v1, const Vec2D& v2, const Vec2D& v3) {
	return (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);
}

double
Range(const Vec2D& v1, const Vec2D& v2) {
	return fastSqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

Vec2D
AngleToVec2D(double angle) {
	return { 
		cos(angle), 
		-sin(angle) 
	};
}

Vec2D
RotatePoint(const Vec2D& pt, double angle) {
	double cosA = cos(angle);
	double sinA = sin(angle);
	return {
		pt.x * cosA + pt.y * sinA,
		pt.y * cosA - pt.x * sinA
	};
}