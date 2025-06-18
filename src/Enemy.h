/**
* @file Enemy.h
* @brief 敵関連 / Enemy Related.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Object.h"

class Enemy : public Object {
public:
	Enemy() = default;
	Enemy(int alive, int isCol, const Vec2D& pos, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startShowAngle, double endShowAngle, int showAngleEaseType, int showAngleEaseTime, const Color& color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int popT, int ID = 0, const std::vector<std::any>& params = {})
		: Object(alive, isCol, OBJECT_ENEMY, pos, startAngle, endAngle, angleEaseType, angleEaseTime, startShowAngle, endShowAngle, showAngleEaseType, showAngleEaseTime, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, popT, 0, 0, 0, 0, 0, 0, 0, ID, params) {
	}

	/**
	* @brief 敵の描画 / Enemy Drawing.
	*/
	void ShowEnemy();
private:
	void MoveFunc() override;
	int ColliCheckObject() override;
	int CheckPosBounds() override;
	int CheckCollisionAndBounds() override;
};

void PushBlankEnemies(int idx);

/**
* @brief 敵の生成 / Create Enemy.
*
* @see objectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
int CreateEnemy(const Vec2D& pos, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID = 0, const std::vector<std::any>& params = {});

/**
* @brief 複数の敵の生成 / Create Multiple Enemy.
*
* @see objectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
void CreateEnemyGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int way, double spread, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID = 0, const std::vector<std::any>& params = {});

/**
* @brief 複数の敵の生成(引数減少版) / Create Multiple 敵(reduced argument version).
*
* @see objectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
void CreateSimpleEnemyGroup(const Vec2D& pos, const Color& color, int style, int blend, int pal, double colSize, double size, int way, double spread, int aim, double angle, double speed, int ID = 0, const std::vector<std::any>& params = {});

/**
* @brief 構造体を引数とした複数の敵の生成 / Create Multiple Enemy with structure as argument.
*
* @see objectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
void CreateSmartEnemyGroup(objectParams param);

void ParallelUpdateEnemies(std::array<Enemy, MAX_ENEMY>& enemies);

/**
* @brief 敵の動作と描画 / Enemy Movement and Drawing.
*/
void MoveEnemies();

#endif