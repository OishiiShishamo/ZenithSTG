#include "main.h"

//TODO: プロパティとかを別で行けるようにする
//TODO: 軽くする(これ重要)
//TODO: フォルダ構成を真面目にやる

imageRes imgRes;

mainLoop Loop;

std::vector<Bullet> Bullets;

long long frame = 0;
long long fps = 60;
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
	switch (Loop.windowSize) {
	case 1:
		SetWindowSize(1280, 720);
		ResInit();
		break;
	case 2:
		SetWindowSize(1600, 900);
		ResInit();
		break;
	case 3:
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
		while (frame < timeMng.framedayo) {
			frame++;
			Loop.Loop();
		}
		if (ProcessMessage() < 0) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}
	DxLib_End();
	return 0;
}