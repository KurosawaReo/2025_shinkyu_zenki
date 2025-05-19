/*
   - Obstacle3.h -
   障害物管理.
*/
#pragma once
#include "Player.h"

//#define MAX_L 100 //ミサイルが飛ぶ最大距離.
//#define PI 3.14159//円周率.
//#define LINE_MAXNUM 3000//描画する線の最大数.

typedef struct TUGLASER
{  
	int   x, y;      //現在の画像.
	int   sx, sy;    //現在の速度.

	int   LogNum;    //記録した軌跡の数.
	float Counter;   //追尾を初めてから通過した時間.

	int   ValidFlag; //このデータが使用中かフラグ.


}LASER,*LPLASER;

typedef struct TUGLINE
{
	int   x1, y1, x2, y2;  //描くラインの座標.
	float Counter;         //描くラインの色決定用値.

    int   ValidFlag;       //このデータが使用中かフラグ.

}LINE,*LPLINE;


class Obstacle4
{
private:
	float Hx, Hy;  //砲台の位置.
	float Hm;      //砲台の移動方向.
	float Hsc;     //砲台のショット間隔カウンタ.
	float HscTm;   //砲台がショットする時間.

	LASER Ld[OBSTACLE4_MAX_L];     //ホーミングレーザーのデータ.
	LINE Line[OBSTACLE4_LINE_MAX]; //ライン描画用データ.
	IMG img;

	GameData* data{};
	Player*   player{};

public:
	void Init(GameData*, Player*);
	void Reset();
	void Update();
	void Draw();
	void enemy4Move();
};