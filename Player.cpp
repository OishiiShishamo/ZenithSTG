#include "Player.h"
#include "Color.h"
#include "playerShot.h"

//TODO: もっと真面目に作る
//TODO: コントローラーに対応させる

double
Player::AimPlayer(Vec2D v) {
	return atan2(-double(pos.y - v.y), double(pos.x - v.x));
}

double
Player::RangePlayer(Vec2D v) {
	return Range(v, pos);
}

void
Player::MovePlayer() {
	vec.x = 0;
	vec.y = 0;
	if (isMouse == 1) {
		int x, y;
		GetMousePoint(&x, &y);
		pos.x = x;
		pos.y = y;
	}
	else {
		if (GetAsyncKeyState(VK_RIGHT)) vec.x += 1;
		if (GetAsyncKeyState(VK_LEFT)) vec.x -= 1;
		if (GetAsyncKeyState(VK_UP)) vec.y -= 1;
		if (GetAsyncKeyState(VK_DOWN)) vec.y += 1;
		VecNorm(vec.x, vec.y);
		if (GetAsyncKeyState(VK_SHIFT)) {
			pos.x += vec.x * Slow;
			pos.y += vec.y * Slow;
		}
		else {
			pos.x += vec.x * Fast;
			pos.y += vec.y * Fast;
		}
	}
	if (pos.x < BORDER_LEFT) pos.x = BORDER_LEFT;
	if (pos.x > BORDER_RIGHT) pos.x = BORDER_RIGHT;
	if (pos.y > BORDER_DOWN) pos.y = BORDER_DOWN;
	if (pos.y < BORDER_UP) pos.y = BORDER_UP;
}

void
Player::ShowPlayer() {
	SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawRotaGraph(pos.x, pos.y, 1.0f, 0, imgRes.PlayerGH[0], 1);
	if (isColShow == 1) {
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		DrawCircle(pos.x, pos.y, colSize, GetColor(255, 255, 255), 1);
		DrawFormatString(pos.x, pos.y, GetColor(GetColorHSV(std::fmod(frame, 360), 1, 1).r, GetColorHSV(std::fmod(frame, 360), 1, 1).g, GetColorHSV(std::fmod(frame, 360), 1, 1).b), "%f", colSize);
	}
}

void
Player::Shot() {
	if (GetAsyncKeyState(0x5A)) {
		CreatePlayerShot(pos, Color(255, 255, 255), 0, BLEND_ADD, 255, 1, 24, 24, 0, 0, 1.0f, 1.0f, 0, 0, Rad(90), Rad(90), 0, 0, 0, 50, EASEINCUBIC, 60);
	}
}

void
Player::HitPlayer() {
	if (protectTime < 0) {
		protectTime = Protect;
		pos = P_DEFAULT_POS;
		Life -= 1;
		Bomb = defaultBomb;
	}
}

void
Player::RoutinePlayer() {
	MovePlayer();
	ShowPlayer();
	Shot();
	protectTime--;
}