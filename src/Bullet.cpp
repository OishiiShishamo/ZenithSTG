#include "Main.h"

#include "Bullet.h"
#include "Color.h"
#include "Easing.h"
#include "Effect.h"
#include "Enemy.h"
#include "Laser.h"
#include "Object.h"
#include "Player.h"
#include "playerShot.h"
#include "Vec2D.h"

//TODO: 引数減らしたラッパー関数作る

std::unique_ptr<std::array<Bullet, MAX_BULLET>> Bullets = std::make_unique< std::array<Bullet, MAX_BULLET>>();
std::array<Bullet*, MAX_BULLET> BulletPtrs;
std::vector<int> BlankBullets;
std::mutex BlankBulletsMutex;
std::array<int, GRAPHIC_HANDLER_NUM> defaultBulletBlend;
std::array<double, GRAPHIC_HANDLER_NUM> drawRatioBulletGraphs;
long long bIndex = 0;

void
Bullet::ShowBullet() {
	if (!(flags & IS_ALIVE)) return;
	std::array<Vec2D, 4> world;
	const bool isScaled = size > 1.0f;
	if (isScaled) {
		double half = size / 2 * 128 * SAFE_ACCESS(drawRatioBulletGraphs, style);
		std::array<Vec2D, 4> local = {
			Vec2D(-half, -half),
			Vec2D(-half, half),
			Vec2D(half, half),
			Vec2D(half, -half)
		};
		for (int i = 0; i < 4; ++i) {
			Vec2D rot = RotatePoint(SAFE_ACCESS(local, i), showAngle + pi / 2);
			SAFE_ACCESS(world, i) = pos + rot;
		}
	}
	if (blend == -1) {
		SmartSetDrawBlendMode(SAFE_ACCESS(defaultBulletBlend, style), pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if (isScaled) {
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
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, SAFE_ACCESS(imgRes.BulletBackGH, style), TRUE);
		SetDrawBright(255, 255, 255);
		if (isScaled) {
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
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, SAFE_ACCESS(imgRes.BulletFrontGH, style), TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if (isScaled) {
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
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, SAFE_ACCESS(imgRes.BulletBackGH, style), TRUE);
		SetDrawBright(255, 255, 255);
		if (isScaled) {
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
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, SAFE_ACCESS(imgRes.BulletFrontGH, style), TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	if (isColShow == 1) {
		if (flags & IS_COL) {
			SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			DrawCircle(pos.GetX(), pos.GetY(), colSize, GetColor(255, 255, 255), 1);
			DrawFormatString(pos.GetX(), pos.GetY(), GetColor(GetColorHSV(std::fmod(t, 360), 1, 1).r, GetColorHSV(std::fmod(t, 360), 1, 1).g, GetColorHSV(std::fmod(t, 360), 1, 1).b), "%f", colSize);
		}
	}
}

int
Bullet::ColliCheckObject() {
	if (colCircleAndCircle(pos, Plyr.pos, colSize + Plyr.colSize)) {
		//Plyr.HitPlayer();
		//return 1;
	}
	return 0;
}

#if GRAZE_ENABLED == 1
void
Bullet::GrazeObject() {
	if ((flags & IS_GRAZE) == 0) return;
	if (colCircleAndCircle(pos, Plyr.pos, colSize + Plyr.colSize + GrazeRange)) {
		addScore(GrazeScore);
		graze++;
		//GrazeEffect(Plyr.pos);
#if BULLET_GRAZE_EVERY_FRAME == 0
		flags &= ~IS_GRAZE;
#endif
	}
}
#endif

int
Bullet::CheckPosBounds() {
	double limit = size * 128 * 2 * SAFE_ACCESS(drawRatioBulletGraphs, style);
	if (pos.GetX() < BORDER_LEFT - limit) return 1;
	if (pos.GetX() > BORDER_RIGHT + limit) return 1;
	if (pos.GetY() < BORDER_UP - limit) return 1;
	if (pos.GetY() > BORDER_DOWN + limit) return 1;

	return 0;
}

int
Bullet::CheckCollisionAndBounds() {
	if (flags & IS_COL) {
		if (ColliCheckObject()) {
			PushBlankBullets(index);
			flags &= ~IS_ALIVE;
			return 1;
		}
	}
	if (CheckPosBounds()) {
		PushBlankBullets(index);
		flags &= ~IS_ALIVE;
		return 1;
	}
	return 0;
}

void
Bullet::MoveFunc() {
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
PushBlankBullets(int idx) {
	std::lock_guard<std::mutex> lock(BlankBulletsMutex);
	BlankBullets.emplace_back(idx);
}

int
CreateBullet(const Vec2D& pos, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID, const std::vector<std::any>& params) {
	if (BlankBullets.empty()) return 1;
	int idx = BlankBullets.back();
	SAFE_PTR_ACCESS(Bullets, idx).flags = IS_ALIVE | isCol * IS_COL | IS_GRAZE;
	SAFE_PTR_ACCESS(Bullets, idx).objType = OBJECT_BULLET;
	SAFE_PTR_ACCESS(Bullets, idx).pos = pos;
	SAFE_PTR_ACCESS(Bullets, idx).color = color;
	SAFE_PTR_ACCESS(Bullets, idx).style = style;
	SAFE_PTR_ACCESS(Bullets, idx).blend = blend;
	SAFE_PTR_ACCESS(Bullets, idx).pal = pal;
	SAFE_PTR_ACCESS(Bullets, idx).startColSize = startColSize;
	SAFE_PTR_ACCESS(Bullets, idx).endColSize = endColSize;
	SAFE_PTR_ACCESS(Bullets, idx).colSizeEaseType = colSizeEaseType;
	SAFE_PTR_ACCESS(Bullets, idx).colSizeEaseTime = colSizeEaseTime;
	SAFE_PTR_ACCESS(Bullets, idx).startSize = startSize;
	SAFE_PTR_ACCESS(Bullets, idx).endSize = endSize;
	SAFE_PTR_ACCESS(Bullets, idx).sizeEaseType = sizeEaseType;
	SAFE_PTR_ACCESS(Bullets, idx).sizeEaseTime = sizeEaseTime;
	if (aim == AIM_TRUE) {
		SAFE_PTR_ACCESS(Bullets, idx).startAngle = Plyr.AimPlayer(pos) + startAngle;
		SAFE_PTR_ACCESS(Bullets, idx).endAngle = Plyr.AimPlayer(pos) + endAngle;
	}
	else {
		SAFE_PTR_ACCESS(Bullets, idx).startAngle = startAngle;
		SAFE_PTR_ACCESS(Bullets, idx).endAngle = endAngle;
	}
	SAFE_PTR_ACCESS(Bullets, idx).angleEaseType = angleEaseType;
	SAFE_PTR_ACCESS(Bullets, idx).angleEaseTime = angleEaseTime;
	SAFE_PTR_ACCESS(Bullets, idx).startSpeed = startSpeed;
	SAFE_PTR_ACCESS(Bullets, idx).endSpeed = endSpeed;
	SAFE_PTR_ACCESS(Bullets, idx).speedEaseType = speedEaseType;
	SAFE_PTR_ACCESS(Bullets, idx).speedEaseTime = speedEaseTime;
	SAFE_PTR_ACCESS(Bullets, idx).popT = t;
	SAFE_PTR_ACCESS(Bullets, idx).length = 0;
	SAFE_PTR_ACCESS(Bullets, idx).width = 0;
	SAFE_PTR_ACCESS(Bullets, idx).frontNode = 0;
	SAFE_PTR_ACCESS(Bullets, idx).currentNodeNum = 0;
	SAFE_PTR_ACCESS(Bullets, idx).order = bIndex;
	SAFE_PTR_ACCESS(Bullets, idx).index = idx;
	SAFE_PTR_ACCESS(Bullets, idx).ID = ID;
	SAFE_PTR_ACCESS(Bullets, idx).params = params;
	BlankBullets.pop_back();
	bIndex++;
	return 0;
}

void
CreateBulletGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int way, double spread, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID, const std::vector<std::any>& params) {
	switch (aim) {
	case AIM_FALSE:
		for (int i = 0; i < way; i++) {
			if (CreateBullet(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params)) return;
		}
		break;
	case AIM_TRUE:
		for (int i = 0; i < way; i++) {
			if (CreateBullet(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params)) return;
		}
		break;
	case AIM_TRUE_OFFSET:
		for (int i = 0; i < way; i++) {
			if (CreateBullet(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle + spread / (way * 2) - spread / 2, spread / way * i + endAngle + spread / (way * 2) - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params)) return;
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			if (CreateBullet(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params)) return;
		}
		break;
	}
}

void
CreateSimpleBulletGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, double colSize, double size, int way, double spread, int aim, double angle, double speed, int ID, const std::vector<std::any>& params) {
	switch (aim) {
	case AIM_FALSE:
		for (int i = 0; i < way; i++) {
			if (CreateBullet(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID, params)) return;
		}
		break;
	case AIM_TRUE:
		for (int i = 0; i < way; i++) {
			if (CreateBullet(pos, color, style, blend, pal, 0, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID, params)) return;
		}
		break;
	case AIM_TRUE_OFFSET:
		for (int i = 0; i < way; i++) {
			if (CreateBullet(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle + spread / (way * 2) - spread / 2, spread / way * i + angle + spread / (way * 2) - spread / 2, 0, 0, speed, speed, 0, 0, ID, params)) return;
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			if (CreateBullet(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID, params)) return;
		}
		break;
	}
}

void
CreateSmartBulletGroup(objectParams param) {
	switch (param.aim) {
	case AIM_FALSE:
		for (int i = 0; i < param.way; i++) {
			if (CreateBullet(param.pos, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 0, param.spread / param.way * i + param.startAngle - param.spread / 2, param.spread / param.way * i + param.endAngle - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, param.ID, param.params)) return;
		}
		break;
	case AIM_TRUE:
		for (int i = 0; i < param.way; i++) {
			if (CreateBullet(param.pos, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 1, param.spread / param.way * i + param.startAngle - param.spread / 2, param.spread / param.way * i + param.endAngle - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, param.ID, param.params)) return;
		}
		break;
	case AIM_TRUE_OFFSET:
		for (int i = 0; i < param.way; i++) {
			if (CreateBullet(param.pos, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 1, param.spread / param.way * i + param.startAngle + param.spread / (param.way * 2) - param.spread / 2, param.spread / param.way * i + param.endAngle + param.spread / (param.way * 2) - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, param.ID, param.params)) return;
		}
		break;
	default:
		for (int i = 0; i < param.way; i++) {
			if (CreateBullet(param.pos, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 0, param.spread / param.way * i + param.startAngle - param.spread / 2, param.spread / param.way * i + param.endAngle - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, param.ID, param.params)) return;
		}
		break;
	}
}

void
ParallelUpdateBullets(std::array<Bullet, MAX_BULLET>& bullets) {
	std::for_each(std::execution::par_unseq, bullets.begin(), bullets.end(),
		[](Bullet& B) {
			B.UpdateObject();
		});
}

void
MoveBullets() {
	if (t % 1 == 0) {
		std::sort(BulletPtrs.begin(), BulletPtrs.end(), [](const Bullet* a, const Bullet* b) {
			return a->order < b->order;
			});
	}
	ParallelUpdateBullets(*Bullets);
	for (auto* B : BulletPtrs) {
		B->ShowBullet();
	}
}