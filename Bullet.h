#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "Object.h"

class Bullet : public Object {
public:
	Bullet() = default;
	Bullet(int alive, int isCol, const Vec2D& pos, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startShowAngle, double endShowAngle, int showAngleEaseType, int showAngleEaseTime, const Color& color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int popFrame, int ID = 0, const std::vector<std::any>& params = {})
		: Object(alive, isCol, OBJECT_BULLET, pos, startAngle, endAngle, angleEaseType, angleEaseTime, startShowAngle, endShowAngle, showAngleEaseType, showAngleEaseTime, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, popFrame, 0, 0, 0, 0, 0, 0, 0, ID, params) {
	}
	void ShowBullet();
	void ColliCheckObject() override;
	int CheckPosBounds() override;
	void MoveFunc() override;
};

void CreateBullet(const Vec2D& pos, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID = 0, const std::vector<std::any>& params = {});
void CreateBulletGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int way, double spread, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID = 0, const std::vector<std::any>& params = {});
void CreateSimpleBulletGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, double colSize, double size, int way, double spread, int aim, double angle, double speed, int ID = 0, const std::vector<std::any>& params = {});
void MoveBullets();

#endif