#include "Main.h"

#include "Bullet.h"
#include "Color.h"
#include "Easing.h"
#include "Laser.h"
#include "Player.h"
#include "Time.h"
#include "Effect.h"

std::unique_ptr<std::array<Laser, MAX_LASER>> Lasers = std::make_unique< std::array<Laser, MAX_LASER>>();

void
Laser::ShowLaser() {
	if (!(flags & IS_ALIVE)) return;
	double halfW = width / 2;
	std::array<Vec2D, 4> local = {
		Vec2D(-halfW, 0),
		Vec2D(-halfW, length),
		Vec2D(halfW, length),
		Vec2D(halfW, 0)
	};
	std::array<Vec2D, 4> world;
	for (int i = 0; i < 4; ++i) {
		Vec2D rot = RotatePoint(SAFE_ACCESS(local, i), showAngle + pi / 2);
		SAFE_ACCESS(world, i) = pos + rot;
	}
	if (blend == -1) {
		SmartSetDrawBlendMode(SAFE_ACCESS(defaultBulletBlend, style), pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		DrawRectModiGraph(
			SAFE_ACCESS(world, 0).GetX(), SAFE_ACCESS(world, 0).GetY(),
			SAFE_ACCESS(world, 1).GetX(), SAFE_ACCESS(world, 1).GetY(),
			SAFE_ACCESS(world, 2).GetX(), SAFE_ACCESS(world, 2).GetY(),
			SAFE_ACCESS(world, 3).GetX(), SAFE_ACCESS(world, 3).GetY(),
			64 - 128 * SAFE_ACCESS(drawRatioBulletGraphs, style) / 2,
			64 - 128 * SAFE_ACCESS(drawRatioBulletGraphs, style) / 2,
			128 * SAFE_ACCESS(drawRatioBulletGraphs, style),
			128 * SAFE_ACCESS(drawRatioBulletGraphs, style),
			SAFE_ACCESS(imgRes.BulletBackGH, style),
			TRUE);
		SetDrawBright(255, 255, 255);
		DrawRectModiGraph(
			SAFE_ACCESS(world, 0).GetX(), SAFE_ACCESS(world, 0).GetY(),
			SAFE_ACCESS(world, 1).GetX(), SAFE_ACCESS(world, 1).GetY(),
			SAFE_ACCESS(world, 2).GetX(), SAFE_ACCESS(world, 2).GetY(),
			SAFE_ACCESS(world, 3).GetX(), SAFE_ACCESS(world, 3).GetY(),
			64 - 128 * SAFE_ACCESS(drawRatioBulletGraphs, style) / 2,
			64 - 128 * SAFE_ACCESS(drawRatioBulletGraphs, style) / 2,
			128 * SAFE_ACCESS(drawRatioBulletGraphs, style),
			128 * SAFE_ACCESS(drawRatioBulletGraphs, style),
			SAFE_ACCESS(imgRes.BulletFrontGH, style),
			TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		DrawRectModiGraph(
			SAFE_ACCESS(world, 0).GetX(), SAFE_ACCESS(world, 0).GetY(),
			SAFE_ACCESS(world, 1).GetX(), SAFE_ACCESS(world, 1).GetY(),
			SAFE_ACCESS(world, 2).GetX(), SAFE_ACCESS(world, 2).GetY(),
			SAFE_ACCESS(world, 3).GetX(), SAFE_ACCESS(world, 3).GetY(),
			64 - 128 * SAFE_ACCESS(drawRatioBulletGraphs, style) / 2,
			64 - 128 * SAFE_ACCESS(drawRatioBulletGraphs, style) / 2,
			128 * SAFE_ACCESS(drawRatioBulletGraphs, style),
			128 * SAFE_ACCESS(drawRatioBulletGraphs, style),
			SAFE_ACCESS(imgRes.BulletBackGH, style),
			TRUE);
		SetDrawBright(255, 255, 255);
		DrawRectModiGraph(
			SAFE_ACCESS(world, 0).GetX(), SAFE_ACCESS(world, 0).GetY(),
			SAFE_ACCESS(world, 1).GetX(), SAFE_ACCESS(world, 1).GetY(),
			SAFE_ACCESS(world, 2).GetX(), SAFE_ACCESS(world, 2).GetY(),
			SAFE_ACCESS(world, 3).GetX(), SAFE_ACCESS(world, 3).GetY(),
			64 - 128 * SAFE_ACCESS(drawRatioBulletGraphs, style) / 2,
			64 - 128 * SAFE_ACCESS(drawRatioBulletGraphs, style) / 2,
			128 * SAFE_ACCESS(drawRatioBulletGraphs, style),
			128 * SAFE_ACCESS(drawRatioBulletGraphs, style),
			SAFE_ACCESS(imgRes.BulletFrontGH, style),
			TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	if (isColShow == 1) {
		if ((flags & IS_COL) == 1) {
			SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			DrawCircle(pos.GetX(), pos.GetY(), colSize, GetColor(255, 255, 255), 1);
			DrawFormatString(pos.GetX(), pos.GetY(), GetColor(GetColorHSV(std::fmod(t, 360), 1, 1).r, GetColorHSV(std::fmod(t, 360), 1, 1).g, GetColorHSV(std::fmod(t, 360), 1, 1).b), "%f", colSize);
		}
	}
}

void
Laser::ColliCheckObject() {
	double r = (length * length + colSize * colSize) / 4;
	Vec2D d = pos - Plyr.pos;
	if (d.GetX() * d.GetX() + d.GetY() * d.GetY() <= r) {
		return;
	}
	double halfW = colSize / 2;
	std::array<Vec2D, 4> local = {
		Vec2D(-halfW, 0),
		Vec2D(-halfW, length),
		Vec2D(halfW, length),
		Vec2D(halfW, 0)
	};
	std::array<Vec2D, 4> world;
	for (int i = 0; i < 4; ++i) {
		Vec2D rot = RotatePoint(SAFE_ACCESS(local, i), showAngle + pi / 2);
		SAFE_ACCESS(world, i) = pos + rot;
	}
	if (
		colPointAndRect(Plyr.pos,
			SAFE_ACCESS(world, 0),
			SAFE_ACCESS(world, 1),
			SAFE_ACCESS(world, 2),
			SAFE_ACCESS(world, 3))) {
		Plyr.HitPlayer();
		flags &= ~IS_ALIVE;
	}
}

#if GRAZE_ENABLED == 1
void
Laser::GrazeObject() {
	double r = (length * length + colSize * colSize + GrazeRange * GrazeRange) / 4;
	Vec2D d = pos - Plyr.pos;
	if (d.GetX() * d.GetX() + d.GetY() * d.GetY() <= r || flags & IS_GRAZE == 0) {
		return;
	}
	double halfW = (colSize + GrazeRange) / 2;
	std::array<Vec2D, 4> local = {
		Vec2D(-halfW, 0),
		Vec2D(-halfW, length),
		Vec2D(halfW, length),
		Vec2D(halfW, 0)
	};
	std::array<Vec2D, 4> world;
	for (int i = 0; i < 4; ++i) {
		Vec2D rot = RotatePoint(SAFE_ACCESS(local, i), showAngle + pi / 2);
		SAFE_ACCESS(world, i) = pos + rot;
	}
	if (
		colPointAndRect(Plyr.pos,
			SAFE_ACCESS(world, 0),
			SAFE_ACCESS(world, 1),
			SAFE_ACCESS(world, 2),
			SAFE_ACCESS(world, 3))) {
		addScore(GrazeScore);
		graze++;
		GrazeEffect(Plyr.pos);
#if LASER_GRAZE_EVERY_FRAME == 0
		flags &= ~IS_GRAZE;
#endif
	}
}
#endif

int
Laser::CheckPosBounds() {
	double limit = size * 128 * 2 * SAFE_ACCESS(drawRatioBulletGraphs, style);
	if (pos.GetX() < BORDER_LEFT - limit) return 1;
	if (pos.GetX() > BORDER_RIGHT + limit) return 1;
	if (pos.GetY() < BORDER_UP - limit) return 1;
	if (pos.GetY() > BORDER_DOWN + limit) return 1;

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
	for (int i = 0; i < Lasers->size(); i++) {
		if (!(SAFE_PTR_ACCESS(Lasers, i).flags & IS_ALIVE)) {
			SAFE_PTR_ACCESS(Lasers, i).flags = IS_ALIVE | isCol * IS_COL | IS_GRAZE;
			SAFE_PTR_ACCESS(Lasers, i).objType = OBJECT_LASER;
			SAFE_PTR_ACCESS(Lasers, i).pos = pos;
			SAFE_PTR_ACCESS(Lasers, i).color = color;
			SAFE_PTR_ACCESS(Lasers, i).style = style;
			SAFE_PTR_ACCESS(Lasers, i).blend = blend;
			SAFE_PTR_ACCESS(Lasers, i).pal = pal;
			SAFE_PTR_ACCESS(Lasers, i).startColSize = startColSize;
			SAFE_PTR_ACCESS(Lasers, i).endColSize = endColSize;
			SAFE_PTR_ACCESS(Lasers, i).colSizeEaseType = colSizeEaseType;
			SAFE_PTR_ACCESS(Lasers, i).colSizeEaseTime = colSizeEaseTime;
			SAFE_PTR_ACCESS(Lasers, i).startSize = startSize;
			SAFE_PTR_ACCESS(Lasers, i).endSize = endSize;
			SAFE_PTR_ACCESS(Lasers, i).sizeEaseType = sizeEaseType;
			SAFE_PTR_ACCESS(Lasers, i).sizeEaseTime = sizeEaseTime;
			if (aim == AIM_TRUE) {
				SAFE_PTR_ACCESS(Lasers, i).startAngle = Plyr.AimPlayer(pos) + startAngle;
				SAFE_PTR_ACCESS(Lasers, i).endAngle = Plyr.AimPlayer(pos) + endAngle;
			}
			else {
				SAFE_PTR_ACCESS(Lasers, i).startAngle = startAngle;
				SAFE_PTR_ACCESS(Lasers, i).endAngle = endAngle;
			}
			SAFE_PTR_ACCESS(Lasers, i).angleEaseType = angleEaseType;
			SAFE_PTR_ACCESS(Lasers, i).angleEaseTime = angleEaseTime;
			SAFE_PTR_ACCESS(Lasers, i).startSpeed = startSpeed;
			SAFE_PTR_ACCESS(Lasers, i).endSpeed = endSpeed;
			SAFE_PTR_ACCESS(Lasers, i).speedEaseType = speedEaseType;
			SAFE_PTR_ACCESS(Lasers, i).speedEaseTime = speedEaseTime;
			SAFE_PTR_ACCESS(Lasers, i).popT = t;
			SAFE_PTR_ACCESS(Lasers, i).length = length;
			SAFE_PTR_ACCESS(Lasers, i).width = width;
			SAFE_PTR_ACCESS(Lasers, i).frontNode = 0;
			SAFE_PTR_ACCESS(Lasers, i).currentNodeNum = 0;
			SAFE_PTR_ACCESS(Lasers, i).ID = 0;
			SAFE_PTR_ACCESS(Lasers, i).params = params;
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
	case AIM_FALSE:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params);
		}
		break;
	case AIM_TRUE:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params);
		}
		break;
	case AIM_TRUE_OFFSET:
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
	case AIM_FALSE:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID, params);
		}
		break;
	case AIM_TRUE:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, 0, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID, params);
		}
		break;
	case AIM_TRUE_OFFSET:
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
CreateSmartLaserGroup(objectParams param) {
	switch (param.aim) {
	case AIM_FALSE:
		for (int i = 0; i < param.way; i++) {
			CreateLaser(param.pos, param.length, param.width, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 0, param.spread / param.way * i + param.startAngle - param.spread / 2, param.spread / param.way * i + param.endAngle - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, param.ID, param.params);
		}
		break;
	case AIM_TRUE:
		for (int i = 0; i < param.way; i++) {
			CreateLaser(param.pos, param.length, param.width, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 1, param.spread / param.way * i + param.startAngle - param.spread / 2, param.spread / param.way * i + param.endAngle - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, param.ID, param.params);
		}
		break;
	case AIM_TRUE_OFFSET:
		for (int i = 0; i < param.way; i++) {
			CreateLaser(param.pos, param.length, param.width, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 1, param.spread / param.way * i + param.startAngle + param.spread / (param.way * 2) - param.spread / 2, param.spread / param.way * i + param.endAngle + param.spread / (param.way * 2) - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, param.ID, param.params);
		}
		break;
	default:
		for (int i = 0; i < param.way; i++) {
			CreateLaser(param.pos, param.length, param.width, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 0, param.spread / param.way * i + param.startAngle - param.spread / 2, param.spread / param.way * i + param.endAngle - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, param.ID, param.params);
		}
		break;
	}
}

void
MoveLasers() {
	for (auto& L : (*Lasers)) {
		L.UpdateObject();
		L.ShowLaser();
	}
	if (t % 10 == 0) {
		std::sort(Lasers->begin(), Lasers->end(), [](const Laser& a, const Laser& b) {
			return a.popT < b.popT;
			});
	}
}