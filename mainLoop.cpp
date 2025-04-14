#include "Main.h"

#include "mainLoop.h"
#include "Init.h"
#include "Time.h"
#include "Color.h"
#include "Easing.h"
#include "Bullet.h"
#include "Laser.h"
#include "Enemy.h"
#include "Player.h"
#include "playerShot.h"

Color gamingColor(0, 0, 0);
double screenSizeRate = 1.0f;
double screenRotaX = 0;
double screenRotaY = 0;
double screenRotaZ = 0;

void
mainLoop::Loop() {
	SetDrawScreen(backgroundCanvas);
	ClearDrawScreen();
	//TESTDANMAKUKUKUKUKUKUKUKUKUKUKU
	if (frame % 1 == 0) {
		CreateLaserGroup(CENTER, 256, 32, GamingColor(), B_LIGHT, BLEND_ADD, 255, 1, 16, 16, 0, 0, 1.0f, 1.0f, 0, 0, 48, TAU, 0, Rad(sin(Rad(frame)) * 360), 0, EASEINCUBIC, 60, -8, 15, EASEINOUTCUBIC, 60, 0);
	}
	DrawBox(0, 0, 1920, 1080, GetColor(C_GRAY), 1);
	SetDrawScreen(playerShotCanvas);
	ClearDrawScreen();
	MovePlayerShots();
	SetDrawScreen(playerCanvas);
	ClearDrawScreen();
	Plyr.RoutinePlayer();
	SetDrawScreen(bulletCanvas);
	ClearDrawScreen();
	MoveBullets();
	MoveLasers();
	SetDrawScreen(screenCanvas);
	ClearDrawScreen();
	SmartSetDrawBlendMode(BLEND_PMA_ALPHA, 255);
	DrawRotaGraph4(CENTER_X, CENTER_Y, 1.0f, 0, 0, 0, backgroundCanvas, 1, 0, 0);
	DrawRotaGraph4(CENTER_X, CENTER_Y, 1.0f, 0, 0, 0, playerShotCanvas, 1, 0, 0);
	DrawRotaGraph4(CENTER_X, CENTER_Y, 1.0f, 0, 0, 0, playerCanvas, 1, 0, 0);
	DrawRotaGraph4(CENTER_X, CENTER_Y, 1.0f, 0, 0, 0, bulletCanvas, 1, 0, 0);
	if (GetAsyncKeyState(VK_SHIFT)) {
		DrawRotaGraph(Plyr.pos.x, Plyr.pos.y, 1.0f, 0, imgRes.UIGH[1], TRUE);
	}
	DrawRotaGraph(CENTER_X, CENTER_Y, 1.0f, 0, imgRes.UIGH[0], 1, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();
	//unko = abs(sin(Rad(frame)));
	//DrawRotaGraph(CENTER_X, CENTER_Y, 1.0f, 0, screenCanvas, TRUE);
	if (isWindowSplit) {
		int slice_tmp = 0;
		for (int x = 0; x < SCREEN_WIDTH; x += screenSizeRate * SCREEN_WIDTH) {
			for (int y = 0; y < SCREEN_HEIGHT; y += screenSizeRate * SCREEN_HEIGHT) {
				DrawRotaGraph4(x + screenSizeRate * SCREEN_WIDTH / 2, y + screenSizeRate * SCREEN_HEIGHT / 2, screenSizeRate, 0, 0, 0, screenCanvas, 1, 0, 0);
				slice_tmp++;
				if (slice_tmp > 2048) break;
			}
			if (slice_tmp > 2048) break;
		}
	}
	else {
		DrawRotaGraph4(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, screenSizeRate, screenRotaX, screenRotaY, screenRotaZ, screenCanvas, 1, 0, 0);
	}
	SmartSetDrawBlendMode(BLEND_NOBLEND, 255);
	if (CheckHitKey(KEY_INPUT_P) == 1) {
		SaveDrawScreen(0, 0, 1920, 1080, "ScreenShot.bmp");
	}
	if (GetAsyncKeyState(VK_F4) & 1) {
		if (frame > frontChangeWindowSizeFrame + 15) {
			frontChangeWindowSizeFrame = frame;
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
		if (frame > frontChangeWindowFrame + 15) {
			frontChangeWindowFrame = frame;
			Properties.isWindow++;
			if (Properties.isWindow > 1) Properties.isWindow = 0;
			ChangeWindowMode(Properties.isWindow);
		}
	}
	if (GetAsyncKeyState(VK_RETURN) && GetAsyncKeyState(VK_MENU)) {
		if (frame > frontChangeWindowFrame + 15) {
			frontChangeWindowFrame = frame;
			Properties.isWindow++;
			if (Properties.isWindow > 1) Properties.isWindow = 0;
			ChangeWindowMode(Properties.isWindow);
		}
	}
}