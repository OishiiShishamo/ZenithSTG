#include "Main.h"

#include "Player.h"
#include "Color.h"

//TODO: Ç‡Ç¡Ç∆ê^ñ ñ⁄Ç…çÏÇÈ
//TODO: íeë≈ÇƒÇÈÇÊÇ§Ç…Ç∑ÇÈ

double
Player::AimPlayer(double x, double y) {
	return atan2(-double(posY - y), double(posX - x));
}

double
Player::RangePlayer(double x, double y) {
	return Range(y, posY, x, posX);
}

void
Player::MovePlayer() {
	vecX = 0;
	vecY = 0;
	if (isMouse == 1) {
		GetMousePoint(&posX, &posY);
	}
	else {
		if (GetAsyncKeyState(VK_RIGHT)) vecX += 1;
		if (GetAsyncKeyState(VK_LEFT)) vecX -= 1;
		if (GetAsyncKeyState(VK_UP)) vecY -= 1;
		if (GetAsyncKeyState(VK_DOWN)) vecY += 1;
		VecNorm(vecX, vecY);
		if (GetAsyncKeyState(VK_SHIFT)) {
			posX += vecX * Slow;
			posY += vecY * Slow;
		}
		else {
			posX += vecX * Fast;
			posY += vecY * Fast;
		}
	}
	if (posX < BORDER_LEFT) posX = BORDER_LEFT;
	if (posX > BORDER_RIGHT) posX = BORDER_RIGHT;
	if (posY > BORDER_DOWN) posY = BORDER_DOWN;
	if (posY < BORDER_UP) posY = BORDER_UP;
}

void
Player::ShowPlayer() {
	SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawRotaGraph(posX, posY, 1.0f, 0, imgRes.PlayerGH[0], 1);
	if (isColShow == 1) {
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		DrawCircle(posX, posY, colSize, GetColor(255, 255, 255), 1);
		DrawFormatString(posX, posY, GetColor(GetColorHSV(std::fmod(frame, 360), 1, 1).r, GetColorHSV(std::fmod(frame, 360), 1, 1).g, GetColorHSV(std::fmod(frame, 360), 1, 1).b), "%f", colSize);
	}
}

void
Player::HitPlayer() {
	if (protectTime < 0) {
		protectTime = Protect;
		posX = DEFAULT_X;
		posY = DEFAULT_Y;
		Life -= 1;
		Bomb = defaultBomb;
	}
}

void
Player::RoutinePlayer() {
	MovePlayer();
	ShowPlayer();
	protectTime--;
}

Player Plyr;