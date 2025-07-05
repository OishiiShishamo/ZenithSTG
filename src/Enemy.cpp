#include "Main.h"

#include "Bullet.h"
#include "Particle.h"
#include "Enemy.h"
#include "Laser.h"
#include "Object.h"
#include "Player.h"
#include "player_shot.h"
#include "Vec2D.h"

//TODO: 引数減らしたラッパー関数作る

std::array<Enemy, kMaxEnemy> enemies;
std::array<Enemy*, kMaxEnemy> enemy_ptrs;
std::vector<int> blank_enemies;
std::mutex blank_enemy_mutex;
std::array<int, kGraphicHandlerNum> default_enemy_blend;
std::array<double, kGraphicHandlerNum> draw_ratio_enemy_graphs;

void
Enemy::ShowEnemy() {
	if (!(flags & kIsAlive)) return;
	if (blend == -1) {
		SmartSetDrawBlendMode(SafeAccess(default_enemy_blend, style), pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(pos.GetX(), pos.GetY(), size, -show_angle, SafeAccess(img_res.enemy_gh, style), TRUE);
		SetDrawBright(255, 255, 255);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(pos.GetX(), pos.GetY(), size, -show_angle, SafeAccess(img_res.enemy_gh, style), TRUE);
		SetDrawBright(255, 255, 255);
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
Enemy::ColliCheckObject() {
	if (ColCircleAndCircle(pos, Plyr.pos, col_size + Plyr.col_size)) {
		Plyr.HitPlayer();
		return 1;
	}
	return 0;
}

int
Enemy::CheckPosBounds() {
	double limit = size * 128 * 2 * SafeAccess(draw_ratio_enemy_graphs, style);
	if (pos.GetX() < kBorderLeft - limit) return 1;
	if (pos.GetX() > kBorderRight + limit) return 1;
	if (pos.GetY() < kBorderUp - limit) return 1;
	if (pos.GetY() > kBorderDown + limit) return 1;

	return 0;
}

int
Enemy::CheckCollisionAndBounds() {
	if (flags & kIsCol) {
		if (ColliCheckObject()) {
			PushBlankEnemies(index);
			flags &= ~kIsAlive;
			return 1;
		}
	}
	if (CheckPosBounds()) {
		PushBlankEnemies(index);
		flags &= ~kIsAlive;
		return 1;
	}
	return 0;
}

void
Enemy::MoveFunc() {
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
PushBlankEnemies(int idx) {
	std::lock_guard<std::mutex> lock(blank_enemy_mutex);
	blank_enemies.emplace_back(idx);
}

int
CreateEnemy(const Vec2D& pos, const Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se, int id, const std::vector<std::any>& params) {
	sound_mng_.ReserveSe(se);
	if (blank_enemies.empty()) return 1;
	int idx = blank_enemies.back();
	blank_enemies.pop_back();
	SafeAccess(enemies, idx).flags = kIsAlive | is_col * kIsCol;
	SafeAccess(enemies, idx).obj_type = kObjectEnemy;
	SafeAccess(enemies, idx).pos = pos;
	SafeAccess(enemies, idx).color = color;
	SafeAccess(enemies, idx).style = style;
	SafeAccess(enemies, idx).blend = blend;
	SafeAccess(enemies, idx).pal = pal;
	SafeAccess(enemies, idx).start_col_size = start_col_size;
	SafeAccess(enemies, idx).end_col_size = end_col_size;
	SafeAccess(enemies, idx).col_size_ease_type = col_size_ease_type;
	SafeAccess(enemies, idx).col_size_ease_time = col_size_ease_time;
	SafeAccess(enemies, idx).start_size = start_size;
	SafeAccess(enemies, idx).end_size = end_size;
	SafeAccess(enemies, idx).size_ease_type = size_ease_type;
	SafeAccess(enemies, idx).size_ease_time = size_ease_time;
	if (aim == kAimTrue) {
		SafeAccess(enemies, idx).start_angle = Plyr.AimPlayer(pos) + start_angle;
		SafeAccess(enemies, idx).end_angle = Plyr.AimPlayer(pos) + end_angle;
	}
	else {
		SafeAccess(enemies, idx).start_angle = start_angle;
		SafeAccess(enemies, idx).end_angle = end_angle;
	}
	SafeAccess(enemies, idx).angle_ease_type = angle_ease_type;
	SafeAccess(enemies, idx).angle_ease_time = angle_ease_time;
	SafeAccess(enemies, idx).start_speed = start_speed;
	SafeAccess(enemies, idx).end_speed = end_speed;
	SafeAccess(enemies, idx).speed_ease_type = speed_ease_type;
	SafeAccess(enemies, idx).speed_ease_time = speed_ease_time;
	SafeAccess(enemies, idx).pop_t = t;
	SafeAccess(enemies, idx).length = 0;
	SafeAccess(enemies, idx).width = 0;
	SafeAccess(enemies, idx).front_node = 0;
	SafeAccess(enemies, idx).current_node_num = 0;
	SafeAccess(enemies, idx).index = idx;
	SafeAccess(enemies, idx).id = id;
	SafeAccess(enemies, idx).params = params;
	return 0;
}

void
CreateEnemyGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int way, double spread, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se, int id, const std::vector<std::any>& params) {
	sound_mng_.ReserveSe(se);
	switch (aim) {
	case kAimFalse:
		for (int i = 0; i < way; i++) {
			if (CreateEnemy(pos, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 0, spread / way * i + start_angle - spread / 2, spread / way * i + end_angle - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, params)) return;
		}
		break;
	case kAimTrue:
		for (int i = 0; i < way; i++) {
			if (CreateEnemy(pos, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 1, spread / way * i + start_angle - spread / 2, spread / way * i + end_angle - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, params)) return;
		}
		break;
	case kAimOffset:
		for (int i = 0; i < way; i++) {
			if (CreateEnemy(pos, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 1, spread / way * i + start_angle + spread / (way * 2) - spread / 2, spread / way * i + end_angle + spread / (way * 2) - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, params)) return;
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			if (CreateEnemy(pos, color, style, blend, pal, is_col, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, 0, spread / way * i + start_angle - spread / 2, spread / way * i + end_angle - spread / 2, angle_ease_type, angle_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, kSoundEffectNone, id, params)) return;
		}
		break;
	}
}

void
CreateSimpleEnemyGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, double col_size, double size, int way, double spread, int aim, double angle, double speed, int se, int id, const std::vector<std::any>& params) {
	sound_mng_.ReserveSe(se);
	switch (aim) {
	case kAimFalse:
		for (int i = 0; i < way; i++) {
			if (CreateEnemy(pos, color, style, blend, pal, 1, col_size, col_size, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, params)) return;
		}
		break;
	case kAimTrue:
		for (int i = 0; i < way; i++) {
			if (CreateEnemy(pos, color, style, blend, pal, 0, col_size, col_size, 0, 0, size, size, 0, 0, 1, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, params)) return;
		}
		break;
	case kAimOffset:
		for (int i = 0; i < way; i++) {
			if (CreateEnemy(pos, color, style, blend, pal, 1, col_size, col_size, 0, 0, size, size, 0, 0, 1, spread / way * i + angle + spread / (way * 2) - spread / 2, spread / way * i + angle + spread / (way * 2) - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, params)) return;
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			if (CreateEnemy(pos, color, style, blend, pal, 1, col_size, col_size, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, kSoundEffectNone, id, params)) return;
		}
		break;
	}
}

void
CreateSmartEnemyGroup(ObjectParams param) {
	sound_mng_.ReserveSe(param.se);
	switch (param.aim) {
	case kAimFalse:
		for (int i = 0; i < param.way; i++) {
			if (CreateEnemy(param.pos, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 0, param.spread / param.way * i + param.start_angle - param.spread / 2, param.spread / param.way * i + param.end_angle - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, kSoundEffectNone, param.id, param.params)) return;
		}
		break;
	case kAimTrue:
		for (int i = 0; i < param.way; i++) {
			if (CreateEnemy(param.pos, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 1, param.spread / param.way * i + param.start_angle - param.spread / 2, param.spread / param.way * i + param.end_angle - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, kSoundEffectNone, param.id, param.params)) return;
		}
		break;
	case kAimOffset:
		for (int i = 0; i < param.way; i++) {
			if (CreateEnemy(param.pos, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 1, param.spread / param.way * i + param.start_angle + param.spread / (param.way * 2) - param.spread / 2, param.spread / param.way * i + param.end_angle + param.spread / (param.way * 2) - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, kSoundEffectNone, param.id, param.params)) return;
		}
		break;
	default:
		for (int i = 0; i < param.way; i++) {
			if (CreateEnemy(param.pos, param.color, param.style, param.blend, param.pal, param.is_col, param.start_col_size, param.end_col_size, param.col_size_ease_type, param.col_size_ease_time, param.start_size, param.end_size, param.size_ease_type, param.size_ease_time, 0, param.spread / param.way * i + param.start_angle - param.spread / 2, param.spread / param.way * i + param.end_angle - param.spread / 2, param.angle_ease_type, param.angle_ease_time, param.start_speed, param.end_speed, param.speed_ease_type, param.speed_ease_time, kSoundEffectNone, param.id, param.params)) return;
		}
		break;
	}
}

void
ParallelUpdateEnemies(std::array<Enemy, kMaxEnemy>& enemies) {
	std::for_each(std::execution::par_unseq, enemies.begin(), enemies.end(),
		[](Enemy& E) {
			E.UpdateObject();
		});
}

void
MoveEnemies() {
	ParallelUpdateEnemies(enemies);
	for (auto* E : enemy_ptrs) {
		E->ShowEnemy();
	}
	if (t % 10 == 0) {
		std::sort(enemy_ptrs.begin(), enemy_ptrs.end(), [](const Enemy* a, const Enemy* b) {
			return a->pop_t < b->pop_t;
			});
	}
}