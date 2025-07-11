#pragma once
#ifndef ZENITHSTG_SRC_GLOBAL_H_
#define ZENITHSTG_SRC_GLOBAL_H_

namespace zenithstg {
	inline constexpr double kPi = 3.1415926535897932384626433832795;
	inline constexpr double kTau = kPi * 2;
	inline constexpr double kOneDeg = (kPi / 180);

	inline constexpr int kFontTypeNum = 128;

	enum BlendType {
		kBlendDefault = -1,
		kBlendNoblend = DX_BLENDMODE_NOBLEND,
		kBlendAlpha = DX_BLENDMODE_ALPHA,
		kBlendAdd = DX_BLENDMODE_ADD,
		kBlendSub = DX_BLENDMODE_SUB,
		kBlendMulA = DX_BLENDMODE_MULA,
		kBlendInvSrc = DX_BLENDMODE_INVSRC,
		kBlendPmaAlpha = DX_BLENDMODE_PMA_ALPHA,
		kBlendPmaAdd = DX_BLENDMODE_PMA_ADD,
		kBlendPmaSub = DX_BLENDMODE_PMA_SUB,
		kBlendPmaInvSrc = DX_BLENDMODE_PMA_INVSRC,
	};

	enum ObjectType {
		kObjectBase = 0,
		kObjectBullet = 1,
		kObjectLaser = 2,
		kObjectBentLaser = 3,
		kObjectEnemy = 4,
		kObjectPlayerShot = 5,
		kObjectParticle = 6,
	};

	enum BulletType {
		kBulletNormal = 0,
		kBulletMedium = 1,
		kBulletScale = 2,
		kBulletLaser = 3,
		kBulletLight = 4,
		kBulletBig = 5,
	};

	enum ParticleType {
		kParticleLight = 0,
		kParticleStar = 1,
		kParticleRect = 2,
	};

	enum EnemyType {
		kEnemyNormal = 0,
	};

	enum PlayerShotType {
		kPlayerShotNormal = 0,
	};

	enum EaseType {
		kLinear = 0,
		kEaseInQuad = 1,
		kEaseOutQuad = 2,
		kEaseInOutQuad = 3,
		kEaseInCubic = 4,
		kEaseOutCubic = 5,
		kEaseInOutCubic = 6,
	};

	enum FontType {
		kFontUi0 = 0,
		kFontUi1 = 1,
	};

	enum SoundEffectType {
		kSoundEffectNone = -1,
		kSoundEffectGraze = 0,
		kSoundEffectPlayerHit = 1,
		kSoundEffectEnemyShot = 2,
	};

	enum AimType {
		kAimFalse = 0,
		kAimTrue = 1,
		kAimOffset = 2,
	};

	extern std::array<int, kFontTypeNum> font_types;
}

#endif