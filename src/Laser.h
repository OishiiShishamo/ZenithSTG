/**
* @file Laser.h
* @brief レーザー関連 / Laser Related.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef ZENITHSTG_SRC_LASER_H_
#define ZENITHSTG_SRC_LASER_H_

#include "Object.h"

class Laser : public Object {
public:
	Laser() = default;
	Laser(int alive, int isCol, const Vec2D& pos, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startShowAngle, double endShowAngle, int showAngleEaseType, int showAngleEaseTime, Color color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int popT, double length, double width, int ID = 0, const std::vector<std::any>& params = {})
		: Object(alive, isCol, OBJECT_LASER, pos, startAngle, endAngle, angleEaseType, angleEaseTime, startShowAngle, endShowAngle, showAngleEaseType, showAngleEaseTime, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, popT, length, width, 0, 0, 0, 0, 0, ID, params) {
	}

	/**
	* @brief レーザーの描画 / Laser Drawing.
	*/
	void ShowLaser();
private:
	void MoveFunc() override;
	int ColliCheckObject() override;
#if GRAZE_ENABLED == 1
	void GrazeObject() override;
#endif
	int CheckPosBounds() override;
	int CheckCollisionAndBounds() override;
	
};

void PushBlankLasers(int idx);

/**
* @brief レーザーの生成 / Create Laser.
*
* @see objectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
int CreateLaser(const Vec2D& pos, double length, double width, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int SE = SE_NONE, int ID = 0, const std::vector<std::any>& params = {});

/**
* @brief 複数のレーザーの生成 / Create Multiple Laser.
*
* @see objectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
void CreateLaserGroup(const Vec2D& pos, double length, double width, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int way, double spread, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int SE = SE_NONE, int ID = 0, const std::vector<std::any>& params = {});

/**
* @brief 複数のレーザーの生成(引数減少版) / Create Multiple Laser(reduced argument version).
*
* @see objectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
void CreateSimpleLaserGroup(const Vec2D& pos, double length, double width, const Color& color, int style, int blend, int pal, double colSize, double size, int way, double spread, int aim, double angle, double speed, int SE = SE_NONE, int ID = 0, const std::vector<std::any>& params = {});

/**
* @brief 構造体を引数とした複数のレーザーの生成 / Create Multiple Laser with structure as argument.
*
* @see objectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
void CreateSmartLaserGroup(objectParams param);

void ParallelUpdateLasers(std::array<Laser, MAX_LASER>& lasers);

/**
* @brief レーザーの動作と描画 / Laser Movement and Drawing.
*/
void MoveLasers();

#endif