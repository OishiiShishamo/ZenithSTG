#include "bullet.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <execution>
#include <mutex>
#include <vector>

#include "DxLib.h"

#include "collision.h"
#include "color.h"
#include "graze.h"
#include "object.h"
#include "player.h"
#include "sound.h"
#include "utility.h"
#include "vec2d.h"
#include "params.h"

std::array<Bullet, kMaxBullet> bullets;
std::array<Bullet*, kMaxBullet> bullet_ptrs;
std::vector<int> blank_bullets;
std::mutex blank_bullets_mutex;
std::array<int, kGraphicHandlerNum> default_bullet_blend;
std::array<double, kGraphicHandlerNum> draw_ratio_bullet_graphs;
long long bullet_index = 0;

void
Bullet::ShowBullet() {
	if (!(flags_ & kIsAlive)) return;
	std::array<Vec2D, 4> world;
	const bool is_scaled = size_ > 1.0f;
	if (is_scaled) {
		double half = size_ / 2 * 128 * SafeAccess(draw_ratio_bullet_graphs, style_);
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
		SmartSetDrawBlendMode(SafeAccess(default_bullet_blend, style_), pal_);
		SetDrawBright(color_.GetR(), color_.GetG(), color_.GetB());
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if (is_scaled) {
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
		}
		else DrawRotaGraph(pos_.GetX(), pos_.GetY(), size_, -show_angle_, SafeAccess(img_res.bullet_back_gh, style_), TRUE);
		SetDrawBright(255, 255, 255);
		if (is_scaled) {
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
		}
		else DrawRotaGraph(pos_.GetX(), pos_.GetY(), size_, -show_angle_, SafeAccess(img_res.bullet_front_gh, style_), TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend_, pal_);
		SetDrawBright(color_.GetR(), color_.GetG(), color_.GetB());
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if (is_scaled) {
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
		}
		else DrawRotaGraph(pos_.GetX(), pos_.GetY(), size_, -show_angle_, SafeAccess(img_res.bullet_back_gh, style_), TRUE);
		SetDrawBright(255, 255, 255);
		if (is_scaled) {
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
		}
		else DrawRotaGraph(pos_.GetX(), pos_.GetY(), size_, -show_angle_, SafeAccess(img_res.bullet_front_gh, style_), TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	if (kIsColShow == 1) {
		if (flags_ & kIsCol) {
			SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			DrawCircle(pos_.GetX(), pos_.GetY(), col_size_, GetColor(255, 255, 255), 1);
			DrawFormatString(pos_.GetX(), pos_.GetY(), GetColor(GamingColor().GetR(), GamingColor().GetG(), GamingColor().GetB()), "%f", col_size_);
		}
	}
}

int
Bullet::ColliCheckObject() {
	if (ColCircleAndCircle(pos_, player.pos_, col_size_ + player.col_size_)) {
		player.HitPlayer();
		return 1;
	}
	return 0;
}

#if kGrazeEnabled == 1
void
Bullet::GrazeObject() {
	if ((flags_ & kIsGraze) == 0) return;
	if (ColCircleAndCircle(pos_, player.pos_, col_size_ + player.col_size_ + kGrazeRange)) {
		Graze();
#if kBulletGrazeEveryFrame == 0
		flags_ &= ~kIsGraze;
#endif
	}
}
#endif

int
Bullet::CheckPosBounds() {
	double limit = size_ * 128 * 2 * SafeAccess(draw_ratio_bullet_graphs, style_);
	if (pos_.GetX() < kBorderLeft - limit) return 1;
	if (pos_.GetX() > kBorderRight + limit) return 1;
	if (pos_.GetY() < kBorderUp - limit) return 1;
	if (pos_.GetY() > kBorderDown + limit) return 1;

	return 0;
}

int
Bullet::CheckCollisionAndBounds() {
	if (flags_ & kIsCol) {
		if (ColliCheckObject()) {
			PushBlankBullets(index_);
			flags_ &= ~kIsAlive;
			return 1;
		}
	}
	if (CheckPosBounds()) {
		PushBlankBullets(index_);
		flags_ &= ~kIsAlive;
		return 1;
	}
	return 0;
}

void
Bullet::MoveFunc() {
	switch (id_) {
	case 0:
	default: {
		int needsMultiStep = speed_ >= col_size_ + player.col_size_ && flags_ & kIsCol;
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

void
PushBlankBullets(int idx) {
	std::lock_guard<std::mutex> lock(blank_bullets_mutex);
	blank_bullets.emplace_back(idx);
}

int
CreateBullet(const Vec2D& pos, const zenithstg::Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se, int id, const std::vector<std::any>& params) {
	sound_mng_.ReserveSe(se);
	if (blank_bullets.empty()) return 1;
	int idx = blank_bullets.back();
	blank_bullets.pop_back();
	SafeAccess(bullets, idx).flags_ = kIsAlive | is_col * kIsCol | kIsGraze;
	SafeAccess(bullets, idx).obj_type_ = kObjectBullet;
	SafeAccess(bullets, idx).pos_ = pos;
	SafeAccess(bullets, idx).color_ = color;
	SafeAccess(bullets, idx).style_ = style;
	SafeAccess(bullets, idx).blend_ = blend;
	SafeAccess(bullets, idx).pal_ = pal;
	SafeAccess(bullets, idx).start_col_size_ = start_col_size;
	SafeAccess(bullets, idx).end_col_size_ = end_col_size;
	SafeAccess(bullets, idx).col_size_ease_type_ = col_size_ease_type;
	SafeAccess(bullets, idx).col_size_ease_time_ = col_size_ease_time;
	SafeAccess(bullets, idx).start_size_ = start_size;
	SafeAccess(bullets, idx).end_size_ = end_size;
	SafeAccess(bullets, idx).size_ease_type_ = size_ease_type;
	SafeAccess(bullets, idx).size_ease_time_ = size_ease_time;
	if (aim == kAimTrue) {
		SafeAccess(bullets, idx).start_angle_ = player.AimPlayer(pos) + start_angle;
		SafeAccess(bullets, idx).end_angle_ = player.AimPlayer(pos) + end_angle;
	}
	else {
		SafeAccess(bullets, idx).start_angle_ = start_angle;
		SafeAccess(bullets, idx).end_angle_ = end_angle;
	}
	SafeAccess(bullets, idx).angle_ease_type_ = angle_ease_type;
	SafeAccess(bullets, idx).angle_ease_time_ = angle_ease_time;
	SafeAccess(bullets, idx).start_speed_ = start_speed;
	SafeAccess(bullets, idx).end_speed_ = end_speed;
	SafeAccess(bullets, idx).speed_ease_type_ = speed_ease_type;
	SafeAccess(bullets, idx).speed_ease_time_ = speed_ease_time;
	SafeAccess(bullets, idx).pop_t_ = t;
	SafeAccess(bullets, idx).length_ = 0;
	SafeAccess(bullets, idx).width_ = 0;
	SafeAccess(bullets, idx).front_node_ = 0;
	SafeAccess(bullets, idx).current_node_num_ = 0;
	SafeAccess(bullets, idx).order_ = bullet_index;
	SafeAccess(bullets, idx).index_ = idx;
	SafeAccess(bullets, idx).id_ = id;
	SafeAccess(bullets, idx).params_ = params;
	bullet_index++;
	return 0;
}

void
CreateBulletGroup(const Vec2D& pos, const zenithstg::Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int way, double spread, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se, int id, const std::vector<std::any>& params) {
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
CreateSimpleBulletGroup(const Vec2D& pos, const zenithstg::Color& color, int style, int blend, int pal, double col_size, double size, int way, double spread, int aim, double angle, double speed, int se, int id, const std::vector<std::any>& params) {
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
			return a->order_ < b->order_;
			});
	}
	ParallelUpdateBullets(bullets);
	for (auto* B : bullet_ptrs) {
		B->ShowBullet();
	}
}