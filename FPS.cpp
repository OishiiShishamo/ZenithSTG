#include "Main.h"
#include "FPS.h"

void
ShowFPS(int x, int y, int fontSize, int elapsedFrame, Color color) {
	SetFontSize(fontSize);
	DrawFormatString(x, y, GetColor(color.r, color.g, color.b), "%.2fFPS", fps / elapsedFrame * 1.0f);
}