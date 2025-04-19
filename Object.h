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
* @enum objectFlags
* @brief オブジェクトの状態をまとめたもの / A summary of the object's state.
*/
enum objectFlags {
	ALIVE = 1 << 0,
	IS_COL = 1 << 1,
	IS_HEAD = 1 << 2,
};

/**
* @class Object
* @brief オブジェクトの基底クラス / Objects Super Class!!!!
*/
class Object {
public:
	std::uint8_t flags = 0b00000010;
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
	int pal = 255;
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
	long long popFrame = 0;
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
	Object(std::uint8_t alive, std::uint8_t isCol, int objType, const Vec2D& pos, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startShowAngle, double endShowAngle, int showAngleEaseType, int showAngleEaseTime, const Color& color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int popFrame = 0, double length = 0, double width = 0, long long frontNode = 0, long long nextNode = 0, int currentNodeNum = 0, int isHead = 0, long long index = 0, int ID = 0, const std::vector<std::any>& params = {})
		: objType(objType), pos(pos), startAngle(startAngle), endAngle(endAngle), angleEaseType(angleEaseType), angleEaseTime(angleEaseTime), startShowAngle(startShowAngle), endShowAngle(endShowAngle), showAngleEaseType(showAngleEaseType), showAngleEaseTime(showAngleEaseTime), color(color), style(style), blend(blend), pal(pal), startColSize(startColSize), endColSize(endColSize), colSizeEaseType(colSizeEaseType), colSizeEaseTime(colSizeEaseTime), colSize(startColSize), startSize(startSize), endSize(endSize), sizeEaseType(sizeEaseType), sizeEaseTime(sizeEaseTime), size(1.0f), startSpeed(startSpeed), endSpeed(endSpeed), speedEaseType(speedEaseType), speedEaseTime(speedEaseTime), popFrame(popFrame), length(length), width(width), frontNode(frontNode), nextNode(nextNode), currentNodeNum(currentNodeNum), index(index), ID(ID), params(params) {
		flags |= ALIVE * alive | IS_COL * isCol | IS_HEAD * isHead;
	}

	/**
	* @brief オブジェクトの動作など。 / Object behavior, etc.
	*
	* @param Index 現状用途なし / No current use
	*/
	void UpdateObject(long long Index = 0);

	/**
	* @brief イージングによるパラメータの更新。 / Updating parameters by easing.
	*/
	void UpdateEase();

	/**
	* @brief オブジェクトの移動。 / Moving objects.
	* 
	* @param speed 移動スピード / Move Speed
	*/
	void MoveObject(double speed);

	/**
	* @brief オブジェクトの当たり判定 / Collision check.
	*/
	virtual void ColliCheckObject();

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