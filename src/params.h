#pragma once
#ifndef ZENITHSTG_SRC_PARAMS_H_
#define ZENITHSTG_SRC_PARAMS_H_

#define kUiPosOffset Vec2D(1400, 50)

#define kMaxBullet 8192
#define kMaxLaser 8192
#define kMaxEnemy 8192
#define kMaxPlayerShot 8192
#define kMaxParticle 8192

#define kGrazeEnabled 1
#define kBulletGrazeEveryFrame 0
#define kLaserGrazeEveryFrame 1

namespace zenithstg {
	inline constexpr long long kGrazeScore = 1;

	inline constexpr int kGrazeRange = 16;
}

#endif