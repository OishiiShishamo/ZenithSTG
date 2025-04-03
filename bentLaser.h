#pragma once
#ifndef BENT_LASER_H
#define BENT_LASER_H

#include "Object.h"

class bentLaser : public Object {
public:
	bentLaser(int alive, int isCol, Vec2D pos, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startShowAngle, double endShowAngle, int showAngleEaseType, int showAngleEaseTime, Color color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int popFrame, double length, double width, long long frontNode, long long nextNode, int currentNodeNum, int isHead)
		: Object(alive, isCol, OBJECT_LASER, pos, startAngle, endAngle, angleEaseType, angleEaseTime, startShowAngle, endShowAngle, showAngleEaseType, showAngleEaseTime, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, popFrame, length, width, frontNode, nextNode, currentNodeNum, isHead) {
	}
	void ShowBentLaser();
};

void CreateBentLaser(Vec2D pos, double length, double width, Color color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime);
void CreateBentLaserNode(Vec2D pos, double length, double width, Color color, int style, int blend, int pal, int isCol, double ColSize, double Size, double Angle, double Speed, long long frontNode, int currentNode);
void MoveBentLasers();

#endif