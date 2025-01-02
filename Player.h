#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Main.h"

#define DEFAULT_X CENTER_X
#define DEFAULT_Y 900
#define DEFAULT_LIFE 2
#define DEFAULT_BOMB 3
#define PLAYER_COL 5.0f
#define PLAYER_PROTECT 60

#define PLAYER_NUM 1

class Player {
public:
	int posX;
	int posY;
	double vecX;
	double vecY;
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
	double AimPlayer(double x, double y);
	double RangePlayer(double x, double y);
	void MovePlayer();
	void ShowPlayer(); 
	void HitPlayer();
	void RoutinePlayer();
};

extern Player Plyr;

#endif