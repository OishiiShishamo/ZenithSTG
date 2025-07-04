/**
* @file Bullet.h
* @brief 弾関連 / Bullet Related.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef ZENITHSTG_SRC_BULLET_H_
#define ZENITHSTG_SRC_BULLET_H_

#include "Object.h"

/**
* @class Bullet
* @brief 弾関連 / Bullet Related.
* @extends Object
*/
class Bullet : public Object {
public:
	Bullet() = default;
	Bullet(int alive, int isCol, const Vec2D& pos, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startShowAngle, double endShowAngle, int showAngleEaseType, int showAngleEaseTime, const Color& color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int popT, int ID = 0, const std::vector<std::any>& params = {})
		: Object(alive, isCol, OBJECT_BULLET, pos, startAngle, endAngle, angleEaseType, angleEaseTime, startShowAngle, endShowAngle, showAngleEaseType, showAngleEaseTime, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, popT, 0, 0, 0, 0, 0, 0, 0, ID, params) {
	}

	/**
	* @brief 弾の描画 / Bullet Drawing.
	*/
	void ShowBullet();
private:
	void MoveFunc() override;
	int ColliCheckObject() override;
#if GRAZE_ENABLED == 1
	void GrazeObject() override;
#endif
	int CheckPosBounds() override;

	int CheckCollisionAndBounds() override;
};

void PushBlankBullets(int idx);

/**
* @brief 弾の生成 / Create Bullet.
*
* @see objectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
int CreateBullet(const Vec2D& pos, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int SE = SE_NONE, int ID = 0, const std::vector<std::any>& params = {});

/**
* @brief 複数の弾の生成 / Create Multiple Bullet.
*
* @see objectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
void CreateBulletGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int way, double spread, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int SE = SE_NONE, int ID = 0, const std::vector<std::any>& params = {});

/**
* @brief 複数の弾の生成(引数減少版) / Create Multiple Bullet(reduced argument version).
*
* @see objectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
void CreateSimpleBulletGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, double colSize, double size, int way, double spread, int aim, double angle, double speed, int SE = SE_NONE, int ID = 0, const std::vector<std::any>& params = {});

/**
* @brief 構造体を引数とした複数の弾の生成 / Create Multiple Bullet with structure as argument.
*
* @see objectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
void CreateSmartBulletGroup(objectParams param);

void ParallelUpdateBullets(std::array<Bullet, MAX_BULLET>& bullets);

/**
* @brief 弾の動作と描画 / Bullet Movement and Drawing.
*/
void MoveBullets();

#endif