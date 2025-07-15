/*
   - LaserManager.h -
   元々Obstacle4mainとしてまとめられてたレーザー.
*/
#pragma once

#include "MeteoManager.h"

//レーザータイプ.
enum LaserType
{
	Laser_Normal,    //通常レーザー.
	Laser_Reflected, //反射レーザー.
};

//レーザー本体.
typedef struct tagLASER_DATA
{
	LaserType type;      //レーザータイプ.

	double    x,  y;     //現在の座標.
	double    vx, vy;    //進行方向ベクトル.

	DBL_XY    goalPos;   //最寄り隕石座標を記録する用.
	BOOL      isGoGoal;  //目標地点に向かって進むか.

	int       LogNum;    //記録した軌跡の数.
	float     Counter;   //追尾を初めてから通過した時間.

	int       ValidFlag; //このデータが使用中かフラグ.

}LASER_DATA, *LPLASER_DATA;

//レーザーが描く軌道ライン.
typedef struct tagLINE_DATA
{
	LaserType type;         //レーザータイプ.

	double x1, y1, x2, y2;  //描くラインの座標.
	float  Counter;         //描くラインの色決定用値.

	int    ValidFlag;       //このデータが使用中かフラグ

}LINE_DATA, *LPLINE_DATA;

//レーザー管理用.
class LaserManager
{
private:
	LASER_DATA laser[OBSTACLE4_LASER_LIM]{}; //ホーミングレーザーのデータ.
	LINE_DATA  line [OBSTACLE4_LINE_MAX]{};  //ライン描画用データ.

	DBL_XY plyPos{}; //プレイヤー座標保管用.

	GameData*     p_data{};
	Player*       p_player{};
	MeteoManager* p_meteoMng{};

public:
	void Init(GameData*, Player*, MeteoManager*);
	void Reset();
	void Update();
	void Draw();

	void UpdateLaser();                      //各レーザーの更新.
	void UpdateLaserLine();                  //各レーザー描画線の更新.

	BOOL SpawnLaser      (float x, float y); //召喚.
	void DeleteLaser     (int idx);          //消去.
	void ReflectLaser    (int idx);			 //反射.

	void LaserNorTracking(int idx);          //レーザー(normal)   の隕石追尾.
	void LaserRefTracking(int idx);          //レーザー(reflected)の隕石追尾.
};