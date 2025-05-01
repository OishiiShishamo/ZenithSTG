/**
* @file Vec2D.h
* @brief 2Dのベクトル関連 / 2D Vector Related.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef VEC2D_H
#define VEC2D_H

#include <emmintrin.h>
#include <pmmintrin.h>

class Vec2D {
public:
	__m128d xy;

	Vec2D(double x = 0, double y = 0) {
		xy = _mm_set_pd(y, x);
	}

	explicit Vec2D(__m128d reg) : xy(reg) {}

	Vec2D operator+(const Vec2D& rhs) const { return Vec2D(_mm_add_pd(xy, rhs.xy)); }
	Vec2D operator-(const Vec2D& rhs) const { return Vec2D(_mm_sub_pd(xy, rhs.xy)); }
	Vec2D operator*(double scalar) const { return Vec2D(_mm_mul_pd(xy, _mm_set1_pd(scalar))); }
	Vec2D operator*(const Vec2D& rhs) const { return Vec2D(_mm_mul_pd(xy, rhs.xy)); }
	Vec2D operator/(double scalar) const { return Vec2D(_mm_div_pd(xy, _mm_set1_pd(scalar))); }
	Vec2D operator/(const Vec2D& rhs) const { return Vec2D(_mm_div_pd(xy, rhs.xy)); }

	Vec2D& operator+=(const Vec2D& rhs) { xy = _mm_add_pd(xy, rhs.xy); return *this; }
	Vec2D& operator-=(const Vec2D& rhs) { xy = _mm_sub_pd(xy, rhs.xy); return *this; }
	Vec2D& operator*=(double scalar) { xy = _mm_mul_pd(xy, _mm_set1_pd(scalar)); return *this; }
	Vec2D& operator*=(const Vec2D& rhs) { xy = _mm_mul_pd(xy, rhs.xy); return *this; }
	Vec2D& operator/=(double scalar) { xy = _mm_div_pd(xy, _mm_set1_pd(scalar)); return *this; }
	Vec2D& operator/=(const Vec2D& rhs) { xy = _mm_div_pd(xy, rhs.xy); return *this; }

	bool operator==(const Vec2D& rhs) const { return (_mm_movemask_pd(_mm_cmpeq_pd(xy, rhs.xy)) == 0b11); }
	bool operator!=(const Vec2D& rhs) const { return !(*this == rhs); }

	double GetX() const { return _mm_cvtsd_f64(xy); }
	double GetY() const { return _mm_cvtsd_f64(_mm_unpackhi_pd(xy, xy)); }

	void SetX(double x) { xy = _mm_unpacklo_pd(_mm_set_sd(x), _mm_unpackhi_pd(xy, xy)); }
	void SetY(double y) { xy = _mm_unpacklo_pd(_mm_unpacklo_pd(xy, xy), _mm_set_sd(y)); }

	void VecNorm() {
		__m128d mul = _mm_mul_pd(xy, xy);
		__m128d temp = _mm_unpackhi_pd(mul, mul);
		__m128d sum = _mm_add_pd(mul, temp);
		__m128d length = _mm_sqrt_pd(sum);

		double len = _mm_cvtsd_f64(length);
		if (len != 0.0) {
			xy = _mm_div_pd(xy, _mm_set1_pd(len));
		}
	}
};

double crossProduct(const Vec2D& v1, const Vec2D& v2, const Vec2D& v3);
double Range(const Vec2D& v1, const Vec2D& v2);
Vec2D AngleToVec2D(double angle);
Vec2D RotatePoint(const Vec2D& pt, double angle);

#endif