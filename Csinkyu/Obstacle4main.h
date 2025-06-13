/*
   - Obstacle4main.h -
   障害物管理.
*/
#pragma once
#include "Player.h"

typedef struct tagLASER_DATA
{
	double x, y;      //現在の画像.
	double sx, sy;    //現在の速度.

	int    LogNum;    //記録した軌跡の数.
	float  Counter;   //追尾を初めてから通過した時間.

	int    ValidFlag; //このデータが使用中かフラグ.
	BOOL isReflected;

}LASER_DATA, * LPLASER_DATA;

typedef struct tagLINE_DATA
{
	double x1, y1, x2, y2;  //描くラインの座標.
	float  Counter;         //描くラインの色決定用値.

	int    ValidFlag;       //このデータが使用中かフラグ
}LINE_DATA, * LPLINE_DATA;

//継承元となるクラス(親)
class Obstacle4main
{
protected:
	float Hx{}, Hy{};  //砲台の位置.
	float Hm{};        //砲台の移動方向.
	float Hsc{};       //砲台のショット間隔カウンタ.
	float HscTm{};     //砲台がショットする時間.
<<<<<<< HEAD
	MoveDir moveDir{};  // 現在の移動方向.

	LASER_DATA ld[OBSTACLE4_LASER_LIM]{};        //ホーミングレーザーのデータ.
=======
	LASER_DATA ld[OBSTACLE4_LASER_LIM]{};      //ホーミングレーザーのデータ.
>>>>>>> Item
	LINE_DATA  line[OBSTACLE4_LASER_LINE_MAX]{}; //ライン描画用データ.
	IMG        img{};

	GameData*  data{};
	Player*    player{};

public:
	//基本処理.
	virtual void Init  (GameData*, Player*) = 0;
	virtual void Reset (float _Hx, float _Hy, float _Hm) = 0;
	        void Update();
	        void Draw  ();
	//移動系.
	        void enemy4Move();
	virtual void Move() = 0;
<<<<<<< HEAD
=======
	//反射処理.
	BOOL HandleLaserHit(int laserIndex);
	void CreateReflectedLasers(double reflectX, double reflectY, int originalSx, int originalSy);
>>>>>>> Item
};
