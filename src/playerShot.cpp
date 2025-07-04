#include "Main.h"

#include "Bullet.h"
#include "Particle.h"
#include "Enemy.h"
#include "Laser.h"
#include "Object.h"
#include "Player.h"
#include "playerShot.h"
#include "Vec2D.h"

std::array<playerShot, MAX_PLAYER_SHOT> plyrShots;
std::array<playerShot*, MAX_PLAYER_SHOT> PlayerShotPtrs;
std::vector<int> BlankPlayerShots;
std::mutex BlankPlayerShotMutex;
std::array<int, GRAPHIC_HANDLER_NUM> defaultPlayerShotBlend;
std::array<double, GRAPHIC_HANDLER_NUM> drawRatioPlayerShotGraphs;

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
			DrawFormatString(pos.GetX(), pos.GetY(), GetColor(GetColorHSV(std::fmod(t, 360), 1, 1).r, GetColorHSV(std::fmod(t, 360), 1, 1).g, GetColorHSV(std::fmod(t, 360), 1, 1).b), "%f", colSize);
		}
	}
}

int
playerShot::ColliCheckObject() {
	return 0;
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

int
playerShot::CheckCollisionAndBounds() {
	if (flags & IS_COL) {
		if (ColliCheckObject()) {
			PushBlankPlayerShots(index);
			flags &= ~IS_ALIVE;
			return 1;
		}
	}
	if (CheckPosBounds()) {
		PushBlankPlayerShots(index);
		flags &= ~IS_ALIVE;
		return 1;
	}
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
PushBlankPlayerShots(int idx) {
	std::lock_guard<std::mutex> lock(BlankPlayerShotMutex);
	BlankPlayerShots.emplace_back(idx);
}

int
CreatePlayerShot(const Vec2D& pos, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int SE, int ID, const std::vector<std::any>& params) {
	soundMng.ReserveSE(SE);
	if (BlankPlayerShots.empty()) return 1;
	int idx = BlankPlayerShots.back();
	BlankPlayerShots.pop_back();
	SAFE_ACCESS(plyrShots, idx).flags = IS_ALIVE | isCol * IS_COL;
	SAFE_ACCESS(plyrShots, idx).objType = OBJECT_PLAYER_SHOT;
	SAFE_ACCESS(plyrShots, idx).pos = pos;
	SAFE_ACCESS(plyrShots, idx).color = color;
	SAFE_ACCESS(plyrShots, idx).style = style;
	SAFE_ACCESS(plyrShots, idx).blend = blend;
	SAFE_ACCESS(plyrShots, idx).pal = pal;
	SAFE_ACCESS(plyrShots, idx).startColSize = startColSize;
	SAFE_ACCESS(plyrShots, idx).endColSize = endColSize;
	SAFE_ACCESS(plyrShots, idx).colSizeEaseType = colSizeEaseType;
	SAFE_ACCESS(plyrShots, idx).colSizeEaseTime = colSizeEaseTime;
	SAFE_ACCESS(plyrShots, idx).startSize = startSize;
	SAFE_ACCESS(plyrShots, idx).endSize = endSize;
	SAFE_ACCESS(plyrShots, idx).sizeEaseType = sizeEaseType;
	SAFE_ACCESS(plyrShots, idx).sizeEaseTime = sizeEaseTime;
	SAFE_ACCESS(plyrShots, idx).startAngle = startAngle;
	SAFE_ACCESS(plyrShots, idx).endAngle = endAngle;
	SAFE_ACCESS(plyrShots, idx).angleEaseType = angleEaseType;
	SAFE_ACCESS(plyrShots, idx).angleEaseTime = angleEaseTime;
	SAFE_ACCESS(plyrShots, idx).startSpeed = startSpeed;
	SAFE_ACCESS(plyrShots, idx).endSpeed = endSpeed;
	SAFE_ACCESS(plyrShots, idx).speedEaseType = speedEaseType;
	SAFE_ACCESS(plyrShots, idx).speedEaseTime = speedEaseTime;
	SAFE_ACCESS(plyrShots, idx).popT = t;
	SAFE_ACCESS(plyrShots, idx).length = 0;
	SAFE_ACCESS(plyrShots, idx).width = 0;
	SAFE_ACCESS(plyrShots, idx).frontNode = 0;
	SAFE_ACCESS(plyrShots, idx).currentNodeNum = 0;
	SAFE_ACCESS(plyrShots, idx).index = idx;
	SAFE_ACCESS(plyrShots, idx).ID = 0;
	SAFE_ACCESS(plyrShots, idx).params = params;
	return 0;
}

void
ParallelUpdatePlayerShots(std::array<playerShot, MAX_PLAYER_SHOT>& playerShots) {
	std::for_each(std::execution::par_unseq, playerShots.begin(), playerShots.end(),
		[](playerShot& PS) {
			PS.UpdateObject();
		});
}

void
MovePlayerShots() {
	ParallelUpdatePlayerShots(plyrShots);
	for (auto* PS : PlayerShotPtrs) {
		PS->ShowPlayerShot();
	}
	if (t % 10 == 0) {
		std::sort(PlayerShotPtrs.begin(), PlayerShotPtrs.end(), [](const playerShot* a, const playerShot* b) {
			return a->popT < b->popT;
			});
	}
}