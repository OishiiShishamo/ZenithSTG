#include "main.h"

#include "background.h"
#include "bullet.h"
#include "particle.h"
#include "enemy.h"
#include "init.h"
#include "laser.h"
#include "main_loop.h"
#include "player.h"
#include "player_shot.h"
#include "script.h"
#include "sound.h"
#include "time_utl.h"
#include "ui.h"

double screen_size_rate = 1.0f;
double screen_rota_x = 0;
double screen_rota_y = 0;
double screen_rota_z = 0;

void
MainLoop::Update() {
	SafeAccess(scripts, 0).RunScript();
	sound_mng_.ReservePlaySe();
	SetDrawScreen(background_canvas);
	ClearDrawScreen();
	//bg_.DrawBackground();
	SetDrawScreen(player_shot_canvas);
	ClearDrawScreen();
	MovePlayerShots();
	SetDrawScreen(player_canvas);
	ClearDrawScreen();
	player.RoutinePlayer();
	SetDrawScreen(bullet_canvas);
	ClearDrawScreen();
	MoveEnemies();
	MoveBullets();
	MoveLasers();
	MoveParticles();
	SetDrawScreen(ui_canvas);
	ClearDrawScreen();
	DrawUi();
	SetDrawScreen(screen_canvas);
	ClearDrawScreen();
	ScreenDraw();
	if (CheckHitKey(KEY_INPUT_P) == 1) {
		SaveDrawScreen(0, 0, 1920, 1080, "ScreenShot.bmp");
	}
	if (GetAsyncKeyState(VK_F4) & 1) {
		if (t > front_change_window_size_frame + 15) {
			front_change_window_size_frame = t;
			properties_.window_size_++;
			if (properties_.window_size_ > 2) properties_.window_size_ = 0;
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
		}
	}
	if (GetAsyncKeyState(VK_F11) & 1) {
		if (t > front_change_window_frame + 15) {
			front_change_window_frame = t;
			properties_.is_window_++;
			if (properties_.is_window_ > 1) properties_.is_window_ = 0;
			ChangeWindowMode(properties_.is_window_);
		}
	}
	if (GetAsyncKeyState(VK_RETURN) && GetAsyncKeyState(VK_MENU)) {
		if (t > front_change_window_frame + 15) {
			front_change_window_frame = t;
			properties_.is_window_++;
			if (properties_.is_window_ > 1) properties_.is_window_ = 0;
			ChangeWindowMode(properties_.is_window_);
		}
	}
}

MainLoop loop_;