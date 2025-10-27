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
        Color() noexcept : rgba_(_mm_set1_ps(1.0f)) {}

        Color(float r, float g, float b, float a = 255.0f) noexcept {
            rgba_ = _mm_setr_ps(r, g, b, a);
            rgba_ = _mm_div_ps(_mm_max_ps(_mm_min_ps(rgba_, _mm_set1_ps(255.0f)), _mm_set1_ps(0.0f)), _mm_set1_ps(255.0f));
        }

        explicit Color(__m128 rgba) noexcept : rgba_(rgba) {
            Saturate();
        }

        float GetR() const noexcept { return rgba_array()[0] * 255.0f; }
        float GetG() const noexcept { return rgba_array()[1] * 255.0f; }
        float GetB() const noexcept { return rgba_array()[2] * 255.0f; }
        float GetA() const noexcept { return rgba_array()[3] * 255.0f; }
        float GetNR() const noexcept { return rgba_array()[0]; }
        float GetNG() const noexcept { return rgba_array()[1]; }
        float GetNB() const noexcept { return rgba_array()[2]; }
        float GetNA() const noexcept { return rgba_array()[3]; }

        __m128 Get() const noexcept { return rgba_; }

        void Set(float r, float g, float b, float a = 255.0f) noexcept {
            rgba_ = _mm_setr_ps(r, g, b, a);
            rgba_ = _mm_div_ps(rgba_, _mm_set1_ps(255.0f));
            Saturate();
        }

        unsigned int GetDxColor() const noexcept {
            alignas(16) float arr[4];
            _mm_storeu_ps(arr, _mm_mul_ps(rgba_, _mm_set1_ps(255.0f)));
            return GetColor(arr[0], arr[1], arr[2]);
        }

        Color operator+(const Color& rhs) const noexcept { return Color(_mm_add_ps(rgba_, rhs.rgba_)); }
        Color operator-(const Color& rhs) const noexcept { return Color(_mm_sub_ps(rgba_, rhs.rgba_)); }
        Color operator*(const Color& rhs) const noexcept { return Color(_mm_mul_ps(rgba_, rhs.rgba_)); }
        Color operator/(const Color& rhs) const noexcept { return Color(_mm_div_ps(rgba_, rhs.rgba_)); }

        Color operator*(float s) const noexcept { return Color(_mm_mul_ps(rgba_, _mm_set1_ps(s))); }
        Color operator/(float s) const noexcept { return Color(_mm_div_ps(rgba_, _mm_set1_ps(s))); }

        Color& operator+=(const Color& rhs) noexcept { rgba_ = _mm_add_ps(rgba_, rhs.rgba_); Saturate(); return *this; }
        Color& operator-=(const Color& rhs) noexcept { rgba_ = _mm_sub_ps(rgba_, rhs.rgba_); Saturate(); return *this; }
        Color& operator*=(float s) noexcept { rgba_ = _mm_mul_ps(rgba_, _mm_set1_ps(s)); Saturate(); return *this; }

    private:
        __m128 rgba_;

        void Saturate() noexcept {
            rgba_ = _mm_max_ps(_mm_min_ps(rgba_, _mm_set1_ps(1.0f)), _mm_set1_ps(0.0f));
        }

        inline std::array<float, 4> rgba_array() const noexcept {
            alignas(16) float tmp[4];
            _mm_storeu_ps(tmp, rgba_);
            return { tmp[0], tmp[1], tmp[2], tmp[3] };
        }
    };
}

#endif