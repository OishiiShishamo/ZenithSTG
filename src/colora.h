#pragma once
#ifndef ZENITHSTG_SRC_COLOR_H_
#define ZENITHSTG_SRC_COLOR_H_

//SIMPLE

#define kColorRed 255, 0, 0
#define kColorGreen 0, 255, 0
#define kColorBlue 0, 0, 255
#define kColorYellow 255, 255, 0
#define kColorAqua 0, 255, 255
#define kColorCyan 0, 255, 255
#define kColorPurple 255, 0, 255
#define kColorOrange 255, 127, 0
#define kColorWhite 255, 255, 255
#define kColorGray 127, 127, 127
#define kColorBlack 0, 0, 0

//NOT-SIMPLE

#define kColorAliceBlue 240, 248, 255
#define kColorAntiqueWhite 250, 235, 215
#define kColorAquamarine 127, 255, 212
#define kColorAzure 240, 255, 255
#define kColorBeige 245, 245, 220
#define kColorBisque 255, 228, 196
#define kColorBlanchedalmond 255, 235, 205
#define kColorBlueViolet 138, 43, 226
#define kColorBrown 165, 42, 42
#define kColorBurlyWood 222, 184, 135

#include <algorithm>

#include <emmintrin.h>
#include <immintrin.h>
#include <pmmintrin.h>

#include "DxLib.h"

#include "global.h"

namespace  zenithstg {
	class alignas(16) Color {
	public:
		float GetR() const {
			alignas(16) float rgba_array_[4];
			_mm_store_ps(rgba_array_, rgba_);
			return rgba_array_[0];
		}
		float GetG() const {
			alignas(16) float rgba_array_[4];
			_mm_store_ps(rgba_array_, rgba_);
			return rgba_array_[1];
		}
		float GetB() const {
			alignas(16) float rgba_array_[4];
			_mm_store_ps(rgba_array_, rgba_);
			return rgba_array_[2];
		}
		float GetA() const {
			alignas(16) float rgba_array_[4];
			_mm_store_ps(rgba_array_, rgba_);
			return rgba_array_[3];
		}
		__m128 GetRGBA() const { return rgba_; }
		void SetR(float r) {
			alignas(16) float rgba_array_[4];
			_mm_store_ps(rgba_array_, rgba_);
			rgba_array_[0] = r / 255.0f;
			rgba_ = _mm_load_ps(rgba_array_);
			Saturate();
		}
		void SetG(float g) {
			alignas(16) float rgba_array_[4];
			_mm_store_ps(rgba_array_, rgba_);
			rgba_array_[1] = g / 255.0f;
			rgba_ = _mm_load_ps(rgba_array_);
			Saturate();
		}
		void SetB(float b) {
			alignas(16) float rgba_array_[4];
			_mm_store_ps(rgba_array_, rgba_);
			rgba_array_[2] = b / 255.0f;
			rgba_ = _mm_load_ps(rgba_array_);
			Saturate();
		}
		void SetA(float a) {
			alignas(16) float rgba_array_[4];
			_mm_store_ps(rgba_array_, rgba_);
			rgba_array_[3] = a / 255.0f;
			rgba_ = _mm_load_ps(rgba_array_);
			Saturate();
		}
		void SetRGBA(float r, float g, float b, float a = 255.0f) { rgba_ = _mm_set_ps(a / 255.0f, b / 255.0f, g / 255.0f, r / 255.0f); }
		void SetRGBA(__m128 rgba) {
			rgba_ = rgba;
			Saturate255();
			rgba_ = _mm_div_ps(rgba_, _mm_set1_ps(255.0f));
		}
		int GetDxColor() const { return GetColor(GetR255(), GetG255(), GetB255()); }

		void Saturate() {
			rgba_ = _mm_max_ps(_mm_min_ps(rgba_, _mm_set1_ps(1.0f)), _mm_set1_ps(0.0f));
		}
		void Saturate255() {
			rgba_ = _mm_max_ps(_mm_min_ps(rgba_, _mm_set1_ps(255.0f)), _mm_set1_ps(0.0f));
		}

		Color operator+(const Color& rhs) const { return Color(_mm_add_ps(rgba_, rhs.rgba_)); }
		Color operator+(float scalar)     const { return Color(_mm_add_ps(rgba_, _mm_set1_ps(scalar))); }
		Color operator-(const Color& rhs) const { return Color(_mm_sub_ps(rgba_, rhs.rgba_)); }
		Color operator-(float scalar)     const { return Color(_mm_sub_ps(rgba_, _mm_set1_ps(scalar))); }
		Color operator*(const Color& rhs) const { return Color(_mm_mul_ps(rgba_, rhs.rgba_)); }
		Color operator*(float scalar)     const { return Color(_mm_mul_ps(rgba_, _mm_set1_ps(scalar))); }
		Color operator/(const Color& rhs) const { return Color(_mm_div_ps(rgba_, rhs.rgba_)); }
		Color operator/(float scalar)     const { return Color(_mm_div_ps(rgba_, _mm_set1_ps(scalar))); }

		Color& operator=(const Color& rhs) { if (this != &rhs) { rgba_ = rhs.rgba_;          return *this; } }
		Color& operator+=(const Color& rhs) { rgba_ = _mm_add_ps(rgba_, rhs.rgba_);           return *this; }
		Color& operator+=(float scalar) { rgba_ = _mm_add_ps(rgba_, _mm_set1_ps(scalar)); return *this; }
		Color& operator-=(const Color& rhs) { rgba_ = _mm_sub_ps(rgba_, rhs.rgba_);           return *this; }
		Color& operator-=(float scalar) { rgba_ = _mm_sub_ps(rgba_, _mm_set1_ps(scalar)); return *this; }
		Color& operator*=(const Color& rhs) { rgba_ = _mm_mul_ps(rgba_, rhs.rgba_);           return *this; }
		Color& operator*=(float scalar) { rgba_ = _mm_mul_ps(rgba_, _mm_set1_ps(scalar)); return *this; }
		Color& operator/=(const Color& rhs) { rgba_ = _mm_div_ps(rgba_, rhs.rgba_);           return *this; }
		Color& operator/=(float scalar) { rgba_ = _mm_div_ps(rgba_, _mm_set1_ps(scalar)); return *this; }

		Color() {
			rgba_ = _mm_set_ss(1.0f);
		}
		Color(__m128 rgba) : rgba_(rgba) {
			Saturate255();
			rgba_ = _mm_div_ps(rgba_, _mm_set1_ps(255.0f));
		}
		Color(float rgba) {
			rgba_ = _mm_set1_ps(rgba);
			rgba_ = _mm_div_ps(rgba_, _mm_set1_ps(255.0f));
		}
		Color(float r, float g, float b, float a = 255.0f) {
			rgba_ = _mm_set_ps(a, b, g, r);
			Saturate255();
			rgba_ = _mm_div_ps(rgba_, _mm_set1_ps(255.0f));
		}
	private:
		__m128 rgba_;
	};

	inline __m128 sin(__m128 x) {
		const __m128 tau = _mm_set1_ps(kTau);
		const __m128 inv2pi = _mm_set1_ps(1 / kTau);

		__m128 k = _mm_mul_ps(x, inv2pi);
		k = _mm_round_ps(k, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
		__m128 xr = _mm_sub_ps(x, _mm_mul_ps(k, tau));

		__m128 x2 = _mm_mul_ps(xr, xr);
		__m128 x3 = _mm_mul_ps(x2, xr);
		__m128 x5 = _mm_mul_ps(x3, x2);

		const __m128 c3 = _mm_set1_ps(1.0f / 120.0f);
		const __m128 c1 = _mm_set1_ps(-1.0f / 6.0f);

		__m128 poly = _mm_fmadd_ps(c3, x2, c1);
		poly = _mm_fmadd_ps(poly, x2, _mm_set1_ps(1.0f));
		return _mm_mul_ps(xr, poly);
	}

	inline __m128 cos(__m128 x) {
		const __m128 pihalf = _mm_set1_ps(kPi / 2);
		return sin(_mm_add_ps(x, pihalf));
	}
}

#endif