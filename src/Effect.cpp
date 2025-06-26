#include "Main.h"
#include "Effect.h"
#include "Player.h"
#include "Easing.h"
#include <algorithm>
#include <execution>

std::unique_ptr<std::array<Effect, MAX_EFFECT>> Effects = std::make_unique<std::array<Effect, MAX_EFFECT>>();
std::array<Effect*, MAX_EFFECT> EffectPtrs;
std::vector<int> BlankEffects;
std::mutex BlankEffectsMutex;
std::array<int, GRAPHIC_HANDLER_NUM> defaultEffectBlend;
std::array<double, GRAPHIC_HANDLER_NUM> drawRatioEffectGraphs;
long long eIndex = 0;

void
Effect::UpdateObject(long long Index) {
	if (!(flags & IS_ALIVE)) return;

	UpdateEase();

	vec = AngleToVec2D(angle);
	MoveFunc();
	if (t - popT >= palEaseTime) {
		PushBlankEffects(index);
		flags &= ~IS_ALIVE;
	}
}

void
Effect::UpdateEase() {
	double elapsedFrame = (static_cast<double>(t - popT));
	if (angleEaseTime == 0) {
		angle = endAngle;
	}
	else {
		angleT = elapsedFrame / angleEaseTime;
		if (angleT > 1)angleT = 1;
		angle = Easing(angleEaseType, angleT, startAngle, endAngle);
	}
	if (isAlignedAngle == 1) {
		showAngle = angle;
	}

	if (speedEaseTime == 0) {
		speed = endSpeed;
	}
	else {
		speedT = elapsedFrame / speedEaseTime;
		if (speedT > 1) speedT = 1;
		speed = Easing(speedEaseType, speedT, startSpeed, endSpeed);
	}

	if (colSizeEaseTime == 0) {
		colSize = endColSize;
	}
	else {
		colSizeT = elapsedFrame / colSizeEaseTime;
		if (colSizeT > 1)colSizeT = 1;
		colSize = Easing(colSizeEaseType, colSizeT, startColSize, endColSize);
	}

	if (sizeEaseTime == 0) {
		size = endSize;
	}
	else {
		sizeT = elapsedFrame / sizeEaseTime;
		if (sizeT > 1) sizeT = 1;
		size = Easing(sizeEaseType, sizeT, startSize, endSize);
	}

	if (palEaseTime == 0) {
		pal = 0;
	}
	else {
		palT = elapsedFrame / palEaseTime;
		if (palT > 1) palT = 1;
		pal = Easing(palEaseType, palT, startPal, 0);
	}
}

void
Effect::ShowEffect() {
	if (!(flags & IS_ALIVE)) return;
	std::array<Vec2D, 4> world;
	const bool isScaled = size > 1.0f;
	if (isScaled) {
		double half = size / 2 * 128 * SAFE_ACCESS(drawRatioEffectGraphs, style);
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
		SmartSetDrawBlendMode(SAFE_ACCESS(defaultEffectBlend, style), pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if (isScaled) {
			DrawRectModiGraph(
				SAFE_ACCESS(world, 0).GetX(), SAFE_ACCESS(world, 0).GetY(),
				SAFE_ACCESS(world, 1).GetX(), SAFE_ACCESS(world, 1).GetY(),
				SAFE_ACCESS(world, 2).GetX(), SAFE_ACCESS(world, 2).GetY(),
				SAFE_ACCESS(world, 3).GetX(), SAFE_ACCESS(world, 3).GetY(),
				64 - 128 * SAFE_ACCESS(drawRatioEffectGraphs, style) / 2,
				64 - 128 * SAFE_ACCESS(drawRatioEffectGraphs, style) / 2,
				128 * SAFE_ACCESS(drawRatioEffectGraphs, style),
				128 * SAFE_ACCESS(drawRatioEffectGraphs, style),
				SAFE_ACCESS(imgRes.EffectBackGH, style),
				TRUE);
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, SAFE_ACCESS(imgRes.EffectBackGH, style), TRUE);
		SetDrawBright(255, 255, 255);
		if (isScaled) {
			DrawRectModiGraph(
				SAFE_ACCESS(world, 0).GetX(), SAFE_ACCESS(world, 0).GetY(),
				SAFE_ACCESS(world, 1).GetX(), SAFE_ACCESS(world, 1).GetY(),
				SAFE_ACCESS(world, 2).GetX(), SAFE_ACCESS(world, 2).GetY(),
				SAFE_ACCESS(world, 3).GetX(), SAFE_ACCESS(world, 3).GetY(),
				64 - 128 * SAFE_ACCESS(drawRatioEffectGraphs, style) / 2,
				64 - 128 * SAFE_ACCESS(drawRatioEffectGraphs, style) / 2,
				128 * SAFE_ACCESS(drawRatioEffectGraphs, style),
				128 * SAFE_ACCESS(drawRatioEffectGraphs, style),
				SAFE_ACCESS(imgRes.EffectFrontGH, style),
				TRUE);
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, SAFE_ACCESS(imgRes.EffectFrontGH, style), TRUE);
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
					64 - 128 * SAFE_ACCESS(drawRatioEffectGraphs, style) / 2,
					64 - 128 * SAFE_ACCESS(drawRatioEffectGraphs, style) / 2,
					128 * SAFE_ACCESS(drawRatioEffectGraphs, style),
					128 * SAFE_ACCESS(drawRatioEffectGraphs, style),
					SAFE_ACCESS(imgRes.EffectBackGH, style),
					TRUE);
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, SAFE_ACCESS(imgRes.EffectBackGH, style), TRUE);
		SetDrawBright(255, 255, 255);
		if (isScaled) {
			DrawRectModiGraph(
				SAFE_ACCESS(world, 0).GetX(), SAFE_ACCESS(world, 0).GetY(),
				SAFE_ACCESS(world, 1).GetX(), SAFE_ACCESS(world, 1).GetY(),
				SAFE_ACCESS(world, 2).GetX(), SAFE_ACCESS(world, 2).GetY(),
				SAFE_ACCESS(world, 3).GetX(), SAFE_ACCESS(world, 3).GetY(),
				64 - 128 * SAFE_ACCESS(drawRatioEffectGraphs, style) / 2,
				64 - 128 * SAFE_ACCESS(drawRatioEffectGraphs, style) / 2,
				128 * SAFE_ACCESS(drawRatioEffectGraphs, style),
				128 * SAFE_ACCESS(drawRatioEffectGraphs, style),
				SAFE_ACCESS(imgRes.EffectFrontGH, style),
				TRUE);
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, SAFE_ACCESS(imgRes.EffectFrontGH, style), TRUE);
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

void
Effect::MoveFunc() {
	switch (ID) {
	case 0:
	default: {
		MoveObject(speed);
	}
	}
}

void PushBlankEffects(int idx) {
	std::lock_guard<std::mutex> lock(BlankEffectsMutex);
	BlankEffects.emplace_back(idx);
}

int CreateEffect(const Vec2D& pos, const Color& color, int style, int blend, double pal, int palEaseType, int palEaseTime, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID, const std::vector<std::any>& params) {
	if (BlankEffects.empty()) return 1;
	int idx = BlankEffects.back();
	BlankEffects.pop_back();
	SAFE_PTR_ACCESS(Effects, idx).flags = IS_ALIVE | isCol * IS_COL;
	SAFE_PTR_ACCESS(Effects, idx).objType = OBJECT_EFFECT;
	SAFE_PTR_ACCESS(Effects, idx).pos = pos;
	SAFE_PTR_ACCESS(Effects, idx).color = color;
	SAFE_PTR_ACCESS(Effects, idx).style = style;
	SAFE_PTR_ACCESS(Effects, idx).blend = blend;
	SAFE_PTR_ACCESS(Effects, idx).pal = pal;
	SAFE_PTR_ACCESS(Effects, idx).startPal = pal;
	SAFE_PTR_ACCESS(Effects, idx).palEaseType = palEaseType;
	SAFE_PTR_ACCESS(Effects, idx).palEaseTime = palEaseTime;
	SAFE_PTR_ACCESS(Effects, idx).startColSize = startColSize;
	SAFE_PTR_ACCESS(Effects, idx).endColSize = endColSize;
	SAFE_PTR_ACCESS(Effects, idx).colSizeEaseType = colSizeEaseType;
	SAFE_PTR_ACCESS(Effects, idx).colSizeEaseTime = colSizeEaseTime;
	SAFE_PTR_ACCESS(Effects, idx).startSize = startSize;
	SAFE_PTR_ACCESS(Effects, idx).endSize = endSize;
	SAFE_PTR_ACCESS(Effects, idx).sizeEaseType = sizeEaseType;
	SAFE_PTR_ACCESS(Effects, idx).sizeEaseTime = sizeEaseTime;
	if (aim == 1) {
		SAFE_PTR_ACCESS(Effects, idx).startAngle = Plyr.AimPlayer(pos) + startAngle;
		SAFE_PTR_ACCESS(Effects, idx).endAngle = Plyr.AimPlayer(pos) + endAngle;
	}
	else {
		SAFE_PTR_ACCESS(Effects, idx).startAngle = startAngle;
		SAFE_PTR_ACCESS(Effects, idx).endAngle = endAngle;
	}
	SAFE_PTR_ACCESS(Effects, idx).angleEaseType = angleEaseType;
	SAFE_PTR_ACCESS(Effects, idx).angleEaseTime = angleEaseTime;
	SAFE_PTR_ACCESS(Effects, idx).startSpeed = startSpeed;
	SAFE_PTR_ACCESS(Effects, idx).endSpeed = endSpeed;
	SAFE_PTR_ACCESS(Effects, idx).speedEaseType = speedEaseType;
	SAFE_PTR_ACCESS(Effects, idx).speedEaseTime = speedEaseTime;
	SAFE_PTR_ACCESS(Effects, idx).popT = t;
	SAFE_PTR_ACCESS(Effects, idx).length = 0;
	SAFE_PTR_ACCESS(Effects, idx).width = 0;
	SAFE_PTR_ACCESS(Effects, idx).frontNode = 0;
	SAFE_PTR_ACCESS(Effects, idx).currentNodeNum = 0;
	SAFE_PTR_ACCESS(Effects, idx).order = eIndex;
	SAFE_PTR_ACCESS(Effects, idx).index = idx;
	SAFE_PTR_ACCESS(Effects, idx).ID = ID;
	SAFE_PTR_ACCESS(Effects, idx).params = params;
	eIndex++;
	return 0;
}

void ParallelUpdateEffects(std::array<Effect, MAX_EFFECT>& effects) {
	std::for_each(std::execution::par_unseq, effects.begin(), effects.end(),
		[](Effect& E) {
			E.UpdateObject();
		});
}

void MoveEffects() {
	if (t % 1 == 0) {
		std::sort(EffectPtrs.begin(), EffectPtrs.end(), [](const Effect* a, const Effect* b) {
			return a->order < b->order;
		});
	}
	ParallelUpdateEffects(*Effects);
	for (auto* E : EffectPtrs) {
		E->ShowEffect();
	}
}

void
GrazeEffect(const Vec2D& pos) {
	for (int i = 0; i < 1; i++) {
		RandTMP = std::fmod(rng() / 100.0f, 360);
		CreateEffect(pos, Color(C_WHITE), EF_STAR, BLEND_ADD, 255, EASEINQUAD, 15, 0, 0, 0, 0, 0, std::fmod(rng() / 100.0f, 1.5f), 0, EASEINQUAD, 120, 0, RandTMP, RandTMP, 0, 0, std::fmod(rng() / 100.0f, 32), 0, EASEINQUAD, 120);
	}
}