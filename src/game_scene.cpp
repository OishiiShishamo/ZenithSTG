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
	Vec2D screen_pos_offset = Vec2D(0, 0);

	void GameScene::Update() {
		SafeAccess(scripts, 0).RunScript();
		sound_mng_.ReservePlaySe();
		MovePlayerShots();
		player_.RoutinePlayer();
		MoveEnemies();
		MoveBullets();
		MoveLasers();
		MoveParticles();
	}

	void GameScene::Render() {
		//SetDrawScreen(background_canvas);
		//ClearDrawScreen();
		//bg_.DrawBackground();

		SetDrawScreen(back_object_canvas);
		ClearDrawScreen();
		RenderPlayerShots();

		SetDrawScreen(player_canvas);
		ClearDrawScreen();
		player_.RenderPlayer();

		SetDrawScreen(front_object_canvas);
		ClearDrawScreen();
		RenderEnemies();
		RenderBullets();
		RenderLasers();
		RenderParticles();

		SetDrawScreen(ui_canvas);
		ClearDrawScreen();
		DrawUi();

		SetDrawScreen(screen_canvas);
		ClearDrawScreen();
		ScreenDraw();
	}
}