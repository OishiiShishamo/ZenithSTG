#pragma once
#ifndef SSMLIB_H
#define SSMLIB_H

//あったら便利そうなやつまとめ

void DrawRotaGraph4(int x, int y, double rate, double anglex, double angley, double anglez, int handle, int tranflag, int x_turn_flag, int y_turn_flag);
Color GetColorHSV(float H, float S, float V);
void SmartSetDrawBlendMode(int BlendMode, int Pal);
double Rad(double angle);

#endif