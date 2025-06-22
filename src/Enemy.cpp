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

std::unique_ptr<std::array<Enemy, MAX_ENEMY>> Enemies = std::make_unique<std::array<Enemy, MAX_ENEMY>>();
std::array<Enemy*, MAX_ENEMY> EnemyPtrs;
std::vector<int> BlankEnemies;
std::mutex BlankEnemyMutex;
std::array<int, GRAPHIC_HANDLER_NUM> defaultEnemyBlend;
std::array<double, GRAPHIC_HANDLER_NUM> drawRatioEnemyGraphs;

void
Enemy::ShowEnemy() {
	if (!(flags & IS_ALIVE)) return;
	if (blend == -1) {
		SmartSetDrawBlendMode(SAFE_ACCESS(defaultEnemyBlend, style), pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, SAFE_ACCESS(imgRes.EnemyGH, style), TRUE);
		SetDrawBright(255, 255, 255);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, SAFE_ACCESS(imgRes.EnemyGH, style), TRUE);
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
Enemy::ColliCheckObject() {
	if (colCircleAndCircle(pos, Plyr.pos, colSize + Plyr.colSize)) {
		Plyr.HitPlayer();
		return 1;
	}
	return 0;
}

int
Enemy::CheckPosBounds() {
	double limit = size * 128 * 2 * SAFE_ACCESS(drawRatioEnemyGraphs, style);
	if (pos.GetX() < BORDER_LEFT - limit) return 1;
	if (pos.GetX() > BORDER_RIGHT + limit) return 1;
	if (pos.GetY() < BORDER_UP - limit) return 1;
	if (pos.GetY() > BORDER_DOWN + limit) return 1;

	return 0;
}

int
Enemy::CheckCollisionAndBounds() {
	if (flags & IS_COL) {
		if (ColliCheckObject()) {
			PushBlankEnemies(index);
			flags &= ~IS_ALIVE;
			return 1;
		}
	}
	if (CheckPosBounds()) {
		PushBlankEnemies(index);
		flags &= ~IS_ALIVE;
		return 1;
	}
	return 0;
}

void
Enemy::MoveFunc() {
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
PushBlankEnemies(int idx) {
	std::lock_guard<std::mutex> lock(BlankEnemyMutex);
	BlankEnemies.emplace_back(idx);
}

int
CreateEnemy(const Vec2D& pos, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int SE, int ID, const std::vector<std::any>& params) {
	soundMng.ReserveSE(SE);
	if (BlankEnemies.empty()) return 1;
	int idx = BlankEnemies.back();
	SAFE_PTR_ACCESS(Enemies, idx).flags = IS_ALIVE | isCol * IS_COL;
	SAFE_PTR_ACCESS(Enemies, idx).objType = OBJECT_ENEMY;
	SAFE_PTR_ACCESS(Enemies, idx).pos = pos;
	SAFE_PTR_ACCESS(Enemies, idx).color = color;
	SAFE_PTR_ACCESS(Enemies, idx).style = style;
	SAFE_PTR_ACCESS(Enemies, idx).blend = blend;
	SAFE_PTR_ACCESS(Enemies, idx).pal = pal;
	SAFE_PTR_ACCESS(Enemies, idx).startColSize = startColSize;
	SAFE_PTR_ACCESS(Enemies, idx).endColSize = endColSize;
	SAFE_PTR_ACCESS(Enemies, idx).colSizeEaseType = colSizeEaseType;
	SAFE_PTR_ACCESS(Enemies, idx).colSizeEaseTime = colSizeEaseTime;
	SAFE_PTR_ACCESS(Enemies, idx).startSize = startSize;
	SAFE_PTR_ACCESS(Enemies, idx).endSize = endSize;
	SAFE_PTR_ACCESS(Enemies, idx).sizeEaseType = sizeEaseType;
	SAFE_PTR_ACCESS(Enemies, idx).sizeEaseTime = sizeEaseTime;
	if (aim == AIM_TRUE) {
		SAFE_PTR_ACCESS(Enemies, idx).startAngle = Plyr.AimPlayer(pos) + startAngle;
		SAFE_PTR_ACCESS(Enemies, idx).endAngle = Plyr.AimPlayer(pos) + endAngle;
	}
	else {
		SAFE_PTR_ACCESS(Enemies, idx).startAngle = startAngle;
		SAFE_PTR_ACCESS(Enemies, idx).endAngle = endAngle;
	}
	SAFE_PTR_ACCESS(Enemies, idx).angleEaseType = angleEaseType;
	SAFE_PTR_ACCESS(Enemies, idx).angleEaseTime = angleEaseTime;
	SAFE_PTR_ACCESS(Enemies, idx).startSpeed = startSpeed;
	SAFE_PTR_ACCESS(Enemies, idx).endSpeed = endSpeed;
	SAFE_PTR_ACCESS(Enemies, idx).speedEaseType = speedEaseType;
	SAFE_PTR_ACCESS(Enemies, idx).speedEaseTime = speedEaseTime;
	SAFE_PTR_ACCESS(Enemies, idx).popT = t;
	SAFE_PTR_ACCESS(Enemies, idx).length = 0;
	SAFE_PTR_ACCESS(Enemies, idx).width = 0;
	SAFE_PTR_ACCESS(Enemies, idx).frontNode = 0;
	SAFE_PTR_ACCESS(Enemies, idx).currentNodeNum = 0;
	SAFE_PTR_ACCESS(Enemies, idx).index = idx;
	SAFE_PTR_ACCESS(Enemies, idx).ID = ID;
	SAFE_PTR_ACCESS(Enemies, idx).params = params;
	BlankEnemies.pop_back();
	return 0;
}

void
CreateEnemyGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int way, double spread, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int SE, int ID, const std::vector<std::any>& params) {
	soundMng.ReserveSE(SE);
	switch (aim) {
	case AIM_FALSE:
		for (int i = 0; i < way; i++) {
			if (CreateEnemy(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, SE_NONE, ID, params)) return;
		}
		break;
	case AIM_TRUE:
		for (int i = 0; i < way; i++) {
			if (CreateEnemy(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, SE_NONE, ID, params)) return;
		}
		break;
	case AIM_TRUE_OFFSET:
		for (int i = 0; i < way; i++) {
			if (CreateEnemy(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle + spread / (way * 2) - spread / 2, spread / way * i + endAngle + spread / (way * 2) - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, SE_NONE, ID, params)) return;
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			if (CreateEnemy(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, SE_NONE, ID, params)) return;
		}
		break;
	}
}

void
CreateSimpleEnemyGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, double colSize, double size, int way, double spread, int aim, double angle, double speed, int SE, int ID, const std::vector<std::any>& params) {
	soundMng.ReserveSE(SE);
	switch (aim) {
	case AIM_FALSE:
		for (int i = 0; i < way; i++) {
			if (CreateEnemy(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, SE_NONE, ID, params)) return;
		}
		break;
	case AIM_TRUE:
		for (int i = 0; i < way; i++) {
			if (CreateEnemy(pos, color, style, blend, pal, 0, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, SE_NONE, ID, params)) return;
		}
		break;
	case AIM_TRUE_OFFSET:
		for (int i = 0; i < way; i++) {
			if (CreateEnemy(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle + spread / (way * 2) - spread / 2, spread / way * i + angle + spread / (way * 2) - spread / 2, 0, 0, speed, speed, 0, 0, SE_NONE, ID, params)) return;
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			if (CreateEnemy(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, SE_NONE, ID, params)) return;
		}
		break;
	}
}

void
CreateSmartEnemyGroup(objectParams param) {
	soundMng.ReserveSE(param.SE); 
	switch (param.aim) {
	case AIM_FALSE:
		for (int i = 0; i < param.way; i++) {
			if (CreateEnemy(param.pos, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 0, param.spread / param.way * i + param.startAngle - param.spread / 2, param.spread / param.way * i + param.endAngle - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, SE_NONE, param.ID, param.params)) return;
		}
		break;
	case AIM_TRUE:
		for (int i = 0; i < param.way; i++) {
			if (CreateEnemy(param.pos, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 1, param.spread / param.way * i + param.startAngle - param.spread / 2, param.spread / param.way * i + param.endAngle - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, SE_NONE, param.ID, param.params)) return;
		}
		break;
	case AIM_TRUE_OFFSET:
		for (int i = 0; i < param.way; i++) {
			if (CreateEnemy(param.pos, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 1, param.spread / param.way * i + param.startAngle + param.spread / (param.way * 2) - param.spread / 2, param.spread / param.way * i + param.endAngle + param.spread / (param.way * 2) - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, SE_NONE, param.ID, param.params)) return;
		}
		break;
	default:
		for (int i = 0; i < param.way; i++) {
			if (CreateEnemy(param.pos, param.color, param.style, param.blend, param.pal, param.isCol, param.startColSize, param.endColSize, param.colSizeEaseType, param.colSizeEaseTime, param.startSize, param.endSize, param.sizeEaseType, param.sizeEaseTime, 0, param.spread / param.way * i + param.startAngle - param.spread / 2, param.spread / param.way * i + param.endAngle - param.spread / 2, param.angleEaseType, param.angleEaseTime, param.startSpeed, param.endSpeed, param.speedEaseType, param.speedEaseTime, SE_NONE, param.ID, param.params)) return;
		}
		break;
	}
}

void
ParallelUpdateEnemies(std::array<Enemy, MAX_ENEMY>& enemies) {
	std::for_each(std::execution::par_unseq, enemies.begin(), enemies.end(),
		[](Enemy& E) {
			E.UpdateObject();
		});
}

void
MoveEnemies() {
	ParallelUpdateEnemies(*Enemies);
	for (auto* E : EnemyPtrs) {
		E->ShowEnemy();
	}
	if (t % 10 == 0) {
		std::sort(EnemyPtrs.begin(), EnemyPtrs.end(), [](const Enemy* a, const Enemy* b) {
			return a->popT < b->popT;
			});
	}
}