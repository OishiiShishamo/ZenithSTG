#pragma once
#ifndef ZENITHSTG_SRC_MAINLOOP_H_
#define ZENITHSTG_SRC_MAINLOOP_H_

#include "main.h"

//TODO: 変数名いい感じにする

class MainLoop {
public:
	long long front_change_window_size_frame = 0;
	long long front_change_window_frame = 0;
	void Update();
};

#endif