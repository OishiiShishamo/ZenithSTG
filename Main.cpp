#include "Main.h"

#include "Color.h"
#include "Object.h"
#include "Bullet.h"
#include "Laser.h"
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

std::vector<Bullet> Bullets;
std::vector<Laser> Lasers;
std::vector<playerShot> plyrShots;

std::vector<float> drawRatioBulletGraphs;

long long frame = 0;
long long fps = 60;
int elapsedFrame = 0;
int currentBlendMode = DX_BLENDGRAPHTYPE_NORMAL;
int currentBlendPal = 255;

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
		elapsedFrame = timeMng.framedayo - frame;
		while (frame < timeMng.framedayo) {
			frame++;
			Loop.Loop();
		}
		if (elapsedFrame == 0) {
			elapsedFrame = 1;
		}
		ShowFPS(0, 0, 20, elapsedFrame, Color(C_WHITE));

		ScreenFlip();

		if (ProcessMessage() < 0) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}
	DxLib_End();
	return 0;
}