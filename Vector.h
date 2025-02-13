#pragma once
#ifndef VECTOR_H
#define VECTOR_H

class Vector {
public:
	double x;
	double y;
	Vector(double x, double y) : x(x), y(y) {
	}
};

double crossProduct(Vector v1, Vector v2, Vector v3);
double Range(Vector v1, Vector v2);
Vector VecNorm(Vector v);

#endif