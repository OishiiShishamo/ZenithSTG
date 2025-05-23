﻿#include "Main.h"

#include "Color.h"
#include "Easing.h"
#include "Player.h"
#include "playerShot.h"

std::array<playerShot, MAX_PLAYER_SHOT> plyrShots;
std::array<int, 128> defaultPlayerShotBlend;
std::array<double, 128> drawRatioPlayerShotGraphs;

void
playerShot::ShowPlayerShot() {
	if (!(flags & IS_ALIVE)) return;
	if (blend == -1) {
		SmartSetDrawBlendMode(SAFE_ACCESS(defaultPlayerShotBlend, style), pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, SAFE_ACCESS(imgRes.ShotGH, style), TRUE);
		SetDrawBright(255, 255, 255);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, SAFE_ACCESS(imgRes.ShotGH, style), TRUE);
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
playerShot::ColliCheckObject() {
	return;
}

int
playerShot::CheckPosBounds() {
	double limit = size * 128 * 2 * SAFE_ACCESS(drawRatioPlayerShotGraphs, style);
	if (pos.GetX() < BORDER_LEFT - limit) return 1;
	if (pos.GetX() > BORDER_RIGHT + limit) return 1;
	if (pos.GetY() < BORDER_UP - limit) return 1;
	if (pos.GetY() > BORDER_DOWN + limit) return 1;

	return 0;
}

void
playerShot::MoveFunc() {
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
CreatePlayerShot(const Vec2D& pos, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID, const std::vector<std::any>& params) {
	for (int i = 0; i < plyrShots.size(); i++) {
		if (!(SAFE_ACCESS(plyrShots, i).flags & IS_ALIVE)) {
			SAFE_ACCESS(plyrShots, i).flags = IS_ALIVE | isCol * IS_COL;
			SAFE_ACCESS(plyrShots, i).objType = OBJECT_PLAYER_SHOT;
			SAFE_ACCESS(plyrShots, i).pos = pos;
			SAFE_ACCESS(plyrShots, i).color = color;
			SAFE_ACCESS(plyrShots, i).style = style;
			SAFE_ACCESS(plyrShots, i).blend = blend;
			SAFE_ACCESS(plyrShots, i).pal = pal;
			SAFE_ACCESS(plyrShots, i).startColSize = startColSize;
			SAFE_ACCESS(plyrShots, i).endColSize = endColSize;
			SAFE_ACCESS(plyrShots, i).colSizeEaseType = colSizeEaseType;
			SAFE_ACCESS(plyrShots, i).colSizeEaseTime = colSizeEaseTime;
			SAFE_ACCESS(plyrShots, i).startSize = startSize;
			SAFE_ACCESS(plyrShots, i).endSize = endSize;
			SAFE_ACCESS(plyrShots, i).sizeEaseType = sizeEaseType;
			SAFE_ACCESS(plyrShots, i).sizeEaseTime = sizeEaseTime;
			SAFE_ACCESS(plyrShots, i).startAngle = startAngle;
			SAFE_ACCESS(plyrShots, i).endAngle = endAngle;
			SAFE_ACCESS(plyrShots, i).angleEaseType = angleEaseType;
			SAFE_ACCESS(plyrShots, i).angleEaseTime = angleEaseTime;
			SAFE_ACCESS(plyrShots, i).startSpeed = startSpeed;
			SAFE_ACCESS(plyrShots, i).endSpeed = endSpeed;
			SAFE_ACCESS(plyrShots, i).speedEaseType = speedEaseType;
			SAFE_ACCESS(plyrShots, i).speedEaseTime = speedEaseTime;
			SAFE_ACCESS(plyrShots, i).popFrame = frame;
			SAFE_ACCESS(plyrShots, i).length = 0;
			SAFE_ACCESS(plyrShots, i).width = 0;
			SAFE_ACCESS(plyrShots, i).frontNode = 0;
			SAFE_ACCESS(plyrShots, i).currentNodeNum = 0;
			SAFE_ACCESS(plyrShots, i).ID = 0;
			SAFE_ACCESS(plyrShots, i).params = params;
			return;
		}
	}
	//plyrShots.emplace_back(1, isCol, pos, startAngle, endAngle, angleEaseType, angleEaseTime, 0, 0, 0, 0, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame, ID, params);
}

void
MovePlayerShots() {
	for (auto& PS : plyrShots) {
		PS.UpdateObject();
		PS.ShowPlayerShot();
	}
	if (frame % 10 == 0) {
		std::sort(plyrShots.begin(), plyrShots.end(), [](const playerShot& a, const playerShot& b) {
			return a.popFrame < b.popFrame;
			});
		//std::erase_if(plyrShots, , )(const playerShot& ps) { return !ps.alive; });
	}
}