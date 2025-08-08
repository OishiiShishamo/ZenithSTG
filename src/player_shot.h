/**
* @file playerShot.h
* @brief プレイヤーショット関連 / Player Shot Related.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef ZENITHSTG_SRC_PLAYERSHOT_H_
#define ZENITHSTG_SRC_PLAYERSHOT_H_

#include <cmath>

#include "debug.h"
#include "enemy.h"
#include "object.h"
#include "player.h"
#include "vec2d.h"

namespace zenithstg {
	class PlayerShot : public Object {
	public:
		PlayerShot() = default;
		PlayerShot(int alive, int is_col, const Vec2D& pos, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_show_angle, double end_show_angle, int show_angle_ease_type, int show_angle_ease_time, const Color& color, int style, int blend, int pal, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int pop_t, int id = 0, const std::vector<std::any>& params = {})
			: Object(alive, is_col, kObjectPlayerShot, pos, start_angle, end_angle, angle_ease_type, angle_ease_time, start_show_angle, end_show_angle, show_angle_ease_type, show_angle_ease_time, color, style, blend, pal, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, pop_t, 0, 0, 0, 0, 0, 0, 0, id, params) {
		}

		/**
		* @brief プレイヤーショットの描画 / Player Shot Drawing.
		*/
		void ShowPlayerShot();
	private:
		void MoveFunc() override;
		void KillObject() override;
		int ColliCheckObject() override;
		int CheckPosBounds() override;
		int CheckCollisionAndBounds() override;
	};

	void PushBlankPlayerShots(int idx);

	/**
	* @brief プレイヤーショットの生成 / Create Player Shot.
	*
	* @see ObjectParams 引数の詳細はこちらを参照 / See here for details of the argument.
	*/
	int CreatePlayerShot(const Vec2D& pos, const Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se = kSoundEffectNone, int id = 0, const std::vector<std::any>& params = {});

	void ParallelUpdatePlayerShots(std::array<PlayerShot, kMaxPlayerShot>& playerShots);

	/**
	* @brief プレイヤーショットの動作と描画 / Player Shot Movement and Drawing.
	*/
	void MovePlayerShots();

	void RenderPlayerShots();
}

#endif