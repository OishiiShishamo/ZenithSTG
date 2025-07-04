/**
* @file Vec2D.h
* @brief 3Dのベクトル関連(90%未完成) / 3D Vector Related(90% WIP).
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef ZENITHSTG_SRC_VEC3D_H_
#define ZENITHSTG_SRC_VEC3D_H_

class Vec3D {
public:
	double x = 0;
	double y = 0;
	double z = 0;
	Vec3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {
	}
};

Vec3D sumVec3D(Vec3D v1, Vec3D v2);
Vec3D subVec3D(Vec3D v1, Vec3D v2);
Vec3D mulVec3D(Vec3D v1, double num);
double Range(Vec3D v1, Vec3D v2);
Vec3D VecNorm(Vec3D v);
Vec3D AngleToVec3D(double angleX, double angleY, double angleZ);
//Vec3D RotatePoint(const Vec3D& pt, double angleX, double angleY, double angleZ);

#endif