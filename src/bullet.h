/**
* @file Bullet.h
* @brief 弾関連 / Bullet Related.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef ZENITHSTG_SRC_BULLET_H_
#define ZENITHSTG_SRC_BULLET_H_

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
#include "graze.h"
#include "object.h"
#include "params.h"
#include "player.h"
#include "sound.h"
#include "utility.h"
#include "vec2d.h"

namespace zenithstg {
	/**
	* @class Bullet
	* @brief 弾関連 / Bullet Related.
	* @extends Object
	*/
	class Bullet : public Object {
	public:
		Bullet() = default;
		Bullet(int alive, int is_col, const Vec2D& pos, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_show_angle, double end_show_angle, int show_angle_ease_type, int show_angle_ease_time, const Color& color, int style, int blend, int pal, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int pop_t, int id = 0, const std::vector<std::any>& params = {})
			: Object(alive, is_col, kObjectBullet, pos, start_angle, end_angle, angle_ease_type, angle_ease_time, start_show_angle, end_show_angle, show_angle_ease_type, show_angle_ease_time, color, style, blend, pal, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, pop_t, 0, 0, 0, 0, 0, 0, 0, id, params) {
		}

		/**
		* @brief 弾の描画 / Bullet Drawing.
		*/
		void ShowBullet();
	private:
		void MoveFunc() override;
		void KillObject() override;
		int ColliCheckObject() override;
#if kGrazeEnabled == 1
		void GrazeObject() override;
#endif
		int CheckPosBounds() override;

		int CheckCollisionAndBounds() override;
	};

	void PushBlankBullets(int idx);

	/**
	* @brief 弾の生成 / Create Bullet.
	*
	* @see ObjectParams 引数の詳細はこちらを参照 / See here for details of the argument.
	*/
	int CreateBullet(const Vec2D& pos, const Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se = kSoundEffectNone, int id = 0, const std::vector<std::any>& params = {});

	/**
	* @brief 複数の弾の生成 / Create Multiple Bullet.
	*
	* @see ObjectParams 引数の詳細はこちらを参照 / See here for details of the argument.
	*/
	void CreateBulletGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int way, double spread, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se = kSoundEffectNone, int id = 0, const std::vector<std::any>& params = {});

	/**
	* @brief 複数の弾の生成(引数減少版) / Create Multiple Bullet(reduced argument version).
	*
	* @see ObjectParams 引数の詳細はこちらを参照 / See here for details of the argument.
	*/
	void CreateSimpleBulletGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, double col_size, double size, int way, double spread, int aim, double angle, double speed, int se = kSoundEffectNone, int id = 0, const std::vector<std::any>& params = {});

	/**
	* @brief 構造体を引数とした複数の弾の生成 / Create Multiple Bullet with structure as argument.
	*
	* @see ObjectParams 引数の詳細はこちらを参照 / See here for details of the argument.
	*/
	void CreateSmartBulletGroup(ObjectParams param);

	void ParallelUpdateBullets(std::array<Bullet, kMaxBullet>& bullets);

	/**
	* @brief 弾の動作と描画 / Bullet Movement and Drawing.
	*/
	void MoveBullets();

	void RenderBullets();
}

#endif