#include "mainLoop.h"

Color coltmp(0, 0, 0);
double unko = 1.0f;

void
mainLoop::Loop() {
	SetDrawScreen(backgroundCanvas);
	ClearDrawScreen();
	//TESTDANMAKUKUKUKUKUKUKUKUKUKUKU
	if (frame % 1 == 0) {
		coltmp = GetColorHSV(std::fmod(frame, 360), 1, 1);
		CreateBulletGroup(CENTER_X, CENTER_Y, GetColorHSV(std::fmod(frame, 360), 1, 1), B_LIGHT, BLEND_ADD, 255, 10.0f, 10.0f, EASEINQUAD, 120, 2.0f, 1.0f, EASEINQUAD, 120, 8, TAU, 0, Rad(frame), Rad(frame + 80), EASEOUTQUAD, 240, -10.0f, 10.0f, EASEINQUAD, 120);
	}
	DrawBox(0, 0, 1920, 1080, GetColor(C_GRAY), 1);
	SetDrawScreen(bulletCanvas);
	ClearDrawScreen();
	MoveBullets();
	SetDrawScreen(playerCanvas);
	ClearDrawScreen();
	Plyr.RoutinePlayer();
	SetDrawScreen(screenCanvas);
	ClearDrawScreen();
	SmartSetDrawBlendMode(BLEND_PMA_ALPHA, 255);
	DrawRotaGraph4(CENTER_X, CENTER_Y, 1.0f, 0, 0, 0, backgroundCanvas, 1, 0, 0);
	DrawRotaGraph4(CENTER_X, CENTER_Y, 1.0f, 0, 0, 0, playerCanvas, 1, 0, 0);
	DrawRotaGraph4(CENTER_X, CENTER_Y, 1.0f, 0, 0, 0, bulletCanvas, 1, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();
	//DrawRotaGraph(CENTER_X, CENTER_Y, 1.0f, 0, screenCanvas, TRUE);
	if (isWindowSplit) {
		int slice_tmp = 0;
		for (int x = 0; x < BORDER_RIGHT; x += unko * BORDER_RIGHT) {
			for (int y = 0; y < BORDER_DOWN; y += unko * BORDER_DOWN) {
				DrawRotaGraph4(x + unko * BORDER_RIGHT / 2, y + unko * BORDER_DOWN / 2, unko, 0, 0, 0, screenCanvas, 1, 0, 0);
				slice_tmp++;
				if (slice_tmp > 2048) break;
			}
			if (slice_tmp > 2048) break;
		}
	}
	else {
		DrawRotaGraph4(BORDER_RIGHT / 2, BORDER_DOWN / 2, unko, 0, 0, 0, screenCanvas, 1, 0, 0);
	}
	SmartSetDrawBlendMode(BLEND_NOBLEND, 255);
	if (frame == timeMng.framedayo) {
		ScreenFlip();
	}
	if (CheckHitKey(KEY_INPUT_P) == 1) {
		SaveDrawScreen(0, 0, 1920, 1080, "ScreenShot.bmp");
	}
	if (GetAsyncKeyState(VK_F4) & 1) {
		if (frame > frontChangeWindowSizeFrame + 15) {
			frontChangeWindowSizeFrame = frame;
			windowSize++;
			if (windowSize > 3)windowSize = 1;
			switch (windowSize) {
			case 1:
				SetWindowSize(1280, 720);
				ResInit();
				break;
			case 2:
				SetWindowSize(1600, 900);
				ResInit();
				break;
			case 3:
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
}