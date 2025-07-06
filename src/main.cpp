#include "main.h"

#include "bullet.h"
#include "enemy.h"
#include "fps.h"
#include "init.h"
#include "laser.h"
#include "main_loop.h"
#include "object.h"
#include "player.h"
#include "player_shot.h"
#include "res_load.h"
#include "script.h"
#include "time_utl.h"
#include "utility.h"

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
	switch (properties_.window_size_) {
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
		elapsed_frame = timeMng.target_frame_ - t;
		while (t < timeMng.target_frame_) {
			t++;
			loop_.Update();
		}
		if (elapsed_frame == 0) {
			elapsed_frame = 1;
		}
		ShowFPS(Vec2D(0, 0), elapsed_frame, zenithstg::Color(kColorWhite));

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