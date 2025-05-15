#include "Main.h"

#include "Bullet.h"
#include "Color.h"
#include "Easing.h"
#include "Enemy.h"
#include "FPS.h"
#include "Init.h"
#include "Laser.h"
#include "mainLoop.h"
#include "Object.h"
#include "Player.h"
#include "playerShot.h"
#include "resLoad.h"
#include "Script.h"
#include "Time.h"
#include "Utility.h"

//TODO: リファクタリングする
//TODO: フォルダ構成を真面目にやる

int elapsedFrame = 0;
int currentBlendMode = BLEND_NOBLEND;
int currentBlendPal = 255;

int
WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Init();
	if (DxLib_Init() == -1)	return -1;
	apply_window_size();
	if (Properties.onerror == 1) {
		PRINT("ERROR: 画面のサイズに非対応");
		Logger("画面のサイズに非対応", logType::LOG_WARNING);
	}
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
	SetDrawScreen(DX_SCREEN_BACK);
	timeMng.StartTimer();
	while (1) {
		timeMng.ElapsedTime();
		elapsedFrame = timeMng.targetFrame - frame;
		while (frame < timeMng.targetFrame) {
			frame++;
			Loop.Loop();
		}
		if (elapsedFrame == 0) {
			elapsedFrame = 1;
		}
		ShowFPS(Vec2D(0, 0), elapsedFrame, Color(C_WHITE));
		//DrawFormatString(0, 20, GetColor(C_WHITE), "Objects:%d", Bullets.size() + Lasers.size() + plyrShots.size());

		ScreenFlip();

		timeMng.FrameWait();

		if (ProcessMessage() < 0) {
			writeLog();
			break;
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			writeLog();
			break;
		}
	}
	DxLib_End();
	return 0;
}