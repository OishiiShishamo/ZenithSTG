#include "main.h"
#include "particle.h"
#include "player.h"

std::array<Particle, kMaxParticle> particles;
std::array<Particle*, kMaxParticle> particle_ptrs;
std::vector<int> blank_particles;
std::mutex blank_particles_mutex;
std::array<int, kGraphicHandlerNum> default_particle_blend;
std::array<double, kGraphicHandlerNum> draw_ratio_particle_graphs;
long long particle_index = 0;

void
Particle::UpdateObject() {
	if (!(flags & kIsAlive)) return;

	UpdateEase();

	vec = AngleToVec2D(angle);
	MoveFunc();
	if (t - pop_t >= pal_ease_time) {
		PushBlankParticles(index);
		flags &= ~kIsAlive;
	}
}

void
Particle::UpdateEase() {
	double elapsed_frame = (static_cast<double>(t - pop_t));
	if (angle_ease_time == 0) {
		angle = end_angle;
	}
	else {
		angle_t = elapsed_frame / angle_ease_time;
		if (angle_t > 1)angle_t = 1;
		angle = Easing(angle_ease_type, angle_t, start_angle, end_angle);
	}
	if (is_aligned_angle == 1) {
		show_angle = angle;
	}

	if (speed_ease_time == 0) {
		speed = end_speed;
	}
	else {
		speed_t = elapsed_frame / speed_ease_time;
		if (speed_t > 1) speed_t = 1;
		speed = Easing(speed_ease_type, speed_t, start_speed, end_speed);
	}

	if (col_size_ease_time == 0) {
		col_size = end_col_size;
	}
	else {
		col_tize_t = elapsed_frame / col_size_ease_time;
		if (col_tize_t > 1)col_tize_t = 1;
		col_size = Easing(col_size_ease_type, col_tize_t, start_col_size, end_col_size);
	}

	if (size_ease_time == 0) {
		size = end_size;
	}
	else {
		size_t = elapsed_frame / size_ease_time;
		if (size_t > 1) size_t = 1;
		size = Easing(size_ease_type, size_t, start_size, end_size);
	}

	if (pal_ease_time == 0) {
		pal = 0;
	}
	else {
		pal_t = elapsed_frame / pal_ease_time;
		if (pal_t > 1) pal_t = 1;
		pal = Easing(pal_ease_type, pal_t, start_pal, 0);
	}
}

void
Particle::ShowParticle() {
	if (!(flags & kIsAlive)) return;
	std::array<Vec2D, 4> world;
	const bool isScaled = size > 1.0f;
	if (isScaled) {
		double half = size / 2 * 128 * SafeAccess(draw_ratio_particle_graphs, style);
		std::array<Vec2D, 4> local = {
			Vec2D(-half, -half),
			Vec2D(-half, half),
			Vec2D(half, half),
			Vec2D(half, -half)
		};
		for (int i = 0; i < 4; ++i) {
			Vec2D rot = RotatePoint(SafeAccess(local, i), show_angle + kPi / 2);
			SafeAccess(world, i) = pos + rot;
		}
	}
	if (blend == -1) {
		SmartSetDrawBlendMode(SafeAccess(default_particle_blend, style), pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if (isScaled) {
			DrawRectModiGraph(
				SafeAccess(world, 0).GetX(), SafeAccess(world, 0).GetY(),
				SafeAccess(world, 1).GetX(), SafeAccess(world, 1).GetY(),
				SafeAccess(world, 2).GetX(), SafeAccess(world, 2).GetY(),
				SafeAccess(world, 3).GetX(), SafeAccess(world, 3).GetY(),
				64 - 128 * SafeAccess(draw_ratio_particle_graphs, style) / 2,
				64 - 128 * SafeAccess(draw_ratio_particle_graphs, style) / 2,
				128 * SafeAccess(draw_ratio_particle_graphs, style),
				128 * SafeAccess(draw_ratio_particle_graphs, style),
				SafeAccess(img_res.particle_back_gh, style),
				TRUE);
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -show_angle, SafeAccess(img_res.particle_back_gh, style), TRUE);
		SetDrawBright(255, 255, 255);
		if (isScaled) {
			DrawRectModiGraph(
				SafeAccess(world, 0).GetX(), SafeAccess(world, 0).GetY(),
				SafeAccess(world, 1).GetX(), SafeAccess(world, 1).GetY(),
				SafeAccess(world, 2).GetX(), SafeAccess(world, 2).GetY(),
				SafeAccess(world, 3).GetX(), SafeAccess(world, 3).GetY(),
				64 - 128 * SafeAccess(draw_ratio_particle_graphs, style) / 2,
				64 - 128 * SafeAccess(draw_ratio_particle_graphs, style) / 2,
				128 * SafeAccess(draw_ratio_particle_graphs, style),
				128 * SafeAccess(draw_ratio_particle_graphs, style),
				SafeAccess(img_res.particle_front_gh, style),
				TRUE);
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -show_angle, SafeAccess(img_res.particle_front_gh, style), TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if (isScaled) {
			DrawRectModiGraph(
				SafeAccess(world, 0).GetX(), SafeAccess(world, 0).GetY(),
				SafeAccess(world, 1).GetX(), SafeAccess(world, 1).GetY(),
				SafeAccess(world, 2).GetX(), SafeAccess(world, 2).GetY(),
				SafeAccess(world, 3).GetX(), SafeAccess(world, 3).GetY(),
				64 - 128 * SafeAccess(draw_ratio_particle_graphs, style) / 2,
				64 - 128 * SafeAccess(draw_ratio_particle_graphs, style) / 2,
				128 * SafeAccess(draw_ratio_particle_graphs, style),
				128 * SafeAccess(draw_ratio_particle_graphs, style),
				SafeAccess(img_res.particle_back_gh, style),
				TRUE);
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -show_angle, SafeAccess(img_res.particle_back_gh, style), TRUE);
		SetDrawBright(255, 255, 255);
		if (isScaled) {
			DrawRectModiGraph(
				SafeAccess(world, 0).GetX(), SafeAccess(world, 0).GetY(),
				SafeAccess(world, 1).GetX(), SafeAccess(world, 1).GetY(),
				SafeAccess(world, 2).GetX(), SafeAccess(world, 2).GetY(),
				SafeAccess(world, 3).GetX(), SafeAccess(world, 3).GetY(),
				64 - 128 * SafeAccess(draw_ratio_particle_graphs, style) / 2,
				64 - 128 * SafeAccess(draw_ratio_particle_graphs, style) / 2,
				128 * SafeAccess(draw_ratio_particle_graphs, style),
				128 * SafeAccess(draw_ratio_particle_graphs, style),
				SafeAccess(img_res.particle_front_gh, style),
				TRUE);
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -show_angle, SafeAccess(img_res.particle_front_gh, style), TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	if (kIsColShow == 1) {
		if (flags & kIsCol) {
			SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			DrawCircle(pos.GetX(), pos.GetY(), col_size, GetColor(255, 255, 255), 1);
			DrawFormatString(pos.GetX(), pos.GetY(), GetColor(GetColorHsv(std::fmod(t, 360), 1, 1).r, GetColorHsv(std::fmod(t, 360), 1, 1).g, GetColorHsv(std::fmod(t, 360), 1, 1).b), "%f", col_size);
		}
	}
}

void
Particle::MoveFunc() {
	switch (id) {
	case 0:
	default: {
		MoveObject(speed);
	}
	}
}

void PushBlankParticles(int idx) {
	std::lock_guard<std::mutex> lock(blank_particles_mutex);
	blank_particles.emplace_back(idx);
}

int CreateParticle(const Vec2D& pos, const Color& color, int style, int blend, double pal, int palEaseType, int palEaseTime, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int id, const std::vector<std::any>& params) {
	if (blank_particles.empty()) return 1;
	int idx = blank_particles.back();
	blank_particles.pop_back();
	SafeAccess(particles, idx).flags = kIsAlive | is_col * kIsCol;
	SafeAccess(particles, idx).obj_type = kObjectParticle;
	SafeAccess(particles, idx).pos = pos;
	SafeAccess(particles, idx).color = color;
	SafeAccess(particles, idx).style = style;
	SafeAccess(particles, idx).blend = blend;
	SafeAccess(particles, idx).pal = pal;
	SafeAccess(particles, idx).start_pal = pal;
	SafeAccess(particles, idx).pal_ease_type = palEaseType;
	SafeAccess(particles, idx).pal_ease_time = palEaseTime;
	SafeAccess(particles, idx).start_col_size = start_col_size;
	SafeAccess(particles, idx).end_col_size = end_col_size;
	SafeAccess(particles, idx).col_size_ease_type = col_size_ease_type;
	SafeAccess(particles, idx).col_size_ease_time = col_size_ease_time;
	SafeAccess(particles, idx).start_size = start_size;
	SafeAccess(particles, idx).end_size = end_size;
	SafeAccess(particles, idx).size_ease_type = size_ease_type;
	SafeAccess(particles, idx).size_ease_time = size_ease_time;
	if (aim == 1) {
		SafeAccess(particles, idx).start_angle = Plyr.AimPlayer(pos) + start_angle;
		SafeAccess(particles, idx).end_angle = Plyr.AimPlayer(pos) + end_angle;
	}
	else {
		SafeAccess(particles, idx).start_angle = start_angle;
		SafeAccess(particles, idx).end_angle = end_angle;
	}
	SafeAccess(particles, idx).angle_ease_type = angle_ease_type;
	SafeAccess(particles, idx).angle_ease_time = angle_ease_time;
	SafeAccess(particles, idx).start_speed = start_speed;
	SafeAccess(particles, idx).end_speed = end_speed;
	SafeAccess(particles, idx).speed_ease_type = speed_ease_type;
	SafeAccess(particles, idx).speed_ease_time = speed_ease_time;
	SafeAccess(particles, idx).pop_t = t;
	SafeAccess(particles, idx).length = 0;
	SafeAccess(particles, idx).width = 0;
	SafeAccess(particles, idx).front_node = 0;
	SafeAccess(particles, idx).current_node_num = 0;
	SafeAccess(particles, idx).order = particle_index;
	SafeAccess(particles, idx).index = idx;
	SafeAccess(particles, idx).id = id;
	SafeAccess(particles, idx).params = params;
	particle_index++;
	return 0;
}

void ParallelUpdateParticles(std::array<Particle, kMaxParticle>& particles) {
	std::for_each(std::execution::par_unseq, particles.begin(), particles.end(),
		[](Particle& E) {
			E.UpdateObject();
		});
}

void MoveParticles() {
	if (t % 1 == 0) {
		std::sort(particle_ptrs.begin(), particle_ptrs.end(), [](const Particle* a, const Particle* b) {
			return a->order < b->order;
			});
	}
	ParallelUpdateParticles(particles);
	for (auto* E : particle_ptrs) {
		E->ShowParticle();
	}
}

void
GrazeParticle(const Vec2D& pos) {
	for (int i = 0; i < 1; i++) {
		rand_tmp = std::fmod(rng() / 100.0f, 360);
		CreateParticle(pos, Color(kColorWhite), kParticleStar, kBlendAdd, 255, kEaseInQuad, 15, 0, 0, 0, 0, 0, std::fmod(rng() / 100.0f, 1.5f), 0, kEaseInQuad, 120, 0, rand_tmp, rand_tmp, 0, 0, std::fmod(rng() / 100.0f, 32), 0, kEaseInQuad, 120);
	}
}