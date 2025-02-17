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
	int defaultLife;
	int Life;
	int defaultBomb;
	int Bomb;
	double colSize;
	double Slow;
	double Fast;
	int isFocus;
	int isShowCol;
	int Protect;
	int protectTime;
	int isMouse;
	double AimPlayer(Vec2D v);
	double RangePlayer(Vec2D v);
	void MovePlayer();
	void ShowPlayer();
	void Shot();
	void HitPlayer();
	void RoutinePlayer();
};

#endif