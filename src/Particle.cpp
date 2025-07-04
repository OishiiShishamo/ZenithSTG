#include "Main.h"
#include "Particle.h"
#include "Player.h"

std::array<Particle, MAX_PARTICLE> Particles;
std::array<Particle*, MAX_PARTICLE> ParticlePtrs;
std::vector<int> BlankParticles;
std::mutex BlankParticlesMutex;
std::array<int, GRAPHIC_HANDLER_NUM> defaultParticleBlend;
std::array<double, GRAPHIC_HANDLER_NUM> drawRatioParticleGraphs;
long long eIndex = 0;

void
Particle::UpdateObject(long long Index) {
	if (!(flags & IS_ALIVE)) return;

	UpdateEase();

	vec = AngleToVec2D(angle);
	MoveFunc();
	if (t - popT >= palEaseTime) {
		PushBlankParticles(index);
		flags &= ~IS_ALIVE;
	}
}

void
Particle::UpdateEase() {
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
Particle::ShowParticle() {
	if (!(flags & IS_ALIVE)) return;
	std::array<Vec2D, 4> world;
	const bool isScaled = size > 1.0f;
	if (isScaled) {
		double half = size / 2 * 128 * SAFE_ACCESS(drawRatioParticleGraphs, style);
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
		SmartSetDrawBlendMode(SAFE_ACCESS(defaultParticleBlend, style), pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if (isScaled) {
			DrawRectModiGraph(
				SAFE_ACCESS(world, 0).GetX(), SAFE_ACCESS(world, 0).GetY(),
				SAFE_ACCESS(world, 1).GetX(), SAFE_ACCESS(world, 1).GetY(),
				SAFE_ACCESS(world, 2).GetX(), SAFE_ACCESS(world, 2).GetY(),
				SAFE_ACCESS(world, 3).GetX(), SAFE_ACCESS(world, 3).GetY(),
				64 - 128 * SAFE_ACCESS(drawRatioParticleGraphs, style) / 2,
				64 - 128 * SAFE_ACCESS(drawRatioParticleGraphs, style) / 2,
				128 * SAFE_ACCESS(drawRatioParticleGraphs, style),
				128 * SAFE_ACCESS(drawRatioParticleGraphs, style),
				SAFE_ACCESS(imgRes.ParticleBackGH, style),
				TRUE);
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, SAFE_ACCESS(imgRes.ParticleBackGH, style), TRUE);
		SetDrawBright(255, 255, 255);
		if (isScaled) {
			DrawRectModiGraph(
				SAFE_ACCESS(world, 0).GetX(), SAFE_ACCESS(world, 0).GetY(),
				SAFE_ACCESS(world, 1).GetX(), SAFE_ACCESS(world, 1).GetY(),
				SAFE_ACCESS(world, 2).GetX(), SAFE_ACCESS(world, 2).GetY(),
				SAFE_ACCESS(world, 3).GetX(), SAFE_ACCESS(world, 3).GetY(),
				64 - 128 * SAFE_ACCESS(drawRatioParticleGraphs, style) / 2,
				64 - 128 * SAFE_ACCESS(drawRatioParticleGraphs, style) / 2,
				128 * SAFE_ACCESS(drawRatioParticleGraphs, style),
				128 * SAFE_ACCESS(drawRatioParticleGraphs, style),
				SAFE_ACCESS(imgRes.ParticleFrontGH, style),
				TRUE);
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, SAFE_ACCESS(imgRes.ParticleFrontGH, style), TRUE);
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
				64 - 128 * SAFE_ACCESS(drawRatioParticleGraphs, style) / 2,
				64 - 128 * SAFE_ACCESS(drawRatioParticleGraphs, style) / 2,
				128 * SAFE_ACCESS(drawRatioParticleGraphs, style),
				128 * SAFE_ACCESS(drawRatioParticleGraphs, style),
				SAFE_ACCESS(imgRes.ParticleBackGH, style),
				TRUE);
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, SAFE_ACCESS(imgRes.ParticleBackGH, style), TRUE);
		SetDrawBright(255, 255, 255);
		if (isScaled) {
			DrawRectModiGraph(
				SAFE_ACCESS(world, 0).GetX(), SAFE_ACCESS(world, 0).GetY(),
				SAFE_ACCESS(world, 1).GetX(), SAFE_ACCESS(world, 1).GetY(),
				SAFE_ACCESS(world, 2).GetX(), SAFE_ACCESS(world, 2).GetY(),
				SAFE_ACCESS(world, 3).GetX(), SAFE_ACCESS(world, 3).GetY(),
				64 - 128 * SAFE_ACCESS(drawRatioParticleGraphs, style) / 2,
				64 - 128 * SAFE_ACCESS(drawRatioParticleGraphs, style) / 2,
				128 * SAFE_ACCESS(drawRatioParticleGraphs, style),
				128 * SAFE_ACCESS(drawRatioParticleGraphs, style),
				SAFE_ACCESS(imgRes.ParticleFrontGH, style),
				TRUE);
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -showAngle, SAFE_ACCESS(imgRes.ParticleFrontGH, style), TRUE);
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
Particle::MoveFunc() {
	switch (ID) {
	case 0:
	default: {
		MoveObject(speed);
	}
	}
}

void PushBlankParticles(int idx) {
	std::lock_guard<std::mutex> lock(BlankParticlesMutex);
	BlankParticles.emplace_back(idx);
}

int CreateParticle(const Vec2D& pos, const Color& color, int style, int blend, double pal, int palEaseType, int palEaseTime, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID, const std::vector<std::any>& params) {
	if (BlankParticles.empty()) return 1;
	int idx = BlankParticles.back();
	BlankParticles.pop_back();
	SAFE_ACCESS(Particles, idx).flags = IS_ALIVE | isCol * IS_COL;
	SAFE_ACCESS(Particles, idx).objType = OBJECT_PARTICLE;
	SAFE_ACCESS(Particles, idx).pos = pos;
	SAFE_ACCESS(Particles, idx).color = color;
	SAFE_ACCESS(Particles, idx).style = style;
	SAFE_ACCESS(Particles, idx).blend = blend;
	SAFE_ACCESS(Particles, idx).pal = pal;
	SAFE_ACCESS(Particles, idx).startPal = pal;
	SAFE_ACCESS(Particles, idx).palEaseType = palEaseType;
	SAFE_ACCESS(Particles, idx).palEaseTime = palEaseTime;
	SAFE_ACCESS(Particles, idx).startColSize = startColSize;
	SAFE_ACCESS(Particles, idx).endColSize = endColSize;
	SAFE_ACCESS(Particles, idx).colSizeEaseType = colSizeEaseType;
	SAFE_ACCESS(Particles, idx).colSizeEaseTime = colSizeEaseTime;
	SAFE_ACCESS(Particles, idx).startSize = startSize;
	SAFE_ACCESS(Particles, idx).endSize = endSize;
	SAFE_ACCESS(Particles, idx).sizeEaseType = sizeEaseType;
	SAFE_ACCESS(Particles, idx).sizeEaseTime = sizeEaseTime;
	if (aim == 1) {
		SAFE_ACCESS(Particles, idx).startAngle = Plyr.AimPlayer(pos) + startAngle;
		SAFE_ACCESS(Particles, idx).endAngle = Plyr.AimPlayer(pos) + endAngle;
	}
	else {
		SAFE_ACCESS(Particles, idx).startAngle = startAngle;
		SAFE_ACCESS(Particles, idx).endAngle = endAngle;
	}
	SAFE_ACCESS(Particles, idx).angleEaseType = angleEaseType;
	SAFE_ACCESS(Particles, idx).angleEaseTime = angleEaseTime;
	SAFE_ACCESS(Particles, idx).startSpeed = startSpeed;
	SAFE_ACCESS(Particles, idx).endSpeed = endSpeed;
	SAFE_ACCESS(Particles, idx).speedEaseType = speedEaseType;
	SAFE_ACCESS(Particles, idx).speedEaseTime = speedEaseTime;
	SAFE_ACCESS(Particles, idx).popT = t;
	SAFE_ACCESS(Particles, idx).length = 0;
	SAFE_ACCESS(Particles, idx).width = 0;
	SAFE_ACCESS(Particles, idx).frontNode = 0;
	SAFE_ACCESS(Particles, idx).currentNodeNum = 0;
	SAFE_ACCESS(Particles, idx).order = eIndex;
	SAFE_ACCESS(Particles, idx).index = idx;
	SAFE_ACCESS(Particles, idx).ID = ID;
	SAFE_ACCESS(Particles, idx).params = params;
	eIndex++;
	return 0;
}

void ParallelUpdateParticles(std::array<Particle, MAX_PARTICLE>& particles) {
	std::for_each(std::execution::par_unseq, particles.begin(), particles.end(),
		[](Particle& E) {
			E.UpdateObject();
		});
}

void MoveParticles() {
	if (t % 1 == 0) {
		std::sort(ParticlePtrs.begin(), ParticlePtrs.end(), [](const Particle* a, const Particle* b) {
			return a->order < b->order;
			});
	}
	ParallelUpdateParticles(Particles);
	for (auto* E : ParticlePtrs) {
		E->ShowParticle();
	}
}

void
GrazeParticle(const Vec2D& pos) {
	for (int i = 0; i < 1; i++) {
		RandTMP = std::fmod(rng() / 100.0f, 360);
		CreateParticle(pos, Color(C_WHITE), P_STAR, BLEND_ADD, 255, EASEINQUAD, 15, 0, 0, 0, 0, 0, std::fmod(rng() / 100.0f, 1.5f), 0, EASEINQUAD, 120, 0, RandTMP, RandTMP, 0, 0, std::fmod(rng() / 100.0f, 32), 0, EASEINQUAD, 120);
	}
}