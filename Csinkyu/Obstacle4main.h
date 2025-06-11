/*
   - Obstacle4main.h -
   障害物管理.
*/
#pragma once
#include "Player.h"

//#define MAX_L 100 //ミサイルが飛ぶ最大距離.
//#define PI 3.14159//円周率.
//#define LINE_MAXNUM 3000//描画する線の最大数.

typedef struct tagLASER_DATA
{
	double x, y;      //現在の画像.
	double sx, sy;    //現在の速度.

	int    LogNum;    //記録した軌跡の数.
	float  Counter;   //追尾を初めてから通過した時間.

	int    ValidFlag; //このデータが使用中かフラグ.

}LASER_DATA, * LPLASER_DATA;

typedef struct tagLINE_DATA
{
	double x1, y1, x2, y2;  //描くラインの座標.
	float  Counter;         //描くラインの色決定用値.

	int    ValidFlag;       //このデータが使用中かフラグ.

}LINE_DATA, * LPLINE_DATA;

class Obstacle4main
{
protected:
	float Hx{}, Hy{};  //砲台の位置.
	float Hm{};        //砲台の移動方向.
	float Hsc{};       //砲台のショット間隔カウンタ.
	float HscTm{};     //砲台がショットする時間.

	LASER_DATA ld[OBSTACLE4_LASER_LIM]{};      //ホーミングレーザーのデータ.
	LINE_DATA  line[OBSTACLE4_LASER_LINE_MAX]{}; //ライン描画用データ.
	IMG        img{};
	MoveDir moveDir;  // 現在の移動方向.
	GameData* data{};
	Player* player{};
public:
    void Init(GameData*, Player*);
	virtual void Reset(float _Hx, float _Hy, float _Hm) = 0;
	void Update();
	void Draw();
	void enemy4Move();
	virtual void idou() = 0;
};
