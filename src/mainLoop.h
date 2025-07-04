#pragma once
#ifndef ZENITHSTG_SRC_MAINLOOP_H_
#define ZENITHSTG_SRC_MAINLOOP_H_

#include "Main.h"

//TODO: 変数名いい感じにする

class mainLoop {
public:
	long long frontChangeWindowSizeFrame = 0;
	long long frontChangeWindowFrame = 0;
	void Loop();
};

#endif