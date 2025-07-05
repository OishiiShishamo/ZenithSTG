/**
* @file Init.h
* @brief 初期化関連 / Initialization related.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef ZENITHSTG_SRC_INIT_H_
#define ZENITHSTG_SRC_INIT_H_

/**
* @brief DxLib_Init()実行前に行う初期化処理 / Initialization process performed before DxLib_Init() execution.
*/
void Init();

/**
* @brief DxLib_Init()実行後に行うグラフィックハンドラの取得などの初期化処理 / Initialization processes such as acquisition of graphics handler to be performed after DxLib_Init() is executed.
*/
void ResInit();

#endif