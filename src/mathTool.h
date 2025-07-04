/**
* @file mathTool.h
* @brief 数学系関数まとめ / Math Functions.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef ZENITHSTG_SRC_MATHTOOL_H_
#define ZENITHSTG_SRC_MATHTOOL_H_

/**
* @brief ニュートン法を用いた高速な平方根の計算 / Fast square root calculations using Newton's method.
*/
double fastSqrt(double x, double epsilon = 1e-10);

#endif
