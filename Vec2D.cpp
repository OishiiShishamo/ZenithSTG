#include "Vec2D.h"
#include "MathTool.h"
#include <cmath>

double
crossProduct(const Vec2D& v1, const Vec2D& v2, const Vec2D& v3) {
    __m128d v1_xy = v1.xy;
    __m128d v2_xy = v2.xy;
    __m128d v3_xy = v3.xy;

    __m128d diff1 = _mm_sub_pd(v2_xy, v1_xy);
    __m128d diff2 = _mm_sub_pd(v3_xy, v1_xy);

    __m128d mul1 = _mm_mul_pd(diff1, diff2);

    __m128d temp = _mm_shuffle_pd(mul1, mul1, 1);
    __m128d result = _mm_sub_pd(mul1, temp);

    alignas(16) double res[2];
    _mm_store_pd(res, result);
    return res[0];
}

double
Range(const Vec2D& v1, const Vec2D& v2) {
    __m128d v1_xy = v1.xy;
    __m128d v2_xy = v2.xy;

    __m128d diff = _mm_sub_pd(v1_xy, v2_xy);

    __m128d sqr = _mm_mul_pd(diff, diff);

    __m128d sum = _mm_add_pd(sqr, _mm_shuffle_pd(sqr, sqr, 1));

    __m128d length = _mm_sqrt_pd(sum);

    alignas(16) double len[2];
    _mm_store_pd(len, length);
    return len[0];
}

Vec2D
AngleToVec2D(double angle) {
	return { 
		cos(angle), 
		-sin(angle) 
	};
}

Vec2D
RotatePoint(const Vec2D& pt, double angle) {
	double cosA = cos(angle);
	double sinA = sin(angle);
	return {
		pt.GetX() * cosA + pt.GetY() * sinA,
		pt.GetY() * cosA - pt.GetX() * sinA
	};
}