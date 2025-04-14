#pragma once
#ifndef LASER_H
#define LASER_H

#include "Object.h"

class Laser : public Object {
public:
	Laser(int alive, int isCol, Vec2D pos, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startShowAngle, double endShowAngle, int showAngleEaseType, int showAngleEaseTime, Color color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int popFrame, double length, double width, int ID = 0, const std::vector<std::any>& params = {})
		: Object(alive, isCol, OBJECT_LASER, pos, startAngle, endAngle, angleEaseType, angleEaseTime, startShowAngle, endShowAngle, showAngleEaseType, showAngleEaseTime, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, popFrame, length, width, 0, 0, 0, 0, ID, params) {
	}
	void ShowLaser();
};

void CreateLaser(Vec2D pos, double length, double width, Color color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID = 0, const std::vector<std::any>& params = {});
void CreateLaserGroup(Vec2D pos, double length, double width, Color color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int way, double spread, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID = 0, const std::vector<std::any>& params = {});
void CreateSimpleLaserGroup(Vec2D pos, double length, double width, Color color, int style, int blend, int pal, double colSize, double size, int way, double spread, int aim, double angle, double speed, int ID = 0, const std::vector<std::any>& params = {});
void MoveLasers();

#endif