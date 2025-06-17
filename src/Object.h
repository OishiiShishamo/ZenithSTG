/**
* @file Object.h
* @brief オブジェクトの基底クラスを定義している / Defines the super class of the object.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include "Color.h"

/**
* @brief オブジェクトの生成に関するもの / Relates to the creation of objects
*
* @param pos 生成位置 / Create Position
* @param color 色 / Color
* @param style 見た目 / Style
* @param blend ブレンドモード / Blend Mode
* @param pal ブレンドのパラメータ / Blend Param
* @param isCol 判定の有無 / Collision availability
* @param startColSize 判定サイズの始点 / Start Collision Size
* @param endColSize 判定サイズの終点 / End Collision Size
* @param colSizeEaseType 判定サイズのイージング方法 / Easing method for Collision Size
* @param colSizeEaseTime 判定サイズのイージングにかかる時間 / Time required for Collision Size easing
* @param startSize 表示サイズの始点 / Start Display Size
* @param endSize 表示サイズの終点 / End Display Size
* @param sizeEaseType 表示サイズのイージング方法 / Easing method for Display Size
* @param sizeEaseTime 表示サイズのイージングにかかる時間 / Time required for Display Size easing
* @param way way数 / way num
* @param spread 拡散 / spread
* @param aim 自機に角度を合わせるか(1 = 自機狙い, 2 = 自機外し) / Aim Player(1 = targeting, 2 = offset targeting)
* @param startAngle 角度の始点 / Start Angle
* @param endAngle 角度の終点 / End Angle
* @param angleEaseType 角度のイージング方法 / Easing method for Angle
* @param angleEaseTime 角度のイージングにかかる時間 / Time required for Angle easing
* @param startSpeed 速度の始点 / Start Speed
* @param endSpeed 速度の終点 / End Speed
* @param speedEaseType 速度のイージング方法 / Easing method for Speed
* @param speedEaseTime 速度のイージングにかかる時間 / Time required for Speed easing
* @param ID 特殊な動作を行うためのID / ID for special operation
* @param params 特殊な動作を行うためのパラメータ / Parameter for special operation
*/
struct objectParams {
	Vec2D pos = Vec2D(0, 0);
	double length = 0;
	double width = 0;
	Color color = Color(0, 0, 0);
	int style = 0;
	int blend = 0;
	int pal = 255;
	int isCol = 1;
	int isAlignedAngle = 1;
	int isGraze = 1;
	double startColSize = 0;
	double endColSize = 0;
	int colSizeEaseType = 0;
	int colSizeEaseTime = 0;
	double startSize = 0;
	double endSize = 0;
	int sizeEaseType = 0;
	int sizeEaseTime = 0;
	int way = 1;
	double spread = tau;
	int aim = 0;
	double startAngle = 0;
	double endAngle = 0;
	int angleEaseType = 0;
	int angleEaseTime = 0;
	double startShowAngle = 0;
	double endShowAngle = 0;
	int showAngleEaseType = 0;
	int showAngleEaseTime = 0;
	double startSpeed = 0;
	double endSpeed = 0;
	int speedEaseType = 0;
	int speedEaseTime = 0;
	int ID = 0;
	std::vector<std::any> params;
};

/**
* @enum objectFlags
* @brief オブジェクトの状態をまとめたもの / A summary of the object's state.
*/
enum objectFlags {
	IS_ALIVE = 1 << 0,
	IS_COL = 1 << 1,
	IS_HEAD = 1 << 2,
	IS_GRAZE = 1 << 3,
};

/**
* @class Object
* @brief オブジェクトの基底クラス / Objects Super Class!!!!
*/
class Object {
public:
	std::uint8_t flags = 0b00001010;
	int objType = 0;
	Vec2D pos = Vec2D(0, 0);
	Vec2D vec = Vec2D(0, 0);
	double startAngle = 0;
	double endAngle = 0;
	int angleEaseType = 0;
	int angleEaseTime = 0;
	double angle = 0;
	double startShowAngle = 0;
	double endShowAngle = 0;
	int showAngleEaseType = 0;
	int showAngleEaseTime = 0;
	double showAngle = 0;
	int isAlignedAngle = 1;
	Color color = Color(0, 0, 0);
	int style = 0;
	int blend = 0;
	double pal = 255;
	double startColSize = 0;
	double endColSize = 0;
	int colSizeEaseType = 0;
	int colSizeEaseTime = 0;
	double colSize = 0;
	double startSize = 0;
	double endSize = 0;
	int sizeEaseType = 0;
	int sizeEaseTime = 0;
	double size = 1.0f;
	double startSpeed = 0;
	double endSpeed = 0;
	int speedEaseType = 0;
	int speedEaseTime = 0;
	double speed = 0.0f;
	long long popT = 0;
	double angleT = 0, speedT = 0, colSizeT = 0, sizeT = 0;
	double length = 0;
	double width = 0;
	long long frontNode = 0;
	long long nextNode = -1;
	int currentNodeNum = 0;
	int ID = 0;
	long long index = 0;
	std::vector<std::any> params;
	Object() = default;
	Object(std::uint8_t alive, std::uint8_t isCol, int objType, const Vec2D& pos, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startShowAngle, double endShowAngle, int showAngleEaseType, int showAngleEaseTime, const Color& color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int popT = 0, double length = 0, double width = 0, long long frontNode = 0, long long nextNode = 0, int currentNodeNum = 0, int isHead = 0, long long index = 0, int ID = 0, const std::vector<std::any>& params = {}, int isGraze = 1)
		: objType(objType), pos(pos), startAngle(startAngle), endAngle(endAngle), angleEaseType(angleEaseType), angleEaseTime(angleEaseTime), startShowAngle(startShowAngle), endShowAngle(endShowAngle), showAngleEaseType(showAngleEaseType), showAngleEaseTime(showAngleEaseTime), color(color), style(style), blend(blend), pal(pal), startColSize(startColSize), endColSize(endColSize), colSizeEaseType(colSizeEaseType), colSizeEaseTime(colSizeEaseTime), colSize(startColSize), startSize(startSize), endSize(endSize), sizeEaseType(sizeEaseType), sizeEaseTime(sizeEaseTime), size(1.0f), startSpeed(startSpeed), endSpeed(endSpeed), speedEaseType(speedEaseType), speedEaseTime(speedEaseTime), popT(popT), length(length), width(width), frontNode(frontNode), nextNode(nextNode), currentNodeNum(currentNodeNum), index(index), ID(ID), params(params) {
		flags |= IS_ALIVE * alive | IS_COL * isCol | IS_HEAD * isHead | IS_GRAZE * isGraze;
	}

	/**
	* @brief オブジェクトの動作など。 / Object behavior, etc.
	*
	* @param Index 現状用途なし / No current use
	*/
	virtual void UpdateObject(long long Index = 0);

	/**
	* @brief イージングによるパラメータの更新。 / Updating parameters by easing.
	*/
	virtual void UpdateEase();

	/**
	* @brief オブジェクトの移動。 / Moving objects.
	* 
	* @param speed 移動スピード / Move Speed
	*/
	void MoveObject(double speed);

	/**
	* @brief オブジェクトの当たり判定 / Collision check.
	*/
	virtual int ColliCheckObject();

	/**
	* @brief オブジェクトの掠り判定とスコアの上昇処理 / Processing of object snatching judgment and score increase.
	*/
	virtual void GrazeObject();

	/**
	* @brief 枠外判定 / Out-of-bounds check.
	*/
	virtual int CheckPosBounds();

	/**
	* @brief 当たり判定と枠外判定 / Collision and out-of-bounds check.
	*/
	virtual int CheckCollisionAndBounds();

	/**
	* @brief 移動及びID毎の分岐処理 / Branch processing for each move and ID.
	*/
	virtual void MoveFunc();
};

#endif