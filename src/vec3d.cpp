#include "vec3d.h"

Vec3D
sumVec3D(Vec3D v1, Vec3D v2) {
	return Vec3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vec3D
subVec3D(Vec3D v1, Vec3D v2) {
	return Vec3D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vec3D
mulVec3D(Vec3D v1, double num) {
	return Vec3D(v1.x * num, v1.y * num, v1.z * num);
}

double
Range(Vec3D v1, Vec3D v2) {
	return std::sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y) + (v1.z - v2.z) * (v1.z - v2.z));
}

Vec3D
VecNorm(Vec3D v) {
	if (v.x + v.y + v.z == 0) return v;
	v.x *= 1 / std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.y *= 1 / std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.z *= 1 / std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return v;
}

Vec3D
AngleToVec3D(double angleX, double angleY, double angleZ) {
	return Vec3D(0, 0, 0);
}

Vec3D
RotatePoint(const Vec3D& pt, double angle) {
	double cosA = std::cos(angle);
	double sinA = std::sin(angle);
	return {
		pt.x * cosA + pt.y * sinA,
		pt.y * cosA - pt.x * sinA
	};
}

void GetRotationMatrixX(double angle, double matrix[3][3]) {
	matrix[0][0] = 1.0;
	matrix[0][1] = 0.0;
	matrix[0][2] = 0.0;
	matrix[1][0] = 0.0;
	matrix[1][1] = std::cos(angle);
	matrix[1][2] = -std::sin(angle);
	matrix[2][0] = 0.0;
	matrix[2][1] = std::sin(angle);
	matrix[2][2] = std::cos(angle);
}

void GetRotationMatrixY(double angle, double matrix[3][3]) {
	matrix[0][0] = std::cos(angle);
	matrix[0][1] = 0.0;
	matrix[0][2] = std::sin(angle);
	matrix[1][0] = 0.0;
	matrix[1][1] = 1.0;
	matrix[1][2] = 0.0;
	matrix[2][0] = -std::sin(angle);
	matrix[2][1] = 0.0;
	matrix[2][2] = std::cos(angle);
}

void GetRotationMatrixZ(double angle, double matrix[3][3]) {
	matrix[0][0] = std::cos(angle);
	matrix[0][1] = -std::sin(angle);
	matrix[0][2] = 0.0;
	matrix[1][0] = std::sin(angle);
	matrix[1][1] = std::cos(angle);
	matrix[1][2] = 0.0;
	matrix[2][0] = 0.0;
	matrix[2][1] = 0.0;
	matrix[2][2] = 1.0;
}