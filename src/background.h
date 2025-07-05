#pragma once
#ifndef ZENITHSTG_SRC_BACKGROUND_H_
#define ZENITHSTG_SRC_BACKGROUND_H_

class Background {
public:
	int id = 0;
	void DrawBackground();
};

extern Background bg_;

#endif