/**
* @file Utility.h
* @brief あったら便利そうなやつまとめ / Utilities.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef ZENITHSTG_SRC_UTILITY_H_
#define ZENITHSTG_SRC_UTILITY_H_

/**
* @brief 画像を3D回転させて描画する。 / Draws an image with 3D rotation.
*
* @param x 描画するX座標 / X coordinate to be drawn
* @param y 描画するY座標 / Y coordinate to be drawn
* @param rate 描画サイズの倍率 / Drawing size magnification
* @param angle_x X回転 / X-rotation
* @param angle_y Y回転 / Y-rotation
* @param angle_z Z回転 / Z-rotation
* @param handle グラフィックハンドルの指定 / Graphic handle specification
* @param tran_flag 透過するかどうか / Transparent or not
* @param x_turn_flag X軸で反転するかどうか / Whether inverted on X-axis
* @param y_turn_flag Y軸で反転するかどうか / Whether inverted on Y-axis
*/
void DrawRotaGraph4(int x, int y, double rate, double angle_x, double angle_y, double angle_z, int handle, int tran_flag = 1, int x_turn_flag = 0, int y_turn_flag = 0);

/**
* @brief HSVで色を生成 / HSV Color Generation.
*
* @param h 色相 / Hue
* @param s 彩度 / Saturation
* @param v 明度 / value
*/
Color GetColorHsv(double h, double s, double v);

/**
* @brief HSVを使用したゲーミングカラーの生成 / hSV used Gaming Color Generation.
*
* @param mul 色の変化速度の倍率 / Color change speed multiplier
*/
Color GamingColor(int offset = 0, double mul = 1);

/**
* @brief 余計なブレンドモードの切り替えを防いだブレンドモードの切り替え / Switching blend modes preventing unnecessary blend mode switching
*
* @param blend_mode ブレンドモード / Blend Mode
* @param pal ブレンドのパラメータ / Blend Param
*/
void SmartSetDrawBlendMode(int blend_mode, int pal);

/**
* @brief 角度からラジアンに変換 / Angle to Radian.
*
* @param angle 角度 / Angle
*/
double Rad(double angle);
void ApplyWindowSize();

template <typename T, size_t N>
T&
SafeAccess(std::array<T, N>& array, size_t index) {
#ifdef NDEBUG
	return array[index];
#else
	return array.at(index);
#endif
}

template <typename T>
T&
SafeAccess(std::vector<T>& array, size_t index) {
#ifdef NDEBUG
	return array[index];
#else
	return array.at(index);
#endif
}

template <typename T, size_t N>
T&
SafePtrAccess(std::array<T, N>* array, size_t index) {
#ifdef NDEBUG
	return (*array)[index];
#else
	return array->at(index);
#endif
}

template <typename T>
T&
SafePtrAccess(std::vector<T>* array, size_t index) {
#ifdef NDEBUG
	return (*array)[index];
#else
	return array->at(index);
#endif
}

inline int isRangeValid(int index, int max, int min = 0) {
	return ((index >= min) && (index < max)) == 0;
}

#endif