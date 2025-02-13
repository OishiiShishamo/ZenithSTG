#pragma once
#ifndef VECTOR_H
#define VECTOR_H

class Vec2D {
public:
	double x;
	double y;
	Vec2D(double x, double y) : x(x), y(y) {
	}
};

double crossProduct(Vec2D v1, Vec2D v2, Vec2D v3);
double Range(Vec2D v1, Vec2D v2);
Vec2D VecNorm(Vec2D v);

#endif