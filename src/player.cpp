#include "player.h"

#include "player_shot.h"
#include "particle.h"
#include "sound.h"

//TODO: もっと真面目に作る
//TODO: コントローラーに対応させる

namespace zenithstg {
	double Player::AimPlayer(const Vec2D& v) {
		return Vec2DToAngle(pos_, v);
	}

	double Player::RangePlayer(const Vec2D& v) {
		return Range(v, pos_);
	}

	void Player::MovePlayer() {
		vec_ = Vec2D(_mm_set1_pd(0));
		if (is_mouse_ == 1) {
			int x, y;
			GetMousePoint(&x, &y);
			pos_.SetXY(x, y);
		}
		else {
			if (GetAsyncKeyState(VK_RIGHT) & (1 << 15)) vec_ += Vec2D(1, 0);
			if (GetAsyncKeyState(VK_LEFT) & (1 << 15)) vec_ -= Vec2D(1, 0);
			if (GetAsyncKeyState(VK_UP) & (1 << 15)) vec_ -= Vec2D(0, 1);
			if (GetAsyncKeyState(VK_DOWN) & (1 << 15)) vec_ += Vec2D(0, 1);

			vec_.VecNorm();

			if (GetAsyncKeyState(VK_SHIFT) & (1 << 15)) {
				pos_ += vec_ * slow_;
			}
			else {
				pos_ += vec_ * fast_;
			}
		}
		if (pos_.GetX() < kBorderLeft + kPlayerSideBorderOffset) pos_.SetX(kBorderLeft + kPlayerSideBorderOffset);
		if (pos_.GetX() > kBorderRight - kPlayerSideBorderOffset) pos_.SetX(kBorderRight - kPlayerSideBorderOffset);
		if (pos_.GetY() > kBorderDown - kPlayerBottomBorderOffset) pos_.SetY(kBorderDown - kPlayerBottomBorderOffset);
		if (pos_.GetY() < kBorderUp + kPlayerTopBorderOffset) pos_.SetY(kBorderUp + kPlayerTopBorderOffset);
	}

	void Player::ShowPlayer() {
		SmartSetDrawBlendMode(kBlendNoblend, 255);
		DrawRotaGraph(pos_.GetX(), pos_.GetY(), 1.0f, 0, SafeAccess(img_res.player_gh, 0), 1);
		if (kIsColShow == 1) {
			SmartSetDrawBlendMode(kBlendNoblend, 255);
			DrawCircle(pos_.GetX(), pos_.GetY(), col_size_, GetColor(255, 255, 255), 1);
			DrawFormatString(pos_.GetX(), pos_.GetY(), GetColor(GamingColor().GetR(), GamingColor().GetG(), GamingColor().GetB()), "%f", col_size_);
		}
	}

	void Player::Shot() {
		if (GetAsyncKeyState(0x5A) & (1 << 15)) {
			CreatePlayerShot(pos_, Color(255, 255, 255), 0, kBlendAdd, 255, 1, 24, 24, 0, 0, 1.0f, 1.0f, 0, 0, Rad(90), Rad(90), 0, 0, 0, 50, kEaseInCubic, 60, -1, 0);
		}
	}

	void Player::HitPlayer() {
		if (protect_time_ > 0) {
			return;
		}
		for (int i = 0; i < 64; i++) {
			double angle = Rad(static_cast<double>(rng() % 36000) / 100.0);
			CreateParticle(pos_, Color(kColorRed), ParticleType::kParticleRect, BlendType::kBlendAdd, 255, EaseType::kEaseInQuad, 60, 0, 0, 0, 0, 0, 0.5f, 0.0f, EaseType::kEaseInQuad, 60, 0, angle, angle, 0, 0, static_cast<double>(rng() % 160) / 10.0f + 3, 0.0f, EaseType::kEaseInQuad, 60);
		}
		protect_time_ = protect_;
		pos_ = kPlayerDefaultPos;
		life_ -= 1;
		bomb_ = default_bomb_;
		sound_mng_.ReserveSe(kSoundEffectPlayerHit);
	}

	void Player::RoutinePlayer() {
		MovePlayer();
		ShowPlayer();
		Shot();
		protect_time_--;
	}

	Player player_;
}