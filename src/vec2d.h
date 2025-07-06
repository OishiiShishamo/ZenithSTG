/**
* @file Vec2D.h
* @brief 2Dのベクトル関連 / 2D Vector Related.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef ZENITHSTG_SRC_VEC2D_H_
#define ZENITHSTG_SRC_VEC2D_H_

class alignas(16) Vec2D {
public:
	Vec2D(double x = 0, double y = 0) {
		xy_ = _mm_set_pd(y, x);
	}

	explicit Vec2D(__m128d reg) : xy_(reg) {}

	Vec2D operator+(const Vec2D& rhs) const { return Vec2D(_mm_add_pd(xy_, rhs.xy_)); }
	Vec2D operator-(const Vec2D& rhs) const { return Vec2D(_mm_sub_pd(xy_, rhs.xy_)); }
	Vec2D operator*(double scalar) const { return Vec2D(_mm_mul_pd(xy_, _mm_set1_pd(scalar))); }
	Vec2D operator*(const Vec2D& rhs) const { return Vec2D(_mm_mul_pd(xy_, rhs.xy_)); }
	Vec2D operator/(double scalar) const { return Vec2D(_mm_div_pd(xy_, _mm_set1_pd(scalar))); }
	Vec2D operator/(const Vec2D& rhs) const { return Vec2D(_mm_div_pd(xy_, rhs.xy_)); }

	Vec2D& operator=(const Vec2D& rhs) { if (this != &rhs) { xy_ = rhs.xy_; return *this; } }
	Vec2D& operator+=(const Vec2D& rhs) { xy_ = _mm_add_pd(xy_, rhs.xy_); return *this; }
	Vec2D& operator-=(const Vec2D& rhs) { xy_ = _mm_sub_pd(xy_, rhs.xy_); return *this; }
	Vec2D& operator*=(double scalar) { xy_ = _mm_mul_pd(xy_, _mm_set1_pd(scalar)); return *this; }
	Vec2D& operator*=(const Vec2D& rhs) { xy_ = _mm_mul_pd(xy_, rhs.xy_); return *this; }
	Vec2D& operator/=(double scalar) { xy_ = _mm_div_pd(xy_, _mm_set1_pd(scalar)); return *this; }
	Vec2D& operator/=(const Vec2D& rhs) { xy_ = _mm_div_pd(xy_, rhs.xy_); return *this; }

	bool operator==(const Vec2D& rhs) const { return (*this == rhs); }
	bool operator!=(const Vec2D& rhs) const { return !(*this == rhs); }

	double GetX() const { return _mm_cvtsd_f64(xy_); }
	double GetY() const { return _mm_cvtsd_f64(_mm_unpackhi_pd(xy_, xy_)); }
	__m128d GetXY() const { return xy_; }

	void SetX(double x) { xy_ = _mm_unpacklo_pd(_mm_set_sd(x), _mm_unpackhi_pd(xy_, xy_)); }
	void SetY(double y) { xy_ = _mm_unpacklo_pd(_mm_unpacklo_pd(xy_, xy_), _mm_set_sd(y)); }
	void SetXY(double x, double y) { xy_ = _mm_set_pd(y, x); }
	void SetXY(__m128d xy) { xy_ = xy; }

	void VecNorm() {
		__m128d mul = _mm_mul_pd(xy_, xy_);
		__m128d temp = _mm_unpackhi_pd(mul, mul);
		__m128d sum = _mm_add_pd(mul, temp);
		__m128d length = _mm_sqrt_pd(sum);

		double len = _mm_cvtsd_f64(length);
		if (len != 0.0) {
			xy_ = _mm_div_pd(xy_, _mm_set1_pd(len));
		}
	}
private:
	__m128d xy_;
};

double CrossProduct(const Vec2D& v1, const Vec2D& v2, const Vec2D& v3);
double Range(const Vec2D& v1, const Vec2D& v2);
Vec2D AngleToVec2D(double angle);
Vec2D RotatePoint(const Vec2D& pt, double angle);

#endif