#pragma once
#ifndef EFFECT_H
#define EFFECT_H

#include "Object.h"

/**
* @class Effect
* @brief エフェクト関連 / Effect Related.
* @extends Object
*/
class Effect : public Object {
public:
	double startPal = 0;
	int palEaseTime = 0;
	int palEaseType = 0;
	double palT = 0;
	Effect() = default;
	Effect(int alive, int isCol, const Vec2D& pos, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startShowAngle, double endShowAngle, int showAngleEaseType, int showAngleEaseTime, const Color& color, int style, int blend, int pal, int palEaseTime, int palEaseType, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int popT, int ID = 0, const std::vector<std::any>& params = {})
		: Object(alive, isCol, OBJECT_EFFECT, pos, startAngle, endAngle, angleEaseType, angleEaseTime, startShowAngle, endShowAngle, showAngleEaseType, showAngleEaseTime, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, popT, 0, 0, 0, 0, 0, 0, 0, ID, params) {
	}

	/**
	* @brief オブジェクトの動作など。 / Object behavior, etc.
	*
	* @param Index 現状用途なし / No current use
	*/
	void UpdateObject(long long Index = 0) override;

	/**
	* @brief イージングによるパラメータの更新。 / Updating parameters by easing.
	*/
	void UpdateEase() override;

	/**
	* @brief エフェクトの描画 / Effect Drawing.
	*/
	void ShowEffect();
	void MoveFunc() override;
};

/**
* @brief エフェクトの生成 / Create Effect.
*
* @see objectParams 引数の詳細はこちらを参照 / See here for details of the argument.
*/
void CreateEffect(const Vec2D& pos, const Color& color, int style, int blend, double pal, int palEaseTime, int palEaseType, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID = 0, const std::vector<std::any>& params = {});

/**
* @brief エフェクトの動作と描画 / Effect Movement and Drawing.
*/
void MoveEffects();

void GrazeEffect(const Vec2D& pos);

#endif