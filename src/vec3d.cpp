#include "vec3d.h"

Vec3D
sumVec3D(Vec3D v1, Vec3D v2) {
	return Vec3D(v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_);
}

Vec3D
subVec3D(Vec3D v1, Vec3D v2) {
	return Vec3D(v1.x_ - v2.x_, v1.y_ - v2.y_, v1.z_ - v2.z_);
}

Vec3D
mulVec3D(Vec3D v1, double num) {
	return Vec3D(v1.x_ * num, v1.y_ * num, v1.z_ * num);
}

double
Range(Vec3D v1, Vec3D v2) {
	return std::sqrt((v1.x_ - v2.x_) * (v1.x_ - v2.x_) + (v1.y_ - v2.y_) * (v1.y_ - v2.y_) + (v1.z_ - v2.z_) * (v1.z_ - v2.z_));
}

Vec3D
VecNorm(Vec3D v) {
	if (v.x_ + v.y_ + v.z_ == 0) return v;
	v.x_ *= 1 / std::sqrt(v.x_ * v.x_ + v.y_ * v.y_ + v.z_ * v.z_);
	v.y_ *= 1 / std::sqrt(v.x_ * v.x_ + v.y_ * v.y_ + v.z_ * v.z_);
	v.z_ *= 1 / std::sqrt(v.x_ * v.x_ + v.y_ * v.y_ + v.z_ * v.z_);
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
		pt.x_ * cosA + pt.y_ * sinA,
		pt.y_ * cosA - pt.x_ * sinA
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