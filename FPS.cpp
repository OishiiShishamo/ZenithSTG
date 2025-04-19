#include "Main.h"

#include "FPS.h"

void
ShowFPS(int x, int y, int fontSize, int elapsedFrame, Color color) {
	SetFontSize(fontSize);
	fpsHistory[fpsHistoryIndex] = static_cast<double>(fps) / elapsedFrame;
	fpsHistoryIndex++;
	if (fpsHistoryIndex >= FPS_HISTORY_LENGTH) fpsHistoryIndex = 0;
	DrawFormatString(x, y, GetColor(color.r, color.g, color.b), "%.2fFPS", std::accumulate(fpsHistory.begin(), fpsHistory.end(), 0.0f) / fpsHistory.size());
}