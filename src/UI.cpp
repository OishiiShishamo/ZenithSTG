#include "Global.h"
#include "Main.h"
#include "Player.h"
#include "UI.h"
#include "Vec2D.h"

std::string scoreStr = "";
std::string hiScoreStr = "";

void
DrawUI(Color fontColor) {
	if (GetAsyncKeyState(VK_SHIFT)) {
		DrawRotaGraph(Plyr.pos.GetX(), Plyr.pos.GetY(), 1.0f, 0, SAFE_ACCESS(imgRes.UIGH, 1), TRUE);
	}
	DrawRotaGraph(CENTER_X, CENTER_Y, 1.0f, 0, SAFE_ACCESS(imgRes.UIGH, 0), 1, 0, 0);
	if (score.load() == 0) {
		scoreStr = "0";
	}
	else {
		scoreStr = std::to_string(score.load()) + "0";
	}
	if (Properties.hiScore == 0) {
		hiScoreStr = "0";
	}
	else {
		hiScoreStr = std::to_string(Properties.hiScore) + "0";
	}
#if GRAZE_ENABLED == 1
	DrawFormatStringToHandle(UI_POS_OFFSET.GetX(), UI_POS_OFFSET.GetY(), GetColor(fontColor.r, fontColor.g, fontColor.b), SAFE_ACCESS(fontTypes, UI_1), "Score: \nHi-Score: \nPlayer: \nBomb: \nGraze: ");
	DrawFormatStringToHandle(UI_POS_OFFSET.GetX() + 200, UI_POS_OFFSET.GetY(), GetColor(fontColor.r, fontColor.g, fontColor.b), SAFE_ACCESS(fontTypes, UI_1), "%s\n%s\n%d\n%d\n%" PRId64, scoreStr.c_str(), hiScoreStr.c_str(), Plyr.Life.load(), Plyr.Bomb.load(), graze.load());
#else
	DrawFormatStringToHandle(UI_POS_OFFSET.GetX(), UI_POS_OFFSET.GetY(), GetColor(fontColor.r, fontColor.g, fontColor.b), SAFE_ACCESS(fontTypes, UI_1), "Score: \nHi-Score: \nPlayer: \nBomb: ");
	DrawFormatStringToHandle(UI_POS_OFFSET.GetX() + 200, UI_POS_OFFSET.GetY(), GetColor(fontColor.r, fontColor.g, fontColor.b), SAFE_ACCESS(fontTypes, UI_1), "%s\n%s\n%d\n%d" PRId64, scoreStr.c_str(), hiScoreStr.c_str(), Plyr.Life.load(), Plyr.Bomb.load());
#endif
}