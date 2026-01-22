#include "laser.h"

#include <cmath>

#include "debug.h"
#include "enemy.h"
#include "graze.h"
#include "object.h"
#include "particle.h"
#include "player.h"
#include "player_shot.h"
#include "sound.h"
#include "time_utl.h"
#include "vec2d.h"

namespace zenithstg {
	std::array<Laser, kMaxLaser> lasers;
	std::array<Laser*, kMaxLaser> laser_ptrs;
	std::vector<int> blank_lasers;
	std::mutex blank_laser_mutex;
	long long laser_index = 0;

	void Laser::DrawObject() {
		if (!(flags_ & kIsAlive)) return;
		double half_w = width_ / 2;
		std::array<Vec2D, 4> local = {
			Vec2D(-half_w, 0),
			Vec2D(-half_w, length_),
			Vec2D(half_w, length_),
			Vec2D(half_w, 0)
		};
		std::array<Vec2D, 4> world;
		for (int i = 0; i < 4; ++i) {
			Vec2D rot = RotatePoint(SafeAccess(local, i), show_angle_ + kPi / 2);
			SafeAccess(world, i) = pos_ + rot;
		}
		if (blend_ == -1) {
			SmartSetDrawBlendMode(SafeAccess(default_bullet_blend, style_), pal_);
			SetDrawBright(color_.GetR255(), color_.GetG255(), color_.GetB255());
			SetDrawMode(DX_DRAWMODE_NEAREST);
			DrawRectModiGraph(
				SafeAccess(world, 0).GetX(), SafeAccess(world, 0).GetY(),
				SafeAccess(world, 1).GetX(), SafeAccess(world, 1).GetY(),
				SafeAccess(world, 2).GetX(), SafeAccess(world, 2).GetY(),
				SafeAccess(world, 3).GetX(), SafeAccess(world, 3).GetY(),
				64 - 128 * SafeAccess(draw_ratio_bullet_graphs, style_) / 2,
				64 - 128 * SafeAccess(draw_ratio_bullet_graphs, style_) / 2,
				128 * SafeAccess(draw_ratio_bullet_graphs, style_),
				128 * SafeAccess(draw_ratio_bullet_graphs, style_),
				SafeAccess(img_res.bullet_back_gh, style_),
				TRUE);
			SetDrawBright(255, 255, 255);
			DrawRectModiGraph(
				SafeAccess(world, 0).GetX(), SafeAccess(world, 0).GetY(),
				SafeAccess(world, 1).GetX(), SafeAccess(world, 1).GetY(),
				SafeAccess(world, 2).GetX(), SafeAccess(world, 2).GetY(),
				SafeAccess(world, 3).GetX(), SafeAccess(world, 3).GetY(),
				64 - 128 * SafeAccess(draw_ratio_bullet_graphs, style_) / 2,
				64 - 128 * SafeAccess(draw_ratio_bullet_graphs, style_) / 2,
				128 * SafeAccess(draw_ratio_bullet_graphs, style_),
				128 * SafeAccess(draw_ratio_bullet_graphs, style_),
				SafeAccess(img_res.bullet_front_gh, style_),
				TRUE);
			SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			SetDrawMode(DX_DRAWMODE_NEAREST);
		}
		else {
			SmartSetDrawBlendMode(blend_, pal_);
			SetDrawBright(color_.GetR255(), color_.GetG255(), color_.GetB255());
			SetDrawMode(DX_DRAWMODE_NEAREST);
			DrawRectModiGraph(
				SafeAccess(world, 0).GetX(), SafeAccess(world, 0).GetY(),
				SafeAccess(world, 1).GetX(), SafeAccess(world, 1).GetY(),
				SafeAccess(world, 2).GetX(), SafeAccess(world, 2).GetY(),
				SafeAccess(world, 3).GetX(), SafeAccess(world, 3).GetY(),
				64 - 128 * SafeAccess(draw_ratio_bullet_graphs, style_) / 2,
				64 - 128 * SafeAccess(draw_ratio_bullet_graphs, style_) / 2,
				128 * SafeAccess(draw_ratio_bullet_graphs, style_),
				128 * SafeAccess(draw_ratio_bullet_graphs, style_),
				SafeAccess(img_res.bullet_back_gh, style_),
				TRUE);
			SetDrawBright(255, 255, 255);
			DrawRectModiGraph(
				SafeAccess(world, 0).GetX(), SafeAccess(world, 0).GetY(),
				SafeAccess(world, 1).GetX(), SafeAccess(world, 1).GetY(),
				SafeAccess(world, 2).GetX(), SafeAccess(world, 2).GetY(),
				SafeAccess(world, 3).GetX(), SafeAccess(world, 3).GetY(),
				64 - 128 * SafeAccess(draw_ratio_bullet_graphs, style_) / 2,
				64 - 128 * SafeAccess(draw_ratio_bullet_graphs, style_) / 2,
				128 * SafeAccess(draw_ratio_bullet_graphs, style_),
				128 * SafeAccess(draw_ratio_bullet_graphs, style_),
				SafeAccess(img_res.bullet_front_gh, style_),
				TRUE);
			SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			SetDrawMode(DX_DRAWMODE_NEAREST);
		}
		if (kIsColShow == 1) {
			if ((flags_ & kIsCol) == 1) {
				SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
				DrawCircle(pos_.GetX(), pos_.GetY(), col_size_, GetColor(255, 255, 255), 1);
				DrawFormatString(pos_.GetX(), pos_.GetY(), GamingColor().GetDxColor(), "%f", col_size_);
			}
		}
	}

	int Laser::ColliCheckObject() {
		double r = (length_ * length_ + col_size_ * col_size_) / 4;
		Vec2D d = pos_ - player_.GetPos();
		if (d.GetX() * d.GetX() + d.GetY() * d.GetY() <= r) {
			return 0;
		}
		double half_w = col_size_ / 2;
		std::array<Vec2D, 4> local = {
			Vec2D(-half_w, 0),
			Vec2D(-half_w, length_),
			Vec2D(half_w, length_),
			Vec2D(half_w, 0)
		};
		std::array<Vec2D, 4> world;
		for (int i = 0; i < 4; ++i) {
			Vec2D rot = RotatePoint(SafeAccess(local, i), show_angle_ + kPi / 2);
			SafeAccess(world, i) = pos_ + rot;
		}
		if (
			ColPointAndRect(player_.GetPos(),
				SafeAccess(world, 0),
				SafeAccess(world, 1),
				SafeAccess(world, 2),
				SafeAccess(world, 3))) {
			player_.HitPlayer();
			return 1;
		}
		return 0;
	}

	void Laser::GrazeObject() {
		if (kGrazeEnabled == 1) return;
		double r = (length_ * length_ + col_size_ * col_size_ + kGrazeRange * kGrazeRange) / 4;
		Vec2D d = pos_ - player_.GetPos();
		if (d.GetX() * d.GetX() + d.GetY() * d.GetY() <= r || (flags_ & kIsGraze) == 0) {
			return;
		}
		double half_w = (col_size_ + kGrazeRange) / 2;
		std::array<Vec2D, 4> local = {
			Vec2D(-half_w, 0),
			Vec2D(-half_w, length_),
			Vec2D(half_w, length_),
			Vec2D(half_w, 0)
		};
		std::array<Vec2D, 4> world;
		for (int i = 0; i < 4; ++i) {
			Vec2D rot = RotatePoint(SafeAccess(local, i), show_angle_ + kPi / 2);
			SafeAccess(world, i) = pos_ + rot;
		}
		if (
			ColPointAndRect(player_.GetPos(),
				SafeAccess(world, 0),
				SafeAccess(world, 1),
				SafeAccess(world, 2),
				SafeAccess(world, 3))) {
			Graze();
			if (kLaserGrazeEveryFrame == 0) {
				flags_ &= ~kIsGraze;
			}
		}
	}

	int Laser::CheckPosBounds() {
		double limit = size_ * 128 * 2 * SafeAccess(draw_ratio_bullet_graphs, style_);
		if (pos_.GetX() < kBorderLeft - limit) return 1;
		if (pos_.GetX() > kBorderRight + limit) return 1;
		if (pos_.GetY() < kBorderUp - limit) return 1;
		if (pos_.GetY() > kBorderDown + limit) return 1;

		return 0;
	}

	int Laser::CheckCollisionAndBounds() {
		if (flags_ & kIsCol) {
			if (ColliCheckObject()) {
				KillObject();
				return 1;
			}
		}
		if (CheckPosBounds()) {
			KillObject();
			return 1;
		}
		return 0;
	}

	void Laser::MoveFunc() {
		switch (id_) {
		case 0:
		default: {
			int needsMultiStep = speed_ >= col_size_ + player_.col_size_ && flags_ & kIsCol;
			if (needsMultiStep) {
				int step = static_cast<int>(std::ceil(speed_ / 1.0f));
				for (int i = 0; i < step; i++) {
					MoveObject(speed_ / step);
					if (CheckCollisionAndBounds()) return;
				}
			}
			else {
				MoveObject(speed_);
				if (CheckCollisionAndBounds()) return;
			}
			break;
		}
		}
	}

	void Laser::KillObject() {
		PushBlankLasers(index_);
		flags_ &= ~kIsAlive;
	}

	void PushBlankLasers(int idx) {
		std::lock_guard<std::mutex> lock(blank_laser_mutex);
		blank_lasers.emplace_back(idx);
	}

	int CreateLaser(const Vec2D& pos, double length, double width, const Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se, int id, int priority, const std::vector<std::any>& params) {
		sound_mng_.ReserveSe(se);
		if (blank_lasers.empty()) return 1;
		int idx = blank_lasers.back();
		blank_lasers.pop_back();
		SafeAccess(lasers, idx).flags_ = kIsAlive | is_col * kIsCol | kIsGraze;
		SafeAccess(lasers, idx).obj_type_ = kObjectLaser;
		SafeAccess(lasers, idx).pos_ = pos;
		SafeAccess(lasers, idx).color_ = color;
		SafeAccess(lasers, idx).style_ = style;
		SafeAccess(lasers, idx).blend_ = blend;
		SafeAccess(lasers, idx).pal_ = pal;
		SafeAccess(lasers, idx).start_col_size_ = start_col_size;
		SafeAccess(lasers, idx).end_col_size_ = end_col_size;
		SafeAccess(lasers, idx).col_size_ease_type_ = col_size_ease_type;
		SafeAccess(lasers, idx).col_size_ease_time_ = col_size_ease_time;
		SafeAccess(lasers, idx).start_size_ = start_size;
		SafeAccess(lasers, idx).end_size_ = end_size;
		SafeAccess(lasers, idx).size_ease_type_ = size_ease_type;
		SafeAccess(lasers, idx).size_ease_time_ = size_ease_time;
		if (aim == kAimTrue) {
			SafeAccess(lasers, idx).start_angle_ = player_.AimPlayer(pos) + start_angle;
			SafeAccess(lasers, idx).end_angle_ = player_.AimPlayer(pos) + end_angle;
		}
		else {
			SafeAccess(lasers, idx).start_angle_ = start_angle;
			SafeAccess(lasers, idx).end_angle_ = end_angle;
		}
		SafeAccess(lasers, idx).angle_ease_type_ = angle_ease_type;
		SafeAccess(lasers, idx).angle_ease_time_ = angle_ease_time;
		SafeAccess(lasers, idx).start_speed_ = start_speed;
		SafeAccess(lasers, idx).end_speed_ = end_speed;
		SafeAccess(lasers, idx).speed_ease_type_ = speed_ease_type;
		SafeAccess(lasers, idx).speed_ease_time_ = speed_ease_time;
		SafeAccess(lasers, idx).pop_t_ = t;
		SafeAccess(lasers, idx).length_ = length;
		SafeAccess(lasers, idx).width_ = width;
		SafeAccess(lasers, idx).front_node_ = 0;
		SafeAccess(lasers, idx).current_node_num_ = 0;
		SafeAccess(lasers, idx).order_ = laser_index++;
		SafeAccess(lasers, idx).index_ = idx;
		SafeAccess(lasers, idx).id_ = id;
		SafeAccess(lasers, idx).priority_ = priority;
		SafeAccess(lasers, idx).params_ = params;
		return 0;
	}

	void CreateLaserGroup(const Vec2D& pos, double length, double width, const Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int way, double spread, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se, int id, int priority, const std::vector<std::any>& params) {
		sound_mng_.ReserveSe(se);
		switch (aim) {
		case kAimFalse:
			for (int i = 0; i < way; i++) {
				if (CreateLaser(pos, length, width, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 0, spread / way * i + start_angle - spread / 2, spread / way * i + end_angle - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, priority, params)) return;
			}
			break;
		case kAimTrue:
			for (int i = 0; i < way; i++) {
				if (CreateLaser(pos, length, width, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 1, spread / way * i + start_angle - spread / 2, spread / way * i + end_angle - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, priority, params)) return;
			}
			break;
		case kAimOffset:
			for (int i = 0; i < way; i++) {
				if (CreateLaser(pos, length, width, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 1, spread / way * i + start_angle + spread / (way * 2) - spread / 2, spread / way * i + end_angle + spread / (way * 2) - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, priority, params)) return;
			}
			break;
		default:
			for (int i = 0; i < way; i++) {
				if (CreateLaser(pos, length, width, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 0, spread / way * i + start_angle - spread / 2, spread / way * i + end_angle - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, priority, params)) return;
			}
			break;
		}
	}

	void CreateSimpleLaserGroup(const Vec2D& pos, double length, double width, const Color& color, int style, int blend, int pal, double col_size, double size, int way, double spread, int aim, double angle, double speed, int se, int id, const std::vector<std::any>& params) {
		sound_mng_.ReserveSe(se);
		switch (aim) {
		case kAimFalse:
			for (int i = 0; i < way; i++) {
				if (CreateLaser(pos, length, width, color, style, blend, pal, 1, col_size, col_size, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, 0, params)) return;
			}
			break;
		case kAimTrue:
			for (int i = 0; i < way; i++) {
				if (CreateLaser(pos, length, width, color, style, blend, pal, 0, col_size, col_size, 0, 0, size, size, 0, 0, 1, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, 0, params)) return;
			}
			break;
		case kAimOffset:
			for (int i = 0; i < way; i++) {
				if (CreateLaser(pos, length, width, color, style, blend, pal, 1, col_size, col_size, 0, 0, size, size, 0, 0, 1, spread / way * i + angle + spread / (way * 2) - spread / 2, spread / way * i + angle + spread / (way * 2) - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, 0, params)) return;
			}
			break;
		default:
			for (int i = 0; i < way; i++) {
				if (CreateLaser(pos, length, width, color, style, blend, pal, 1, col_size, col_size, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, 0, params)) return;
			}
			break;
		}
	}

	void CreateSmartLaserGroup(ObjectParams param) {
		sound_mng_.ReserveSe(param.se);
		switch (param.aim) {
		case kAimFalse:
			for (int i = 0; i < param.way; i++) {
				if (CreateLaser(param.pos, param.length, param.width, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 0, param.spread / param.way * i + param.start_angle - param.spread / 2, param.spread / param.way * i + param.end_angle - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, kSoundEffectNone, param.id, param.priority, param.params)) return;
			}
			break;
		case kAimTrue:
			for (int i = 0; i < param.way; i++) {
				if (CreateLaser(param.pos, param.length, param.width, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 1, param.spread / param.way * i + param.start_angle - param.spread / 2, param.spread / param.way * i + param.end_angle - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, kSoundEffectNone, param.id, param.priority, param.params)) return;
			}
			break;
		case kAimOffset:
			for (int i = 0; i < param.way; i++) {
				if (CreateLaser(param.pos, param.length, param.width, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 1, param.spread / param.way * i + param.start_angle + param.spread / (param.way * 2) - param.spread / 2, param.spread / param.way * i + param.end_angle + param.spread / (param.way * 2) - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, kSoundEffectNone, param.id, param.priority, param.params)) return;
			}
			break;
		default:
			for (int i = 0; i < param.way; i++) {
				if (CreateLaser(param.pos, param.length, param.width, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 0, param.spread / param.way * i + param.start_angle - param.spread / 2, param.spread / param.way * i + param.end_angle - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, kSoundEffectNone, param.id, param.priority, param.params)) return;
			}
			break;
		}
	}

	void ParallelUpdateLasers(std::array<Laser, kMaxLaser>& lasers) {
		std::for_each(std::execution::par, lasers.begin(), lasers.end(),
			[](Laser& L) {
				L.UpdateObject();
			});
	}

	void MoveLasers() {
		ParallelUpdateLasers(lasers);
	}

	void RenderLasers() {
		std::sort(std::execution::par, laser_ptrs.begin(), laser_ptrs.end(), [](const Laser* a, const Laser* b) {
			if (a->priority_ == b->priority_) {
				return a->order_ < b->order_;
			}
			return a->priority_ < b->priority_;
			});
		for (auto* L : laser_ptrs) {
			L->DrawObject();
		}
	}

	void LuaLaserInit(sol::state& lua) {
		lua.set_function("create_laser", CreateLaser);
		lua.set_function("create_laser_group", CreateLaserGroup);
		lua.set_function("create_simple_laser_group", CreateSimpleLaserGroup);
	}
}