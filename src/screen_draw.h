#pragma once
#ifndef ZENITHSTG_SRC_SCREEN_DRAW_H_
#define ZENITHSTG_SRC_SCREEN_DRAW_H_

#include "DxLib.h"

#include "main.h"
#include "player.h"

namespace zenithstg {
	extern int background_canvas;
	extern int back_object_canvas;
	extern int front_object_canvas;
	extern int player_canvas;
	extern int bomb_canvas;
	extern int screen_canvas;
	extern int ui_canvas;

	extern int is_window_split;

	void ScreenDraw();
}

#endif