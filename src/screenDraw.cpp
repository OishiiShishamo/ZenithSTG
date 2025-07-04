#include "Main.h"

#include "Player.h"

int backgroundCanvas;
int bulletCanvas;
int playerCanvas;
int playerShotCanvas;
int bombCanvas;
int particleCanvas;
int screenCanvas;
int UICanvas;

int isWindowSplit = 0;

void
ScreenDraw() {
	SmartSetDrawBlendMode(BLEND_PMA_ALPHA, 255);
	DrawRotaGraph4(CENTER_X, CENTER_Y, 1.0f, 0, 0, 0, backgroundCanvas, 1, 0, 0);
	DrawRotaGraph4(CENTER_X, CENTER_Y, 1.0f, 0, 0, 0, playerShotCanvas, 1, 0, 0);
	DrawRotaGraph4(CENTER_X, CENTER_Y, 1.0f, 0, 0, 0, playerCanvas, 1, 0, 0);
	DrawRotaGraph4(CENTER_X, CENTER_Y, 1.0f, 0, 0, 0, bulletCanvas, 1, 0, 0);
	DrawRotaGraph4(CENTER_X, CENTER_Y, 1.0f, 0, 0, 0, UICanvas, 1, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();
	if (isWindowSplit) {
		int slice_tmp = 0;
		for (int x = 0; x < GetSystemMetrics(SM_CXSCREEN); x += screenSizeRate * GetSystemMetrics(SM_CXSCREEN)) {
			for (int y = 0; y < GetSystemMetrics(SM_CYSCREEN); y += screenSizeRate * GetSystemMetrics(SM_CYSCREEN)) {
				DrawRotaGraph4(x + screenSizeRate * GetSystemMetrics(SM_CXSCREEN) / 2, y + screenSizeRate * GetSystemMetrics(SM_CYSCREEN) / 2, screenSizeRate, 0, 0, 0, screenCanvas, 1, 0, 0);
				slice_tmp++;
				if (slice_tmp > 2048) break;
			}
			if (slice_tmp > 2048) break;
		}
	}
	else {
		DrawRotaGraph4(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2, screenSizeRate, screenRotaX, screenRotaY, screenRotaZ, screenCanvas, 1, 0, 0);
	}
	SmartSetDrawBlendMode(BLEND_NOBLEND, 255);
}