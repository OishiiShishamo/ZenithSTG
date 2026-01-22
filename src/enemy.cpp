#include "enemy.h"

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
#include "graze.h"
#include "lua_mng.h"
#include "object.h"
#include "player.h"
#include "player_shot.h"
#include "sound.h"
#include "utility.h"
#include "vec2d.h"
#include "params.h"

namespace zenithstg {
	std::array<Enemy, kMaxEnemy> enemies;
	std::array<Enemy*, kMaxEnemy> enemy_ptrs;
	std::vector<int> blank_enemies;
	std::mutex blank_enemy_mutex;
	std::array<int, kGraphicHandlerNum> default_enemy_blend;
	std::array<double, kGraphicHandlerNum> draw_ratio_enemy_graphs;
	long long enemy_index = 0;

	void Enemy::DrawObject() {
		if (!(flags_ & kIsAlive)) return;
		if (blend_ == -1) {
			SmartSetDrawBlendMode(SafeAccess(default_enemy_blend, style_), pal_);
			SetDrawBright(color_.GetR255(), color_.GetG255(), color_.GetB255());
			SetDrawMode(DX_DRAWMODE_BILINEAR);
			DrawRotaGraph(pos_.GetX(), pos_.GetY(), size_, -show_angle_, SafeAccess(img_res.enemy_gh, style_), TRUE);
			SetDrawBright(255, 255, 255);
			SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			SetDrawMode(DX_DRAWMODE_NEAREST);
		}
		else {
			SmartSetDrawBlendMode(blend_, pal_);
			SetDrawBright(color_.GetR255(), color_.GetG255(), color_.GetB255());
			SetDrawMode(DX_DRAWMODE_BILINEAR);
			DrawRotaGraph(pos_.GetX(), pos_.GetY(), size_, -show_angle_, SafeAccess(img_res.enemy_gh, style_), TRUE);
			SetDrawBright(255, 255, 255);
			SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			SetDrawMode(DX_DRAWMODE_NEAREST);
		}
		if (kIsColShow == 1) {
			if (flags_ & kIsCol) {
				SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
				DrawCircle(pos_.GetX(), pos_.GetY(), col_size_, GetColor(255, 255, 255), 1);
				DrawFormatString(pos_.GetX(), pos_.GetY(), GamingColor().GetDxColor(), "%f", col_size_);
			}
		}
	}

	int Enemy::ColliCheckObject() {
		if (ColPointAndCircle(pos_, player_.GetPos(), col_size_ + player_.col_size_)) {
			player_.HitPlayer();
			return 1;
		}
		return 0;
	}

	int Enemy::CheckPosBounds() {
		double limit = size_ * 128 * 2 * SafeAccess(draw_ratio_enemy_graphs, style_);
		if (pos_.GetX() < kBorderLeft - limit) return 1;
		if (pos_.GetX() > kBorderRight + limit) return 1;
		if (pos_.GetY() < kBorderUp - limit) return 1;
		if (pos_.GetY() > kBorderDown + limit) return 1;

		return 0;
	}

	int Enemy::CheckCollisionAndBounds() {
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

	void Enemy::MoveFunc() {
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

	void Enemy::KillObject() {
		PushBlankEnemies(index_);
		flags_ &= ~kIsAlive;
	}

	void PushBlankEnemies(int idx) {
		std::lock_guard<std::mutex> lock(blank_enemy_mutex);
		blank_enemies.emplace_back(idx);
	}

	int CreateEnemy(const Vec2D& pos, const Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se, int id, int priority, const std::vector<std::any>& params) {
		sound_mng_.ReserveSe(se);
		if (blank_enemies.empty()) return 1;
		int idx = blank_enemies.back();
		blank_enemies.pop_back();
		SafeAccess(enemies, idx).flags_ = kIsAlive | is_col * kIsCol;
		SafeAccess(enemies, idx).obj_type_ = kObjectEnemy;
		SafeAccess(enemies, idx).pos_ = pos;
		SafeAccess(enemies, idx).color_ = color;
		SafeAccess(enemies, idx).style_ = style;
		SafeAccess(enemies, idx).blend_ = blend;
		SafeAccess(enemies, idx).pal_ = pal;
		SafeAccess(enemies, idx).start_col_size_ = start_col_size;
		SafeAccess(enemies, idx).end_col_size_ = end_col_size;
		SafeAccess(enemies, idx).col_size_ease_type_ = col_size_ease_type;
		SafeAccess(enemies, idx).col_size_ease_time_ = col_size_ease_time;
		SafeAccess(enemies, idx).start_size_ = start_size;
		SafeAccess(enemies, idx).end_size_ = end_size;
		SafeAccess(enemies, idx).size_ease_type_ = size_ease_type;
		SafeAccess(enemies, idx).size_ease_time_ = size_ease_time;
		if (aim == kAimTrue) {
			SafeAccess(enemies, idx).start_angle_ = player_.AimPlayer(pos) + start_angle;
			SafeAccess(enemies, idx).end_angle_ = player_.AimPlayer(pos) + end_angle;
		}
		else {
			SafeAccess(enemies, idx).start_angle_ = start_angle;
			SafeAccess(enemies, idx).end_angle_ = end_angle;
		}
		SafeAccess(enemies, idx).angle_ease_type_ = angle_ease_type;
		SafeAccess(enemies, idx).angle_ease_time_ = angle_ease_time;
		SafeAccess(enemies, idx).start_speed_ = start_speed;
		SafeAccess(enemies, idx).end_speed_ = end_speed;
		SafeAccess(enemies, idx).speed_ease_type_ = speed_ease_type;
		SafeAccess(enemies, idx).speed_ease_time_ = speed_ease_time;
		SafeAccess(enemies, idx).pop_t_ = t;
		SafeAccess(enemies, idx).length_ = 0;
		SafeAccess(enemies, idx).width_ = 0;
		SafeAccess(enemies, idx).front_node_ = 0;
		SafeAccess(enemies, idx).current_node_num_ = 0;
		SafeAccess(enemies, idx).order_ = enemy_index++;
		SafeAccess(enemies, idx).index_ = idx;
		SafeAccess(enemies, idx).id_ = id;
		SafeAccess(enemies, idx).priority_ = priority;
		SafeAccess(enemies, idx).params_ = params;
		return 0;
	}

	void CreateEnemyGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int way, double spread, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se, int id, int priority, const std::vector<std::any>& params) {
		sound_mng_.ReserveSe(se);
		switch (aim) {
		case kAimFalse:
			for (int i = 0; i < way; i++) {
				if (CreateEnemy(pos, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 0, spread / way * i + start_angle - spread / 2, spread / way * i + end_angle - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, priority, params)) return;
			}
			break;
		case kAimTrue:
			for (int i = 0; i < way; i++) {
				if (CreateEnemy(pos, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 1, spread / way * i + start_angle - spread / 2, spread / way * i + end_angle - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, priority, params)) return;
			}
			break;
		case kAimOffset:
			for (int i = 0; i < way; i++) {
				if (CreateEnemy(pos, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 1, spread / way * i + start_angle + spread / (way * 2) - spread / 2, spread / way * i + end_angle + spread / (way * 2) - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, priority, params)) return;
			}
			break;
		default:
			for (int i = 0; i < way; i++) {
				if (CreateEnemy(pos, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 0, spread / way * i + start_angle - spread / 2, spread / way * i + end_angle - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, priority, params)) return;
			}
			break;
		}
	}

	void CreateSimpleEnemyGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, double col_size, double size, int way, double spread, int aim, double angle, double speed, int se, int id, const std::vector<std::any>& params) {
		sound_mng_.ReserveSe(se);
		switch (aim) {
		case kAimFalse:
			for (int i = 0; i < way; i++) {
				if (CreateEnemy(pos, color, style, blend, pal, 1, col_size, col_size, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, 0, params)) return;
			}
			break;
		case kAimTrue:
			for (int i = 0; i < way; i++) {
				if (CreateEnemy(pos, color, style, blend, pal, 0, col_size, col_size, 0, 0, size, size, 0, 0, 1, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, 0, params)) return;
			}
			break;
		case kAimOffset:
			for (int i = 0; i < way; i++) {
				if (CreateEnemy(pos, color, style, blend, pal, 1, col_size, col_size, 0, 0, size, size, 0, 0, 1, spread / way * i + angle + spread / (way * 2) - spread / 2, spread / way * i + angle + spread / (way * 2) - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, 0, params)) return;
			}
			break;
		default:
			for (int i = 0; i < way; i++) {
				if (CreateEnemy(pos, color, style, blend, pal, 1, col_size, col_size, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, 0, params)) return;
			}
			break;
		}
	}

	void CreateSmartEnemyGroup(ObjectParams param) {
		sound_mng_.ReserveSe(param.se);
		switch (param.aim) {
		case kAimFalse:
			for (int i = 0; i < param.way; i++) {
				if (CreateEnemy(param.pos, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 0, param.spread / param.way * i + param.start_angle - param.spread / 2, param.spread / param.way * i + param.end_angle - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, kSoundEffectNone, param.id, param.priority, param.params)) return;
			}
			break;
		case kAimTrue:
			for (int i = 0; i < param.way; i++) {
				if (CreateEnemy(param.pos, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 1, param.spread / param.way * i + param.start_angle - param.spread / 2, param.spread / param.way * i + param.end_angle - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, kSoundEffectNone, param.id, param.priority, param.params)) return;
			}
			break;
		case kAimOffset:
			for (int i = 0; i < param.way; i++) {
				if (CreateEnemy(param.pos, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 1, param.spread / param.way * i + param.start_angle + param.spread / (param.way * 2) - param.spread / 2, param.spread / param.way * i + param.end_angle + param.spread / (param.way * 2) - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, kSoundEffectNone, param.id, param.priority, param.params)) return;
			}
			break;
		default:
			for (int i = 0; i < param.way; i++) {
				if (CreateEnemy(param.pos, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 0, param.spread / param.way * i + param.start_angle - param.spread / 2, param.spread / param.way * i + param.end_angle - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, kSoundEffectNone, param.id, param. priority, param.params)) return;
			}
			break;
		}
	}

	void ParallelUpdateEnemies(std::array<Enemy, kMaxEnemy>& enemies) {
		std::for_each(std::execution::par, enemies.begin(), enemies.end(),
			[](Enemy& E) {
				E.UpdateObject();
			});
	}

	void MoveEnemies() {
		ParallelUpdateEnemies(enemies);
	}

	void RenderEnemies() {
		std::sort(std::execution::par, enemy_ptrs.begin(), enemy_ptrs.end(), [](const Enemy* a, const Enemy* b) {
			if (a->priority_ == b->priority_) {
				return a->order_ < b->order_;
			}
			return a->priority_ < b->priority_;
			});
		for (auto* E : enemy_ptrs) {
			E->DrawObject();
		}
	}

	void LuaEnemyInit(sol::state& lua) {
		lua.set_function("create_enemy", CreateEnemy);
		lua.set_function("create_enemy_group", CreateEnemyGroup);
		lua.set_function("create_simple_enemy_group", CreateSimpleEnemyGroup);
	}
}