﻿#include "Main.h"

#include "Color.h"
#include "Easing.h"
#include "Enemy.h"
#include "Object.h"
#include "Player.h"

//TODO: 引数減らしたラッパー関数作る

std::array<Enemy, MAX_ENEMY> Enemies;
std::array<int, 128> defaultEnemyBlend;
std::array<double, 128> drawRatioEnemyGraphs;

void
Enemy::ShowEnemy() {
	if (!(flags & IS_ALIVE)) return;
	if (blend == -1) {
		SmartSetDrawBlendMode(SAFE_ACCESS(defaultEnemyBlend, style), pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, SAFE_ACCESS(imgRes.EnemyGH, style), TRUE);
		SetDrawBright(255, 255, 255);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, SAFE_ACCESS(imgRes.EnemyGH, style), TRUE);
		SetDrawBright(255, 255, 255);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	if (isColShow == 1) {
		if (flags & IS_COL) {
			SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			DrawCircle(pos.GetX(), pos.GetY(), colSize, GetColor(255, 255, 255), 1);
			DrawFormatString(pos.GetX(), pos.GetY(), GetColor(GetColorHSV(std::fmod(frame, 360), 1, 1).r, GetColorHSV(std::fmod(frame, 360), 1, 1).g, GetColorHSV(std::fmod(frame, 360), 1, 1).b), "%f", colSize);
		}
	}
}

void
Enemy::ColliCheckObject() {
	if (colCircleAndCircle(pos, Plyr.pos, colSize + Plyr.colSize)) {
		Plyr.HitPlayer();
		flags ^= IS_ALIVE;
	}
}

int
Enemy::CheckPosBounds() {
	double limit = size * 128 * 2 * SAFE_ACCESS(drawRatioEnemyGraphs, style);
	if (pos.GetX() < BORDER_LEFT - limit) return 1;
	if (pos.GetX() > BORDER_RIGHT + limit) return 1;
	if (pos.GetY() < BORDER_UP - limit) return 1;
	if (pos.GetY() > BORDER_DOWN + limit) return 1;

	return 0;
}

void
Enemy::MoveFunc() {
	switch (ID) {
	case 0:
	default: {
		int needsMultiStep = speed >= colSize + Plyr.colSize && flags & IS_COL;
		if (needsMultiStep) {
			int step = static_cast<int>(std::ceil(speed / 1.0f));
			for (int i = 0; i < step; i++) {
				MoveObject(speed / step);
				if (CheckCollisionAndBounds()) return;
			}
		}
		else {
			MoveObject(speed);
			if (CheckCollisionAndBounds()) return;
		}
		break;
	}
	}
}

void
CreateEnemy(const Vec2D& pos, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID, const std::vector<std::any>& params) {
	for (int i = 0; i < Enemies.size(); i++) {
		if (!(SAFE_ACCESS(Enemies, i).flags & IS_ALIVE)) {
			SAFE_ACCESS(Enemies, i).flags = IS_ALIVE | isCol * IS_COL;
			SAFE_ACCESS(Enemies, i).objType = OBJECT_ENEMY;
			SAFE_ACCESS(Enemies, i).pos = pos;
			SAFE_ACCESS(Enemies, i).color = color;
			SAFE_ACCESS(Enemies, i).style = style;
			SAFE_ACCESS(Enemies, i).blend = blend;
			SAFE_ACCESS(Enemies, i).pal = pal;
			SAFE_ACCESS(Enemies, i).startColSize = startColSize;
			SAFE_ACCESS(Enemies, i).endColSize = endColSize;
			SAFE_ACCESS(Enemies, i).colSizeEaseType = colSizeEaseType;
			SAFE_ACCESS(Enemies, i).colSizeEaseTime = colSizeEaseTime;
			SAFE_ACCESS(Enemies, i).startSize = startSize;
			SAFE_ACCESS(Enemies, i).endSize = endSize;
			SAFE_ACCESS(Enemies, i).sizeEaseType = sizeEaseType;
			SAFE_ACCESS(Enemies, i).sizeEaseTime = sizeEaseTime;
			if (aim == 1) {
				SAFE_ACCESS(Enemies, i).startAngle = Plyr.AimPlayer(pos) + startAngle;
				SAFE_ACCESS(Enemies, i).endAngle = Plyr.AimPlayer(pos) + endAngle;
			}
			else {
				SAFE_ACCESS(Enemies, i).startAngle = startAngle;
				SAFE_ACCESS(Enemies, i).endAngle = endAngle;
			}
			SAFE_ACCESS(Enemies, i).angleEaseType = angleEaseType;
			SAFE_ACCESS(Enemies, i).angleEaseTime = angleEaseTime;
			SAFE_ACCESS(Enemies, i).startSpeed = startSpeed;
			SAFE_ACCESS(Enemies, i).endSpeed = endSpeed;
			SAFE_ACCESS(Enemies, i).speedEaseType = speedEaseType;
			SAFE_ACCESS(Enemies, i).speedEaseTime = speedEaseTime;
			SAFE_ACCESS(Enemies, i).popFrame = frame;
			SAFE_ACCESS(Enemies, i).length = 0;
			SAFE_ACCESS(Enemies, i).width = 0;
			SAFE_ACCESS(Enemies, i).frontNode = 0;
			SAFE_ACCESS(Enemies, i).currentNodeNum = 0;
			SAFE_ACCESS(Enemies, i).ID = ID;
			SAFE_ACCESS(Enemies, i).params = params;
			return;
		}
	}
	/*if (aim == 1) {
		Enemies.emplace_back(1, isCol, pos, Plyr.AimPlayer(pos) + startAngle, Plyr.AimPlayer(pos) + endAngle, angleEaseType, angleEaseTime, 0, 0, 0, 0, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame, ID, params);
	}
	else {
		Enemies.emplace_back(1, isCol, pos, startAngle, endAngle, angleEaseType, angleEaseTime, 0, 0, 0, 0, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame, ID, params);
	}*/
}

void
CreateEnemyGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int way, double spread, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID, const std::vector<std::any>& params) {
	switch (aim) {
	case 0:
		for (int i = 0; i < way; i++) {
			CreateEnemy(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params);
		}
		break;
	case 1:
		for (int i = 0; i < way; i++) {
			CreateEnemy(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params);
		}
		break;
	case 2:
		for (int i = 0; i < way; i++) {
			CreateEnemy(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle + spread / (way * 2) - spread / 2, spread / way * i + endAngle + spread / (way * 2) - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params);
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			CreateEnemy(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params);
		}
		break;
	}
}

void
CreateSimpleEnemyGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, double colSize, double size, int way, double spread, int aim, double angle, double speed, int ID, const std::vector<std::any>& params) {
	switch (aim) {
	case 0:
		for (int i = 0; i < way; i++) {
			CreateEnemy(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID, params);
		}
		break;
	case 1:
		for (int i = 0; i < way; i++) {
			CreateEnemy(pos, color, style, blend, pal, 0, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID, params);
		}
		break;
	case 2:
		for (int i = 0; i < way; i++) {
			CreateEnemy(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle + spread / (way * 2) - spread / 2, spread / way * i + angle + spread / (way * 2) - spread / 2, 0, 0, speed, speed, 0, 0, ID, params);
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			CreateEnemy(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID, params);
		}
		break;
	}
}

void
CreateSmartEnemyGroup(objectParams param) {
	switch (param.aim) {
	case 0:
		for (int i = 0; i < param.way; i++) {
			CreateEnemy(param.pos, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 0, param.spread / param.way * i + param.startAngle - param.spread / 2, param.spread / param.way * i + param.endAngle - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, param.ID, param.params);
		}
		break;
	case 1:
		for (int i = 0; i < param.way; i++) {
			CreateEnemy(param.pos, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 1, param.spread / param.way * i + param.startAngle - param.spread / 2, param.spread / param.way * i + param.endAngle - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, param.ID, param.params);
		}
		break;
	case 2:
		for (int i = 0; i < param.way; i++) {
			CreateEnemy(param.pos, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 1, param.spread / param.way * i + param.startAngle + param.spread / (param.way * 2) - param.spread / 2, param.spread / param.way * i + param.endAngle + param.spread / (param.way * 2) - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, param.ID, param.params);
		}
		break;
	default:
		for (int i = 0; i < param.way; i++) {
			CreateEnemy(param.pos, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 0, param.spread / param.way * i + param.startAngle - param.spread / 2, param.spread / param.way * i + param.endAngle - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, param.ID, param.params);
		}
		break;
	}
}

void
MoveEnemies() {
	for (auto& E : Enemies) {
		E.UpdateObject();
		E.ShowEnemy();
	}
	if (frame % 10 == 0) {
		std::sort(Enemies.begin(), Enemies.end(), [](const Enemy& a, const Enemy& b) {
			return a.popFrame < b.popFrame;
			});
	}
}