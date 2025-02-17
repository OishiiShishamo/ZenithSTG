#include "Collision.h"

int
colCircleAndCircle(Vec2D v1, Vec2D v2, double r) {
	if (Range(v1, v2) <= r) {
		return 1;
	}
	else {
		return 0;
	}
}
int
colPointAndRect(Vec2D v, Vec2D r1, Vec2D r2, Vec2D r3, Vec2D r4) {
	double cross1 = crossProduct(r1, r2, v);
	double cross2 = crossProduct(r2, r3, v);
	double cross3 = crossProduct(r3, r4, v);
	double cross4 = crossProduct(r4, r1, v);

	return (cross1 >= 0 && cross2 >= 0 && cross3 >= 0 && cross4 >= 0) ||
		(cross1 <= 0 && cross2 <= 0 && cross3 <= 0 && cross4 <= 0);
}