#pragma once
#ifndef COLOR_H
#define COLOR_H

#include "Main.h"

//SIMPLE

#define C_RED 255, 0, 0
#define C_GREEN 0, 255, 0
#define C_BLUE 0, 0, 255
#define C_YELLOW 255, 255, 0
#define C_AQUA 0, 255, 255
#define C_CYAN 0, 255, 255
#define C_PURPLE 255, 0, 255
#define C_ORANGE 255, 127, 0
#define C_WHITE 255, 255, 255
#define C_GRAY 127, 127, 127
#define C_BLACK 0, 0, 0

//NOT-SIMPLE

#define C_ALICE_BLUE 240, 248, 255
#define C_ANTIQUE_WHITE 250, 235, 215
#define C_AQUAMARINE 127, 255, 212
#define C_AZURE 240, 255, 255
#define C_BEIGE 245, 245, 220
#define C_BISQUE 255, 228, 196
#define C_BLANCHEDALMOND 255, 235, 205
#define C_BLUE_VIOLET 138, 43, 226
#define C_BROWN 165, 42, 42
#define C_BURLY_WOOD 222, 184, 135

class Color {
public:
	int r = 0;
	int g = 0;
	int b = 0;
	Color(int r, int g, int b) : r(r), g(g), b(b) {}
};

#endif