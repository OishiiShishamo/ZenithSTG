#pragma once
#ifndef MAIN_H
#define MAIN_H

struct imageRes;

class timeUtl;
class Property;
class Color;
class Object;
class Bullet;
class Laser;
class Enemy;
class Player;
class playerShot;
class Effect;
class mainLoop;
class Vec2D;
class Script;
class Background;

#define NOMINMAX

#include <algorithm>
#include <atomic>
#include <any>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <DirectXMath.h>
#include <execution>
#include <fstream> 
#include <immintrin.h>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <thread>
#include <tuple>
#include <type_traits>
#include <inttypes.h>
#include <random>
#include <stdint.h>
#include <vector>
#include <pmmintrin.h>
#include <emmintrin.h>

#include "Global.h"
#include "Params.h"

#include "Collision.h"
#include "Utility.h"
#include "Vec2D.h"

#define PRINT(...) printf(__VA_ARGS__)	

#define CENTER_X 960
#define CENTER_Y 540
#define CENTER Vec2D(CENTER_X, CENTER_Y)

#define BORDER_LEFT 528
#define BORDER_RIGHT 1392
#define BORDER_UP 35
#define BORDER_DOWN 1045

#define STAGE_NUM 1

#define FPS_HISTORY_LENGTH 120

#define GRAPHIC_HANDLER_NUM 256
#define SOUND_BGM_HANDLER_NUM 256
#define SOUND_EFFECT_HANDLER_NUM 256
#define SOUND_VOICES 32

struct imageRes {
	std::array<int, GRAPHIC_HANDLER_NUM> UIGH;
	std::array<int, GRAPHIC_HANDLER_NUM> BulletBackGH;
	std::array<int, GRAPHIC_HANDLER_NUM> BulletFrontGH;
	std::array<int, GRAPHIC_HANDLER_NUM> EffectBackGH;
	std::array<int, GRAPHIC_HANDLER_NUM> EffectFrontGH;
	std::array<int, GRAPHIC_HANDLER_NUM> EnemyGH;
	std::array<int, GRAPHIC_HANDLER_NUM> FaceGH;
	std::array<int, GRAPHIC_HANDLER_NUM> PlayerGH;
	std::array<int, GRAPHIC_HANDLER_NUM> ShotGH;
	std::array<int, GRAPHIC_HANDLER_NUM> EtcGH;
};

extern imageRes imgRes;

extern Property Properties;

extern mainLoop Loop;

extern std::array<Script, STAGE_NUM> Scripts;

extern std::unique_ptr<std::array<Bullet, MAX_BULLET>> Bullets;
extern std::array<Bullet*, MAX_BULLET> BulletPtrs;
extern std::vector<int> BlankBullets;
extern std::unique_ptr<std::array<Laser, MAX_LASER>> Lasers;
extern std::unique_ptr<std::array<Enemy, MAX_ENEMY>> Enemies;
extern std::unique_ptr<std::array<playerShot, MAX_PLAYER_SHOT>> plyrShots;
extern std::array<Effect, MAX_EFFECT> Effects;

extern std::random_device rng;

extern int numThreads;

extern long long t;
extern long long fps;
extern int currentBlendMode;
extern int currentBlendPal;
extern std::array<double, FPS_HISTORY_LENGTH> fpsHistory;
extern std::array<int, GRAPHIC_HANDLER_NUM> defaultBulletBlend;
extern std::array<int, GRAPHIC_HANDLER_NUM> defaultEnemyBlend;
extern std::array<int, GRAPHIC_HANDLER_NUM> defaultPlayerShotBlend;
extern std::array<int, GRAPHIC_HANDLER_NUM> defaultEffectBlend;
extern std::array<double, GRAPHIC_HANDLER_NUM> drawRatioBulletGraphs;
extern std::array<double, GRAPHIC_HANDLER_NUM> drawRatioEnemyGraphs;
extern std::array<double, GRAPHIC_HANDLER_NUM> drawRatioPlayerShotGraphs;
extern std::array<double, GRAPHIC_HANDLER_NUM> drawRatioEffectGraphs;
extern int fpsHistoryIndex;

extern double RandTMP;

extern std::atomic<long long> score;
extern std::atomic<long long> graze;

extern double screenSizeRate;
extern double screenRotaX;
extern double screenRotaY;
extern double screenRotaZ;

#endif