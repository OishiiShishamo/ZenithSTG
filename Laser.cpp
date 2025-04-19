#include "Main.h"

#include "Bullet.h"
#include "Color.h"
#include "Easing.h"
#include "Laser.h"
#include "Player.h"
#include "Time.h"

void
Laser::ShowLaser() {
	if (!(flags & ALIVE)) return;
	double halfW = width / 2;
	Vec2D local[4] = {
		{-halfW, 0},
		{-halfW, length},
		{ halfW, length},
		{ halfW, 0}
	};
	Vec2D world[4];
	for (int i = 0; i < 4; ++i) {
		Vec2D rot = RotatePoint(local[i], showAngle + PI / 2);
		world[i].x = pos.x + rot.x;
		world[i].y = pos.y + rot.y;
	}
	if (blend == -1) {
		SmartSetDrawBlendMode(defaultBulletBlend[style], pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		DrawRectModiGraph(
			world[0].x, world[0].y,
			world[1].x, world[1].y,
			world[2].x, world[2].y,
			world[3].x, world[3].y,
			64 - 128 * drawRatioBulletGraphs[style] / 2,
			64 - 128 * drawRatioBulletGraphs[style] / 2,
			128 * drawRatioBulletGraphs[style],
			128 * drawRatioBulletGraphs[style],
			imgRes.BulletBackGH[style],
			TRUE);
		SetDrawBright(255, 255, 255);
		DrawRectModiGraph(
			world[0].x, world[0].y,
			world[1].x, world[1].y,
			world[2].x, world[2].y,
			world[3].x, world[3].y,
			64 - 128 * drawRatioBulletGraphs[style] / 2,
			64 - 128 * drawRatioBulletGraphs[style] / 2,
			128 * drawRatioBulletGraphs[style],
			128 * drawRatioBulletGraphs[style],
			imgRes.BulletFrontGH[style],
			TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		DrawRectModiGraph(
			world[0].x, world[0].y,
			world[1].x, world[1].y,
			world[2].x, world[2].y,
			world[3].x, world[3].y,
			64 - 128 * drawRatioBulletGraphs[style] / 2,
			64 - 128 * drawRatioBulletGraphs[style] / 2,
			128 * drawRatioBulletGraphs[style],
			128 * drawRatioBulletGraphs[style],
			imgRes.BulletBackGH[style],
			TRUE);
		SetDrawBright(255, 255, 255);
		DrawRectModiGraph(
			world[0].x, world[0].y,
			world[1].x, world[1].y,
			world[2].x, world[2].y,
			world[3].x, world[3].y,
			64 - 128 * drawRatioBulletGraphs[style] / 2,
			64 - 128 * drawRatioBulletGraphs[style] / 2,
			128 * drawRatioBulletGraphs[style],
			128 * drawRatioBulletGraphs[style],
			imgRes.BulletFrontGH[style],
			TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	if (isColShow == 1) {
		if ((flags & IS_COL) == 1) {
			SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			DrawCircle(pos.x, pos.y, colSize, GetColor(255, 255, 255), 1);
			DrawFormatString(pos.x, pos.y, GetColor(GetColorHSV(std::fmod(frame, 360), 1, 1).r, GetColorHSV(std::fmod(frame, 360), 1, 1).g, GetColorHSV(std::fmod(frame, 360), 1, 1).b), "%f", colSize);
		}
	}
}

void
Laser::ColliCheckObject() {
	double r = (length * length + colSize * colSize) / 4;
	double dx = pos.x - Plyr.pos.x;
	double dy = pos.y - Plyr.pos.y;
	if (dx * dx + dy * dy <= r) {
		return;
	}
	double halfW = colSize / 2;
	Vec2D local[4] = {
		{-halfW, 0},
		{-halfW, length},
		{ halfW, length},
		{ halfW, 0}
	};
	Vec2D world[4];
	for (int i = 0; i < 4; ++i) {
		Vec2D rot = RotatePoint(local[i], angle + PI / 2);
		world[i].x = pos.x + rot.x;
		world[i].y = pos.y + rot.y;
	}
	if (
		colPointAndRect(Plyr.pos,
			world[0],
			world[1],
			world[2],
			world[3])) {
		Plyr.HitPlayer();
		flags ^= ALIVE;
	}
}

int
Laser::CheckPosBounds() {
	double limit = size * 128 * 2 * drawRatioBulletGraphs[style];
	if (pos.x < BORDER_LEFT - limit) return 1;
	if (pos.x > BORDER_RIGHT + limit) return 1;
	if (pos.y < BORDER_UP - limit) return 1;
	if (pos.y > BORDER_DOWN + limit) return 1;

	return 0;
}

void
Laser::MoveFunc() {
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
CreateLaser(const Vec2D& pos, double length, double width, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID, const std::vector<std::any>& params) {
	for (int i = 0; i < Lasers.size(); i++) {
		if (!(Lasers[i].flags & ALIVE)) {
			Lasers[i].flags = ALIVE | isCol * IS_COL;
			Lasers[i].objType = OBJECT_LASER;
			Lasers[i].pos = pos;
			Lasers[i].color = color;
			Lasers[i].style = style;
			Lasers[i].blend = blend;
			Lasers[i].pal = pal;
			Lasers[i].startColSize = startColSize;
			Lasers[i].endColSize = endColSize;
			Lasers[i].colSizeEaseType = colSizeEaseType;
			Lasers[i].colSizeEaseTime = colSizeEaseTime;
			Lasers[i].startSize = startSize;
			Lasers[i].endSize = endSize;
			Lasers[i].sizeEaseType = sizeEaseType;
			Lasers[i].sizeEaseTime = sizeEaseTime;
			if (aim == 1) {
				Lasers[i].startAngle = Plyr.AimPlayer(pos) + startAngle;
				Lasers[i].endAngle = Plyr.AimPlayer(pos) + endAngle;
			}
			else {
				Lasers[i].startAngle = startAngle;
				Lasers[i].endAngle = endAngle;
			}
			Lasers[i].angleEaseType = angleEaseType;
			Lasers[i].angleEaseTime = angleEaseTime;
			Lasers[i].startSpeed = startSpeed;
			Lasers[i].endSpeed = endSpeed;
			Lasers[i].speedEaseType = speedEaseType;
			Lasers[i].speedEaseTime = speedEaseTime;
			Lasers[i].popFrame = frame;
			Lasers[i].length = length;
			Lasers[i].width = width;
			Lasers[i].frontNode = 0;
			Lasers[i].currentNodeNum = 0;
			Lasers[i].ID = 0;
			Lasers[i].params = params;
			return;
		}
	}
	/*if (aim == 1) {
		Lasers.emplace_back(1, isCol, pos, Plyr.AimPlayer(pos) + startAngle, Plyr.AimPlayer(pos) + endAngle, angleEaseType, angleEaseTime, 0, 0, 0, 0, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame, length, width, ID, params);
	}
	else {
		Lasers.emplace_back(1, isCol, pos, startAngle, endAngle, angleEaseType, angleEaseTime, 0, 0, 0, 0, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame, length, width, ID, params);
	}*/
}

void
CreateLaserGroup(const Vec2D& pos, double length, double width, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int way, double spread, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID, const std::vector<std::any>& params) {
	switch (aim) {
	case 0:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params);
		}
		break;
	case 1:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params);
		}
		break;
	case 2:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle + spread / (way * 2) - spread / 2, spread / way * i + endAngle + spread / (way * 2) - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params);
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params);
		}
		break;
	}
}

void
CreateSimpleLaserGroup(const Vec2D& pos, double length, double width, const Color& color, int style, int blend, int pal, double colSize, double size, int way, double spread, int aim, double angle, double speed, int ID, const std::vector<std::any>& params) {
	switch (aim) {
	case 0:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID, params);
		}
		break;
	case 1:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, 0, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID, params);
		}
		break;
	case 2:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle + spread / (way * 2) - spread / 2, spread / way * i + angle + spread / (way * 2) - spread / 2, 0, 0, speed, speed, 0, 0, ID, params);
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID, params);
		}
		break;
	}
}

void
MoveLasers() {
	for (auto& L : Lasers) {
		L.UpdateObject();
		L.ShowLaser();
	}
	if (frame % 10 == 0) {
		std::sort(Lasers.begin(), Lasers.end(), [](const Laser& a, const Laser& b) {
			return a.popFrame < b.popFrame;
			});
	}
}