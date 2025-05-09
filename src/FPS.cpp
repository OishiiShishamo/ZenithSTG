﻿#include "Main.h"

#include "FPS.h"

std::array<double, FPS_HISTORY_LENGTH> fpsHistory;
int fpsHistoryIndex = 0;

void
ShowFPS(Vec2D pos, int fontSize, int elapsedFrame, Color color) {
	SetFontSize(fontSize);
	fpsHistory[fpsHistoryIndex] = static_cast<double>(fps) / elapsedFrame;
	fpsHistoryIndex++;
	if (fpsHistoryIndex >= FPS_HISTORY_LENGTH) fpsHistoryIndex = 0;
	DrawFormatString(pos.GetX(), pos.GetY(), GetColor(color.r, color.g, color.b), "%.2fFPS", std::accumulate(fpsHistory.begin(), fpsHistory.end(), 0.0f) / fpsHistory.size());
}