#include "game_scene.h"

#include "background.h"
#include "base_scene.h"
#include "bullet.h"
#include "particle.h"
#include "enemy.h"
#include "init.h"
#include "laser.h"
#include "player.h"
#include "player_shot.h"
#include "script.h"
#include "sound.h"
#include "time_utl.h"
#include "ui.h"

namespace zenithstg {
	double screen_size_rate = 1.0f;
	double screen_rota_x = 0;
	double screen_rota_y = 0;
	double screen_rota_z = 0;

	void GameScene::Update() {
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
	}
}