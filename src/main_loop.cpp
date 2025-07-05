#include "Main.h"

#include "background.h"
#include "Bullet.h"
#include "Particle.h"
#include "Enemy.h"
#include "Init.h"
#include "Laser.h"
#include "main_loop.h"
#include "Player.h"
#include "player_shot.h"
#include "Script.h"
#include "Sound.h"
#include "time_utl.h"
#include "UI.h"

double screen_size_rate = 1.0f;
double screen_rota_x = 0;
double screen_rota_y = 0;
double screen_rota_z = 0;

void
mainLoop::Update() {
	SafeAccess(scripts, 0).RunScript();
	sound_mng_.ReservePlaySe();
	SetDrawScreen(background_canvas);
	ClearDrawScreen();
	//BG.DrawBackground();
	SetDrawScreen(player_shot_canvas);
	ClearDrawScreen();
	MovePlayerShots();
	SetDrawScreen(player_canvas);
	ClearDrawScreen();
	Plyr.RoutinePlayer();
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
			properties_.window_size++;
			if (properties_.window_size > 2) properties_.window_size = 0;
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
		}
	}
	if (GetAsyncKeyState(VK_F11) & 1) {
		if (t > front_change_window_frame + 15) {
			front_change_window_frame = t;
			properties_.is_window++;
			if (properties_.is_window > 1) properties_.is_window = 0;
			ChangeWindowMode(properties_.is_window);
		}
	}
	if (GetAsyncKeyState(VK_RETURN) && GetAsyncKeyState(VK_MENU)) {
		if (t > front_change_window_frame + 15) {
			front_change_window_frame = t;
			properties_.is_window++;
			if (properties_.is_window > 1) properties_.is_window = 0;
			ChangeWindowMode(properties_.is_window);
		}
	}
}

mainLoop loop_;