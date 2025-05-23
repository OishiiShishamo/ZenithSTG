﻿#pragma once
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
class Script;
class Background;

#include <algorithm>
#include <any>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <DirectXMath.h>
#include <fstream> 
#include <immintrin.h>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <thread>
#include <tuple>
#include <type_traits>
#include <vector>
#include <pmmintrin.h>
#include <emmintrin.h>

#include "Global.h"

#include "Collision.h"
#include "Property.h"
#include "Utility.h"
#include "Vec2D.h"

using namespace std;

#define PRINT(...) printf(__VA_ARGS__)	

#define CENTER_X 960
#define CENTER_Y 540
#define CENTER Vec2D(CENTER_X, CENTER_Y)

#define BORDER_LEFT 528
#define BORDER_RIGHT 1392
#define BORDER_UP 35
#define BORDER_DOWN 1045

#define STAGE_NUM 1

#define MAX_BULLET 8192
#define MAX_LASER 8192
#define MAX_ENEMY 8192
#define MAX_PLAYER_SHOT 8192

#define FPS_HISTORY_LENGTH 120

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

extern std::array<Script, STAGE_NUM> Scripts;

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
extern std::array<int, 128> defaultEnemyBlend;
extern std::array<int, 128> defaultPlayerShotBlend;
extern std::array<double, 128> drawRatioBulletGraphs;
extern std::array<double, 128> drawRatioEnemyGraphs;
extern std::array<double, 128> drawRatioPlayerShotGraphs;
extern int fpsHistoryIndex;

extern double screenSizeRate;
extern double screenRotaX;
extern double screenRotaY;
extern double screenRotaZ;

#endif