#include "Collision.h"

int
colCircleAndCircle(Vector v1, Vector v2, double r) {
	if (Range(v1, v2) <= r) {
		return 1;
	}
	else {
		return 0;
	}
}
int
colPointAndRect(Vector v, Vector r1, Vector r2, Vector r3, Vector r4) {
	double cross1 = crossProduct(r1, r2, v);
	double cross2 = crossProduct(r2, r3, v);
	double cross3 = crossProduct(r3, r4, v);
	double cross4 = crossProduct(r4, r1, v);

	return (cross1 >= 0 && cross2 >= 0 && cross3 >= 0 && cross4 >= 0) ||
		(cross1 <= 0 && cross2 <= 0 && cross3 <= 0 && cross4 <= 0);
}