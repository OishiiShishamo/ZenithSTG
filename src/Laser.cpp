#include "Main.h"

#include "Bullet.h"
#include "Particle.h"
#include "Enemy.h"
#include "Graze.h"
#include "Laser.h"
#include "Object.h"
#include "Player.h"
#include "playerShot.h"
#include "Sound.h"
#include "timeUtl.h"
#include "Vec2D.h"

std::array<Laser, MAX_LASER> Lasers;
std::array<Laser*, MAX_LASER> LaserPtrs;
std::vector<int> BlankLasers;
std::mutex BlankLaserMutex;

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

int
Laser::ColliCheckObject() {
	double r = (length * length + colSize * colSize) / 4;
	Vec2D d = pos - Plyr.pos;
	if (d.GetX() * d.GetX() + d.GetY() * d.GetY() <= r) {
		return 0;
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
		return 1;
	}
	return 0;
}

#if GRAZE_ENABLED == 1
void
Laser::GrazeObject() {
	double r = (length * length + colSize * colSize + GrazeRange * GrazeRange) / 4;
	Vec2D d = pos - Plyr.pos;
	if (d.GetX() * d.GetX() + d.GetY() * d.GetY() <= r || (flags & IS_GRAZE) == 0) {
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
		Graze();
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

int
Laser::CheckCollisionAndBounds() {
	if (flags & IS_COL) {
		if (ColliCheckObject()) {
			PushBlankLasers(index);
			flags &= ~IS_ALIVE;
			return 1;
		}
	}
	if (CheckPosBounds()) {
		PushBlankLasers(index);
		flags &= ~IS_ALIVE;
		return 1;
	}
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
PushBlankLasers(int idx) {
	std::lock_guard<std::mutex> lock(BlankLaserMutex);
	BlankLasers.emplace_back(idx);
}

int
CreateLaser(const Vec2D& pos, double length, double width, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int SE, int ID, const std::vector<std::any>& params) {
	soundMng.ReserveSE(SE);
	if (BlankLasers.empty()) return 1;
	int idx = BlankLasers.back();
	BlankLasers.pop_back();
	SAFE_ACCESS(Lasers, idx).flags = IS_ALIVE | isCol * IS_COL | IS_GRAZE;
	SAFE_ACCESS(Lasers, idx).objType = OBJECT_LASER;
	SAFE_ACCESS(Lasers, idx).pos = pos;
	SAFE_ACCESS(Lasers, idx).color = color;
	SAFE_ACCESS(Lasers, idx).style = style;
	SAFE_ACCESS(Lasers, idx).blend = blend;
	SAFE_ACCESS(Lasers, idx).pal = pal;
	SAFE_ACCESS(Lasers, idx).startColSize = startColSize;
	SAFE_ACCESS(Lasers, idx).endColSize = endColSize;
	SAFE_ACCESS(Lasers, idx).colSizeEaseType = colSizeEaseType;
	SAFE_ACCESS(Lasers, idx).colSizeEaseTime = colSizeEaseTime;
	SAFE_ACCESS(Lasers, idx).startSize = startSize;
	SAFE_ACCESS(Lasers, idx).endSize = endSize;
	SAFE_ACCESS(Lasers, idx).sizeEaseType = sizeEaseType;
	SAFE_ACCESS(Lasers, idx).sizeEaseTime = sizeEaseTime;
	if (aim == AIM_TRUE) {
		SAFE_ACCESS(Lasers, idx).startAngle = Plyr.AimPlayer(pos) + startAngle;
		SAFE_ACCESS(Lasers, idx).endAngle = Plyr.AimPlayer(pos) + endAngle;
	}
	else {
		SAFE_ACCESS(Lasers, idx).startAngle = startAngle;
		SAFE_ACCESS(Lasers, idx).endAngle = endAngle;
	}
	SAFE_ACCESS(Lasers, idx).angleEaseType = angleEaseType;
	SAFE_ACCESS(Lasers, idx).angleEaseTime = angleEaseTime;
	SAFE_ACCESS(Lasers, idx).startSpeed = startSpeed;
	SAFE_ACCESS(Lasers, idx).endSpeed = endSpeed;
	SAFE_ACCESS(Lasers, idx).speedEaseType = speedEaseType;
	SAFE_ACCESS(Lasers, idx).speedEaseTime = speedEaseTime;
	SAFE_ACCESS(Lasers, idx).popT = t;
	SAFE_ACCESS(Lasers, idx).length = length;
	SAFE_ACCESS(Lasers, idx).width = width;
	SAFE_ACCESS(Lasers, idx).frontNode = 0;
	SAFE_ACCESS(Lasers, idx).currentNodeNum = 0;
	SAFE_ACCESS(Lasers, idx).index = idx;
	SAFE_ACCESS(Lasers, idx).ID = ID;
	SAFE_ACCESS(Lasers, idx).params = params;
	return 0;
}

void
CreateLaserGroup(const Vec2D& pos, double length, double width, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int way, double spread, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int SE, int ID, const std::vector<std::any>& params) {
	soundMng.ReserveSE(SE);
	switch (aim) {
	case AIM_FALSE:
		for (int i = 0; i < way; i++) {
			if (CreateLaser(pos, length, width, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, SE_NONE, ID, params)) return;
		}
		break;
	case AIM_TRUE:
		for (int i = 0; i < way; i++) {
			if (CreateLaser(pos, length, width, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, SE_NONE, ID, params)) return;
		}
		break;
	case AIM_TRUE_OFFSET:
		for (int i = 0; i < way; i++) {
			if (CreateLaser(pos, length, width, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle + spread / (way * 2) - spread / 2, spread / way * i + endAngle + spread / (way * 2) - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, SE_NONE, ID, params)) return;
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			if (CreateLaser(pos, length, width, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, SE_NONE, ID, params)) return;
		}
		break;
	}
}

void
CreateSimpleLaserGroup(const Vec2D& pos, double length, double width, const Color& color, int style, int blend, int pal, double colSize, double size, int way, double spread, int aim, double angle, double speed, int SE, int ID, const std::vector<std::any>& params) {
	soundMng.ReserveSE(SE);
	switch (aim) {
	case AIM_FALSE:
		for (int i = 0; i < way; i++) {
			if (CreateLaser(pos, length, width, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, SE_NONE, ID, params)) return;
		}
		break;
	case AIM_TRUE:
		for (int i = 0; i < way; i++) {
			if (CreateLaser(pos, length, width, color, style, blend, pal, 0, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, SE_NONE, ID, params)) return;
		}
		break;
	case AIM_TRUE_OFFSET:
		for (int i = 0; i < way; i++) {
			if (CreateLaser(pos, length, width, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle + spread / (way * 2) - spread / 2, spread / way * i + angle + spread / (way * 2) - spread / 2, 0, 0, speed, speed, 0, 0, SE_NONE, ID, params)) return;
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			if (CreateLaser(pos, length, width, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, SE_NONE, ID, params)) return;
		}
		break;
	}
}

void
CreateSmartLaserGroup(objectParams param) {
	soundMng.ReserveSE(param.SE);
	switch (param.aim) {
	case AIM_FALSE:
		for (int i = 0; i < param.way; i++) {
			if (CreateLaser(param.pos, param.length, param.width, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 0, param.spread / param.way * i + param.startAngle - param.spread / 2, param.spread / param.way * i + param.endAngle - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, SE_NONE, param.ID, param.params)) return;
		}
		break;
	case AIM_TRUE:
		for (int i = 0; i < param.way; i++) {
			if (CreateLaser(param.pos, param.length, param.width, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 1, param.spread / param.way * i + param.startAngle - param.spread / 2, param.spread / param.way * i + param.endAngle - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, SE_NONE, param.ID, param.params)) return;
		}
		break;
	case AIM_TRUE_OFFSET:
		for (int i = 0; i < param.way; i++) {
			if (CreateLaser(param.pos, param.length, param.width, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 1, param.spread / param.way * i + param.startAngle + param.spread / (param.way * 2) - param.spread / 2, param.spread / param.way * i + param.endAngle + param.spread / (param.way * 2) - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, SE_NONE, param.ID, param.params)) return;
		}
		break;
	default:
		for (int i = 0; i < param.way; i++) {
			if (CreateLaser(param.pos, param.length, param.width, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 0, param.spread / param.way * i + param.startAngle - param.spread / 2, param.spread / param.way * i + param.endAngle - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, SE_NONE, param.ID, param.params)) return;
		}
		break;
	}
}

void
ParallelUpdateLasers(std::array<Laser, MAX_LASER>& lasers) {
	std::for_each(std::execution::par_unseq, lasers.begin(), lasers.end(),
		[](Laser& L) {
			L.UpdateObject();
		});
}

void
MoveLasers() {
	if (t % 10 == 0) {
		std::sort(LaserPtrs.begin(), LaserPtrs.end(), [](const Laser* a, const Laser* b) {
			return a->popT < b->popT;
			});
	}
	ParallelUpdateLasers(Lasers);
	for (auto* L : LaserPtrs) {
		L->ShowLaser();
	}
}