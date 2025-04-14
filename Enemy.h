#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Main.h"
#include "Object.h"

class Enemy : public Object {
public:
	Enemy(int alive, int isCol, Vec2D pos, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startShowAngle, double endShowAngle, int showAngleEaseType, int showAngleEaseTime, Color color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int popFrame, int ID)
		: Object(alive, isCol, OBJECT_ENEMY, pos, startAngle, endAngle, angleEaseType, angleEaseTime, startShowAngle, endShowAngle, showAngleEaseType, showAngleEaseTime, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, popFrame, 0, 0, 0, 0, 0, 0, ID) {
	}
	void ShowEnemy();
};

void CreateEnemy(Vec2D pos, Color color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID);
void CreateEnemyGroup(Vec2D pos, Color color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int way, double spread, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID);
void CreateSimpleEnemyGroup(Vec2D pos, Color color, int style, int blend, int pal, double colSize, double size, int way, double spread, int aim, double angle, double speed, int ID);
void MoveEnemies();

#endif