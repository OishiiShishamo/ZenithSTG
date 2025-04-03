#include "Main.h"

#include "bentLaser.h"
#include "Bullet.h"
#include "Color.h"
#include "Player.h"
#include "Easing.h"

void
bentLaser::ShowBentLaser() {
	if (blend == -1) {
		SmartSetDrawBlendMode(defaultBulletBlend[style], pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		if (isHead) {
			DrawRectModiGraph(
				pos.x + cos(angle + PI / 2) * width / 2,
				pos.y - sin(angle + PI / 2) * width / 2,
				pos.x + cos(angle) * 16,
				pos.y - sin(angle) * 16,
				pos.x + cos(angle) * 16,
				pos.y - sin(angle) * 16,
				pos.x - cos(angle + PI / 2) * width / 2,
				pos.y + sin(angle + PI / 2) * width / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				128 * drawRatioBulletGraphs[style],
				128 * drawRatioBulletGraphs[style],
				imgRes.BulletBackGH[style],
				TRUE);
			SetDrawBright(255, 255, 255);
			DrawRectModiGraph(
				pos.x + cos(angle + PI / 2) * width / 2,
				pos.y - sin(angle + PI / 2) * width / 2,
				pos.x + cos(angle) * 16,
				pos.y - sin(angle) * 16,
				pos.x + cos(angle) * 16,
				pos.y - sin(angle) * 16,
				pos.x - cos(angle + PI / 2) * width / 2,
				pos.y + sin(angle + PI / 2) * width / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				128 * drawRatioBulletGraphs[style],
				128 * drawRatioBulletGraphs[style],
				imgRes.BulletFrontGH[style],
				TRUE);
		}
		else {
			DrawRectModiGraph(
				pos.x + cos(angle + PI / 2) * width / 2,
				pos.y - sin(angle + PI / 2) * width / 2,
				BentLasers.at(frontNode).pos.x + cos(BentLasers.at(frontNode).angle + PI / 2) * width / 2,
				BentLasers.at(frontNode).pos.y - sin(BentLasers.at(frontNode).angle + PI / 2) * width / 2,
				BentLasers.at(frontNode).pos.x - cos(BentLasers.at(frontNode).angle + PI / 2) * width / 2,
				BentLasers.at(frontNode).pos.y + sin(BentLasers.at(frontNode).angle + PI / 2) * width / 2,
				pos.x - cos(angle + PI / 2) * width / 2,
				pos.y + sin(angle + PI / 2) * width / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				128 * drawRatioBulletGraphs[style],
				128 * drawRatioBulletGraphs[style],
				imgRes.BulletBackGH[style],
				TRUE);
			SetDrawBright(255, 255, 255);
			DrawRectModiGraph(
				pos.x + cos(angle + PI / 2) * width / 2,
				pos.y - sin(angle + PI / 2) * width / 2,
				BentLasers.at(frontNode).pos.x + cos(BentLasers.at(frontNode).angle + PI / 2) * width / 2,
				BentLasers.at(frontNode).pos.y - sin(BentLasers.at(frontNode).angle + PI / 2) * width / 2,
				BentLasers.at(frontNode).pos.x - cos(BentLasers.at(frontNode).angle + PI / 2) * width / 2,
				BentLasers.at(frontNode).pos.y + sin(BentLasers.at(frontNode).angle + PI / 2) * width / 2,
				pos.x - cos(angle + PI / 2) * width / 2,
				pos.y + sin(angle + PI / 2) * width / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				128 * drawRatioBulletGraphs[style],
				128 * drawRatioBulletGraphs[style],
				imgRes.BulletFrontGH[style],
				TRUE);
		}
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		if (isHead) {
			DrawRectModiGraph(
				pos.x + cos(angle + PI / 2) * width / 2,
				pos.y - sin(angle + PI / 2) * width / 2,
				pos.x + cos(angle) * 16,
				pos.y - sin(angle) * 16,
				pos.x + cos(angle) * 16,
				pos.y - sin(angle) * 16,
				pos.x - cos(angle + PI / 2) * width / 2,
				pos.y + sin(angle + PI / 2) * width / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				128 * drawRatioBulletGraphs[style],
				128 * drawRatioBulletGraphs[style],
				imgRes.BulletBackGH[style],
				TRUE);
			SetDrawBright(255, 255, 255);
			DrawRectModiGraph(
				pos.x + cos(angle + PI / 2) * width / 2,
				pos.y - sin(angle + PI / 2) * width / 2,
				pos.x + cos(angle) * 16,
				pos.y - sin(angle) * 16,
				pos.x + cos(angle) * 16,
				pos.y - sin(angle) * 16,
				pos.x - cos(angle + PI / 2) * width / 2,
				pos.y + sin(angle + PI / 2) * width / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				128 * drawRatioBulletGraphs[style],
				128 * drawRatioBulletGraphs[style],
				imgRes.BulletFrontGH[style],
				TRUE);
		}
		else {
			DrawRectModiGraph(
				pos.x + cos(angle + PI / 2) * width / 2,
				pos.y - sin(angle + PI / 2) * width / 2,
				BentLasers.at(frontNode).pos.x + cos(BentLasers.at(frontNode).angle + PI / 2) * width / 2,
				BentLasers.at(frontNode).pos.y - sin(BentLasers.at(frontNode).angle + PI / 2) * width / 2,
				BentLasers.at(frontNode).pos.x - cos(BentLasers.at(frontNode).angle + PI / 2) * width / 2,
				BentLasers.at(frontNode).pos.y + sin(BentLasers.at(frontNode).angle + PI / 2) * width / 2,
				pos.x - cos(angle + PI / 2) * width / 2,
				pos.y + sin(angle + PI / 2) * width / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				128 * drawRatioBulletGraphs[style],
				128 * drawRatioBulletGraphs[style],
				imgRes.BulletBackGH[style],
				TRUE);
			SetDrawBright(255, 255, 255);
			DrawRectModiGraph(
				pos.x + cos(angle + PI / 2) * width / 2,
				pos.y - sin(angle + PI / 2) * width / 2,
				BentLasers.at(frontNode).pos.x + cos(BentLasers.at(frontNode).angle + PI / 2) * width / 2,
				BentLasers.at(frontNode).pos.y - sin(BentLasers.at(frontNode).angle + PI / 2) * width / 2,
				BentLasers.at(frontNode).pos.x - cos(BentLasers.at(frontNode).angle + PI / 2) * width / 2,
				BentLasers.at(frontNode).pos.y + sin(BentLasers.at(frontNode).angle + PI / 2) * width / 2,
				pos.x - cos(angle + PI / 2) * width / 2,
				pos.y + sin(angle + PI / 2) * width / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				128 * drawRatioBulletGraphs[style],
				128 * drawRatioBulletGraphs[style],
				imgRes.BulletFrontGH[style],
				TRUE);
		}
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
CreateBentLaser(Vec2D pos, double length, double width, Color color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime) {
	for (int i = 0; i < BentLasers.size(); i++) {
		if (BentLasers[i].alive == 0) {
			BentLasers[i].alive = 1;
			BentLasers[i].isCol = isCol;
			BentLasers[i].objType = OBJECT_LASER;
			BentLasers[i].pos = pos;
			BentLasers[i].color = color;
			BentLasers[i].style = style;
			BentLasers[i].blend = blend;
			BentLasers[i].pal = pal;
			BentLasers[i].startColSize = startColSize;
			BentLasers[i].endColSize = endColSize;
			BentLasers[i].colSizeEaseType = colSizeEaseType;
			BentLasers[i].colSizeEaseTime = colSizeEaseTime;
			BentLasers[i].startSize = startSize;
			BentLasers[i].endSize = endSize;
			BentLasers[i].sizeEaseType = sizeEaseType;
			BentLasers[i].sizeEaseTime = sizeEaseTime;
			if (aim == 1) {
				BentLasers[i].startAngle = Plyr.AimPlayer(pos) + startAngle;
				BentLasers[i].endAngle = Plyr.AimPlayer(pos) + endAngle;
			}
			else {
				BentLasers[i].startAngle = startAngle;
				BentLasers[i].endAngle = endAngle;
			}
			BentLasers[i].angleEaseType = angleEaseType;
			BentLasers[i].angleEaseTime = angleEaseTime;
			BentLasers[i].startSpeed = startSpeed;
			BentLasers[i].endSpeed = endSpeed;
			BentLasers[i].speedEaseType = speedEaseType;
			BentLasers[i].speedEaseTime = speedEaseTime;
			BentLasers[i].popFrame = frame;
			BentLasers[i].length = length;
			BentLasers[i].width = width;
			BentLasers[i].frontNode = -1;
			BentLasers[i].currentNodeNum = 0;
			BentLasers[i].isHead = 1;
			return;
		}
	}
	if (aim == 1) {
		BentLasers.emplace_back(1, isCol, pos, Plyr.AimPlayer(pos) + startAngle, Plyr.AimPlayer(pos) + endAngle, angleEaseType, angleEaseTime, 0, 0, 0, 0, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame, length, width, -1, 0, 1);
	}
	else {
		BentLasers.emplace_back(1, isCol, pos, startAngle, endAngle, angleEaseType, angleEaseTime, 0, 0, 0, 0, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame, length, width, -1, 0, 1);
	}
}

void
CreateBentLaserNode(Vec2D pos, double length, double width, Color color, int style, int blend, int pal, int isCol, double ColSize, double Size, double Angle, double Speed, long long frontNode, int currentNode) {
	for (int i = 0; i < BentLasers.size(); i++) {
		if (BentLasers[i].alive == 0) {
			BentLasers[i].alive = 1;
			BentLasers[i].isCol = isCol;
			BentLasers[i].objType = OBJECT_LASER;
			BentLasers[i].pos = pos;
			BentLasers[i].color = color;
			BentLasers[i].style = style;
			BentLasers[i].blend = blend;
			BentLasers[i].pal = pal;
			BentLasers[i].startColSize = ColSize;
			BentLasers[i].endColSize = ColSize;
			BentLasers[i].colSizeEaseType = 0;
			BentLasers[i].colSizeEaseTime = 0;
			BentLasers[i].startSize = Size;
			BentLasers[i].endSize = Size;
			BentLasers[i].sizeEaseType = 0;
			BentLasers[i].sizeEaseTime = 0;
			BentLasers[i].startAngle = Angle;
			BentLasers[i].endAngle = Angle;
			BentLasers[i].angleEaseType = 0;
			BentLasers[i].angleEaseTime = 0;
			BentLasers[i].startSpeed = Speed;
			BentLasers[i].endSpeed = Speed;
			BentLasers[i].speedEaseType = 0;
			BentLasers[i].speedEaseTime = 0;
			BentLasers[i].popFrame = frame;
			BentLasers[i].length = length;
			BentLasers[i].width = width;
			return;
		}
	}
	BentLasers.emplace_back(1, isCol, pos, Angle, Angle, 0, 0, 0, 0, 0, 0, color, style, blend, pal, ColSize, ColSize, 0, 0, Size, Size, 0, 0, Speed, Speed, 0, 0, frame, length, width, frontNode, currentNode, 0);
}

void
MoveBentLasers() {
	for (int i = BentLasers.size() - 1; i > -1; i++) {
		BentLasers[i].MoveObject(i);
		BentLasers[i].ShowBentLaser();
	}
	if (frame % 10 == 0) {
		std::sort(BentLasers.begin(), BentLasers.end(), [](const bentLaser& a, const bentLaser& b) {
			return a.popFrame < b.popFrame;
			});
		for (int i = 0; i < BentLasers.size(); i++) {
			if (BentLasers[i].alive == 0) {
				BentLasers.erase(BentLasers.begin() + i);
			}
		}
	}
}