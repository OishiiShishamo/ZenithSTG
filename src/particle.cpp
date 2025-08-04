#include "particle.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <execution>
#include <mutex>
#include <vector>

#include "DxLib.h"

#include "collision.h"
#include "color.h"
#include "debug.h"
#include "global.h"
#include "object.h"
#include "params.h"
#include "player.h"
#include "sound.h"
#include "utility.h"
#include "vec2d.h"

namespace zenithstg {
	std::array<Particle, kMaxParticle> particles;
	std::array<Particle*, kMaxParticle> particle_ptrs;
	std::vector<int> blank_particles;
	std::mutex blank_particles_mutex;
	std::array<int, kGraphicHandlerNum> default_particle_blend;
	std::array<double, kGraphicHandlerNum> draw_ratio_particle_graphs;
	long long particle_index = 0;

	void Particle::UpdateObject() {
		if (!(flags_ & kIsAlive)) return;

		UpdateEase();

		vec_ = AngleToVec2D(angle_);
		MoveFunc();
		if (t - pop_t_ >= pal_ease_time_) {
			PushBlankParticles(index_);
			flags_ &= ~kIsAlive;
		}
	}

	void Particle::UpdateEase() {
		double elapsed_frame = t - pop_t_;
		if (angle_ease_time_ == 0) {
			angle_ = end_angle_;
		}
		else {
			angle_t_ = EasingTimeCalc(elapsed_frame, 0, angle_ease_time_);
			angle_ = Easing(angle_ease_type_, angle_t_, start_angle_, end_angle_);
		}
		if (is_aligned_angle_ == 1) {
			show_angle_ = angle_;
		}

		if (speed_ease_time_ == 0) {
			speed_ = end_speed_;
		}
		else {
			speed_t_ = EasingTimeCalc(elapsed_frame, 0, speed_ease_time_);
			speed_ = Easing(speed_ease_type_, speed_t_, start_speed_, end_speed_);
		}

		if (col_size_ease_time_ == 0) {
			col_size_ = end_col_size_;
		}
		else {
			col_tize_t_ = EasingTimeCalc(elapsed_frame, 0, col_size_ease_time_);
			col_size_ = Easing(col_size_ease_type_, col_tize_t_, start_col_size_, end_col_size_);
		}

		if (size_ease_time_ == 0) {
			size_ = end_size_;
		}
		else {
			size_t_ = EasingTimeCalc(elapsed_frame, 0, size_ease_time_);
			size_ = Easing(size_ease_type_, size_t_, start_size_, end_size_);
		}

		if (pal_ease_time_ == 0) {
			pal_ = 0;
		}
		else {
			pal_t_ = EasingTimeCalc(elapsed_frame, 0, pal_ease_time_);
			pal_ = Easing(pal_ease_type_, pal_t_, start_pal_, 0);
		}
	}

	void Particle::ShowParticle() {
		if (!(flags_ & kIsAlive)) return;
		std::array<Vec2D, 4> world;
		const bool isScaled = size_ > 1.0f;
		switch (id_) {
			case 0:
			default:
				if (isScaled) {
					double half = size_ / 2 * 128 * SafeAccess(draw_ratio_particle_graphs, style_);
					std::array<Vec2D, 4> local = {
						Vec2D(-half, -half),
						Vec2D(-half, half),
						Vec2D(half, half),
						Vec2D(half, -half)
					};
					for (int i = 0; i < 4; ++i) {
						Vec2D rot = RotatePoint(SafeAccess(local, i), show_angle_ + kPi / 2);
						SafeAccess(world, i) = pos_ + rot;
					}
				}
				if (blend_ == -1) {
					SmartSetDrawBlendMode(SafeAccess(default_particle_blend, style_), pal_);
					SetDrawBright(color_.GetR(), color_.GetG(), color_.GetB());
					SetDrawMode(DX_DRAWMODE_BILINEAR);
					if (isScaled) {
						DrawRectModiGraph(
							SafeAccess(world, 0).GetX(), SafeAccess(world, 0).GetY(),
							SafeAccess(world, 1).GetX(), SafeAccess(world, 1).GetY(),
							SafeAccess(world, 2).GetX(), SafeAccess(world, 2).GetY(),
							SafeAccess(world, 3).GetX(), SafeAccess(world, 3).GetY(),
							64 - 128 * SafeAccess(draw_ratio_particle_graphs, style_) / 2,
							64 - 128 * SafeAccess(draw_ratio_particle_graphs, style_) / 2,
							128 * SafeAccess(draw_ratio_particle_graphs, style_),
							128 * SafeAccess(draw_ratio_particle_graphs, style_),
							SafeAccess(img_res.particle_back_gh, style_),
							TRUE);
					}
					else DrawRotaGraph(pos_.GetX(), pos_.GetY(), size_, -show_angle_, SafeAccess(img_res.particle_back_gh, style_), TRUE);
					SetDrawBright(255, 255, 255);
					if (isScaled) {
						DrawRectModiGraph(
							SafeAccess(world, 0).GetX(), SafeAccess(world, 0).GetY(),
							SafeAccess(world, 1).GetX(), SafeAccess(world, 1).GetY(),
							SafeAccess(world, 2).GetX(), SafeAccess(world, 2).GetY(),
							SafeAccess(world, 3).GetX(), SafeAccess(world, 3).GetY(),
							64 - 128 * SafeAccess(draw_ratio_particle_graphs, style_) / 2,
							64 - 128 * SafeAccess(draw_ratio_particle_graphs, style_) / 2,
							128 * SafeAccess(draw_ratio_particle_graphs, style_),
							128 * SafeAccess(draw_ratio_particle_graphs, style_),
							SafeAccess(img_res.particle_front_gh, style_),
							TRUE);
					}
					else DrawRotaGraph(pos_.GetX(), pos_.GetY(), size_, -show_angle_, SafeAccess(img_res.particle_front_gh, style_), TRUE);
					SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
					SetDrawMode(DX_DRAWMODE_NEAREST);
				}
				else {
					SmartSetDrawBlendMode(blend_, pal_);
					SetDrawBright(color_.GetR(), color_.GetG(), color_.GetB());
					SetDrawMode(DX_DRAWMODE_BILINEAR);
					if (isScaled) {
						DrawRectModiGraph(
							SafeAccess(world, 0).GetX(), SafeAccess(world, 0).GetY(),
							SafeAccess(world, 1).GetX(), SafeAccess(world, 1).GetY(),
							SafeAccess(world, 2).GetX(), SafeAccess(world, 2).GetY(),
							SafeAccess(world, 3).GetX(), SafeAccess(world, 3).GetY(),
							64 - 128 * SafeAccess(draw_ratio_particle_graphs, style_) / 2,
							64 - 128 * SafeAccess(draw_ratio_particle_graphs, style_) / 2,
							128 * SafeAccess(draw_ratio_particle_graphs, style_),
							128 * SafeAccess(draw_ratio_particle_graphs, style_),
							SafeAccess(img_res.particle_back_gh, style_),
							TRUE);
					}
					else DrawRotaGraph(pos_.GetX(), pos_.GetY(), size_, -show_angle_, SafeAccess(img_res.particle_back_gh, style_), TRUE);
					SetDrawBright(255, 255, 255);
					if (isScaled) {
						DrawRectModiGraph(
							SafeAccess(world, 0).GetX(), SafeAccess(world, 0).GetY(),
							SafeAccess(world, 1).GetX(), SafeAccess(world, 1).GetY(),
							SafeAccess(world, 2).GetX(), SafeAccess(world, 2).GetY(),
							SafeAccess(world, 3).GetX(), SafeAccess(world, 3).GetY(),
							64 - 128 * SafeAccess(draw_ratio_particle_graphs, style_) / 2,
							64 - 128 * SafeAccess(draw_ratio_particle_graphs, style_) / 2,
							128 * SafeAccess(draw_ratio_particle_graphs, style_),
							128 * SafeAccess(draw_ratio_particle_graphs, style_),
							SafeAccess(img_res.particle_front_gh, style_),
							TRUE);
					}
					else DrawRotaGraph(pos_.GetX(), pos_.GetY(), size_, -show_angle_, SafeAccess(img_res.particle_front_gh, style_), TRUE);
					SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
					SetDrawMode(DX_DRAWMODE_NEAREST);
				}
				break;
		}
		
		if (kIsColShow == 1) {
			if (flags_ & kIsCol) {
				SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
				DrawCircle(pos_.GetX(), pos_.GetY(), col_size_, GetColor(255, 255, 255), 1);
				DrawFormatString(pos_.GetX(), pos_.GetY(), GetColor(GamingColor().GetR(), GamingColor().GetG(), GamingColor().GetB()), "%f", col_size_);
			}
		}
	}

	void Particle::MoveFunc() {
		switch (id_) {
		case 0:
		default: {
			MoveObject(speed_);
		}
		}
	}

	void Particle::KillObject() {
		PushBlankParticles(index_);
		flags_ &= ~kIsAlive;
	}

	void PushBlankParticles(int idx) {
		std::lock_guard<std::mutex> lock(blank_particles_mutex);
		blank_particles.emplace_back(idx);
	}

	int CreateParticle(const Vec2D& pos, const Color& color, int style, int blend, double pal, int palEaseType, int palEaseTime, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int id, const std::vector<std::any>& params) {
		if (blank_particles.empty()) return 1;
		int idx = blank_particles.back();
		blank_particles.pop_back();
		SafeAccess(particles, idx).flags_ = kIsAlive | is_col * kIsCol;
		SafeAccess(particles, idx).obj_type_ = kObjectParticle;
		SafeAccess(particles, idx).pos_ = pos;
		SafeAccess(particles, idx).color_ = color;
		SafeAccess(particles, idx).style_ = style;
		SafeAccess(particles, idx).blend_ = blend;
		SafeAccess(particles, idx).pal_ = pal;
		SafeAccess(particles, idx).start_pal_ = pal;
		SafeAccess(particles, idx).pal_ease_type_ = palEaseType;
		SafeAccess(particles, idx).pal_ease_time_ = palEaseTime;
		SafeAccess(particles, idx).start_col_size_ = start_col_size;
		SafeAccess(particles, idx).end_col_size_ = end_col_size;
		SafeAccess(particles, idx).col_size_ease_type_ = col_size_ease_type;
		SafeAccess(particles, idx).col_size_ease_time_ = col_size_ease_time;
		SafeAccess(particles, idx).start_size_ = start_size;
		SafeAccess(particles, idx).end_size_ = end_size;
		SafeAccess(particles, idx).size_ease_type_ = size_ease_type;
		SafeAccess(particles, idx).size_ease_time_ = size_ease_time;
		if (aim == 1) {
			SafeAccess(particles, idx).start_angle_ = player.AimPlayer(pos) + start_angle;
			SafeAccess(particles, idx).end_angle_ = player.AimPlayer(pos) + end_angle;
		}
		else {
			SafeAccess(particles, idx).start_angle_ = start_angle;
			SafeAccess(particles, idx).end_angle_ = end_angle;
		}
		SafeAccess(particles, idx).angle_ease_type_ = angle_ease_type;
		SafeAccess(particles, idx).angle_ease_time_ = angle_ease_time;
		SafeAccess(particles, idx).start_speed_ = start_speed;
		SafeAccess(particles, idx).end_speed_ = end_speed;
		SafeAccess(particles, idx).speed_ease_type_ = speed_ease_type;
		SafeAccess(particles, idx).speed_ease_time_ = speed_ease_time;
		SafeAccess(particles, idx).pop_t_ = t;
		SafeAccess(particles, idx).length_ = 0;
		SafeAccess(particles, idx).width_ = 0;
		SafeAccess(particles, idx).front_node_ = 0;
		SafeAccess(particles, idx).current_node_num_ = 0;
		SafeAccess(particles, idx).order_ = particle_index;
		SafeAccess(particles, idx).index_ = idx;
		SafeAccess(particles, idx).id_ = id;
		SafeAccess(particles, idx).params_ = params;
		particle_index++;
		return 0;
	}

	void ParallelUpdateParticles(std::array<Particle, kMaxParticle>& particles) {
		std::for_each(std::execution::par, particles.begin(), particles.end(),
			[](Particle& E) {
				E.UpdateObject();
			});
	}

	void MoveParticles() {
		ParallelUpdateParticles(particles);
		if (t == time_mng_.target_t_) {
			std::sort(std::execution::par, particle_ptrs.begin(), particle_ptrs.end(), [](const Particle* a, const Particle* b) {
				return a->order_ < b->order_;
				});
			for (auto* E : particle_ptrs) {
				E->ShowParticle();
			}
		}
	}

	void GrazeParticle(const Vec2D& pos) {
		double rand_buffer = 0;
		for (int i = 0; i < 1; i++) {
			rand_buffer = std::fmod(rng() / 100.0f, 360);
			CreateParticle(pos, Color(kColorWhite), kParticleStar, kBlendAdd, 255, kEaseInQuad, 15, 0, 0, 0, 0, 0, std::fmod(rng() / 100.0f, 1.5f), 0, kEaseInQuad, 120, 0, rand_buffer, rand_buffer, 0, 0, std::fmod(rng() / 100.0f, 32), 0, kEaseInQuad, 120);
		}
	}
}