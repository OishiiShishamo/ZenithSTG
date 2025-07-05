#include "Main.h"

#include "FPS.h"
#include "Bullet.h"

std::array<double, kFpsHistoryLength> fps_history;
int fps_history_index = 0;

void
ShowFPS(Vec2D pos, int elapsed_frame, Color color) {
	SafeAccess(fps_history, fps_history_index) = static_cast<double>(fps) / elapsed_frame;
	fps_history_index++;
	if (fps_history_index >= kFpsHistoryLength) fps_history_index = 0;
	int count = 0;
	for (const auto& B : bullets) {
		if (B.flags & kIsAlive) count++;
	}
	DrawFormatStringToHandle(pos.GetX(), pos.GetY(), GetColor(color.r, color.g, color.b), SafeAccess(font_types, kFontUi0), "%.2fFPS\n%dBullets", std::accumulate(fps_history.begin(), fps_history.end(), 0.0f) / fps_history.size(), count);
}