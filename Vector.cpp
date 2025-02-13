#include "Main.h"

#include "Vector.h"

double
crossProduct(Vector v1, Vector v2, Vector v3) {
	return (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);
}

double
Range(Vector v1, Vector v2) {
	return sqrt(pow((v1.y - v2.y), 2) + pow((v1.x - v2.x), 2));
}

Vector
VecNorm(Vector v) {
	if (v.x + v.y == 0) return v;
	v.x *= 1 / std::sqrt(v.x * v.x + v.y * v.y);
	v.y *= 1 / std::sqrt(v.x * v.x + v.y * v.y);
	return v;
}