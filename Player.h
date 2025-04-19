#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#define P_DEFAULT_X CENTER_X
#define P_DEFAULT_Y 900
#define P_DEFAULT_POS Vec2D(P_DEFAULT_X, P_DEFAULT_Y)
#define DEFAULT_LIFE 2
#define DEFAULT_BOMB 3
#define PLAYER_COL 5.0f
#define PLAYER_PROTECT 60

#define PLAYER_NUM 1

#include "Main.h"

class Player {
public:
	Vec2D pos = Vec2D(0, 0);
	Vec2D vec = Vec2D(0, 0);
	int defaultLife = 0;
	int Life = 0;
	int defaultBomb = 0;
	int Bomb = 0;
	double colSize = 0.0f;
	double Slow = 0;
	double Fast = 0;
	int isFocus = 0;
	int isShowCol = 0;
	int Protect = 0;
	int protectTime = 0;
	int isMouse = 0;
	double AimPlayer(const Vec2D& v);
	double RangePlayer(const Vec2D& v);
	void MovePlayer();
	void ShowPlayer();
	void Shot();
	void HitPlayer();
	void RoutinePlayer();
};

#endif