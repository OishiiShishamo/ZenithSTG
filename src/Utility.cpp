﻿#include "Main.h"

#include "Color.h"
#include "Utility.h"

bool debuging = true;

void apply_window_size() {
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	if (width - height < 560 - 1) {
		Properties.windowSize = 0;
	}
	else if (width - height < 700 - 1) {
		Properties.windowSize = 1;
	}
	else if (width - height < 840 - 1) {
		Properties.windowSize = 2;
	}
	else {
		Properties.windowSize = 1;
	}

	if (debuging) Properties.windowSize = 1;

	return;
}

int rnd() {
	int rnd = std::rand() % 65535;    // 0〜65536の乱数
	return rnd;
}

void
DrawRotaGraph4(int x, int y, double rate, double anglex, double angley, double anglez, int handle, int tranflag, int x_turn_flag, int y_turn_flag) {
	int sx = 0, sy = 0;
	MATRIX m;
	VECTOR v;

	GetGraphSize(handle, &sx, &sy);
	m = MMult(MMult(MGetRotZ(anglez), MGetRotY(angley)), MGetRotX(anglex));
	m.m[0][0] *= rate; m.m[0][1] *= rate; m.m[0][2] *= rate;
	m.m[1][0] *= rate; m.m[1][1] *= rate; m.m[1][2] *= rate;
	int lux, luy, rux, ruy, rdx, rdy, ldx, ldy;
	if (x_turn_flag == FALSE) {
		if (y_turn_flag == FALSE) {
			v.x = sx / 2; v.y = -sy / 2;  v.z = 0.0;
			v = VTransform(v, m);
			rux = x + v.x, ruy = y + v.y;
			ldx = x - v.x, ldy = y - v.y;

			v.x = -sx / 2; v.y = -sy / 2;  v.z = 0.0;
			v = VTransform(v, m);
			lux = x + v.x, luy = y + v.y;
			rdx = x - v.x, rdy = y - v.y;
		}
		else {
			v.x = sx / 2; v.y = sy / 2;  v.z = 0.0;
			v = VTransform(v, m);
			rux = x + v.x, ruy = y + v.y;
			ldx = x - v.x, ldy = y - v.y;

			v.x = -sx / 2; v.y = sy / 2;  v.z = 0.0;
			v = VTransform(v, m);
			lux = x + v.x, luy = y + v.y;
			rdx = x - v.x, rdy = y - v.y;
		}
	}
	else {
		if (y_turn_flag == FALSE) {
			v.x = -sx / 2; v.y = -sy / 2;  v.z = 0.0;
			v = VTransform(v, m);
			rux = x + v.x, ruy = y + v.y;
			ldx = x - v.x, ldy = y - v.y;

			v.x = sx / 2; v.y = -sy / 2;  v.z = 0.0;
			v = VTransform(v, m);
			lux = x + v.x, luy = y + v.y;
			rdx = x - v.x, rdy = y - v.y;
		}
		else {
			v.x = -sx / 2; v.y = sy / 2;  v.z = 0.0;
			v = VTransform(v, m);
			rux = x + v.x, ruy = y + v.y;
			ldx = x - v.x, ldy = y - v.y;

			v.x = sx / 2; v.y = sy / 2;  v.z = 0.0;
			v = VTransform(v, m);
			lux = x + v.x, luy = y + v.y;
			rdx = x - v.x, rdy = y - v.y;
		}
	}
	DrawModiGraph(lux, luy, rux, ruy, rdx, rdy, ldx, ldy, handle, tranflag);
}

Color
GetColorHSV(double H, double S, double V) {
	int hi;
	double f, p, q, t;
	double r = 0, g = 0, b = 0;
	int ir, ig, ib;

	hi = (int)(H / 60.0f);
	hi = hi == 6 ? 5 : hi %= 6;
	f = H / 60.0f - (double)hi;
	p = V * (1.0f - S);
	q = V * (1.0f - f * S);
	t = V * (1.0f - (1.0f - f) * S);
	switch (hi)
	{
	case 0: r = V; g = t; b = p; break;
	case 1: r = q; g = V; b = p; break;
	case 2: r = p; g = V; b = t; break;
	case 3: r = p; g = q; b = V; break;
	case 4: r = t; g = p; b = V; break;
	case 5: r = V; g = p; b = q; break;
	}

	ir = (int)(r * 255.0f);
	if (ir > 255) ir = 255;
	else if (ir < 0) ir = 0;

	ig = (int)(g * 255.0f);
	if (ig > 255) ig = 255;
	else if (ig < 0) ig = 0;

	ib = (int)(b * 255.0f);
	if (ib > 255) ib = 255;
	else if (ib < 0) ib = 0;

	return Color(ir, ig, ib);
}

Color
GamingColor(double mul) {
	return GetColorHSV(std::fmod(frame * mul, 360), 1, 1);
}

void
SmartSetDrawBlendMode(int BlendMode, int Pal) {
	GetDrawBlendMode(&currentBlendMode, &currentBlendPal);
	if (!(currentBlendMode == BlendMode && currentBlendPal == Pal)) {
		SetDrawBlendMode(BlendMode, Pal);
	}
}

double
Rad(double angle) {
	return (PI / 180) * angle;
}