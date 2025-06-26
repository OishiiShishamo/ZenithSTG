#include "Main.h"

#include "Background.h"
#include "Bullet.h"
#include "Color.h"
#include "Easing.h"
#include "Effect.h"
#include "Enemy.h"
#include "Init.h"
#include "Laser.h"
#include "mainLoop.h"
#include "Player.h"
#include "playerShot.h"
#include "screenDraw.h"
#include "Script.h"
#include "Sound.h"
#include "timeUtl.h"
#include "UI.h"

Color gamingColor(0, 0, 0);
double screenSizeRate = 1.0f;
double screenRotaX = 0;
double screenRotaY = 0;
double screenRotaZ = 0;

void
mainLoop::Loop() {
	SAFE_ACCESS(Scripts, 0).RunScript();
	soundMng.ReservePlaySE();
	SetDrawScreen(backgroundCanvas);
	ClearDrawScreen();
	//BG.DrawBackground();
	SetDrawScreen(playerShotCanvas);
	ClearDrawScreen();
	MovePlayerShots();
	SetDrawScreen(playerCanvas);
	ClearDrawScreen();
	Plyr.RoutinePlayer();
	SetDrawScreen(bulletCanvas);
	ClearDrawScreen();
	MoveEnemies();
	MoveBullets();
	MoveLasers();
	MoveEffects();
	SetDrawScreen(UICanvas);
	ClearDrawScreen();
	DrawUI();
	SetDrawScreen(screenCanvas);
	ClearDrawScreen();
	ScreenDraw();
	if (CheckHitKey(KEY_INPUT_P) == 1) {
		SaveDrawScreen(0, 0, 1920, 1080, "ScreenShot.bmp");
	}
	if (GetAsyncKeyState(VK_F4) & 1) {
		if (t > frontChangeWindowSizeFrame + 15) {
			frontChangeWindowSizeFrame = t;
			Properties.windowSize++;
			if (Properties.windowSize > 2) Properties.windowSize = 0;
			switch (Properties.windowSize) {
			case 0:
				SetWindowSize(1280, 720);
				ResInit();
				break;
			case 1:
				SetWindowSize(1600, 900);
				ResInit();
				break;
			case 2:
				SetWindowSize(1920, 1080);
				ResInit();
				break;
			default:
				SetWindowSize(1280, 720);
				ResInit();
				break;
			}
		}
	}
	if (GetAsyncKeyState(VK_F11) & 1) {
		if (t > frontChangeWindowFrame + 15) {
			frontChangeWindowFrame = t;
			Properties.isWindow++;
			if (Properties.isWindow > 1) Properties.isWindow = 0;
			ChangeWindowMode(Properties.isWindow);
		}
	}
	if (GetAsyncKeyState(VK_RETURN) && GetAsyncKeyState(VK_MENU)) {
		if (t > frontChangeWindowFrame + 15) {
			frontChangeWindowFrame = t;
			Properties.isWindow++;
			if (Properties.isWindow > 1) Properties.isWindow = 0;
			ChangeWindowMode(Properties.isWindow);
		}
	}
}

mainLoop Loop;