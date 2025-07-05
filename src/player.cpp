#include "player.h"
#include "player_shot.h"
#include "sound.h"

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
	if (is_mouse == 1) {
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
			pos += vec * slow;
		}
		else {
			pos += vec * fast;
		}
	}
	if (pos.GetX() < kBorderLeft + kPlayerSideBorderOffset) pos.SetX(kBorderLeft + kPlayerSideBorderOffset);
	if (pos.GetX() > kBorderRight - kPlayerSideBorderOffset) pos.SetX(kBorderRight - kPlayerSideBorderOffset);
	if (pos.GetY() > kBorderDown - kPlayerBottomBorderOffset) pos.SetY(kBorderDown - kPlayerBottomBorderOffset);
	if (pos.GetY() < kBorderUp + kPlayerTopBorderOffset) pos.SetY(kBorderUp + kPlayerTopBorderOffset);
}

void
Player::ShowPlayer() {
	SmartSetDrawBlendMode(kBlendNoblend, 255);
	DrawRotaGraph(pos.GetX(), pos.GetY(), 1.0f, 0, SafeAccess(img_res.player_gh, 0), 1);
	if (kIsColShow == 1) {
		SmartSetDrawBlendMode(kBlendNoblend, 255);
		DrawCircle(pos.GetX(), pos.GetY(), col_size, GetColor(255, 255, 255), 1);
		DrawFormatString(pos.GetX(), pos.GetY(), GetColor(GetColorHsv(std::fmod(t, 360), 1, 1).r, GetColorHsv(std::fmod(t, 360), 1, 1).g, GetColorHsv(std::fmod(t, 360), 1, 1).b), "%f", col_size);
	}
}

void
Player::Shot() {
	if (GetAsyncKeyState(0x5A)) {
		CreatePlayerShot(pos, Color(255, 255, 255), 0, kBlendAdd, 255, 1, 24, 24, 0, 0, 1.0f, 1.0f, 0, 0, Rad(90), Rad(90), 0, 0, 0, 50, kEaseInCubic, 60, -1, 0);
	}
}

void
Player::HitPlayer() {
	if (protect_time > 0) {
		return;
	}
	protect_time = rrotect;
	pos = kPlayerDefaultPos;
	life -= 1;
	bomb = default_bomb;
	sound_mng_.ReserveSe(kSoundEffectPlayerHit);
}

void
Player::RoutinePlayer() {
	MovePlayer();
	ShowPlayer();
	Shot();
	protect_time--;
}

Player Plyr;