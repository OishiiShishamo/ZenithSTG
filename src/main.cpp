#include "main.h"

#include "base_scene.h"
#include "fps.h"
#include "game_scene.h"
#include "init.h"
#include "params.h"
#include "scene_manager.h"
#include "time_utl.h"
#include "title_scene.h"
#include "bullet.h"
#include "laser.h"
#include "enemy.h"
#include "player.h"
#include "player_shot.h"
#include "script.h"
#include "sound.h"
#include "utility.h"

//TODO: リファクタリングする

namespace zenithstg {
	std::random_device rng;

	int elapsed_frame = 0;
	int current_blend_mode = kBlendNoblend;
	int current_blend_pal = 255;

	std::atomic<long long> score = 0;
	std::atomic<long long> graze = 0;

	int last_change_window_time = 0;
	int last_change_window_size_time = 0;

	SceneManager scene_manager_;
}

int
WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	zenithstg::Init();
	if (DxLib_Init() == -1)	return -1;
	zenithstg::ApplyWindowSize();
	switch (zenithstg::properties_.window_size_) {
	case 0:
		SetWindowSize(1280, 720);
		zenithstg::ResInit();
		break;
	case 1:
		SetWindowSize(1600, 900);
		zenithstg::ResInit();
		break;
	case 2:
		SetWindowSize(1920, 1080);
		zenithstg::ResInit();
		break;
	default:
		SetWindowSize(1280, 720);
		zenithstg::ResInit();
		break;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	zenithstg::time_mng_.StartTimer();
	while (1) {
		zenithstg::time_mng_.ElapsedTime();
		zenithstg::elapsed_frame = zenithstg::time_mng_.target_frame_ - zenithstg::t;
		while (zenithstg::t < zenithstg::time_mng_.target_frame_) {
			zenithstg::t++;
			zenithstg::scene_manager_.Run();
		}
		if (zenithstg::elapsed_frame == 0) {
			zenithstg::elapsed_frame = 1;
		}
		if (GetAsyncKeyState(VK_F4) & (1 << 15)) {
			if (zenithstg::t > zenithstg::last_change_window_size_time + 15) {
				zenithstg::last_change_window_size_time = zenithstg::t;
				zenithstg::properties_.window_size_++;
				if (zenithstg::properties_.window_size_ > 2) zenithstg::properties_.window_size_ = 0;
				switch (zenithstg::properties_.window_size_) {
				case 0:
					SetWindowSize(1280, 720);
					zenithstg::ResInit();
					break;
				case 1:
					SetWindowSize(1600, 900);
					zenithstg::ResInit();
					break;
				case 2:
					SetWindowSize(1920, 1080);
					zenithstg::ResInit();
					break;
				default:
					SetWindowSize(1280, 720);
					zenithstg::ResInit();
					break;
				}
			}
		}
		if (GetAsyncKeyState(VK_F11) & (1 << 15) || (GetAsyncKeyState(VK_RETURN) & (1 << 15) && GetAsyncKeyState(VK_MENU) & (1 << 15))) {
			if (zenithstg::t > zenithstg::last_change_window_time + 15) {
				zenithstg::last_change_window_time = zenithstg::t;
				zenithstg::properties_.is_window_++;
				if (zenithstg::properties_.is_window_ > 1) zenithstg::properties_.is_window_ = 0;
				ChangeWindowMode(zenithstg::properties_.is_window_);
			}
		}

		zenithstg::ShowFPS(zenithstg::Vec2D(0, 0), zenithstg::elapsed_frame, zenithstg::Color(kColorWhite));
		ScreenFlip();
		zenithstg::time_mng_.FrameWait();

		if (ProcessMessage() < 0) {
			zenithstg::WriteLog();
			break;
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			zenithstg::WriteLog();
			break;
		}
	}
	DxLib_End();
	return 0;
}