#include "Main.h"

#include "Bullet.h"
#include "Particle.h"
#include "Enemy.h"
#include "Laser.h"
#include "Object.h"
#include "Player.h"
#include "playerShot.h"
#include "Vec2D.h"

std::array<playerShot, kMaxPlayerShot> player_shots;
std::array<playerShot*, kMaxPlayerShot> player_shot_ptrs;
std::vector<int> blank_player_shots;
std::mutex blank_player_shot_mutex;
std::array<int, kGraphicHandlerNum> default_player_shot_blend;
std::array<double, kGraphicHandlerNum> draw_ratio_player_shot_graphs;

void
playerShot::ShowPlayerShot() {
	if (!(flags & kIsAlive)) return;
	if (blend == -1) {
		SmartSetDrawBlendMode(SafeAccess(default_player_shot_blend, style), pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(pos.GetX(), pos.GetY(), size, -show_angle, SafeAccess(img_res.shot_gh, style), TRUE);
		SetDrawBright(255, 255, 255);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(pos.GetX(), pos.GetY(), size, -show_angle, SafeAccess(img_res.shot_gh, style), TRUE);
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
playerShot::ColliCheckObject() {
	//TODO: 敵との接触判定を実装する / Implement collision detection with enemies.
	return 0;
}

int
playerShot::CheckPosBounds() {
	double limit = size * 128 * 2 * SafeAccess(draw_ratio_player_shot_graphs, style);
	if (pos.GetX() < kBorderLeft - limit) return 1;
	if (pos.GetX() > kBorderRight + limit) return 1;
	if (pos.GetY() < kBorderUp - limit) return 1;
	if (pos.GetY() > kBorderDown + limit) return 1;

	return 0;
}

int
playerShot::CheckCollisionAndBounds() {
	if (flags & kIsCol) {
		if (ColliCheckObject()) {
			PushBlankPlayerShots(index);
			flags &= ~kIsAlive;
			return 1;
		}
	}
	if (CheckPosBounds()) {
		PushBlankPlayerShots(index);
		flags &= ~kIsAlive;
		return 1;
	}
	return 0;
}

void
playerShot::MoveFunc() {
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
PushBlankPlayerShots(int idx) {
	std::lock_guard<std::mutex> lock(blank_player_shot_mutex);
	blank_player_shots.emplace_back(idx);
}

int
CreatePlayerShot(const Vec2D& pos, const Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se, int id, const std::vector<std::any>& params) {
	sound_mng_.ReserveSe(se);
	if (blank_player_shots.empty()) return 1;
	int idx = blank_player_shots.back();
	blank_player_shots.pop_back();
	SafeAccess(player_shots, idx).flags = kIsAlive | is_col * kIsCol;
	SafeAccess(player_shots, idx).obj_type = kObjectPlayerShot;
	SafeAccess(player_shots, idx).pos = pos;
	SafeAccess(player_shots, idx).color = color;
	SafeAccess(player_shots, idx).style = style;
	SafeAccess(player_shots, idx).blend = blend;
	SafeAccess(player_shots, idx).pal = pal;
	SafeAccess(player_shots, idx).start_col_size = start_col_size;
	SafeAccess(player_shots, idx).end_col_size = end_col_size;
	SafeAccess(player_shots, idx).col_size_ease_type = col_size_ease_type;
	SafeAccess(player_shots, idx).col_size_ease_time = col_size_ease_time;
	SafeAccess(player_shots, idx).start_size = start_size;
	SafeAccess(player_shots, idx).end_size = end_size;
	SafeAccess(player_shots, idx).size_ease_type = size_ease_type;
	SafeAccess(player_shots, idx).size_ease_time = size_ease_time;
	SafeAccess(player_shots, idx).start_angle = start_angle;
	SafeAccess(player_shots, idx).end_angle = end_angle;
	SafeAccess(player_shots, idx).angle_ease_type = angle_ease_type;
	SafeAccess(player_shots, idx).angle_ease_time = angle_ease_time;
	SafeAccess(player_shots, idx).start_speed = start_speed;
	SafeAccess(player_shots, idx).end_speed = end_speed;
	SafeAccess(player_shots, idx).speed_ease_type = speed_ease_type;
	SafeAccess(player_shots, idx).speed_ease_time = speed_ease_time;
	SafeAccess(player_shots, idx).pop_t = t;
	SafeAccess(player_shots, idx).length = 0;
	SafeAccess(player_shots, idx).width = 0;
	SafeAccess(player_shots, idx).front_node = 0;
	SafeAccess(player_shots, idx).current_node_num = 0;
	SafeAccess(player_shots, idx).index = idx;
	SafeAccess(player_shots, idx).id = 0;
	SafeAccess(player_shots, idx).params = params;
	return 0;
}

void
ParallelUpdatePlayerShots(std::array<playerShot, kMaxPlayerShot>& playerShots) {
	std::for_each(std::execution::par_unseq, playerShots.begin(), playerShots.end(),
		[](playerShot& PS) {
			PS.UpdateObject();
		});
}

void
MovePlayerShots() {
	ParallelUpdatePlayerShots(player_shots);
	for (auto* PS : player_shot_ptrs) {
		PS->ShowPlayerShot();
	}
	if (t % 10 == 0) {
		std::sort(player_shot_ptrs.begin(), player_shot_ptrs.end(), [](const playerShot* a, const playerShot* b) {
			return a->pop_t < b->pop_t;
			});
	}
}