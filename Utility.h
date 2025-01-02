#pragma once
#ifndef SSMLIB_H
#define SSMLIB_H

#include "main.h"

//‚ ‚Á‚½‚ç•Ö—˜‚»‚¤‚È‚â‚Â‚Ü‚Æ‚ß

void VecNorm(double& x, double& y);
void DrawRotaGraph4(int x, int y, double rate, double anglex, double angley, double anglez, int handle, int tranflag, int x_turn_flag, int y_turn_flag);
Color GetColorHSV(float H, float S, float V);
void SmartSetDrawBlendMode(int BlendMode, int Pal);
double Rad(double angle);
double Range(int y1, int y2, int x1, int x2);

#endif