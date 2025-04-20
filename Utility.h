/**
* @file Utility.h
* @brief あったら便利そうなやつまとめ / Utilities.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef UTILITY_H
#define UTILITY_H

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

/**
* @brief HSVで色を生成 / HSV Color Generation.
* 
* @param 色相 / Hue
* @param 彩度 / Saturation
* @param 明度 / Value
*/
Color GetColorHSV(double H, double S, double V);

/**
* @brief HSVを使用したゲーミングカラーの生成 / HSV used Gaming Color Generation.
* 
* @param mul 色の変化速度の倍率 / Color change speed multiplier
*/
Color GamingColor(double mul = 1);

/**
* @brief 余計なブレンドモードの切り替えを防いだブレンドモードの切り替え / Switching blend modes preventing unnecessary blend mode switching
* 
* @param BlendMode ブレンドモード / Blend Mode
* @param Pal ブレンドのパラメータ / Blend Param
*/
void SmartSetDrawBlendMode(int BlendMode, int Pal);

/**
* @brief 角度からラジアンに変換 / Angle to Radian.
* 
* @param angle 角度 / Angle
*/
double Rad(double angle);
void apply_window_size();
int rnd();

#endif