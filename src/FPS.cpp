#include "Main.h"

#include "FPS.h"

std::array<double, FPS_HISTORY_LENGTH> fpsHistory;
int fpsHistoryIndex = 0;

void
ShowFPS(Vec2D pos, int elapsedFrame, Color color) {
	SAFE_ACCESS(fpsHistory, fpsHistoryIndex) = static_cast<double>(fps) / elapsedFrame;
	fpsHistoryIndex++;
	if (fpsHistoryIndex >= FPS_HISTORY_LENGTH) fpsHistoryIndex = 0;
	DrawFormatStringToHandle(pos.GetX(), pos.GetY(), GetColor(color.r, color.g, color.b), SAFE_ACCESS(fontTypes, UI_0), "%.2fFPS", std::accumulate(fpsHistory.begin(), fpsHistory.end(), 0.0f) / fpsHistory.size());
}