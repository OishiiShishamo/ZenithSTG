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
class Player;
class playerShot;
class mainLoop;
class Vec2D;

#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "boost/multiprecision/cpp_int.hpp"
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

#define BLEND_DEFAULT -1
#define BLEND_NOBLEND DX_BLENDMODE_NOBLEND
#define BLEND_ALPHA DX_BLENDMODE_ALPHA
#define BLEND_ADD DX_BLENDMODE_ADD
#define BLEND_SUB DX_BLENDMODE_SUB
#define BLEND_MULA DX_BLENDMODE_MULA
#define BLEND_INVSRC DX_BLENDMODE_INVSRC
#define BLEND_PMA_ALPHA DX_BLENDMODE_PMA_ALPHA
#define BLEND_PMA_ADD DX_BLENDMODE_PMA_ADD
#define BLEND_PMA_SUB DX_BLENDMODE_PMA_SUB
#define BLEND_PMA_INVSRC DX_BLENDMODE_PMA_INVSRC

#define OBJECT_BULLET 0
#define OBJECT_LASER 1
#define OBJECT_BENT_LASER 2
#define OBJECT_ENEMY 3
#define OBJECT_PLAYER_SHOT 4

#define B_NORMAL 0
#define B_MIDIAM 1
#define B_UROKO 2
#define B_LASER 3
#define B_LIGHT 4
#define B_BIG 5

#define LINEAR 0
#define EASEINQUAD 1
#define EASEOUTQUAD 2
#define EASEINOUTQUAD 3
#define EASEINCUBIC 4
#define EASEOUTCUBIC 5
#define EASEINOUTCUBIC 6

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

extern std::vector<Bullet> Bullets;
extern std::vector<Laser> Lasers;
extern std::vector<playerShot> plyrShots;

extern long long frame;
extern long long fps;
extern int currentBlendMode;
extern int currentBlendPal;
extern std::vector<int> defaultBulletBlend;
extern std::vector<int> defaultPlayerShotBlend;
extern std::vector<float> drawRatioBulletGraphs;
extern int isColShow;

extern int backgroundCanvas;
extern int bulletCanvas;
extern int playerCanvas;
extern int playerShotCanvas;
extern int bombCanvas;
extern int effectCanvas;
extern int screenCanvas;

#endif