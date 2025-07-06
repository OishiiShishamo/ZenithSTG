#pragma once
#ifndef ZENITHSTG_SRC_PARTICLE_H_
#define ZENITHSTG_SRC_PARTICLE_H_

#include "object.h"

/**
* @class Particle
* @brief パーティクル関連 / Particle Related.
* @extends Object
*/
class Particle : public Object {
public:
	double start_pal_ = 0;
	int pal_ease_time_ = 0;
	int pal_ease_type_ = 0;
	double pal_t_ = 0;
	long long order_ = 0; // 並び順
	int index_ = 0;       // 自分のインデックス

	Particle() = default;
	Particle(int alive, int is_col, const Vec2D& pos, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_show_angle, double end_show_angle, int show_angle_ease_type, int show_angle_ease_time, const zenithstg::Color& color, int style, int blend, int pal, int palEaseTime, int palEaseType, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int pop_t, int id = 0, const std::vector<std::any>& params = {})
		: Object(alive, is_col, kObjectParticle, pos, start_angle, end_angle, angle_ease_type, angle_ease_time, start_show_angle, end_show_angle, show_angle_ease_type, show_angle_ease_time, color, style, blend, pal, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, pop_t, 0, 0, 0, 0, 0, 0, 0, id, params) {
	}

	/**
	* @brief オブジェクトの動作など。 / Object behavior, etc.
	*/
	void UpdateObject() override;

	/**
	* @brief イージングによるパラメータの更新。 / Updating parameters by easing.
	*/
	void UpdateEase() override;

	/**
	* @brief パーティクルの描画 / Particle Drawing.
	*/
	void ShowParticle();
	void MoveFunc() override;
};

/**
* @brief 空きインデックスを管理するための関数 / Function to manage blank indices.
*
* @param idx 空きインデックス / Blank index
*/
void PushBlankParticles(int idx);

/**
* @brief パーティクルの生成 / Create Particle.
*
* @see ObjectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
int CreateParticle(const Vec2D& pos, const zenithstg::Color& color, int style, int blend, double pal, int palEaseType, int palEaseTime, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int id = 0, const std::vector<std::any>& params = {});

/**
* @brief パーティクルの動作と描画 / Particle Movement and Drawing.
*/
void MoveParticles();

/**
* @brief パーティクルの並列更新 / Parallel update of particles.
*
* @param particles パーティクル配列 / Array of particles
*/
void ParallelUpdateParticles(std::array<Particle, kMaxParticle>& particles);

void GrazeParticle(const Vec2D& pos);

#endif