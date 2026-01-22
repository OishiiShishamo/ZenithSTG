#pragma once
#ifndef ZENITHSTG_SRC_PLAYER_H_
#define ZENITHSTG_SRC_PLAYER_H_

#define kPlayerDefaultX kCenterX
#define kPlayerDefaultY 900
#define kPlayerDefaultPos Vec2D(kPlayerDefaultX, kPlayerDefaultY)
#define kDefaultLife 2
#define kDefaultBomb 3
#define kPlayerCol 0.0f
#define kPlayerProtect 60

#define kPlayerSideBorderOffset 16
#define kPlayerTopBorderOffset 24
#define kPlayerBottomBorderOffset 32

#define kPlayerNum 1

#include "main.h"

namespace zenithstg {
	enum PlayerFlags {
		kIsFocus = 1 << 0,
		kIsShowCol = 1 << 1,
		kIsMouse = 1 << 2,
		kIsProtect = 1 << 3,
	};

	class Player {
	public:
		std::atomic<std::uint8_t> flags_ = 0b00000000;
		int default_life_ = kDefaultLife;
		std::atomic<int> life_ = 0;
		int default_bomb_ = kDefaultBomb;
		std::atomic<int> bomb_ = 0;
		double col_size_ = 0.0f;
		double slow_ = 0;
		double fast_ = 0;
		// 無敵時間 / Invincibility time.
		int protect_ = 0;
		// 残り無敵時間 / Remaining invincibility time.
		std::atomic<int> protect_time_ = 0;

		// ゲッターとセッター / Getters and Setters.
		Vec2D GetPos();
		void SetPos(const Vec2D& v);
		bool GetIsFocus(std::memory_order order = std::memory_order_seq_cst);
		void SetIsFocus(bool b, std::memory_order order = std::memory_order_seq_cst);
		bool GetIsShowCol(std::memory_order order = std::memory_order_seq_cst);
		bool GetIsMouse(std::memory_order order = std::memory_order_seq_cst);
		void SetIsMouse(bool b, std::memory_order order = std::memory_order_seq_cst);
		bool GetIsProtect(std::memory_order order = std::memory_order_seq_cst);
		void SetIsProtect(bool b, std::memory_order order = std::memory_order_seq_cst);

		double AimPlayer(const Vec2D& v);
		double RangePlayer(const Vec2D& v);
		void MovePlayer();
		void RenderPlayer();
		void Shot();
		bool TryHit();
		void HitPlayer();
		void RoutinePlayer();
	private:
		Vec2D pos_ = Vec2D(0, 0);
		Vec2D vec_ = Vec2D(0, 0);
	};

	extern Player player_;
}

#endif