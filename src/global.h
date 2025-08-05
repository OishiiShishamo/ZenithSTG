#pragma once
#ifndef ZENITHSTG_SRC_GLOBAL_H_
#define ZENITHSTG_SRC_GLOBAL_H_

namespace zenithstg {
	inline constexpr double kPi = 3.1415926535897932384626433832795;
	inline constexpr double kTau = kPi * 2;
	inline constexpr double kOneDeg = (kPi / 180);

	inline constexpr double kE = 2.7182818284590452353602874713527;

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
		kObjectBase,
		kObjectBullet,
		kObjectLaser,
		kObjectBentLaser,
		kObjectEnemy,
		kObjectPlayerShot,
		kObjectParticle,
	};

	enum BulletType {
		kBulletNormal,
		kBulletMedium,
		kBulletScale,
		kBulletLaser,
		kBulletLight,
		kBulletBig,
	};

	enum ParticleType {
		kParticleLight,
		kParticleStar,
		kParticleRect,
	};

	enum EnemyType {
		kEnemyNormal,
	};

	enum PlayerShotType {
		kPlayerShotNormal,
	};

	enum EaseType {
		kLinear,

		kEaseInSine, kEaseOutSine, kEaseInOutSine,
		kEaseInQuad, kEaseOutQuad, kEaseInOutQuad,
		kEaseInCubic, kEaseOutCubic, kEaseInOutCubic,
		kEaseInQuart, kEaseOutQuart, kEaseInOutQuart,
		kEaseInQuint, kEaseOutQuint, kEaseInOutQuint,
		kEaseInExpo, kEaseOutExpo, kEaseInOutExpo,
		kEaseInCirc, kEaseOutCirc, kEaseInOutCirc,
		kEaseInBack, kEaseOutBack, kEaseInOutBack,
		kEaseInElastic, kEaseOutElastic, kEaseInOutElastic,
		kEaseInBounce, kEaseOutBounce, kEaseInOutBounce,
	};

	enum FontType {
		kFontUi0,
		kFontUi1,
	};

	enum BgmType {
		kBgmNone = -1,
		kBgm1,
	};

	enum SoundEffectType {
		kSoundEffectNone = -1,
		kSoundEffectGraze,
		kSoundEffectPlayerHit,
		kSoundEffectEnemyShot,
	};

	enum AimType {
		kAimFalse,
		kAimTrue,
		kAimOffset,
	};

	extern std::array<int, kFontTypeNum> font_types;
}

#endif