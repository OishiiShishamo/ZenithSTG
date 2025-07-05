/**
* @file Object.h
* @brief オブジェクトの基底クラスを定義している / Defines the super class of the object.
* @auther ZenithSTG Dev Team
*/

#pragma once
#ifndef ZENITHSTG_SRC_OBJECT_H_
#define ZENITHSTG_SRC_OBJECT_H_

/**
* @brief オブジェクトの生成に関するもの / Relates to the creation of objects
*
* @param pos 生成位置 / Create Position
* @param color 色 / Color
* @param style 見た目 / Style
* @param blend ブレンドモード / Blend Mode
* @param pal ブレンドのパラメータ / Blend Param
* @param is_col 判定の有無 / Collision availability
* @param start_col_size 判定サイズの始点 / Start Collision Size
* @param end_col_size 判定サイズの終点 / End Collision Size
* @param col_size_ease_type 判定サイズのイージング方法 / Easing method for Collision Size
* @param col_size_ease_time 判定サイズのイージングにかかる時間 / Time required for Collision Size easing
* @param start_size 表示サイズの始点 / Start Display Size
* @param end_size 表示サイズの終点 / End Display Size
* @param size_ease_type 表示サイズのイージング方法 / Easing method for Display Size
* @param size_ease_time 表示サイズのイージングにかかる時間 / Time required for Display Size easing
* @param way way数 / way num
* @param spread 拡散 / spread
* @param aim 自機に角度を合わせるか(1 = 自機狙い, 2 = 自機外し) / Aim Player(1 = targeting, 2 = offset targeting)
* @param start_angle 角度の始点 / Start Angle
* @param end_angle 角度の終点 / End Angle
* @param angle_ease_type 角度のイージング方法 / Easing method for Angle
* @param angle_ease_time 角度のイージングにかかる時間 / Time required for Angle easing
* @param start_speed 速度の始点 / Start Speed
* @param end_speed 速度の終点 / End Speed
* @param speed_ease_type 速度のイージング方法 / Easing method for Speed
* @param speed_ease_time 速度のイージングにかかる時間 / Time required for Speed easing
* @param se SE番号 / se Number
* @param id 特殊な動作を行うためのid / id for special operation
* @param params 特殊な動作を行うためのパラメータ / Parameter for special operation
*/
struct ObjectParams {
	Vec2D pos = Vec2D(0, 0);
	double length = 0;
	double width = 0;
	Color color = Color(0, 0, 0);
	int style = 0;
	int blend = 0;
	int pal = 255;
	int is_col = 1;
	int is_aligned_angle = 1;
	int is_graze = 1;
	double start_col_size = 0;
	double end_col_size = 0;
	int col_size_ease_type = 0;
	int col_size_ease_time = 0;
	double start_size = 1;
	double end_size = 1;
	int size_ease_type = 0;
	int size_ease_time = 0;
	int way = 1;
	double spread = kTau;
	int aim = kAimFalse;
	double start_angle = 0;
	double end_angle = 0;
	int angle_ease_type = 0;
	int angle_ease_time = 0;
	double start_show_angle = 0;
	double end_show_angle = 0;
	int show_angle_ease_type = 0;
	int show_angle_ease_time = 0;
	double start_speed = 0;
	double end_speed = 0;
	int speed_ease_type = 0;
	int speed_ease_time = 0;
	int se = kSoundEffectNone;
	int id = 0;
	std::vector<std::any> params;
};

/**
* @enum ObjectFlags
* @brief オブジェクトの状態をまとめたもの / A summary of the object's state.
*/
enum ObjectFlags {
	kIsAlive = 1 << 0,
	kIsCol = 1 << 1,
	kIsHead = 1 << 2,
	kIsGraze = 1 << 3,
};

/**
* @class Object
* @brief オブジェクトの基底クラス / Objects Super Class!!!!
*/
class Object {
public:
	std::uint8_t flags = 0b00001010;
	int obj_type = kObjectBase;
	Vec2D pos = Vec2D(0, 0);
	Vec2D vec = Vec2D(0, 0);
	double start_angle = 0;
	double end_angle = 0;
	int angle_ease_type = 0;
	int angle_ease_time = 0;
	double angle = 0;
	double start_show_angle = 0;
	double end_show_angle = 0;
	int show_angle_ease_type = 0;
	int show_angle_ease_time = 0;
	double show_angle = 0;
	int is_aligned_angle = 1;
	Color color = Color(0, 0, 0);
	int style = 0;
	int blend = 0;
	double pal = 255;
	double start_col_size = 0;
	double end_col_size = 0;
	int col_size_ease_type = 0;
	int col_size_ease_time = 0;
	double col_size = 0;
	double start_size = 0;
	double end_size = 0;
	int size_ease_type = 0;
	int size_ease_time = 0;
	double size = 1.0f;
	double start_speed = 0;
	double end_speed = 0;
	int speed_ease_type = 0;
	int speed_ease_time = 0;
	double speed = 0.0f;
	long long pop_t = 0;
	double angle_t = 0, speed_t = 0, col_tize_t = 0, size_t = 0;
	double length = 0;
	double width = 0;
	long long front_node = 0;
	long long next_node = -1;
	int current_node_num = 0;
	int id = 0;
	long long order = 0;
	long long index = 0;
	std::vector<std::any> params;
	Object() = default;
	Object(std::uint8_t alive, std::uint8_t is_col, int obj_type, const Vec2D& pos, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_show_angle, double end_show_angle, int show_angle_ease_type, int show_angle_ease_time, const Color& color, int style, int blend, int pal, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int pop_t = 0, double length = 0, double width = 0, long long front_node = 0, long long next_node = 0, int current_node_num = 0, int isHead = 0, long long index = 0, int id = 0, const std::vector<std::any>& params = {}, int is_graze = 1)
		: obj_type(obj_type), pos(pos), start_angle(start_angle), end_angle(end_angle), angle_ease_type(angle_ease_type), angle_ease_time(angle_ease_time), start_show_angle(start_show_angle), end_show_angle(end_show_angle), show_angle_ease_type(show_angle_ease_type), show_angle_ease_time(show_angle_ease_time), color(color), style(style), blend(blend), pal(pal), start_col_size(start_col_size), end_col_size(end_col_size), col_size_ease_type(col_size_ease_type), col_size_ease_time(col_size_ease_time), col_size(start_col_size), start_size(start_size), end_size(end_size), size_ease_type(size_ease_type), size_ease_time(size_ease_time), size(1.0f), start_speed(start_speed), end_speed(end_speed), speed_ease_type(speed_ease_type), speed_ease_time(speed_ease_time), pop_t(pop_t), length(length), width(width), front_node(front_node), next_node(next_node), current_node_num(current_node_num), index(index), id(id), params(params) {
		flags |= kIsAlive * alive | kIsCol * is_col | kIsHead * isHead | kIsGraze * is_graze;
	}

	/**
	* @brief オブジェクトの動作など。 / Object behavior, etc.
	*/
	virtual void UpdateObject();

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
	* @brief 移動及びid毎の分岐処理 / Branch processing for each move and id.
	*/
	virtual void MoveFunc();
};

#endif