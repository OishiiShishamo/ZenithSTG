﻿/**
* @file Laser.h
* @brief レーザー関連 / Laser Related.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef ZENITHSTG_SRC_LASER_H_
#define ZENITHSTG_SRC_LASER_H_

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

class Laser : public Object {
public:
	Laser() = default;
	Laser(int alive, int is_col, const Vec2D& pos, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_show_angle, double end_show_angle, int show_angle_ease_type, int show_angle_ease_time, zenithstg::Color color, int style, int blend, int pal, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int pop_t, double length, double width, int id = 0, const std::vector<std::any>& params = {})
		: Object(alive, is_col, kObjectLaser, pos, start_angle, end_angle, angle_ease_type, angle_ease_time, start_show_angle, end_show_angle, show_angle_ease_type, show_angle_ease_time, color, style, blend, pal, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, pop_t, length, width, 0, 0, 0, 0, 0, id, params) {
	}

	/**
	* @brief レーザーの描画 / Laser Drawing.
	*/
	void ShowLaser();
private:
	void MoveFunc() override;
	int ColliCheckObject() override;
#if kGrazeEnabled == 1
	void GrazeObject() override;
#endif
	int CheckPosBounds() override;
	int CheckCollisionAndBounds() override;
	
};

void PushBlankLasers(int idx);

/**
* @brief レーザーの生成 / Create Laser.
*
* @see ObjectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
int CreateLaser(const Vec2D& pos, double length, double width, const zenithstg::Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se = kSoundEffectNone, int id = 0, const std::vector<std::any>& params = {});

/**
* @brief 複数のレーザーの生成 / Create Multiple Laser.
*
* @see ObjectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
void CreateLaserGroup(const Vec2D& pos, double length, double width, const zenithstg::Color& color, int style, int blend, int pal, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int way, double spread, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int se = kSoundEffectNone, int id = 0, const std::vector<std::any>& params = {});

/**
* @brief 複数のレーザーの生成(引数減少版) / Create Multiple Laser(reduced argument version).
*
* @see ObjectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
void CreateSimpleLaserGroup(const Vec2D& pos, double length, double width, const zenithstg::Color& color, int style, int blend, int pal, double col_size, double size, int way, double spread, int aim, double angle, double speed, int se = kSoundEffectNone, int id = 0, const std::vector<std::any>& params = {});

/**
* @brief 構造体を引数とした複数のレーザーの生成 / Create Multiple Laser with structure as argument.
*
* @see ObjectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
void CreateSmartLaserGroup(ObjectParams param);

void ParallelUpdateLasers(std::array<Laser, kMaxLaser>& lasers);

/**
* @brief レーザーの動作と描画 / Laser Movement and Drawing.
*/
void MoveLasers();

#endif