#include "Main.h"

#include "Enemy.h"
#include "Object.h"
#include "Color.h"
#include "Player.h"
#include "Easing.h"

//TODO: 引数減らしたラッパー関数作る

std::vector<int> defaultEnemyBlend;

void
Enemy::ShowEnemy() {
	if (blend == -1) {
		SmartSetDrawBlendMode(defaultEnemyBlend[style], pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(pos.x, pos.y, size, -showAngle, imgRes.EnemyGH[style], TRUE);
		SetDrawBright(255, 255, 255);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(pos.x, pos.y, size, -showAngle, imgRes.EnemyGH[style], TRUE);
		SetDrawBright(255, 255, 255);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	if (isColShow == 1) {
		if (isCol == 1) {
			SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			DrawCircle(pos.x, pos.y, colSize, GetColor(255, 255, 255), 1);
			DrawFormatString(pos.x, pos.y, GetColor(GetColorHSV(std::fmod(frame, 360), 1, 1).r, GetColorHSV(std::fmod(frame, 360), 1, 1).g, GetColorHSV(std::fmod(frame, 360), 1, 1).b), "%f", colSize);
		}
	}
}

void
CreateEnemy(Vec2D pos, Color color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID) {
	for (int i = 0; i < Enemies.size(); i++) {
		if (Enemies[i].alive == 0) {
			Enemies[i].alive = 1;
			Enemies[i].isCol = isCol;
			Enemies[i].objType = OBJECT_ENEMY;
			Enemies[i].pos = pos;
			Enemies[i].color = color;
			Enemies[i].style = style;
			Enemies[i].blend = blend;
			Enemies[i].pal = pal;
			Enemies[i].startColSize = startColSize;
			Enemies[i].endColSize = endColSize;
			Enemies[i].colSizeEaseType = colSizeEaseType;
			Enemies[i].colSizeEaseTime = colSizeEaseTime;
			Enemies[i].startSize = startSize;
			Enemies[i].endSize = endSize;
			Enemies[i].sizeEaseType = sizeEaseType;
			Enemies[i].sizeEaseTime = sizeEaseTime;
			if (aim == 1) {
				Enemies[i].startAngle = Plyr.AimPlayer(pos) + startAngle;
				Enemies[i].endAngle = Plyr.AimPlayer(pos) + endAngle;
			}
			else {
				Enemies[i].startAngle = startAngle;
				Enemies[i].endAngle = endAngle;
			}
			Enemies[i].angleEaseType = angleEaseType;
			Enemies[i].angleEaseTime = angleEaseTime;
			Enemies[i].startSpeed = startSpeed;
			Enemies[i].endSpeed = endSpeed;
			Enemies[i].speedEaseType = speedEaseType;
			Enemies[i].speedEaseTime = speedEaseTime;
			Enemies[i].popFrame = frame;
			Enemies[i].length = 0;
			Enemies[i].width = 0;
			Enemies[i].frontNode = 0;
			Enemies[i].currentNodeNum = 0;
			Enemies[i].isHead = 0;
			Enemies[i].ID = ID;
			return;
		}
	}
	if (aim == 1) {
		Enemies.emplace_back(1, isCol, pos, Plyr.AimPlayer(pos) + startAngle, Plyr.AimPlayer(pos) + endAngle, angleEaseType, angleEaseTime, 0, 0, 0, 0, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame, ID);
	}
	else {
		Enemies.emplace_back(1, isCol, pos, startAngle, endAngle, angleEaseType, angleEaseTime, 0, 0, 0, 0, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame, ID);
	}
}

void
CreateEnemyGroup(Vec2D pos, Color color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int way, double spread, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID) {
	switch (aim) {
	case 0:
		for (int i = 0; i < way; i++) {
			CreateEnemy(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID);
		}
		break;
	case 1:
		for (int i = 0; i < way; i++) {
			CreateEnemy(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID);
		}
		break;
	case 2:
		for (int i = 0; i < way; i++) {
			CreateEnemy(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle + spread / (way * 2) - spread / 2, spread / way * i + endAngle + spread / (way * 2) - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID);
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			CreateEnemy(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID);
		}
		break;
	}
}

void
CreateSimpleEnemyGroup(Vec2D pos, Color color, int style, int blend, int pal, double colSize, double size, int way, double spread, int aim, double angle, double speed, int ID) {
	switch (aim) {
	case 0:
		for (int i = 0; i < way; i++) {
			CreateEnemy(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID);
		}
		break;
	case 1:
		for (int i = 0; i < way; i++) {
			CreateEnemy(pos, color, style, blend, pal, 0, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID);
		}
		break;
	case 2:
		for (int i = 0; i < way; i++) {
			CreateEnemy(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle + spread / (way * 2) - spread / 2, spread / way * i + angle + spread / (way * 2) - spread / 2, 0, 0, speed, speed, 0, 0, ID);
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			CreateEnemy(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID);
		}
		break;
	}
}

void
MoveEnemies() {
	for (int i = 0; i < Enemies.size(); i++) {
		Enemies[i].UpdateObject(i);
		Enemies[i].ShowEnemy();
	}
	if (frame % 10 == 0) {
		std::sort(Enemies.begin(), Enemies.end(), [](const Enemy& a, const Enemy& b) {
			return a.popFrame < b.popFrame;
			});
		for (int i = 0; i < Enemies.size(); i++) {
			if (Enemies[i].alive == 0) {
				Enemies.erase(Enemies.begin() + i);
			}
		}
	}
}