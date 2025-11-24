/*
   - Laser.h -
   レーザー本体とレーザー描画線.
*/
#pragma once

//レーザータイプ.
enum LaserType
{
	Laser_Normal,       //通常レーザー.
	Laser_Straight,     //直線レーザー.
	Laser_Reflect,      //反射レーザー.
	Laser_SuperReflect, //反射レーザー強化版.
	Laser_Falling,      //落下レーザー(花火用)
};

//レーザー本体.
class LaserData
{
	friend class LaserManager; //アクセス許可.

private:
	LaserType type;      //レーザータイプ.

	DBL_XY    nowPos;    //現在の座標.
	DBL_XY    befPos;    //前回描画した時にいた座標.
	DBL_XY    vec;       //進行方向ベクトル.

	DBL_XY    goalPos;   //目標地点の座標.
	bool      isGoGoal;  //目標地点に向かって進むか.

	int       logNum;    //記録した軌跡の数.
	float     counter;   //経過時間.
};

//レーザーが描く描画線.
class LaserLineData
{
	friend class LaserManager; //アクセス許可.

private:
	LaserType type;         //レーザータイプ.

	DBL_XY pos1, pos2;		//描くラインの座標.
	float  counter;         //描くラインの色決定用値.
};