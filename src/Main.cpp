#include "Main.h"

#include "Bullet.h"
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

int elapsed_frame = 0;
int current_blend_mode = kBlendNoblend;
int current_blend_pal = 255;

double rand_tmp = 0;

std::atomic<long long> score = 0;
std::atomic<long long> graze = 0;

int
WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Init();
	if (DxLib_Init() == -1)	return -1;
	ApplyWindowSize();
	switch (properties_.window_size) {
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
		elapsed_frame = timeMng.target_frame - t;
		while (t < timeMng.target_frame) {
			t++;
			loop_.Update();
		}
		if (elapsed_frame == 0) {
			elapsed_frame = 1;
		}
		ShowFPS(Vec2D(0, 0), elapsed_frame, Color(kColorWhite));

		ScreenFlip();

		timeMng.FrameWait();

		if (ProcessMessage() < 0) {
			WriteLog();
			break;
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			WriteLog();
			break;
		}
	}
	DxLib_End();
	return 0;
}