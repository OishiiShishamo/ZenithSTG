#include "Main.h"
#include "Effect.h"
#include "Player.h"
#include "Easing.h"

std::array<Effect, MAX_EFFECT> Effects;
std::array<int, GRAPHIC_HANDLER_NUM> defaultEffectBlend;
std::array<double, GRAPHIC_HANDLER_NUM> drawRatioEffectGraphs;

void
Effect::UpdateObject(long long Index) {
	if (!(flags & IS_ALIVE)) return;

	UpdateEase();

	vec = AngleToVec2D(angle);
	MoveFunc();
	if(pal <= 0) flags &= ~IS_ALIVE;
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

void
CreateEffect(const Vec2D& pos, const Color& color, int style, int blend, int pal, int palEaseTime, int palEaseType, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID, const std::vector<std::any>& params) {
	for (int i = 0; i < Effects.size(); i++) {
		if (!(SAFE_ACCESS(Effects, i).flags & IS_ALIVE)) {
			SAFE_ACCESS(Effects, i).flags = IS_ALIVE | isCol * IS_COL;
			SAFE_ACCESS(Effects, i).objType = OBJECT_EFFECT;
			SAFE_ACCESS(Effects, i).pos = pos;
			SAFE_ACCESS(Effects, i).color = color;
			SAFE_ACCESS(Effects, i).style = style;
			SAFE_ACCESS(Effects, i).blend = blend;
			SAFE_ACCESS(Effects, i).pal = pal;
			SAFE_ACCESS(Effects, i).startPal = pal;
			SAFE_ACCESS(Effects, i).palEaseTime = palEaseTime;
			SAFE_ACCESS(Effects, i).palEaseType = palEaseType;
			SAFE_ACCESS(Effects, i).startColSize = startColSize;
			SAFE_ACCESS(Effects, i).endColSize = endColSize;
			SAFE_ACCESS(Effects, i).colSizeEaseType = colSizeEaseType;
			SAFE_ACCESS(Effects, i).colSizeEaseTime = colSizeEaseTime;
			SAFE_ACCESS(Effects, i).startSize = startSize;
			SAFE_ACCESS(Effects, i).endSize = endSize;
			SAFE_ACCESS(Effects, i).sizeEaseType = sizeEaseType;
			SAFE_ACCESS(Effects, i).sizeEaseTime = sizeEaseTime;
			if (aim == 1) {
				SAFE_ACCESS(Effects, i).startAngle = Plyr.AimPlayer(pos) + startAngle;
				SAFE_ACCESS(Effects, i).endAngle = Plyr.AimPlayer(pos) + endAngle;
			}
			else {
				SAFE_ACCESS(Effects, i).startAngle = startAngle;
				SAFE_ACCESS(Effects, i).endAngle = endAngle;
			}
			SAFE_ACCESS(Effects, i).angleEaseType = angleEaseType;
			SAFE_ACCESS(Effects, i).angleEaseTime = angleEaseTime;
			SAFE_ACCESS(Effects, i).startSpeed = startSpeed;
			SAFE_ACCESS(Effects, i).endSpeed = endSpeed;
			SAFE_ACCESS(Effects, i).speedEaseType = speedEaseType;
			SAFE_ACCESS(Effects, i).speedEaseTime = speedEaseTime;
			SAFE_ACCESS(Effects, i).popT = t;
			SAFE_ACCESS(Effects, i).length = 0;
			SAFE_ACCESS(Effects, i).width = 0;
			SAFE_ACCESS(Effects, i).frontNode = 0;
			SAFE_ACCESS(Effects, i).currentNodeNum = 0;
			SAFE_ACCESS(Effects, i).index = 0;
			SAFE_ACCESS(Effects, i).ID = ID;
			SAFE_ACCESS(Effects, i).params = params;
			return;
		}
	}
}

void
MoveEffects() {
	for (auto& E : Effects) {
		if (E.flags & IS_ALIVE){
			E.UpdateObject();
			E.ShowEffect();
		}
	}
	if (t % 1 == 0) {
		std::sort(Effects.begin(), Effects.end(), [](const Effect& a, const Effect& b) {
			return a.popT < b.popT;
			});
	}
}

void
GrazeEffect(const Vec2D& pos) {
	for (int i = 0; i < 32; i++) {
		RandTMP = std::fmod(rng() / 100.0f, 360);
		CreateEffect(pos, Color(C_WHITE), EF_STAR, BLEND_ADD, 255, 5000, EASEINQUAD, 0, 0, 0, 0, 0, std::fmod(rng() / 100.0f, 1.5f), 0, 120, EASEINQUAD, 0, RandTMP, RandTMP, 0, 0, std::fmod(rng() / 100.0f, 32) + 16, 0, 120, EASEINQUAD);
	}
}