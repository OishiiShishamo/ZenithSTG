#include "Main.h"

#include "Color.h"
#include "Object.h"
#include "Bullet.h"
#include "Laser.h"
#include "Enemy.h"
#include "Easing.h"
#include "Init.h"
#include "mainLoop.h"
#include "Player.h"
#include "playerShot.h"
#include "resLoad.h"
#include "Time.h"
#include "FPS.h"

//TODO: リファクタリングする
//TODO: フォルダ構成を真面目にやる

imageRes imgRes;

Property Properties;

mainLoop Loop;

Player Plyr;

std::array<Bullet, MAX_BULLET> Bullets;
std::array<Laser, MAX_LASER> Lasers;
std::array<Enemy, MAX_ENEMY> Enemies;
std::array<playerShot, MAX_PLAYER_SHOT> plyrShots;

std::array<double, 128> drawRatioBulletGraphs;
std::array<double, 128> drawRatioEnemyGraphs;
std::array<double, 128> drawRatioPlayerShotGraphs;

int numThreads = std::thread::hardware_concurrency();

long long frame = 0;
long long fps = 60;
int elapsedFrame = 0;
int currentBlendMode = BLEND_NOBLEND;
int currentBlendPal = 255;

std::array<double, FPS_HISTORY_LENGTH> fpsHistory;
int fpsHistoryIndex = 0;

int isColShow = 0;

int backgroundCanvas;
int bulletCanvas;
int playerCanvas;
int playerShotCanvas;
int bombCanvas;
int effectCanvas;
int screenCanvas;

int
WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Init();
	if (DxLib_Init() == -1)	return -1;
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
		ShowFPS(0, 0, 20, elapsedFrame, Color(C_WHITE));
		
		//DrawFormatString(0, 20, GetColor(C_WHITE), "Objects:%d", Bullets.size() + Lasers.size() + plyrShots.size());

		ScreenFlip();

		timeMng.FrameWait();

		if (ProcessMessage() < 0) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}
	DxLib_End();
	return 0;
}