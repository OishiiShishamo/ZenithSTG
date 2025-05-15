#include "Main.h"

#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "Bullet.h"
#include "Color.h"
#include "init.h"
#include "Player.h"
#include "resLoad.h"
#include "screenDraw.h"

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

	defaultEnemyBlend.fill(BLEND_NOBLEND);

	defaultPlayerShotBlend.fill(BLEND_NOBLEND);

	drawRatioBulletGraphs.fill(1.0f);
	SAFE_ACCESS(drawRatioBulletGraphs, B_NORMAL) = 0.15625f;
	SAFE_ACCESS(drawRatioBulletGraphs, B_MIDIAM) = 0.3125f;
	SAFE_ACCESS(drawRatioBulletGraphs, B_UROKO) = 0.15625f;
	SAFE_ACCESS(drawRatioBulletGraphs, B_LASER) = 0.0625f;
	SAFE_ACCESS(drawRatioBulletGraphs, B_LIGHT) = 0.25f;
	SAFE_ACCESS(drawRatioBulletGraphs, B_BIG) = 0.75f;

	drawRatioEnemyGraphs.fill(1.0f);
	SAFE_ACCESS(drawRatioEnemyGraphs, E_NORMAL) = 0.5f;

	drawRatioPlayerShotGraphs.fill(1.0f);
	SAFE_ACCESS(drawRatioPlayerShotGraphs, PS_NORMAL) = 0.5f;
}

void
ResInit() {
	res.UIGHLoad();
	res.BulletGHLoad();
	res.EnemyGHLoad();
	res.FaceGHLoad();
	res.PlayerGHLoad();
	res.ShotGHLoad();
	res.FontLoad();

	backgroundCanvas = MakeScreen(1920, 1080, 1);
	bulletCanvas = MakeScreen(1920, 1080, 1);
	playerCanvas = MakeScreen(1920, 1080, 1);
	playerShotCanvas = MakeScreen(1920, 1080, 1);
	bombCanvas = MakeScreen(1920, 1080, 1);
	effectCanvas = MakeScreen(1920, 1080, 1);
	screenCanvas = MakeScreen(1920, 1080, 1);
}