#include "Main.h"

#include "Bullet.h"
#include "Color.h"
#include "Easing.h"
#include "Object.h"
#include "Player.h"

//TODO: 引数減らしたラッパー関数作る

std::array<Bullet, MAX_BULLET> Bullets;
std::array<int, 128> defaultBulletBlend;
std::array<double, 128> drawRatioBulletGraphs;
long long bIndex = 0;

void
Bullet::ShowBullet() {
	if (!(flags & ALIVE)) return;
	Vec2D world[4];
	const bool isScaled = size > 1.0f;
	if (isScaled) {
		double half = size / 2 * 128 * drawRatioBulletGraphs[style];
		Vec2D local[4] = {
			{-half, -half},
			{-half, half},
			{ half, half},
			{ half, -half}
		};
		for (int i = 0; i < 4; ++i) {
			Vec2D rot = RotatePoint(local[i], showAngle + PI / 2);
			world[i] = pos + rot;
		}
	}
	if (blend == -1) {
		SmartSetDrawBlendMode(defaultBulletBlend[style], pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if (isScaled) {
			DrawRectModiGraph(
				world[0].GetX(), world[0].GetY(),
				world[1].GetX(), world[1].GetY(),
				world[2].GetX(), world[2].GetY(),
				world[3].GetX(), world[3].GetY(),
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				128 * drawRatioBulletGraphs[style],
				128 * drawRatioBulletGraphs[style],
				imgRes.BulletBackGH[style],
				TRUE);
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, imgRes.BulletBackGH[style], TRUE);
		SetDrawBright(255, 255, 255);
		if (isScaled) {
			DrawRectModiGraph(
				world[0].GetX(), world[0].GetY(),
				world[1].GetX(), world[1].GetY(),
				world[2].GetX(), world[2].GetY(),
				world[3].GetX(), world[3].GetY(),
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				128 * drawRatioBulletGraphs[style],
				128 * drawRatioBulletGraphs[style],
				imgRes.BulletFrontGH[style],
				TRUE);
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, imgRes.BulletFrontGH[style], TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if (isScaled) {
			DrawRectModiGraph(
				world[0].GetX(), world[0].GetY(),
				world[1].GetX(), world[1].GetY(),
				world[2].GetX(), world[2].GetY(),
				world[3].GetX(), world[3].GetY(),
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				128 * drawRatioBulletGraphs[style],
				128 * drawRatioBulletGraphs[style],
				imgRes.BulletBackGH[style],
				TRUE);
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, imgRes.BulletBackGH[style], TRUE);
		SetDrawBright(255, 255, 255);
		if (isScaled) {
			DrawRectModiGraph(
				world[0].GetX(), world[0].GetY(),
				world[1].GetX(), world[1].GetY(),
				world[2].GetX(), world[2].GetY(),
				world[3].GetX(), world[3].GetY(),
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				64 - 128 * drawRatioBulletGraphs[style] / 2,
				128 * drawRatioBulletGraphs[style],
				128 * drawRatioBulletGraphs[style],
				imgRes.BulletFrontGH[style],
				TRUE);
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, imgRes.BulletFrontGH[style], TRUE);
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
Bullet::ColliCheckObject() {
	if (colCircleAndCircle(pos, Plyr.pos, colSize + Plyr.colSize)) {
		Plyr.HitPlayer();
		flags ^= ALIVE;
	}
}

int
Bullet::CheckPosBounds() {
	double limit = size * 128 * 2 * drawRatioBulletGraphs[style];
	if (pos.GetX() < BORDER_LEFT - limit) return 1;
	if (pos.GetX() > BORDER_RIGHT + limit) return 1;
	if (pos.GetY() < BORDER_UP - limit) return 1;
	if (pos.GetY() > BORDER_DOWN + limit) return 1;

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
CreateBullet(const Vec2D& pos, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID, const std::vector<std::any>& params) {
	for (int i = 0; i < Bullets.size(); i++) {
		if (!(Bullets[i].flags & ALIVE)) {
			Bullets[i].flags = ALIVE | isCol * IS_COL;
			Bullets[i].objType = OBJECT_BULLET;
			Bullets[i].pos = pos;
			Bullets[i].color = color;
			Bullets[i].style = style;
			Bullets[i].blend = blend;
			Bullets[i].pal = pal;
			Bullets[i].startColSize = startColSize;
			Bullets[i].endColSize = endColSize;
			Bullets[i].colSizeEaseType = colSizeEaseType;
			Bullets[i].colSizeEaseTime = colSizeEaseTime;
			Bullets[i].startSize = startSize;
			Bullets[i].endSize = endSize;
			Bullets[i].sizeEaseType = sizeEaseType;
			Bullets[i].sizeEaseTime = sizeEaseTime;
			if (aim == 1) {
				Bullets[i].startAngle = Plyr.AimPlayer(pos) + startAngle;
				Bullets[i].endAngle = Plyr.AimPlayer(pos) + endAngle;
			}
			else {
				Bullets[i].startAngle = startAngle;
				Bullets[i].endAngle = endAngle;
			}
			Bullets[i].angleEaseType = angleEaseType;
			Bullets[i].angleEaseTime = angleEaseTime;
			Bullets[i].startSpeed = startSpeed;
			Bullets[i].endSpeed = endSpeed;
			Bullets[i].speedEaseType = speedEaseType;
			Bullets[i].speedEaseTime = speedEaseTime;
			Bullets[i].popFrame = frame;
			Bullets[i].length = 0;
			Bullets[i].width = 0;
			Bullets[i].frontNode = 0;
			Bullets[i].currentNodeNum = 0;
			Bullets[i].index = bIndex;
			Bullets[i].ID = ID;
			Bullets[i].params = params;

			bIndex++;
			return;
		}
	}
	/*if (aim == 1) {
		Bullets.emplace_back(1, isCol, pos, Plyr.AimPlayer(pos) + startAngle, Plyr.AimPlayer(pos) + endAngle, angleEaseType, angleEaseTime, 0, 0, 0, 0, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame, ID, params);
	}
	else {
		Bullets.emplace_back(1, isCol, pos, startAngle, endAngle, angleEaseType, angleEaseTime, 0, 0, 0, 0, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame, ID, params);
	}*/
}

void
CreateBulletGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int way, double spread, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID, const std::vector<std::any>& params) {
	switch (aim) {
	case 0:
		for (int i = 0; i < way; i++) {
			CreateBullet(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params);
		}
		break;
	case 1:
		for (int i = 0; i < way; i++) {
			CreateBullet(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params);
		}
		break;
	case 2:
		for (int i = 0; i < way; i++) {
			CreateBullet(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle + spread / (way * 2) - spread / 2, spread / way * i + endAngle + spread / (way * 2) - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params);
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			CreateBullet(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params);
		}
		break;
	}
}

void
CreateSimpleBulletGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, double colSize, double size, int way, double spread, int aim, double angle, double speed, int ID, const std::vector<std::any>& params) {
	switch (aim) {
	case 0:
		for (int i = 0; i < way; i++) {
			CreateBullet(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID, params);
		}
		break;
	case 1:
		for (int i = 0; i < way; i++) {
			CreateBullet(pos, color, style, blend, pal, 0, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID, params);
		}
		break;
	case 2:
		for (int i = 0; i < way; i++) {
			CreateBullet(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle + spread / (way * 2) - spread / 2, spread / way * i + angle + spread / (way * 2) - spread / 2, 0, 0, speed, speed, 0, 0, ID, params);
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			CreateBullet(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID, params);
		}
		break;
	}
}

void
CreateSmartBulletGroup(objectParams param) {
	switch (param.aim) {
	case 0:
		for (int i = 0; i < param.way; i++) {
			CreateBullet(param.pos, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 0, param.spread / param.way * i + param.startAngle - param.spread / 2, param.spread / param.way * i + param.endAngle - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, param.ID, param.params);
		}
		break;
	case 1:
		for (int i = 0; i < param.way; i++) {
			CreateBullet(param.pos, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 1, param.spread / param.way * i + param.startAngle - param.spread / 2, param.spread / param.way * i + param.endAngle - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, param.ID, param.params);
		}
		break;
	case 2:
		for (int i = 0; i < param.way; i++) {
			CreateBullet(param.pos, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 1, param.spread / param.way * i + param.startAngle + param.spread / (param.way * 2) - param.spread / 2, param.spread / param.way * i + param.endAngle + param.spread / (param.way * 2) - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, param.ID, param.params);
		}
		break;
	default:
		for (int i = 0; i < param.way; i++) {
			CreateBullet(param.pos, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 0, param.spread / param.way * i + param.startAngle - param.spread / 2, param.spread / param.way * i + param.endAngle - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, param.ID, param.params);
		}
		break;
	}
}

void
MoveBullets() {
	for (auto& B : Bullets) {
		B.UpdateObject();
		B.ShowBullet();
	}
	if (frame % 1 == 0) {
		std::sort(Bullets.begin(), Bullets.end(), [](const Bullet& a, const Bullet& b) {
			return a.index < b.index;
			});
	}
}