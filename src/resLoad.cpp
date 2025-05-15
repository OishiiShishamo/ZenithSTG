#include "Main.h"

#include "resLoad.h"
#include "Player.h"
#include "Color.h"


void
resLoad::UIGHLoad() {
	imgRes.UIGH.emplace_back(LoadGraph("res/img/ui/UI_Frame.png"));
	imgRes.UIGH.emplace_back(LoadGraph("res/img/ui/Weak_Point.png"));
}

void
resLoad::BulletGHLoad() {
	imgRes.BulletBackGH.resize(256);
	imgRes.BulletFrontGH.resize(256);
	LoadDivGraph("res/img/bullet/Bullet_Back.png", 256, 16, 16, 128, 128, imgRes.BulletBackGH.data());
	LoadDivGraph("res/img/bullet/Bullet_Front.png", 256, 16, 16, 128, 128, imgRes.BulletFrontGH.data());
}

void
resLoad::EnemyGHLoad() {
	imgRes.EnemyGH.resize(256);
	LoadDivGraph("res/img/enemy/Enemy.png", 256, 16, 16, 128, 128, imgRes.EnemyGH.data());
}

void
resLoad::FaceGHLoad() {
}

void
resLoad::PlayerGHLoad() {
	for (int i = 0; i < PLAYER_NUM; i++) {
		std::string tmp = "res/img/player/" + std::to_string(i) + ".png";
		imgRes.PlayerGH.emplace_back(LoadGraph(tmp.c_str()));
	}
}

void
resLoad::ShotGHLoad() {
	imgRes.ShotGH.emplace_back(LoadGraph("res/img/shot/0.png"));
}

void
resLoad::FontLoad() {
	SAFE_ACCESS(fontTypes, UI_0) = CreateFontToHandle("Meiryo UI", 20, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	SAFE_ACCESS(fontTypes, UI_1) = CreateFontToHandle("Meiryo UI", 40, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	int i = 0;
	for (auto& F : fontTypes) {
		if (F == -1) {
			Logger("FontID: " + to_string(i) + " FontLoading Fail.", logType::LOG_WARNING);
		}
		i++;
	}
}