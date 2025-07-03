#include "Main.h"

#include "Bullet.h"
#include "Enemy.h"
#include "init.h"
#include "Laser.h"
#include "Player.h"
#include "playerShot.h"
#include "resLoad.h"
#include "Sound.h"
#include "Effect.h"

resLoad res;
imageRes imgRes;
Property Properties;

std::array<int, fontTypeNum> fontTypes;

int numThreads = std::thread::hardware_concurrency();

void
Init() {
	boost::property_tree::ptree pt;
	boost::property_tree::read_xml("ZenithSTG_property.xml", pt);
	if (boost::optional<std::string> title = pt.get_optional<std::string>("root.title")) {
		Properties.title = title.get();
	}
	else {
		Properties.title = "ZenithSTG";
	}
	if (boost::optional<int> windowSize = pt.get_optional<int>("root.windowSize")) {
		Properties.windowSize = windowSize.get();
		if (Properties.windowSize < 0 || Properties.windowSize > 2) Properties.windowSize = 0;
	}
	else {
		Properties.windowSize = 0;
	}
	if (boost::optional<int> isWindow = pt.get_optional<int>("root.isWindow")) {
		Properties.isWindow = isWindow.get();
		if (Properties.isWindow < 0 || Properties.isWindow > 1) Properties.isWindow = 1;
	}
	else {
		Properties.isWindow = 1;
	}
	if (boost::optional<long long> hiScore = pt.get_optional<long long>("root.hiScore")) {
		Properties.hiScore = hiScore.get();
		if (Properties.hiScore < 0) Properties.hiScore = 0;
	}
	else {
		Properties.hiScore = 0;
	}
	if (boost::optional<int> BGMVolume = pt.get_optional<int>("root.BGMVolume")) {
		Properties.BGMVolume = BGMVolume.get();
		if (Properties.BGMVolume < 0) Properties.BGMVolume = 0;
		if (Properties.BGMVolume > 100) Properties.BGMVolume = 100;
	}
	else {
		Properties.BGMVolume = Properties.BGMVolume;
	}
	if (boost::optional<int> SEVolume = pt.get_optional<int>("root.SEVolume")) {
		Properties.SEVolume = SEVolume.get();
		if (Properties.SEVolume < 0) Properties.SEVolume = 0;
		if (Properties.SEVolume > 100) Properties.SEVolume = 100;
	}
	else {
		Properties.SEVolume = Properties.SEVolume;
	}

	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(Properties.isWindow);
	SetWindowText(Properties.title.c_str());
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

	Plyr.pos = P_DEFAULT_POS;
	Plyr.Slow = 5;
	Plyr.Fast = 7;
	Plyr.Life = Plyr.defaultLife;
	Plyr.Bomb = Plyr.defaultBomb;
	Plyr.colSize = PLAYER_COL;
	Plyr.Protect = PLAYER_PROTECT;
	Plyr.protectTime = 0;
	Plyr.isMouse = 0;

	fpsHistory.fill(fps);

	defaultBulletBlend.fill(BLEND_NOBLEND);
	SAFE_ACCESS(defaultBulletBlend, B_LIGHT) = BLEND_ADD;
	SAFE_ACCESS(defaultBulletBlend, B_BIG) = BLEND_ADD;

	defaultEffectBlend.fill(BLEND_NOBLEND);
	SAFE_ACCESS(defaultEffectBlend, EF_LIGHT) = BLEND_ADD;
	SAFE_ACCESS(defaultEffectBlend, EF_STAR) = BLEND_ADD;

	defaultEnemyBlend.fill(BLEND_NOBLEND);

	defaultPlayerShotBlend.fill(BLEND_NOBLEND);

	drawRatioBulletGraphs.fill(1.0f);
	SAFE_ACCESS(drawRatioBulletGraphs, B_NORMAL) = 0.15625f;
	SAFE_ACCESS(drawRatioBulletGraphs, B_MIDIAM) = 0.3125f;
	SAFE_ACCESS(drawRatioBulletGraphs, B_UROKO) = 0.15625f;
	SAFE_ACCESS(drawRatioBulletGraphs, B_LASER) = 0.0625f;
	SAFE_ACCESS(drawRatioBulletGraphs, B_LIGHT) = 0.25f;
	SAFE_ACCESS(drawRatioBulletGraphs, B_BIG) = 0.75f;

	drawRatioEffectGraphs.fill(1.0f);
	SAFE_ACCESS(drawRatioEffectGraphs, EF_LIGHT) = 0.25f;
	SAFE_ACCESS(drawRatioEffectGraphs, EF_STAR) = 0.125f;

	drawRatioEnemyGraphs.fill(1.0f);
	SAFE_ACCESS(drawRatioEnemyGraphs, EN_NORMAL) = 0.5f;

	drawRatioPlayerShotGraphs.fill(1.0f);
	SAFE_ACCESS(drawRatioPlayerShotGraphs, PS_NORMAL) = 0.5f;

	for (int i = 0; i < MAX_BULLET; i++) {
		SAFE_ACCESS(BulletPtrs, i) = &SAFE_PTR_ACCESS(Bullets, i);
		BlankBullets.emplace_back(i);
	}
	for (int i = 0; i < MAX_LASER; i++) {
		SAFE_ACCESS(LaserPtrs, i) = &SAFE_PTR_ACCESS(Lasers, i);
		BlankLasers.emplace_back(i);
	}
	for (int i = 0; i < MAX_ENEMY; i++) {
		SAFE_ACCESS(EnemyPtrs, i) = &SAFE_PTR_ACCESS(Enemies, i);
		BlankEnemies.emplace_back(i);
	}
	for (int i = 0; i < MAX_PLAYER_SHOT; i++) {
		SAFE_ACCESS(PlayerShotPtrs, i) = &SAFE_PTR_ACCESS(plyrShots, i);
		BlankPlayerShots.emplace_back(i);
	}
	for (int i = 0; i < MAX_EFFECT; i++) {
		SAFE_ACCESS(EffectPtrs, i) = &SAFE_PTR_ACCESS(Effects, i);
		BlankEffects.emplace_back(i);
	}
}

void
ResInit() {
	res.UIGHLoad();
	res.BulletGHLoad();
	res.EffectGHLoad();
	res.EnemyGHLoad();
	res.FaceGHLoad();
	res.PlayerGHLoad();
	res.ShotGHLoad();
	res.FontLoad();

	soundMng.SoundLoad();

	backgroundCanvas = MakeScreen(1920, 1080, 1);
	bulletCanvas = MakeScreen(1920, 1080, 1);
	playerCanvas = MakeScreen(1920, 1080, 1);
	playerShotCanvas = MakeScreen(1920, 1080, 1);
	bombCanvas = MakeScreen(1920, 1080, 1);
	effectCanvas = MakeScreen(1920, 1080, 1);
	screenCanvas = MakeScreen(1920, 1080, 1);
	UICanvas = MakeScreen(1920, 1080, 1);
}