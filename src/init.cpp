#include "init.h"

#include "DxLib.h"

#include "property.h"
#include "player.h"
#include "res_load.h"
#include "sound.h"

ResLoad res;
ImageRes img_res;
Property properties_;

std::array<int, kFontTypeNum> font_types;

int num_threads = std::thread::hardware_concurrency();

void
Init() {
	boost::property_tree::ptree pt;
	boost::property_tree::read_xml("ZenithSTG_property.xml", pt);
	if (boost::optional<std::string> title = pt.get_optional<std::string>("root.title")) {
		properties_.title_ = title.get();
	}
	else {
		properties_.title_ = "ZenithSTG";
	}
	if (boost::optional<int> window_size = pt.get_optional<int>("root.windowSize")) {
		properties_.window_size_ = window_size.get();
		if (properties_.window_size_ < 0 || properties_.window_size_ > 2) properties_.window_size_ = 0;
	}
	else {
		properties_.window_size_ = 0;
	}
	if (boost::optional<int> is_window = pt.get_optional<int>("root.isWindow")) {
		properties_.is_window_ = is_window.get();
		if (properties_.is_window_ < 0 || properties_.is_window_ > 1) properties_.is_window_ = 1;
	}
	else {
		properties_.is_window_ = 1;
	}
	if (boost::optional<long long> hi_score = pt.get_optional<long long>("root.hiScore")) {
		properties_.hi_score_ = hi_score.get();
		if (properties_.hi_score_ < 0) properties_.hi_score_ = 0;
	}
	else {
		properties_.hi_score_ = 0;
	}
	if (boost::optional<int> bgm_volume = pt.get_optional<int>("root.BGMVolume")) {
		properties_.bgm_volume_ = bgm_volume.get();
		if (properties_.bgm_volume_ < 0) properties_.bgm_volume_ = 0;
		if (properties_.bgm_volume_ > 100) properties_.bgm_volume_ = 100;
	}
	else {
		properties_.bgm_volume_ = properties_.bgm_volume_;
	}
	if (boost::optional<int> se_volume = pt.get_optional<int>("root.SEVolume")) {
		properties_.se_volume_ = se_volume.get();
		if (properties_.se_volume_ < 0) properties_.se_volume_ = 0;
		if (properties_.se_volume_ > 100) properties_.se_volume_ = 100;
	}
	else {
		properties_.se_volume_ = properties_.se_volume_;
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
	SetFontSize(20);

	std::srand(42);

	player.pos_ = kPlayerDefaultPos;
	player.slow_ = 5;
	player.fast_ = 7;
	player.life_ = player.default_life_;
	player.bomb_ = player.default_bomb_;
	player.col_size_ = kPlayerCol;
	player.protect_ = kPlayerProtect;
	player.protect_time_ = 0;
	player.is_mouse_ = 0;

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
}

void
ResInit() {
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
	bullet_canvas = MakeScreen(1920, 1080, 1);
	player_canvas = MakeScreen(1920, 1080, 1);
	player_shot_canvas = MakeScreen(1920, 1080, 1);
	bomb_canvas = MakeScreen(1920, 1080, 1);
	particle_canvas = MakeScreen(1920, 1080, 1);
	screen_canvas = MakeScreen(1920, 1080, 1);
	ui_canvas = MakeScreen(1920, 1080, 1);
}