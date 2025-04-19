#pragma once
#ifndef MAIN_H
#define MAIN_H

struct imageRes;

class Time;
class Property;
class Color;
class Object;
class Bullet;
class Laser;
class Enemy;
class Player;
class playerShot;
class mainLoop;
class Vec2D;

#include <any>
#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <thread>

#include <DirectXMath.h>
#include <immintrin.h>

#include "DxLib.h"
#include "Utility.h"
#include "Vec2D.h"
#include "Collision.h"
#include "Property.h"

#define PI DX_PI
#define TAU PI * 2
#define ICHIDO (PI / 180)

#define CENTER_X 960
#define CENTER_Y 540
#define CENTER Vec2D(CENTER_X, CENTER_Y)

#define BORDER_LEFT 528
#define BORDER_RIGHT 1392
#define BORDER_UP 35
#define BORDER_DOWN 1045

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define MAX_BULLET 8192
#define MAX_LASER 8192
#define MAX_ENEMY 8192
#define MAX_PLAYER_SHOT 8192

#define FPS_HISTORY_LENGTH 120

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

struct imageRes {
	std::vector<int> UIGH;
	std::vector<int> BulletBackGH;
	std::vector<int> BulletFrontGH;
	std::vector<int> EnemyGH;
	std::vector<int> FaceGH;
	std::vector<int> PlayerGH;
	std::vector<int> ShotGH;
	std::vector<int> EtcGH;
};

extern imageRes imgRes;

extern Property Properties;

extern mainLoop Loop;

extern Player Plyr;

extern std::array<Bullet, MAX_BULLET> Bullets;
extern std::array<Laser, MAX_LASER> Lasers;
extern std::array<Enemy, MAX_ENEMY> Enemies;
extern std::array<playerShot, MAX_PLAYER_SHOT> plyrShots;

extern int numThreads;

extern long long frame;
extern long long fps;
extern int currentBlendMode;
extern int currentBlendPal;
extern std::array<double, FPS_HISTORY_LENGTH> fpsHistory;
extern std::array<int, 128> defaultBulletBlend;
extern std::array<int, 128> defaultPlayerShotBlend;
extern std::array<double, 128> drawRatioBulletGraphs;
extern std::array<double, 128> drawRatioEnemyGraphs;
extern std::array<double, 128> drawRatioPlayerShotGraphs;
extern int fpsHistoryIndex;
extern int isColShow;

extern double screenSizeRate;
extern double screenRotaX;
extern double screenRotaY;
extern double screenRotaZ;

extern int backgroundCanvas;
extern int bulletCanvas;
extern int playerCanvas;
extern int playerShotCanvas;
extern int bombCanvas;
extern int effectCanvas;
extern int screenCanvas;

#endif