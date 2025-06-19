#include "Color.h"
#include "Player.h"
#include "playerShot.h"
#include "Sound.h"

//TODO: もっと真面目に作る
//TODO: コントローラーに対応させる

double
Player::AimPlayer(const Vec2D& v) {
	return atan2(-double(pos.GetY() - v.GetY()), double(pos.GetX() - v.GetX()));
}

double
Player::RangePlayer(const Vec2D& v) {
	return Range(v, pos);
}

void
Player::MovePlayer() {
	vec = Vec2D(_mm_set1_pd(0));
	if (isMouse == 1) {
		int x, y;
		GetMousePoint(&x, &y);
		pos.xy = _mm_set_pd(y, x);
	}
	else {
		if (GetAsyncKeyState(VK_RIGHT)) vec += Vec2D(1, 0);
		if (GetAsyncKeyState(VK_LEFT)) vec -= Vec2D(1, 0);
		if (GetAsyncKeyState(VK_UP)) vec -= Vec2D(0, 1);
		if (GetAsyncKeyState(VK_DOWN)) vec += Vec2D(0, 1);

		vec.VecNorm();

		if (GetAsyncKeyState(VK_SHIFT)) {
			pos += vec * Slow;
		}
		else {
			pos += vec * Fast;
		}
	}
	if (pos.GetX() < BORDER_LEFT) pos.SetX(BORDER_LEFT);
	if (pos.GetX() > BORDER_RIGHT) pos.SetX(BORDER_RIGHT);
	if (pos.GetY() > BORDER_DOWN) pos.SetY(BORDER_DOWN);
	if (pos.GetY() < BORDER_UP) pos.SetY(BORDER_UP);
}

void
Player::ShowPlayer() {
	SmartSetDrawBlendMode(BLEND_NOBLEND, 255);
	DrawRotaGraph(pos.GetX(), pos.GetY(), 1.0f, 0, SAFE_ACCESS(imgRes.PlayerGH, 0), 1);
	if (isColShow == 1) {
		SmartSetDrawBlendMode(BLEND_NOBLEND, 255);
		DrawCircle(pos.GetX(), pos.GetY(), colSize, GetColor(255, 255, 255), 1);
		DrawFormatString(pos.GetX(), pos.GetY(), GetColor(GetColorHSV(std::fmod(t, 360), 1, 1).r, GetColorHSV(std::fmod(t, 360), 1, 1).g, GetColorHSV(std::fmod(t, 360), 1, 1).b), "%f", colSize);
	}
}

void
Player::Shot() {
	if (GetAsyncKeyState(0x5A)) {
		CreatePlayerShot(pos, Color(255, 255, 255), 0, BLEND_ADD, 255, 1, 24, 24, 0, 0, 1.0f, 1.0f, 0, 0, Rad(90), Rad(90), 0, 0, 0, 50, EASEINCUBIC, 60, 0);
	}
}

void
Player::HitPlayer() {
	if (protectTime > 0) {
		return;
	}
	protectTime = Protect;
	pos = P_DEFAULT_POS;
	Life -= 1;
	Bomb = defaultBomb;
	soundMng.ReserveSE(SE_PLAYER_HIT);
}

void
Player::RoutinePlayer() {
	MovePlayer();
	ShowPlayer();
	Shot();
	protectTime--;
}

Player Plyr;