#pragma once
#ifndef ZENITHSTG_SRC_PARAMS_H_
#define ZENITHSTG_SRC_PARAMS_H_

#include "vec2d.h"

inline constexpr int kMaxBullet = 8192;
inline constexpr int kMaxLaser = 8192;
inline constexpr int kMaxEnemy = 8192;
inline constexpr int kMaxPlayerShot = 8192;
inline constexpr int kMaxParticle = 8192;

inline constexpr int kGrazeEnabled = 1;
inline constexpr int kBulletGrazeEveryFrame = 0;
inline constexpr int kLaserGrazeEveryFrame = 1;

inline constexpr int kSinCosTabled = 1;

namespace zenithstg {
	const Vec2D kUiPosOffset = Vec2D(1400, 50);

	inline constexpr long long kGrazeScore = 1;

	inline constexpr int kGrazeRange = 16;
}

#endif