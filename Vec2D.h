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

Vec2D sumVec2D(Vec2D v1, Vec2D v2);
Vec2D subVec2D(Vec2D v1, Vec2D v2);
Vec2D mulVec2D(Vec2D v1, double num);
double crossProduct(Vec2D v1, Vec2D v2, Vec2D v3);
double Range(Vec2D v1, Vec2D v2);
Vec2D VecNorm(Vec2D v);

#endif