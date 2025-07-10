#pragma once
#ifndef ZENITHSTG_SRC_BACKGROUND_H_
#define ZENITHSTG_SRC_BACKGROUND_H_

#include "DxLib.h"

#include "color.h"

namespace zenithstg {
	class Background {
	public:
		int id = 0;
		void DrawBackground();
	};

	extern Background bg_;
}

#endif