#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include "Color.h"

class Object {
public:
	int alive = 0;
	int isCol = 1;
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
	long long popFrame = 0;
	double angleT, speedT, colSizeT, sizeT;
	Object(int alive, int isCol, double posX, double posY, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, Color color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int popFrame)
		: alive(alive), isCol(isCol), posX(posX), posY(posY), startAngle(startAngle), endAngle(endAngle), angleEaseType(angleEaseType), angleEaseTime(angleEaseTime), color(color), style(style), blend(blend), pal(pal), startColSize(startColSize), endColSize(startColSize), colSizeEaseType(colSizeEaseType), colSizeEaseTime(colSizeEaseTime), colSize(colSize), startSize(startSize), endSize(endSize), sizeEaseType(sizeEaseType), sizeEaseTime(sizeEaseTime), size(size), startSpeed(startSpeed), endSpeed(endSpeed), speedEaseType(speedEaseType), speedEaseTime(speedEaseTime), popFrame(popFrame) {
	}
	void MoveObject();
};

#endif