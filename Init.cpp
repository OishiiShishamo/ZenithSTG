#include "Main.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/lexical_cast.hpp>

#include "init.h"
#include "resLoad.h"
#include "Player.h"
#include "Bullet.h"
#include "Color.h"

resLoad res;

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
	SetGraphMode(1920, 1080, 32);
	SetDoubleStartValidFlag(TRUE);
	SetAlwaysRunFlag(TRUE);
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