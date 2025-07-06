#include "main.h"

#include "res_load.h"
#include "player.h"


void
ResLoad::UiGhLoad() {
	SafeAccess(img_res.ui_gh, 0) = (LoadGraph("res/img/ui/UI_Frame.png"));
	SafeAccess(img_res.ui_gh, 1) = (LoadGraph("res/img/ui/Weak_Point.png"));
}

void
ResLoad::BulletGhLoad() {
	LoadDivGraph("res/img/bullet/Bullet_Back.png", 256, 16, 16, 128, 128, img_res.bullet_back_gh.data());
	LoadDivGraph("res/img/bullet/Bullet_Front.png", 256, 16, 16, 128, 128, img_res.bullet_front_gh.data());
}

void
ResLoad::ParticleGhLoad() {
	LoadDivGraph("res/img/particle/Particle_Back.png", 256, 16, 16, 128, 128, img_res.particle_back_gh.data());
	LoadDivGraph("res/img/particle/Particle_Front.png", 256, 16, 16, 128, 128, img_res.particle_front_gh.data());
}

void
ResLoad::EnemyGhLoad() {
	LoadDivGraph("res/img/enemy/Enemy.png", 256, 16, 16, 128, 128, img_res.enemy_gh.data());
}

void
ResLoad::FaceGhLoad() {
}

void
ResLoad::PlayerGhLoad() {
	for (int i = 0; i < kPlayerNum; i++) {
		std::string tmp = "res/img/player/" + std::to_string(i) + ".png";
		SafeAccess(img_res.player_gh, i) = (LoadGraph(tmp.c_str()));
	}
}

void
ResLoad::ShotGhLoad() {
	SafeAccess(img_res.shot_gh, 0) = (LoadGraph("res/img/shot/0.png"));
}

void
ResLoad::FontLoad() {
	SafeAccess(font_types, kFontUi0) = CreateFontToHandle("Meiryo UI", 20, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	SafeAccess(font_types, kFontUi1) = CreateFontToHandle("Meiryo UI", 40, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	int i = 0;
	for (auto& F : font_types) {
		if (F == -1) {
			Logger("Fontid: " + std::to_string(i) + " FontLoading Fail.", LogType::kLogWarning);
		}
		else {
			Logger("Fontid: " + std::to_string(i) + " FontLoading Success.", LogType::kLogInfo);
		}
		i++;
	}
}