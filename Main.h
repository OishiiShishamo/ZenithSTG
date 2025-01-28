#pragma once
#ifndef MAIN_H
#define MAIN_H

struct imageRes;

class Color;
class Object;
class Bullet;
class Player;
class mainLoop;

#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "boost/multiprecision/cpp_int.hpp"
#include "DxLib.h"
#include "Utility.h"

#define PI DX_PI
#define TAU PI * 2
#define ICHIDO (PI / 180)

#define CENTER_X 960
#define CENTER_Y 540

#define BORDER_LEFT 0
#define BORDER_RIGHT 1920
#define BORDER_UP 0
#define BORDER_DOWN 1080

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

struct imageRes {
	std::vector<int> UIGH;
	std::vector<int> BulletBackGH;
	std::vector<int> BulletFrontGH;
	std::vector<int> EnemyGH;
	std::vector<int> FaceGH;
	std::vector<int> PlayerGH;
	std::vector<int> EtcGH;
};

extern imageRes imgRes;

extern mainLoop Loop;

extern std::vector<Bullet> Bullets;

extern long long frame;
extern long long fps;
extern int currentBlendMode;
extern int currentBlendPal;
extern std::vector<int> defaultBulletBlend;
extern int isColShow;

extern int backgroundCanvas;
extern int bulletCanvas;
extern int playerCanvas;
extern int playerShotCanvas;
extern int bombCanvas;
extern int effectCanvas;
extern int screenCanvas;

#endif