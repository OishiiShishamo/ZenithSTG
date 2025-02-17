#pragma once
#ifndef MAINLOOP_H
#define MAINLOOP_H

#include "Main.h"

//TODO: 変数名いい感じにする

class mainLoop {
public:
	long long frontChangeWindowSizeFrame = 0;
	long long frontChangeWindowFrame = 0;
	int isWindowSplit = 0;
	void Loop();
};

#endif