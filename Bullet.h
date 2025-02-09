#pragma once
#ifndef BULLET_H
#define BULLET_H

#define B_NORMAL 0
#define B_MIDIAM 1
#define B_UROKO 2
#define B_LASER 3
#define B_LIGHT 4
#define B_BIG 5

#include "Object.h"

class Bullet : public Object {
public:
	Bullet(int alive, int isCol, double posX, double posY, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startShowAngle, double endShowAngle, int showAngleEaseType, int showAngleEaseTime, Color color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int popFrame)
		: Object(alive, isCol, 0, posX, posY, startAngle, endAngle, angleEaseType, angleEaseTime, startShowAngle, endShowAngle, showAngleEaseType, showAngleEaseTime, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, popFrame) {
	}
	void ShowBullet();
};

void CreateBullet(double x, double y, Color color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime);
void CreateBulletGroup(double x, double y, Color color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int way, double spread, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime);
void CreateSimpleBulletGroup(double x, double y, Color color, int style, int blend, int pal, double colSize, double size, int way, double spread, int aim, double angle, double speed);
void MoveBullets();

#endif