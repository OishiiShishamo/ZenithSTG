/**
* @file FPS.h
* @brief 実FPSの描画と計算 / Calculation and display of real FPS.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef ZENITHSTG_SRC_FPS_H_
#define ZENITHSTG_SRC_FPS_H_

#include "DxLib.h"

#include "bullet.h"
#include "color.h"
#include "vec2d.h"

/**
* @brief 実FPSの計算と表示 / Calculation and display of real FPS.
* 
* @param pos 表示する座標 / Display Position
* @param elapsed_frame 前回の描画から経過したフレーム数 / Number of frames elapsed since the last drawing
* @param color フォントカラー / Font Color
*/
void ShowFPS(Vec2D pos, int elapsed_frame, zenithstg::Color color);

#endif