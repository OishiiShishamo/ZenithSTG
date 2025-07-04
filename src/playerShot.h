/**
* @file playerShot.h
* @brief プレイヤーショット関連 / Player Shot Related.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef ZENITHSTG_SRC_PLAYERSHOT_H_
#define ZENITHSTG_SRC_PLAYERSHOT_H_

#include "Object.h"

class playerShot : public Object {
public:
	playerShot() = default;
	playerShot(int alive, int isCol, const Vec2D& pos, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startShowAngle, double endShowAngle, int showAngleEaseType, int showAngleEaseTime, const Color& color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int popT, int ID = 0, const std::vector<std::any>& params = {})
		: Object(alive, isCol, OBJECT_PLAYER_SHOT, pos, startAngle, endAngle, angleEaseType, angleEaseTime, startShowAngle, endShowAngle, showAngleEaseType, showAngleEaseTime, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, popT, 0, 0, 0, 0, 0, 0, 0, ID, params) {
	}

	/**
	* @brief プレイヤーショットの描画 / Player Shot Drawing.
	*/
	void ShowPlayerShot();
private:
	void MoveFunc() override;
	int ColliCheckObject() override;
	int CheckPosBounds() override;
	int CheckCollisionAndBounds() override;
};

void PushBlankPlayerShots(int idx);

/**
* @brief プレイヤーショットの生成 / Create Player Shot.
*
* @see objectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
int CreatePlayerShot(const Vec2D& pos, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int SE = SE_NONE, int ID = 0, const std::vector<std::any>& params = {});

void ParallelUpdatePlayerShots(std::array<playerShot, MAX_PLAYER_SHOT>& playerShots);

/**
* @brief プレイヤーショットの動作と描画 / Player Shot Movement and Drawing.
*/
void MovePlayerShots();

#endif