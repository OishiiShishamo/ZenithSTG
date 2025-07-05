#pragma once
#ifndef ZENITHSTG_SRC_PLAYER_H_
#define ZENITHSTG_SRC_PLAYER_H_

#define kPlayerDefaultX kCenterX
#define kPlayerDefaultY 900
#define kPlayerDefaultPos Vec2D(kPlayerDefaultX, kPlayerDefaultY)
#define kDefaultLife 2
#define kDefaultBomb 3
#define kPlayerCol 0.0f
#define kPlayerProtect 60

#define kPlayerSideBorderOffset 16
#define kPlayerTopBorderOffset 24
#define kPlayerBottomBorderOffset 32

#define kPlayerNum 1

#include "main.h"

class Player {
public:
	Vec2D pos = Vec2D(0, 0);
	Vec2D vec = Vec2D(0, 0);
	int default_life = kDefaultLife;
	std::atomic<int> life = 0;
	int default_bomb = kDefaultBomb;
	std::atomic<int> bomb = 0;
	double col_size = 0.0f;
	double slow = 0;
	double fast = 0;
	int is_focus = 0;
	int is_show_col = 0;
	int rrotect = 0;
	std::atomic<int> protect_time = 0;
	int is_mouse = 0;
	double AimPlayer(const Vec2D& v);
	double RangePlayer(const Vec2D& v);
	void MovePlayer();
	void ShowPlayer();
	void Shot();
	void HitPlayer();
	void RoutinePlayer();
};

extern Player Plyr;

#endif