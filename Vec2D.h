/**
* @file Vec2D.h
* @brief 2Dのベクトル関連 / 2D Vector Related.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef VECTOR_H
#define VECTOR_H

#include <emmintrin.h>

class Vec2D {
public:
    __m128d xy;

	Vec2D(double x = 0, double y = 0) {
        xy = _mm_set_pd(y, x);
	}

    explicit Vec2D(__m128d reg) : xy(reg) {}

    Vec2D operator+(const Vec2D& rhs) const {
        return Vec2D(_mm_add_pd(xy, rhs.xy));
    }

    Vec2D operator-(const Vec2D& rhs) const {
        return Vec2D(_mm_sub_pd(xy, rhs.xy));
    }

    Vec2D operator*(double scalar) const {
        __m128d s = _mm_set1_pd(scalar);
        return Vec2D(_mm_mul_pd(xy, s));
    }

    Vec2D operator*(const Vec2D& rhs) const {
        return Vec2D(_mm_mul_pd(xy, rhs.xy));
    }

    Vec2D operator/(double scalar) const {
        __m128d s = _mm_set1_pd(scalar);
        return Vec2D(_mm_div_pd(xy, s));
    }

    Vec2D operator/(const Vec2D& rhs) const {
        return Vec2D(_mm_div_pd(xy, rhs.xy));
    }

    Vec2D& operator+=(const Vec2D& rhs) {
        xy = _mm_add_pd(xy, rhs.xy);
        return *this;
    }

    Vec2D& operator-=(const Vec2D& rhs) {
        xy = _mm_sub_pd(xy, rhs.xy);
        return *this;
    }

    Vec2D& operator*=(double scalar) {
        __m128d s = _mm_set1_pd(scalar);
        xy = _mm_mul_pd(xy, s);
        return *this;
    }

    Vec2D& operator*=(const Vec2D& rhs) {
        xy = _mm_mul_pd(xy, rhs.xy);
        return *this;
    }

    Vec2D& operator/=(double scalar) {
        __m128d s = _mm_set1_pd(scalar);
        xy = _mm_div_pd(xy, s);
        return *this;
    }

    Vec2D& operator/=(const Vec2D& rhs) {
        xy = _mm_div_pd(xy, rhs.xy);
        return *this;
    }

    bool operator==(const Vec2D& rhs) const {
        __m128d cmp = _mm_cmpeq_pd(xy, rhs.xy);
        return (_mm_movemask_pd(cmp) == 0b11);
    }

    double GetX() const {
        return _mm_cvtsd_f64(xy);
    }

    double GetY() const {
        return _mm_cvtsd_f64(_mm_unpackhi_pd(xy, xy));
    }

    void VecNorm() {
        __m128d mul = _mm_mul_pd(xy, xy);

        __m128d temp = _mm_unpackhi_pd(mul, mul);
        __m128d sum = _mm_add_pd(mul, temp);

        __m128d length = _mm_sqrt_pd(sum);

        alignas(16) double lenArr[2];
        _mm_store_pd(lenArr, length);
        if (lenArr[0] != 0.0) {
            xy = _mm_div_pd(xy, _mm_set1_pd(lenArr[0]));
        }
    }
};

double crossProduct(const Vec2D& v1, const Vec2D& v2, const Vec2D& v3);
double Range(const Vec2D& v1, const Vec2D& v2);
Vec2D AngleToVec2D(double angle);
Vec2D RotatePoint(const Vec2D& pt, double angle);

#endif