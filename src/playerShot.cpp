#include "Main.h"

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
		SmartSetDrawBlendMode(defaultPlayerShotBlend[style], pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, imgRes.ShotGH[style], TRUE);
		SetDrawBright(255, 255, 255);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, imgRes.ShotGH[style], TRUE);
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
	double limit = size * 128 * 2 * drawRatioPlayerShotGraphs[style];
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
		if (!(plyrShots[i].flags & IS_ALIVE)) {
			plyrShots[i].flags = IS_ALIVE | isCol * IS_COL;
			plyrShots[i].objType = OBJECT_PLAYER_SHOT;
			plyrShots[i].pos = pos;
			plyrShots[i].color = color;
			plyrShots[i].style = style;
			plyrShots[i].blend = blend;
			plyrShots[i].pal = pal;
			plyrShots[i].startColSize = startColSize;
			plyrShots[i].endColSize = endColSize;
			plyrShots[i].colSizeEaseType = colSizeEaseType;
			plyrShots[i].colSizeEaseTime = colSizeEaseTime;
			plyrShots[i].startSize = startSize;
			plyrShots[i].endSize = endSize;
			plyrShots[i].sizeEaseType = sizeEaseType;
			plyrShots[i].sizeEaseTime = sizeEaseTime;
			plyrShots[i].startAngle = startAngle;
			plyrShots[i].endAngle = endAngle;
			plyrShots[i].angleEaseType = angleEaseType;
			plyrShots[i].angleEaseTime = angleEaseTime;
			plyrShots[i].startSpeed = startSpeed;
			plyrShots[i].endSpeed = endSpeed;
			plyrShots[i].speedEaseType = speedEaseType;
			plyrShots[i].speedEaseTime = speedEaseTime;
			plyrShots[i].popFrame = frame;
			plyrShots[i].length = 0;
			plyrShots[i].width = 0;
			plyrShots[i].frontNode = 0;
			plyrShots[i].currentNodeNum = 0;
			plyrShots[i].ID = 0;
			plyrShots[i].params = params;
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
		//std::erase_if(plyrShots, [](const playerShot& ps) { return !ps.alive; });
	}
}