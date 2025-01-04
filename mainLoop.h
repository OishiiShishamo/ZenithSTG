#pragma once
#ifndef MAINLOOP_H
#define MAINLOOP_H

#include "Main.h"

class mainLoop {
public:
	int windowSize = 2;
	long long frontChangeWindowSizeFrame = 0;
	int isWindowSplit = 0;
	void Loop();
};

#endif