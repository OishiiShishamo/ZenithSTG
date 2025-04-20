/**
* @file Vec2D.h
* @brief 2Dのベクトル関連 / 2D Vector Related.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef VECTOR_H
#define VECTOR_H

class Vec2D {
public:
	double x = 0;
	double y = 0;
	Vec2D(double x = 0, double y = 0) : x(x), y(y) {
	}

    Vec2D operator+(const Vec2D& rhs) const {
        return Vec2D(x + rhs.x, y + rhs.y);
    }

    Vec2D operator-(const Vec2D& rhs) const {
        return Vec2D(x - rhs.x, y - rhs.y);
    }

    Vec2D operator*(double scalar) const {
        return Vec2D(x * scalar, y * scalar);
    }

    Vec2D operator/(double scalar) const {
        return Vec2D(x / scalar, y / scalar);
    }

    Vec2D& operator+=(const Vec2D& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vec2D& operator-=(const Vec2D& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    bool operator==(const Vec2D& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    void VecNorm();
};

double crossProduct(const Vec2D& v1, const Vec2D& v2, const Vec2D& v3);
double Range(const Vec2D& v1, const Vec2D& v2);
Vec2D AngleToVec2D(double angle);
Vec2D RotatePoint(const Vec2D& pt, double angle);

#endif