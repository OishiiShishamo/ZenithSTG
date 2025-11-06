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
	class Player {
	public:
		Vec2D pos_ = Vec2D(0, 0);
		Vec2D vec_ = Vec2D(0, 0);
		int default_life_ = kDefaultLife;
		std::atomic<int> life_ = 0;
		int default_bomb_ = kDefaultBomb;
		std::atomic<int> bomb_ = 0;
		double col_size_ = 0.0f;
		double slow_ = 0;
		double fast_ = 0;
		int is_focus_ = 0;
		int is_show_col_ = 0;
		int protect_ = 0;
		std::atomic<int> protect_time_ = 0;
		int is_mouse_ = 0;
		double AimPlayer(const Vec2D& v);
		double RangePlayer(const Vec2D& v);
		void MovePlayer();
		void RenderPlayer();
		void Shot();
		void HitPlayer();
		void RoutinePlayer();
	};

	extern Player player_;
}

#endif