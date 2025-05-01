/**
* @file FPS.h
* @brief 実FPSの描画と計算 / Calculation and display of real FPS.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef FPS_H
#define FPS_H

#include "Color.h"

/**
* @brief 実FPSの計算と表示 / Calculation and display of real FPS.
* 
* @param pos 表示する座標 / Display Position
* @param fontSize FPS表示のフォントサイズ / Display FPS Font Size
* @param elapsedFrame 前回の描画から経過したフレーム数 / Number of frames elapsed since the last drawing
* @param color フォントカラー / Font Color
*/
void ShowFPS(Vec2D pos, int fontSize, int elapsedFrame, Color color);

#endif