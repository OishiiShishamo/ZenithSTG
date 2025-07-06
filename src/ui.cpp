#include "ui.h"

#include "player.h"
#include "property.h"
#include "ui.h"
#include "vec2d.h"

std::string score_str = "";
std::string hi_score_str = "";

void
DrawUi(zenithstg::Color font_color) {
	if (GetAsyncKeyState(VK_SHIFT)) {
		DrawRotaGraph(player.pos_.GetX(), player.pos_.GetY(), 1.0f, 0, SafeAccess(img_res.ui_gh, 1), TRUE);
	}
	DrawRotaGraph(kCenterX, kCenterY, 1.0f, 0, SafeAccess(img_res.ui_gh, 0), 1, 0, 0);
	if (score.load() == 0) {
		score_str = "0";
	}
	else {
		score_str = std::to_string(score.load()) + "0";
	}
	if (properties_.hi_score_ == 0) {
		hi_score_str = "0";
	}
	else {
		hi_score_str = std::to_string(properties_.hi_score_) + "0";
	}
#if kGrazeEnabled == 1
	DrawFormatStringToHandle(kUiPosOffset.GetX(), kUiPosOffset.GetY(), GetColor(font_color.GetR(), font_color.GetG(), font_color.GetB()), SafeAccess(font_types, kFontUi1), "Score: \nHi-Score: \nPlayer: \nBomb: \nGraze: ");
	DrawFormatStringToHandle(kUiPosOffset.GetX() + 200, kUiPosOffset.GetY(), GetColor(font_color.GetR(), font_color.GetG(), font_color.GetB()), SafeAccess(font_types, kFontUi1), "%s\n%s\n%d\n%d\n%" PRId64, score_str.c_str(), hi_score_str.c_str(), player.life_.load(), player.bomb_.load(), graze.load());
#else
	DrawFormatStringToHandle(kUiPosOffset.GetX(), kUiPosOffset.GetY(), GetColor(font_color.GetR(), font_color.GetG(), font_color.GetB()), SafeAccess(font_types, UI_1), "Score: \nHi-Score: \nPlayer: \nBomb: ");
	DrawFormatStringToHandle(kUiPosOffset.GetX() + 200, kUiPosOffset.GetY(), GetColor(font_color.GetR(), font_color.GetG(), font_color.GetB()), SafeAccess(font_types, UI_1), "%s\n%s\n%d\n%d" PRId64, score_str.c_str(), hi_score_str.c_str(), player.life_.load(), player.bomb_.load());
#endif
}