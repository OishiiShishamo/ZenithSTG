#include "Main.h"

#include "Bullet.h"
#include "Particle.h"
#include "Enemy.h"
#include "Graze.h"
#include "Laser.h"
#include "Object.h"
#include "Player.h"
#include "player_shot.h"
#include "Sound.h"
#include "time_utl.h"
#include "Vec2D.h"

std::array<Laser, kMaxLaser> lasers;
std::array<Laser*, kMaxLaser> laser_ptrs;
std::vector<int> blank_lasers;
std::mutex blank_laser_mutex;

void
Laser::ShowLaser() {
	if (!(flags & kIsAlive)) return;
	double half_w = width / 2;
	std::array<Vec2D, 4> local = {
		Vec2D(-half_w, 0),
		Vec2D(-half_w, length),
		Vec2D(half_w, length),
		Vec2D(half_w, 0)
	};
	std::array<Vec2D, 4> world;
	for (int i = 0; i < 4; ++i) {
		Vec2D rot = RotatePoint(SafeAccess(local, i), show_angle + kPi / 2);
		SafeAccess(world, i) = pos + rot;
	}
	if (blend == -1) {
		SmartSetDrawBlendMode(SafeAccess(default_bullet_blend, style), pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		DrawRectModiGraph(
			SafeAccess(world, 0).GetX(), SafeAccess(world, 0).GetY(),
			SafeAccess(world, 1).GetX(), SafeAccess(world, 1).GetY(),
			SafeAccess(world, 2).GetX(), SafeAccess(world, 2).GetY(),
			SafeAccess(world, 3).GetX(), SafeAccess(world, 3).GetY(),
			64 - 128 * SafeAccess(draw_ratio_bullet_graphs, style) / 2,
			64 - 128 * SafeAccess(draw_ratio_bullet_graphs, style) / 2,
			128 * SafeAccess(draw_ratio_bullet_graphs, style),
			128 * SafeAccess(draw_ratio_bullet_graphs, style),
			SafeAccess(img_res.bullet_back_gh, style),
			TRUE);
		SetDrawBright(255, 255, 255);
		DrawRectModiGraph(
			SafeAccess(world, 0).GetX(), SafeAccess(world, 0).GetY(),
			SafeAccess(world, 1).GetX(), SafeAccess(world, 1).GetY(),
			SafeAccess(world, 2).GetX(), SafeAccess(world, 2).GetY(),
			SafeAccess(world, 3).GetX(), SafeAccess(world, 3).GetY(),
			64 - 128 * SafeAccess(draw_ratio_bullet_graphs, style) / 2,
			64 - 128 * SafeAccess(draw_ratio_bullet_graphs, style) / 2,
			128 * SafeAccess(draw_ratio_bullet_graphs, style),
			128 * SafeAccess(draw_ratio_bullet_graphs, style),
			SafeAccess(img_res.bullet_front_gh, style),
			TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		DrawRectModiGraph(
			SafeAccess(world, 0).GetX(), SafeAccess(world, 0).GetY(),
			SafeAccess(world, 1).GetX(), SafeAccess(world, 1).GetY(),
			SafeAccess(world, 2).GetX(), SafeAccess(world, 2).GetY(),
			SafeAccess(world, 3).GetX(), SafeAccess(world, 3).GetY(),
			64 - 128 * SafeAccess(draw_ratio_bullet_graphs, style) / 2,
			64 - 128 * SafeAccess(draw_ratio_bullet_graphs, style) / 2,
			128 * SafeAccess(draw_ratio_bullet_graphs, style),
			128 * SafeAccess(draw_ratio_bullet_graphs, style),
			SafeAccess(img_res.bullet_back_gh, style),
			TRUE);
		SetDrawBright(255, 255, 255);
		DrawRectModiGraph(
			SafeAccess(world, 0).GetX(), SafeAccess(world, 0).GetY(),
			SafeAccess(world, 1).GetX(), SafeAccess(world, 1).GetY(),
			SafeAccess(world, 2).GetX(), SafeAccess(world, 2).GetY(),
			SafeAccess(world, 3).GetX(), SafeAccess(world, 3).GetY(),
			64 - 128 * SafeAccess(draw_ratio_bullet_graphs, style) / 2,
			64 - 128 * SafeAccess(draw_ratio_bullet_graphs, style) / 2,
			128 * SafeAccess(draw_ratio_bullet_graphs, style),
			128 * SafeAccess(draw_ratio_bullet_graphs, style),
			SafeAccess(img_res.bullet_front_gh, style),
			TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	if (kIsColShow == 1) {
		if ((flags & kIsCol) == 1) {
			SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			DrawCircle(pos.GetX(), pos.GetY(), col_size, GetColor(255, 255, 255), 1);
			DrawFormatString(pos.GetX(), pos.GetY(), GetColor(GetColorHsv(std::fmod(t, 360), 1, 1).r, GetColorHsv(std::fmod(t, 360), 1, 1).g, GetColorHsv(std::fmod(t, 360), 1, 1).b), "%f", col_size);
		}
	}
}

int
Laser::ColliCheckObject() {
	double r = (length * length + col_size * col_size) / 4;
	Vec2D d = pos - Plyr.pos;
	if (d.GetX() * d.GetX() + d.GetY() * d.GetY() <= r) {
		return 0;
	}
	double half_w = col_size / 2;
	std::array<Vec2D, 4> local = {
		Vec2D(-half_w, 0),
		Vec2D(-half_w, length),
		Vec2D(half_w, length),
		Vec2D(half_w, 0)
	};
	std::array<Vec2D, 4> world;
	for (int i = 0; i < 4; ++i) {
		Vec2D rot = RotatePoint(SafeAccess(local, i), show_angle + kPi / 2);
		SafeAccess(world, i) = pos + rot;
	}
	if (
		ColPointAndRect(Plyr.pos,
			SafeAccess(world, 0),
			SafeAccess(world, 1),
			SafeAccess(world, 2),
			SafeAccess(world, 3))) {
		Plyr.HitPlayer();
		return 1;
	}
	return 0;
}

#if kGrazeEnabled == 1
void
Laser::GrazeObject() {
	double r = (length * length + col_size * col_size + kGrazeRange * kGrazeRange) / 4;
	Vec2D d = pos - Plyr.pos;
	if (d.GetX() * d.GetX() + d.GetY() * d.GetY() <= r || (flags & kIsGraze) == 0) {
		return;
	}
	double half_w = (col_size + kGrazeRange) / 2;
	std::array<Vec2D, 4> local = {
		Vec2D(-half_w, 0),
		Vec2D(-half_w, length),
		Vec2D(half_w, length),
		Vec2D(half_w, 0)
	};
	std::array<Vec2D, 4> world;
	for (int i = 0; i < 4; ++i) {
		Vec2D rot = RotatePoint(SafeAccess(local, i), show_angle + kPi / 2);
		SafeAccess(world, i) = pos + rot;
	}
	if (
		ColPointAndRect(Plyr.pos,
			SafeAccess(world, 0),
			SafeAccess(world, 1),
			SafeAccess(world, 2),
			SafeAccess(world, 3))) {
		Graze();
#if kLaserGrazeEveryFrame == 0
		flags &= ~kIsGraze;
#endif
	}
}
#endif

int
Laser::CheckPosBounds() {
	double limit = size * 128 * 2 * SafeAccess(draw_ratio_bullet_graphs, style);
	if (pos.GetX() < kBorderLeft - limit) return 1;
	if (pos.GetX() > kBorderRight + limit) return 1;
	if (pos.GetY() < kBorderUp - limit) return 1;
	if (pos.GetY() > kBorderDown + limit) return 1;

	return 0;
}

int
Laser::CheckCollisionAndBounds() {
	if (flags & kIsCol) {
		if (ColliCheckObject()) {
			PushBlankLasers(index);
			flags &= ~kIsAlive;
			return 1;
		}
	}
	if (CheckPosBounds()) {
		PushBlankLasers(index);
		flags &= ~kIsAlive;
		return 1;
	}
	return 0;
}

void
Laser::MoveFunc() {
	switch (id) {
	case 0:
	default: {
		int needsMultiStep = speed >= col_size + Plyr.col_size && flags & kIsCol;
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
PushBlankLasers(int idx) {
	std::lock_guard<std::mutex> lock(blank_laser_mutex);
	blank_lasers.emplace_back(idx);
}

int
CreateLaser(const Vec2D& pos, double length, double width, const Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se, int id, const std::vector<std::any>& params) {
	sound_mng_.ReserveSe(se);
	if (blank_lasers.empty()) return 1;
	int idx = blank_lasers.back();
	blank_lasers.pop_back();
	SafeAccess(lasers, idx).flags = kIsAlive | is_col * kIsCol | kIsGraze;
	SafeAccess(lasers, idx).obj_type = kObjectLaser;
	SafeAccess(lasers, idx).pos = pos;
	SafeAccess(lasers, idx).color = color;
	SafeAccess(lasers, idx).style = style;
	SafeAccess(lasers, idx).blend = blend;
	SafeAccess(lasers, idx).pal = pal;
	SafeAccess(lasers, idx).start_col_size = start_col_size;
	SafeAccess(lasers, idx).end_col_size = end_col_size;
	SafeAccess(lasers, idx).col_size_ease_type = col_size_ease_type;
	SafeAccess(lasers, idx).col_size_ease_time = col_size_ease_time;
	SafeAccess(lasers, idx).start_size = start_size;
	SafeAccess(lasers, idx).end_size = end_size;
	SafeAccess(lasers, idx).size_ease_type = size_ease_type;
	SafeAccess(lasers, idx).size_ease_time = size_ease_time;
	if (aim == kAimTrue) {
		SafeAccess(lasers, idx).start_angle = Plyr.AimPlayer(pos) + start_angle;
		SafeAccess(lasers, idx).end_angle = Plyr.AimPlayer(pos) + end_angle;
	}
	else {
		SafeAccess(lasers, idx).start_angle = start_angle;
		SafeAccess(lasers, idx).end_angle = end_angle;
	}
	SafeAccess(lasers, idx).angle_ease_type = angle_ease_type;
	SafeAccess(lasers, idx).angle_ease_time = angle_ease_time;
	SafeAccess(lasers, idx).start_speed = start_speed;
	SafeAccess(lasers, idx).end_speed = end_speed;
	SafeAccess(lasers, idx).speed_ease_type = speed_ease_type;
	SafeAccess(lasers, idx).speed_ease_time = speed_ease_time;
	SafeAccess(lasers, idx).pop_t = t;
	SafeAccess(lasers, idx).length = length;
	SafeAccess(lasers, idx).width = width;
	SafeAccess(lasers, idx).front_node = 0;
	SafeAccess(lasers, idx).current_node_num = 0;
	SafeAccess(lasers, idx).index = idx;
	SafeAccess(lasers, idx).id = id;
	SafeAccess(lasers, idx).params = params;
	return 0;
}

void
CreateLaserGroup(const Vec2D& pos, double length, double width, const Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int way, double spread, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se, int id, const std::vector<std::any>& params) {
	sound_mng_.ReserveSe(se);
	switch (aim) {
	case kAimFalse:
		for (int i = 0; i < way; i++) {
			if (CreateLaser(pos, length, width, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 0, spread / way * i + start_angle - spread / 2, spread / way * i + end_angle - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, params)) return;
		}
		break;
	case kAimTrue:
		for (int i = 0; i < way; i++) {
			if (CreateLaser(pos, length, width, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 1, spread / way * i + start_angle - spread / 2, spread / way * i + end_angle - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, params)) return;
		}
		break;
	case kAimOffset:
		for (int i = 0; i < way; i++) {
			if (CreateLaser(pos, length, width, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 1, spread / way * i + start_angle + spread / (way * 2) - spread / 2, spread / way * i + end_angle + spread / (way * 2) - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, params)) return;
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			if (CreateLaser(pos, length, width, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 0, spread / way * i + start_angle - spread / 2, spread / way * i + end_angle - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, params)) return;
		}
		break;
	}
}

void
CreateSimpleLaserGroup(const Vec2D& pos, double length, double width, const Color& color, int style, int blend, int pal, double col_size, double size, int way, double spread, int aim, double angle, double speed, int se, int id, const std::vector<std::any>& params) {
	sound_mng_.ReserveSe(se);
	switch (aim) {
	case kAimFalse:
		for (int i = 0; i < way; i++) {
			if (CreateLaser(pos, length, width, color, style, blend, pal, 1, col_size, col_size, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, params)) return;
		}
		break;
	case kAimTrue:
		for (int i = 0; i < way; i++) {
			if (CreateLaser(pos, length, width, color, style, blend, pal, 0, col_size, col_size, 0, 0, size, size, 0, 0, 1, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, params)) return;
		}
		break;
	case kAimOffset:
		for (int i = 0; i < way; i++) {
			if (CreateLaser(pos, length, width, color, style, blend, pal, 1, col_size, col_size, 0, 0, size, size, 0, 0, 1, spread / way * i + angle + spread / (way * 2) - spread / 2, spread / way * i + angle + spread / (way * 2) - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, params)) return;
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			if (CreateLaser(pos, length, width, color, style, blend, pal, 1, col_size, col_size, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, params)) return;
		}
		break;
	}
}

void
CreateSmartLaserGroup(ObjectParams param) {
	sound_mng_.ReserveSe(param.se);
	switch (param.aim) {
	case kAimFalse:
		for (int i = 0; i < param.way; i++) {
			if (CreateLaser(param.pos, param.length, param.width, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 0, param.spread / param.way * i + param.start_angle - param.spread / 2, param.spread / param.way * i + param.end_angle - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, kSoundEffectNone, param.id, param.params)) return;
		}
		break;
	case kAimTrue:
		for (int i = 0; i < param.way; i++) {
			if (CreateLaser(param.pos, param.length, param.width, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 1, param.spread / param.way * i + param.start_angle - param.spread / 2, param.spread / param.way * i + param.end_angle - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, kSoundEffectNone, param.id, param.params)) return;
		}
		break;
	case kAimOffset:
		for (int i = 0; i < param.way; i++) {
			if (CreateLaser(param.pos, param.length, param.width, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 1, param.spread / param.way * i + param.start_angle + param.spread / (param.way * 2) - param.spread / 2, param.spread / param.way * i + param.end_angle + param.spread / (param.way * 2) - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, kSoundEffectNone, param.id, param.params)) return;
		}
		break;
	default:
		for (int i = 0; i < param.way; i++) {
			if (CreateLaser(param.pos, param.length, param.width, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 0, param.spread / param.way * i + param.start_angle - param.spread / 2, param.spread / param.way * i + param.end_angle - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, kSoundEffectNone, param.id, param.params)) return;
		}
		break;
	}
}

void
ParallelUpdateLasers(std::array<Laser, kMaxLaser>& lasers) {
	std::for_each(std::execution::par_unseq, lasers.begin(), lasers.end(),
		[](Laser& L) {
			L.UpdateObject();
		});
}

void
MoveLasers() {
	if (t % 10 == 0) {
		std::sort(laser_ptrs.begin(), laser_ptrs.end(), [](const Laser* a, const Laser* b) {
			return a->pop_t < b->pop_t;
			});
	}
	ParallelUpdateLasers(lasers);
	for (auto* L : laser_ptrs) {
		L->ShowLaser();
	}
}