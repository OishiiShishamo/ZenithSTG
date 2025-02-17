#include "Main.h"

#include "playerShot.h"

std::vector<int> defaultPlayerShotBlend;

void
playerShot::ShowPlayerShot() {
	if (blend == -1) {
		SmartSetDrawBlendMode(defaultPlayerShotBlend[style], pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(pos.x, pos.y, size, -showAngle, imgRes.ShotGH[style], TRUE);
		SetDrawBright(255, 255, 255);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(pos.x, pos.y, size, -showAngle, imgRes.ShotGH[style], TRUE);
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
CreatePlayerShot(Vec2D pos, Color color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime) {
	for (int i = 0; i < plyrShots.size(); i++) {
		if (plyrShots[i].alive == 0) {
			plyrShots[i].alive = 1;
			plyrShots[i].isCol = isCol;
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
			return;
		}
	}
	plyrShots.emplace_back(1, isCol, pos, startAngle, endAngle, angleEaseType, angleEaseTime, 0, 0, 0, 0, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame);
}

void
MovePlayerShots() {
	for (int i = 0; i < plyrShots.size(); i++) {
		plyrShots[i].MoveObject();
		plyrShots[i].ShowPlayerShot();
	}
	if (frame % 10 == 0) {
		std::sort(plyrShots.begin(), plyrShots.end(), [](const playerShot& a, const playerShot& b) {
			return a.popFrame < b.popFrame;
			});
		for (int i = 0; i < plyrShots.size(); i++) {
			if (plyrShots[i].alive == 0) {
				plyrShots.erase(plyrShots.begin() + i);
			}
		}
	}
}