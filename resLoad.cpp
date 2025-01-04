#include "Main.h"

#include "resLoad.h"
#include "Player.h"
#include "Color.h"

void
resLoad::UIGHLoad() {
	imgRes.UIGH[0] = LoadGraph("res/img/ui/UI_Frame.png");
	imgRes.UIGH[1] = LoadGraph("res/img/ui/Weak_Point.png");
}

void
resLoad::BulletGHLoad() {
	LoadDivGraph("res/img/bullet/Bullet_Back.png", 256, 16, 16, 128, 128, imgRes.BulletBackGH);
	LoadDivGraph("res/img/bullet/Bullet_Front.png", 256, 16, 16, 128, 128, imgRes.BulletFrontGH);
}

void
resLoad::EnemyGHLoad() {
	imgRes.EnemyGH[0] = LoadGraph("res/img/enemy/a.png");
}

void
resLoad::PlayerGHLoad() {
	for (int i = 0; i < PLAYER_NUM; i++) {
		std::string tmp = "res/img/player/" + std::to_string(i) + ".png";
		imgRes.PlayerGH[0] = LoadGraph(tmp.c_str());
	}
}