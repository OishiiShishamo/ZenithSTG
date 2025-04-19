#pragma once
#ifndef UTILITY_H
#define UTILITY_H

using namespace std;
#include <string>

//あったら便利そうなやつまとめ

/**
* @brief 画像を3D回転させて描画する。 / Draws an image with 3D rotation.
*
* @param x 描画するX座標 / X coordinate to be drawn
* @param y 描画するY座標 / Y coordinate to be drawn
* @param rate 描画サイズの倍率 / Drawing size magnification
* @param anglex X回転 / X-rotation
* @param angley Y回転 / Y-rotation
* @param anglez Z回転 / Z-rotation
* @param handle グラフィックハンドルの指定 / Graphic handle specification
* @param tranflag 透過するかどうか / Transparent or not
* @param x_turn_flag X軸で反転するかどうか / Whether inverted on X-axis
* @param y_turn_flag Y軸で反転するかどうか / Whether inverted on Y-axis
*/


void DrawRotaGraph4(int x, int y, double rate, double anglex, double angley, double anglez, int handle, int tranflag, int x_turn_flag, int y_turn_flag);
Color GetColorHSV(double H, double S, double V);
Color GamingColor(double mul = 1);
void SmartSetDrawBlendMode(int BlendMode, int Pal);
double Rad(double angle);
void apply_window_size();
int rnd();
void add_debugging(string debug);
void debuging2log();

#endif