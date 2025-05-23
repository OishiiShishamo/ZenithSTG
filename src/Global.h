#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H

#include <cmath>

#include "DxLib.h"
#include "Debug.h"
#include "Logging.h"

#ifdef NDEBUG
#define SAFE_ACCESS(array, index) (array[index])
#else
#define SAFE_ACCESS(array, index) (array.at(index))
#endif

inline constexpr double pi = 3.1415926535897932384626433832795;
inline constexpr double tau = pi * 2;
inline constexpr double oneDeg = (pi / 180);

inline constexpr int fontTypeNum = 128;

enum blendType {
	BLEND_DEFAULT = -1,
	BLEND_NOBLEND = DX_BLENDMODE_NOBLEND,
	BLEND_ALPHA = DX_BLENDMODE_ALPHA,
	BLEND_ADD = DX_BLENDMODE_ADD,
	BLEND_SUB = DX_BLENDMODE_SUB,
	BLEND_MULA = DX_BLENDMODE_MULA,
	BLEND_INVSRC = DX_BLENDMODE_INVSRC,
	BLEND_PMA_ALPHA = DX_BLENDMODE_PMA_ALPHA,
	BLEND_PMA_ADD = DX_BLENDMODE_PMA_ADD,
	BLEND_PMA_SUB = DX_BLENDMODE_PMA_SUB,
	BLEND_PMA_INVSRC = DX_BLENDMODE_PMA_INVSRC,
};

enum objectType {
	OBJECT_BULLET = 0,
	OBJECT_LASER = 1,
	OBJECT_BENT_LASER = 2,
	OBJECT_ENEMY = 3,
	OBJECT_PLAYER_SHOT = 4,
};

enum bulletType {
	B_NORMAL = 0,
	B_MIDIAM = 1,
	B_UROKO = 2,
	B_LASER = 3,
	B_LIGHT = 4,
	B_BIG = 5,
};

enum enemyType {
	E_NORMAL = 0,
};

enum playerShotType {
	PS_NORMAL = 0,
};

enum easeType {
	LINEAR = 0,
	EASEINQUAD = 1,
	EASEOUTQUAD = 2,
	EASEINOUTQUAD = 3,
	EASEINCUBIC = 4,
	EASEOUTCUBIC = 5,
	EASEINOUTCUBIC = 6,
};

enum fontType {
	UI_0 = 0,
	UI_1 = 1,
};

extern std::array<int, fontTypeNum> fontTypes;

#endif