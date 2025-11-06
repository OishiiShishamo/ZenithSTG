#include "screen_draw.h"

#include "DxLib.h"

#include "main.h"
#include "player.h"

namespace zenithstg {
	int background_canvas;
	int back_object_canvas;
	int front_object_canvas;
	int player_canvas;
	int bomb_canvas;
	int screen_canvas;
	int ui_canvas;

	int is_window_split = 0;

	void ScreenDraw() {
		SmartSetDrawBlendMode(kBlendPmaAlpha, 255);
		DrawRotaGraph4(kCenterX, kCenterY, 1.0f, 0, 0, 0, background_canvas, 1, 0, 0);
		DrawRotaGraph4(kCenterX, kCenterY, 1.0f, 0, 0, 0, back_object_canvas, 1, 0, 0);
		DrawRotaGraph4(kCenterX, kCenterY, 1.0f, 0, 0, 0, player_canvas, 1, 0, 0);
		DrawRotaGraph4(kCenterX, kCenterY, 1.0f, 0, 0, 0, front_object_canvas, 1, 0, 0);
		DrawRotaGraph4(kCenterX, kCenterY, 1.0f, 0, 0, 0, ui_canvas, 1, 0, 0);
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		if (is_window_split) {
			int slice_count = 0;
			for (int x = 0; x < GetSystemMetrics(SM_CXSCREEN); x += screen_size_rate * GetSystemMetrics(SM_CXSCREEN)) {
				for (int y = 0; y < GetSystemMetrics(SM_CYSCREEN); y += screen_size_rate * GetSystemMetrics(SM_CYSCREEN)) {
					DrawRotaGraph4(x + screen_size_rate * GetSystemMetrics(SM_CXSCREEN) / 2 + screen_pos_offset.GetX(), y + screen_size_rate * GetSystemMetrics(SM_CYSCREEN) / 2 + screen_pos_offset.GetY(), screen_size_rate, 0, 0, 0, screen_canvas, 1, 0, 0);
					slice_count++;
					if (slice_count > 2048) break;
				}
				if (slice_count > 2048) break;
			}
		}
		else {
			DrawRotaGraph4(GetSystemMetrics(SM_CXSCREEN) / 2 + screen_pos_offset.GetX(), GetSystemMetrics(SM_CYSCREEN) / 2 + screen_pos_offset.GetY(), screen_size_rate, screen_rota_x, screen_rota_y, screen_rota_z, screen_canvas, 1, 0, 0);
		}
		SmartSetDrawBlendMode(kBlendNoblend, 255);
	}
}