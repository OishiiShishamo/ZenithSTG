#include "Main.h"

#include "Bullet.h"
#include "Color.h"
#include "Particle.h"
#include "Enemy.h"
#include "Laser.h"
#include "Object.h"
#include "Player.h"
#include "player_shot.h"
#include "Graze.h"
#include "Vec2D.h"

std::array<Bullet, kMaxBullet> bullets;
std::array<Bullet*, kMaxBullet> bullet_ptrs;
std::vector<int> blank_bullets;
std::mutex blank_bullets_mutex;
std::array<int, kGraphicHandlerNum> default_bullet_blend;
std::array<double, kGraphicHandlerNum> draw_ratio_bullet_graphs;
long long bullet_index = 0;

void
Bullet::ShowBullet() {
	if (!(flags & kIsAlive)) return;
	std::array<Vec2D, 4> world;
	const bool is_scaled = size > 1.0f;
	if (is_scaled) {
		double half = size / 2 * 128 * SafeAccess(draw_ratio_bullet_graphs, style);
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
		SmartSetDrawBlendMode(SafeAccess(default_bullet_blend, style), pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if (is_scaled) {
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
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -show_angle, SafeAccess(img_res.bullet_back_gh, style), TRUE);
		SetDrawBright(255, 255, 255);
		if (is_scaled) {
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
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -show_angle, SafeAccess(img_res.bullet_front_gh, style), TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if (is_scaled) {
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
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -show_angle, SafeAccess(img_res.bullet_back_gh, style), TRUE);
		SetDrawBright(255, 255, 255);
		if (is_scaled) {
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
		}
		else DrawRotaGraph(pos.GetX(), pos.GetY(), size, -show_angle, SafeAccess(img_res.bullet_front_gh, style), TRUE);
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

int
Bullet::ColliCheckObject() {
	if (ColCircleAndCircle(pos, Plyr.pos, col_size + Plyr.col_size)) {
		Plyr.HitPlayer();
		return 1;
	}
	return 0;
}

#if kGrazeEnabled == 1
void
Bullet::GrazeObject() {
	if ((flags & kIsGraze) == 0) return;
	if (ColCircleAndCircle(pos, Plyr.pos, col_size + Plyr.col_size + kGrazeRange)) {
		Graze();
#if kBulletGrazeEveryFrame == 0
		flags &= ~kIsGraze;
#endif
	}
}
#endif

int
Bullet::CheckPosBounds() {
	double limit = size * 128 * 2 * SafeAccess(draw_ratio_bullet_graphs, style);
	if (pos.GetX() < kBorderLeft - limit) return 1;
	if (pos.GetX() > kBorderRight + limit) return 1;
	if (pos.GetY() < kBorderUp - limit) return 1;
	if (pos.GetY() > kBorderDown + limit) return 1;

	return 0;
}

int
Bullet::CheckCollisionAndBounds() {
	if (flags & kIsCol) {
		if (ColliCheckObject()) {
			PushBlankBullets(index);
			flags &= ~kIsAlive;
			return 1;
		}
	}
	if (CheckPosBounds()) {
		PushBlankBullets(index);
		flags &= ~kIsAlive;
		return 1;
	}
	return 0;
}

void
Bullet::MoveFunc() {
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
PushBlankBullets(int idx) {
	std::lock_guard<std::mutex> lock(blank_bullets_mutex);
	blank_bullets.emplace_back(idx);
}

int
CreateBullet(const Vec2D& pos, const Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se, int id, const std::vector<std::any>& params) {
	sound_mng_.ReserveSe(se);
	if (blank_bullets.empty()) return 1;
	int idx = blank_bullets.back();
	blank_bullets.pop_back();
	SafeAccess(bullets, idx).flags = kIsAlive | is_col * kIsCol | kIsGraze;
	SafeAccess(bullets, idx).obj_type = kObjectBullet;
	SafeAccess(bullets, idx).pos = pos;
	SafeAccess(bullets, idx).color = color;
	SafeAccess(bullets, idx).style = style;
	SafeAccess(bullets, idx).blend = blend;
	SafeAccess(bullets, idx).pal = pal;
	SafeAccess(bullets, idx).start_col_size = start_col_size;
	SafeAccess(bullets, idx).end_col_size = end_col_size;
	SafeAccess(bullets, idx).col_size_ease_type = col_size_ease_type;
	SafeAccess(bullets, idx).col_size_ease_time = col_size_ease_time;
	SafeAccess(bullets, idx).start_size = start_size;
	SafeAccess(bullets, idx).end_size = end_size;
	SafeAccess(bullets, idx).size_ease_type = size_ease_type;
	SafeAccess(bullets, idx).size_ease_time = size_ease_time;
	if (aim == kAimTrue) {
		SafeAccess(bullets, idx).start_angle = Plyr.AimPlayer(pos) + start_angle;
		SafeAccess(bullets, idx).end_angle = Plyr.AimPlayer(pos) + end_angle;
	}
	else {
		SafeAccess(bullets, idx).start_angle = start_angle;
		SafeAccess(bullets, idx).end_angle = end_angle;
	}
	SafeAccess(bullets, idx).angle_ease_type = angle_ease_type;
	SafeAccess(bullets, idx).angle_ease_time = angle_ease_time;
	SafeAccess(bullets, idx).start_speed = start_speed;
	SafeAccess(bullets, idx).end_speed = end_speed;
	SafeAccess(bullets, idx).speed_ease_type = speed_ease_type;
	SafeAccess(bullets, idx).speed_ease_time = speed_ease_time;
	SafeAccess(bullets, idx).pop_t = t;
	SafeAccess(bullets, idx).length = 0;
	SafeAccess(bullets, idx).width = 0;
	SafeAccess(bullets, idx).front_node = 0;
	SafeAccess(bullets, idx).current_node_num = 0;
	SafeAccess(bullets, idx).order = bullet_index;
	SafeAccess(bullets, idx).index = idx;
	SafeAccess(bullets, idx).id = id;
	SafeAccess(bullets, idx).params = params;
	bullet_index++;
	return 0;
}

void
CreateBulletGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int way, double spread, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se, int id, const std::vector<std::any>& params) {
	sound_mng_.ReserveSe(se);
	switch (aim) {
	case kAimFalse:
		for (int i = 0; i < way; i++) {
			if (CreateBullet(pos, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 0, spread / way * i + start_angle - spread / 2, spread / way * i + end_angle - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, params)) return;
		}
		break;
	case kAimTrue:
		for (int i = 0; i < way; i++) {
			if (CreateBullet(pos, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 1, spread / way * i + start_angle - spread / 2, spread / way * i + end_angle - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, params)) return;
		}
		break;
	case kAimOffset:
		for (int i = 0; i < way; i++) {
			if (CreateBullet(pos, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 1, spread / way * i + start_angle + spread / (way * 2) - spread / 2, spread / way * i + end_angle + spread / (way * 2) - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, params)) return;
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			if (CreateBullet(pos, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 0, spread / way * i + start_angle - spread / 2, spread / way * i + end_angle - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, params)) return;
		}
		break;
	}
}

void
CreateSimpleBulletGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, double col_size, double size, int way, double spread, int aim, double angle, double speed, int se, int id, const std::vector<std::any>& params) {
	sound_mng_.ReserveSe(se);
	switch (aim) {
	case kAimFalse:
		for (int i = 0; i < way; i++) {
			if (CreateBullet(pos, color, style, blend, pal, 1, col_size, col_size, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, params)) return;
		}
		break;
	case kAimTrue:
		for (int i = 0; i < way; i++) {
			if (CreateBullet(pos, color, style, blend, pal, 0, col_size, col_size, 0, 0, size, size, 0, 0, 1, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, params)) return;
		}
		break;
	case kAimOffset:
		for (int i = 0; i < way; i++) {
			if (CreateBullet(pos, color, style, blend, pal, 1, col_size, col_size, 0, 0, size, size, 0, 0, 1, spread / way * i + angle + spread / (way * 2) - spread / 2, spread / way * i + angle + spread / (way * 2) - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, params)) return;
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			if (CreateBullet(pos, color, style, blend, pal, 1, col_size, col_size, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, params)) return;
		}
		break;
	}
}

void
CreateSmartBulletGroup(ObjectParams param) {
	sound_mng_.ReserveSe(param.se);
	switch (param.aim) {
	case kAimFalse:
		for (int i = 0; i < param.way; i++) {
			if (CreateBullet(param.pos, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 0, param.spread / param.way * i + param.start_angle - param.spread / 2, param.spread / param.way * i + param.end_angle - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, kSoundEffectNone, param.id, param.params)) return;
		}
		break;
	case kAimTrue:
		for (int i = 0; i < param.way; i++) {
			if (CreateBullet(param.pos, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 1, param.spread / param.way * i + param.start_angle - param.spread / 2, param.spread / param.way * i + param.end_angle - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, param.id, kSoundEffectNone, param.params)) return;
		}
		break;
	case kAimOffset:
		for (int i = 0; i < param.way; i++) {
			if (CreateBullet(param.pos, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 1, param.spread / param.way * i + param.start_angle + param.spread / (param.way * 2) - param.spread / 2, param.spread / param.way * i + param.end_angle + param.spread / (param.way * 2) - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, kSoundEffectNone, param.id, param.params)) return;
		}
		break;
	default:
		for (int i = 0; i < param.way; i++) {
			if (CreateBullet(param.pos, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 0, param.spread / param.way * i + param.start_angle - param.spread / 2, param.spread / param.way * i + param.end_angle - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, param.id, kSoundEffectNone, param.params)) return;
		}
		break;
	}
}

void
ParallelUpdateBullets(std::array<Bullet, kMaxBullet>& bullets) {
	std::for_each(std::execution::par_unseq, bullets.begin(), bullets.end(),
		[](Bullet& B) {
			B.UpdateObject();
		});
}

void
MoveBullets() {
	if (t % 1 == 0) {
		std::sort(bullet_ptrs.begin(), bullet_ptrs.end(), [](const Bullet* a, const Bullet* b) {
			return a->order < b->order;
			});
	}
	ParallelUpdateBullets(bullets);
	for (auto* B : bullet_ptrs) {
		B->ShowBullet();
	}
}