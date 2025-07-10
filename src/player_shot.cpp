#include "player_shot.h"

#include <cmath>

#include "debug.h"
#include "enemy.h"
#include "object.h"
#include "player.h"
#include "vec2d.h"

namespace zenithstg {
	std::array<PlayerShot, kMaxPlayerShot> player_shots;
	std::array<PlayerShot*, kMaxPlayerShot> player_shot_ptrs;
	std::vector<int> blank_player_shots;
	std::mutex blank_player_shot_mutex;
	std::array<int, kGraphicHandlerNum> default_player_shot_blend;
	std::array<double, kGraphicHandlerNum> draw_ratio_player_shot_graphs;

	void PlayerShot::ShowPlayerShot() {
		if (!(flags_ & kIsAlive)) return;
		if (blend_ == -1) {
			SmartSetDrawBlendMode(SafeAccess(default_player_shot_blend, style_), pal_);
			SetDrawBright(color_.GetR(), color_.GetG(), color_.GetB());
			SetDrawMode(DX_DRAWMODE_BILINEAR);
			DrawRotaGraph(pos_.GetX(), pos_.GetY(), size_, -show_angle_, SafeAccess(img_res.shot_gh, style_), TRUE);
			SetDrawBright(255, 255, 255);
			SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			SetDrawMode(DX_DRAWMODE_NEAREST);
		}
		else {
			SmartSetDrawBlendMode(blend_, pal_);
			SetDrawBright(color_.GetR(), color_.GetG(), color_.GetB());
			SetDrawMode(DX_DRAWMODE_BILINEAR);
			DrawRotaGraph(pos_.GetX(), pos_.GetY(), size_, -show_angle_, SafeAccess(img_res.shot_gh, style_), TRUE);
			SetDrawBright(255, 255, 255);
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

	int PlayerShot::ColliCheckObject() {
		//TODO: 敵との接触判定を実装する / Implement collision detection with enemies.
		return 0;
	}

	int PlayerShot::CheckPosBounds() {
		double limit = size_ * 128 * 2 * SafeAccess(draw_ratio_player_shot_graphs, style_);
		if (pos_.GetX() < kBorderLeft - limit) return 1;
		if (pos_.GetX() > kBorderRight + limit) return 1;
		if (pos_.GetY() < kBorderUp - limit) return 1;
		if (pos_.GetY() > kBorderDown + limit) return 1;

		return 0;
	}

	int PlayerShot::CheckCollisionAndBounds() {
		if (flags_ & kIsCol) {
			if (ColliCheckObject()) {
				PushBlankPlayerShots(index_);
				flags_ &= ~kIsAlive;
				return 1;
			}
		}
		if (CheckPosBounds()) {
			PushBlankPlayerShots(index_);
			flags_ &= ~kIsAlive;
			return 1;
		}
		return 0;
	}

	void PlayerShot::MoveFunc() {
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

	void PushBlankPlayerShots(int idx) {
		std::lock_guard<std::mutex> lock(blank_player_shot_mutex);
		blank_player_shots.emplace_back(idx);
	}

	int CreatePlayerShot(const Vec2D& pos, const Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se, int id, const std::vector<std::any>& params) {
		sound_mng_.ReserveSe(se);
		if (blank_player_shots.empty()) return 1;
		int idx = blank_player_shots.back();
		blank_player_shots.pop_back();
		SafeAccess(player_shots, idx).flags_ = kIsAlive | is_col * kIsCol;
		SafeAccess(player_shots, idx).obj_type_ = kObjectPlayerShot;
		SafeAccess(player_shots, idx).pos_ = pos;
		SafeAccess(player_shots, idx).color_ = color;
		SafeAccess(player_shots, idx).style_ = style;
		SafeAccess(player_shots, idx).blend_ = blend;
		SafeAccess(player_shots, idx).pal_ = pal;
		SafeAccess(player_shots, idx).start_col_size_ = start_col_size;
		SafeAccess(player_shots, idx).end_col_size_ = end_col_size;
		SafeAccess(player_shots, idx).col_size_ease_type_ = col_size_ease_type;
		SafeAccess(player_shots, idx).col_size_ease_time_ = col_size_ease_time;
		SafeAccess(player_shots, idx).start_size_ = start_size;
		SafeAccess(player_shots, idx).end_size_ = end_size;
		SafeAccess(player_shots, idx).size_ease_type_ = size_ease_type;
		SafeAccess(player_shots, idx).size_ease_time_ = size_ease_time;
		SafeAccess(player_shots, idx).start_angle_ = start_angle;
		SafeAccess(player_shots, idx).end_angle_ = end_angle;
		SafeAccess(player_shots, idx).angle_ease_type_ = angle_ease_type;
		SafeAccess(player_shots, idx).angle_ease_time_ = angle_ease_time;
		SafeAccess(player_shots, idx).start_speed_ = start_speed;
		SafeAccess(player_shots, idx).end_speed_ = end_speed;
		SafeAccess(player_shots, idx).speed_ease_type_ = speed_ease_type;
		SafeAccess(player_shots, idx).speed_ease_time_ = speed_ease_time;
		SafeAccess(player_shots, idx).pop_t_ = t;
		SafeAccess(player_shots, idx).length_ = 0;
		SafeAccess(player_shots, idx).width_ = 0;
		SafeAccess(player_shots, idx).front_node_ = 0;
		SafeAccess(player_shots, idx).current_node_num_ = 0;
		SafeAccess(player_shots, idx).index_ = idx;
		SafeAccess(player_shots, idx).id_ = 0;
		SafeAccess(player_shots, idx).params_ = params;
		return 0;
	}

	void ParallelUpdatePlayerShots(std::array<PlayerShot, kMaxPlayerShot>& playerShots) {
		std::for_each(std::execution::par_unseq, playerShots.begin(), playerShots.end(),
			[](PlayerShot& PS) {
				PS.UpdateObject();
			});
	}

	void MovePlayerShots() {
		ParallelUpdatePlayerShots(player_shots);
		for (auto* PS : player_shot_ptrs) {
			PS->ShowPlayerShot();
		}
		if (t % 10 == 0) {
			std::sort(player_shot_ptrs.begin(), player_shot_ptrs.end(), [](const PlayerShot* a, const PlayerShot* b) {
				return a->pop_t_ < b->pop_t_;
				});
		}
	}
}