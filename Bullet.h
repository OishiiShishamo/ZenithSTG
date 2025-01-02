#pragma once
#ifndef BULLET_H
#define BULLET_H

#define B_NORMAL 0
#define B_MIDIAM 1
#define B_UROKO 2
#define B_LASER 3
#define B_LIGHT 4
#define B_BIG 5

#include "main.h"

class Bullet {
public:
	int alive = 0;
	double posX = 0;
	double posY = 0;
	double vecX = 0;
	double vecY = 0;
	double startAngle = 0;
	double endAngle = 0;
	int angleEaseType = 0;
	int angleEaseTime = 0;
	double angle = 0;
	Color color = Color(0, 0, 0);
	int style = 0;
	int blend = 0;
	int pal = 255;
	double startColSize = 0;
	double endColSize = 0;
	int colSizeEaseType = 0;
	int colSizeEaseTime = 0;
	double colSize = 0;
	double startSize = 0;
	double endSize = 0;
	int sizeEaseType = 0;
	int sizeEaseTime = 0;
	double size = 1.0;
	double startSpeed = 0;
	double endSpeed = 0;
	int speedEaseType = 0;
	int speedEaseTime = 0;
	double speed = 0.0f;
	long long shotFrame = 0;
	Bullet(int alive, double posX, double posY, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, Color color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int shotFrame) : alive(alive), posX(posX), posY(posY), startAngle(startAngle), endAngle(endAngle), angleEaseType(angleEaseType), angleEaseTime(angleEaseTime), color(color), style(style), blend(blend), pal(pal), startColSize(startColSize), endColSize(startColSize), colSizeEaseType(colSizeEaseType), colSizeEaseTime(colSizeEaseTime), colSize(colSize), startSize(startSize), endSize(endSize), sizeEaseType(sizeEaseType), sizeEaseTime(sizeEaseTime), size(size), startSpeed(startSpeed), endSpeed(endSpeed), speedEaseType(speedEaseType), speedEaseTime(speedEaseTime), shotFrame(shotFrame) {}
	void MoveBullet();
};
void CreateBullet(double x, double y, Color color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime);
void CreateBulletGroup(double x, double y, Color color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int way, double spread, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime);
void CreateSimpleBulletGroup(double x, double y, Color color, int style, int blend, int pal, double colSize, double size, int way, double spread, int aim, double angle, double speed);
void MoveBullets();

#endif