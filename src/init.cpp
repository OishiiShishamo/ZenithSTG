#include "init.h"

#include <algorithm>
#include <fstream>

#include "DxLib.h"
#include <json.hpp>
#include <sol.hpp>

#include "bullet.h"
#include "enemy.h"
#include "laser.h"
#include "lua_mng.h"
#include "math_tool.h"
#include "object.h"
#include "particle.h"
#include "player.h"
#include "player_shot.h"
#include "property.h"
#include "res_load.h"
#include "sound.h"

namespace zenithstg {
	ResLoad res;
	ImageRes img_res;
	Property properties_;

	std::array<int, kFontTypeNum> font_types;

	int num_threads = std::thread::hardware_concurrency();

	void Init() {
		std::ifstream f("ZenithSTG_property.json");
		if (f.is_open()) {
			nlohmann::json prop_json = nlohmann::json::parse(f, nullptr, true, true);
			f.close();
			if (prop_json.contains("title")) {
				properties_.title_ = prop_json["title"].get<std::string>();
			}
			if (prop_json.contains("window_size")) {
				properties_.window_size_ = prop_json["window_size"].get<int>();
			}
			if (prop_json.contains("is_window")) {
				properties_.is_window_ = prop_json["is_window"].get<int>();
			}
			if (prop_json.contains("hi_score")) {
				properties_.hi_score_ = prop_json["hi_score"].get<long long>();
			}
			if (prop_json.contains("bgm_volume")) {
				properties_.bgm_volume_ = prop_json["bgm_volume"].get<int>();
				properties_.bgm_volume_ = std::clamp(properties_.bgm_volume_, 0, 100);
			}
			if (prop_json.contains("se_volume")) {
				properties_.se_volume_ = prop_json["se_volume"].get<int>();
				properties_.se_volume_ = std::clamp(properties_.se_volume_, 0, 100);
			}
		}

		SetOutApplicationLogValidFlag(FALSE);
		ChangeWindowMode(properties_.is_window_);
		SetWindowText(properties_.title_.c_str());
		SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
		SetGraphMode(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 32);
		SetDoubleStartValidFlag(TRUE);
		SetAlwaysRunFlag(TRUE);
		SetUseDirect3DVersion(DX_DIRECT3D_11);
		SetUsePremulAlphaConvertLoad(TRUE);
		SetWaitVSyncFlag(FALSE);
		SetUseASyncLoadFlag(FALSE);
		SetEnableWASAPIFlag(TRUE, FALSE, 0);
		SetWindowSizeExtendRate(1.0);
		SetFontSize(20);

		timeBeginPeriod(1);

		std::srand(42);

		MathInit();

		player_.SetPos(kPlayerDefaultPos);
		player_.slow_ = 5;
		player_.fast_ = 7;
		player_.life_ = player_.default_life_;
		player_.bomb_ = player_.default_bomb_;
		player_.col_size_ = kPlayerCol;
		player_.protect_ = kPlayerProtect;
		player_.protect_time_ = 0;
		player_.SetIsMouse(0);

		fps_history.fill(fps);

		default_bullet_blend.fill(kBlendNoblend);
		SafeAccess(default_bullet_blend, kBulletLight) = kBlendAdd;
		SafeAccess(default_bullet_blend, kBulletBig) = kBlendAdd;

		default_particle_blend.fill(kBlendNoblend);
		SafeAccess(default_particle_blend, kParticleLight) = kBlendAdd;
		SafeAccess(default_particle_blend, kParticleStar) = kBlendAdd;

		default_enemy_blend.fill(kBlendNoblend);

		default_player_shot_blend.fill(kBlendNoblend);

		draw_ratio_bullet_graphs.fill(1.0f);
		SafeAccess(draw_ratio_bullet_graphs, kBulletNormal) = 0.15625f;
		SafeAccess(draw_ratio_bullet_graphs, kBulletMedium) = 0.3125f;
		SafeAccess(draw_ratio_bullet_graphs, kBulletScale) = 0.15625f;
		SafeAccess(draw_ratio_bullet_graphs, kBulletLaser) = 0.0625f;
		SafeAccess(draw_ratio_bullet_graphs, kBulletLight) = 0.25f;
		SafeAccess(draw_ratio_bullet_graphs, kBulletBig) = 0.75f;

		draw_ratio_particle_graphs.fill(1.0f);
		SafeAccess(draw_ratio_particle_graphs, kParticleLight) = 0.25f;
		SafeAccess(draw_ratio_particle_graphs, kParticleStar) = 0.125f;
		SafeAccess(draw_ratio_particle_graphs, kParticleRect) = 0.25f;

		draw_ratio_enemy_graphs.fill(1.0f);
		SafeAccess(draw_ratio_enemy_graphs, kEnemyNormal) = 0.5f;

		draw_ratio_player_shot_graphs.fill(1.0f);
		SafeAccess(draw_ratio_player_shot_graphs, kPlayerShotNormal) = 0.5f;

		for (int i = 0; i < kMaxBullet; i++) {
			SafeAccess(bullet_ptrs, i) = &SafeAccess(bullets, i);
			blank_bullets.emplace_back(i);
		}
		for (int i = 0; i < kMaxLaser; i++) {
			SafeAccess(laser_ptrs, i) = &SafeAccess(lasers, i);
			blank_lasers.emplace_back(i);
		}
		for (int i = 0; i < kMaxEnemy; i++) {
			SafeAccess(enemy_ptrs, i) = &SafeAccess(enemies, i);
			blank_enemies.emplace_back(i);
		}
		for (int i = 0; i < kMaxPlayerShot; i++) {
			SafeAccess(player_shot_ptrs, i) = &SafeAccess(player_shots, i);
			blank_player_shots.emplace_back(i);
		}
		for (int i = 0; i < kMaxParticle; i++) {
			SafeAccess(particle_ptrs, i) = &SafeAccess(particles, i);
			blank_particles.emplace_back(i);
		}

		LuaInit(lua);
	}

	void ResInit() {
		res.UiGhLoad();
		res.BulletGhLoad();
		res.ParticleGhLoad();
		res.EnemyGhLoad();
		res.FaceGhLoad();
		res.PlayerGhLoad();
		res.ShotGhLoad();
		res.FontLoad();

		sound_mng_.SoundLoad();

		background_canvas = MakeScreen(1920, 1080, 1);
		back_object_canvas = MakeScreen(1920, 1080, 1);
		front_object_canvas = MakeScreen(1920, 1080, 1);
		player_canvas = MakeScreen(1920, 1080, 1);
		bomb_canvas = MakeScreen(1920, 1080, 1);
		screen_canvas = MakeScreen(1920, 1080, 1);
		ui_canvas = MakeScreen(1920, 1080, 1);
	}
}