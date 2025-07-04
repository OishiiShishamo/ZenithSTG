#include "Main.h"

#include "FPS.h"
#include "Bullet.h"

std::array<double, FPS_HISTORY_LENGTH> fpsHistory;
int fpsHistoryIndex = 0;

void
ShowFPS(Vec2D pos, int elapsedFrame, Color color) {
	SAFE_ACCESS(fpsHistory, fpsHistoryIndex) = static_cast<double>(fps) / elapsedFrame;
	fpsHistoryIndex++;
	if (fpsHistoryIndex >= FPS_HISTORY_LENGTH) fpsHistoryIndex = 0;
	int count = 0;
	for (const auto& B : Bullets) {
		if (B.flags & IS_ALIVE) count++;
	}
	DrawFormatStringToHandle(pos.GetX(), pos.GetY(), GetColor(color.r, color.g, color.b), SAFE_ACCESS(fontTypes, UI_0), "%.2fFPS\n%dBullets", std::accumulate(fpsHistory.begin(), fpsHistory.end(), 0.0f) / fpsHistory.size(), count);
}