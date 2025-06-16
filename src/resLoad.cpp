#include "Main.h"

#include "resLoad.h"
#include "Player.h"
#include "Color.h"


void
resLoad::UIGHLoad() {
	SAFE_ACCESS(imgRes.UIGH, 0) = (LoadGraph("res/img/ui/UI_Frame.png"));
	SAFE_ACCESS(imgRes.UIGH, 1) = (LoadGraph("res/img/ui/Weak_Point.png"));
}

void
resLoad::BulletGHLoad() {
	LoadDivGraph("res/img/bullet/Bullet_Back.png", 256, 16, 16, 128, 128, imgRes.BulletBackGH.data());
	LoadDivGraph("res/img/bullet/Bullet_Front.png", 256, 16, 16, 128, 128, imgRes.BulletFrontGH.data());
}

void
resLoad::EffectGHLoad() {
	LoadDivGraph("res/img/effect/Effect_Back.png", 256, 16, 16, 128, 128, imgRes.EffectBackGH.data());
	LoadDivGraph("res/img/effect/Effect_Front.png", 256, 16, 16, 128, 128, imgRes.EffectFrontGH.data());
}

void
resLoad::EnemyGHLoad() {
	LoadDivGraph("res/img/enemy/Enemy.png", 256, 16, 16, 128, 128, imgRes.EnemyGH.data());
}

void
resLoad::FaceGHLoad() {
}

void
resLoad::PlayerGHLoad() {
	for (int i = 0; i < PLAYER_NUM; i++) {
		std::string tmp = "res/img/player/" + std::to_string(i) + ".png";
		SAFE_ACCESS(imgRes.PlayerGH, i) = (LoadGraph(tmp.c_str()));
	}
}

void
resLoad::ShotGHLoad() {
	SAFE_ACCESS(imgRes.ShotGH, 0) = (LoadGraph("res/img/shot/0.png"));
}

void
resLoad::FontLoad() {
	SAFE_ACCESS(fontTypes, UI_0) = CreateFontToHandle("Meiryo UI", 20, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	SAFE_ACCESS(fontTypes, UI_1) = CreateFontToHandle("Meiryo UI", 40, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	int i = 0;
	for (auto& F : fontTypes) {
		if (F == -1) {
			Logger("FontID: " + std::to_string(i) + " FontLoading Fail.", logType::LOG_WARNING);
		}
		i++;
	}
}