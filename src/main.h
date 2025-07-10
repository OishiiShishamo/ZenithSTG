#pragma once
#ifndef ZENITHSTG_SRC_MAIN_H_
#define ZENITHSTG_SRC_MAIN_H_

struct ImageRes;

#define NOMINMAX

#include "base_scene.h"
#include "fps.h"
#include "game_scene.h"
#include "init.h"
#include "params.h"
#include "scene_manager.h"
#include "time_utl.h"
#include "title_scene.h"
#include "bullet.h"
#include "laser.h"
#include "enemy.h"
#include "player.h"
#include "player_shot.h"
#include "script.h"
#include "sound.h"
#include "utility.h"

#define PRINT(...) printf(__VA_ARGS__)	

#define kCenterX 960
#define kCenterY 540
#define kCenter Vec2D(kCenterX, kCenterY)

#define kBorderLeft 528
#define kBorderRight 1392
#define kBorderUp 35
#define kBorderDown 1045

#define kStageNum 1

#define kFpsHistoryLength 120

#define kGraphicHandlerNum 256

namespace zenithstg {
	struct ImageRes {
		std::array<int, kGraphicHandlerNum> ui_gh;
		std::array<int, kGraphicHandlerNum> bullet_back_gh;
		std::array<int, kGraphicHandlerNum> bullet_front_gh;
		std::array<int, kGraphicHandlerNum> particle_back_gh;
		std::array<int, kGraphicHandlerNum> particle_front_gh;
		std::array<int, kGraphicHandlerNum> enemy_gh;
		std::array<int, kGraphicHandlerNum> face_gh;
		std::array<int, kGraphicHandlerNum> player_gh;
		std::array<int, kGraphicHandlerNum> shot_gh;
		std::array<int, kGraphicHandlerNum> etc_gh;
	};

	extern ImageRes img_res;
	extern Sound sound_mng_;

	extern Property properties_;

	extern std::array<Script, kStageNum> scripts;

	extern std::array<Bullet, kMaxBullet> bullets;
	extern std::array<Bullet*, kMaxBullet> bullet_ptrs;
	extern std::vector<int> blank_bullets;
	extern std::array<Laser, kMaxLaser> lasers;
	extern std::array<Laser*, kMaxLaser> laser_ptrs;
	extern std::vector<int> blank_lasers;
	extern std::array<Enemy, kMaxEnemy> enemies;
	extern std::array<Enemy*, kMaxEnemy> enemy_ptrs;
	extern std::vector<int> blank_enemies;
	extern std::array<PlayerShot, kMaxPlayerShot> player_shots;
	extern std::array<PlayerShot*, kMaxPlayerShot> player_shot_ptrs;
	extern std::vector<int> blank_player_shots;
	extern std::array<Particle, kMaxParticle> particles;
	extern std::array<Particle*, kMaxParticle> particle_ptrs;
	extern std::vector<int> blank_particles;

	extern std::random_device rng;

	extern int num_threads;

	extern long long t;
	extern long long fps;
	extern int current_blend_mode;
	extern int current_blend_pal;
	extern std::array<double, kFpsHistoryLength> fps_history;
	extern std::array<int, kGraphicHandlerNum> default_bullet_blend;
	extern std::array<int, kGraphicHandlerNum> default_enemy_blend;
	extern std::array<int, kGraphicHandlerNum> default_player_shot_blend;
	extern std::array<int, kGraphicHandlerNum> default_particle_blend;
	extern std::array<double, kGraphicHandlerNum> draw_ratio_bullet_graphs;
	extern std::array<double, kGraphicHandlerNum> draw_ratio_enemy_graphs;
	extern std::array<double, kGraphicHandlerNum> draw_ratio_player_shot_graphs;
	extern std::array<double, kGraphicHandlerNum> draw_ratio_particle_graphs;
	extern int fps_history_index;

	extern double rand_tmp;

	extern std::atomic<long long> score;
	extern std::atomic<long long> graze;

	extern double screen_size_rate;
	extern double screen_rota_x;
	extern double screen_rota_y;
	extern double screen_rota_z;
}

#endif