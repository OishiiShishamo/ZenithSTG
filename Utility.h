#pragma once
#ifndef UTILITY_H
#define UTILITY_H

//あったら便利そうなやつまとめ

void DrawRotaGraph4(int x, int y, double rate, double anglex, double angley, double anglez, int handle, int tranflag, int x_turn_flag, int y_turn_flag);
Color GetColorHSV(double H, double S, double V);
Color GamingColor(double mul = 1);
void SmartSetDrawBlendMode(int BlendMode, int Pal);
double Rad(double angle);

#endif