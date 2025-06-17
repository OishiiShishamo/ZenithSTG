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
#include "timeUtl.h"
#include "Utility.h"

//TODO: リファクタリングする
//TODO: フォルダ構成を真面目にやる

std::random_device rng;

int elapsedFrame = 0;
int currentBlendMode = BLEND_NOBLEND;
int currentBlendPal = 255;

double RandTMP = 0;

std::atomic<long long> score = 0;
std::atomic<long long> graze = 0;

int
WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Init();
	if (DxLib_Init() == -1)	return -1;
	apply_window_size();
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
		elapsedFrame = timeMng.targetFrame - t;
		while (t < timeMng.targetFrame) {
			t++;
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