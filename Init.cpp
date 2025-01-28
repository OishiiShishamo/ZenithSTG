#include "Main.h"

#include "init.h"
#include "resLoad.h"
#include "Player.h"
#include "Bullet.h"
#include "Color.h"

resLoad res;

void
Init() {
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	SetWindowText("ZenithSTG");
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	SetGraphMode(1920, 1080, 32);
	SetDoubleStartValidFlag(TRUE);
	SetAlwaysRunFlag(1);
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	SetUsePremulAlphaConvertLoad(TRUE);
	SetFontSize(20);
	
	//SetCreateDrawValidGraphMultiSample(16, 8);

	Bullets.reserve(1000);

	Plyr.posX = DEFAULT_X;
	Plyr.posY = DEFAULT_Y;
	Plyr.Slow = 5;
	Plyr.Fast = 7;
	Plyr.Life = Plyr.defaultLife;
	Plyr.Bomb = Plyr.defaultBomb;
	Plyr.colSize = PLAYER_COL;
	Plyr.Protect = PLAYER_PROTECT;
	Plyr.protectTime = 0;
	Plyr.isMouse = 0;

	for (int i = 0; i < 128; i++) {
		defaultBulletBlend.emplace_back(BLEND_NOBLEND);
	}
	defaultBulletBlend[B_LIGHT] = BLEND_ADD;
	defaultBulletBlend[B_BIG] = BLEND_ADD;
}

void
ResInit() {
	res.UIGHLoad();
	res.BulletGHLoad();
	res.EnemyGHLoad();
	res.FaceGHLoad();
	res.PlayerGHLoad();

	backgroundCanvas = MakeScreen(1920, 1080, 1);
	bulletCanvas = MakeScreen(1920, 1080, 1);
	playerCanvas = MakeScreen(1920, 1080, 1);
	playerShotCanvas = MakeScreen(1920, 1080, 1);
	bombCanvas = MakeScreen(1920, 1080, 1);
	effectCanvas = MakeScreen(1920, 1080, 1);
	screenCanvas = MakeScreen(1920, 1080, 1);
}