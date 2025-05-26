/*
   - Global.h -
   ver.2025/05/21

   共通で使用する型やマクロを入れる所.
*/
#pragma once

//このGlobal.hが定義されているか判別する用.
#define DEF_GLOBAL_H

//stdafxがあるならいらない.
#if true
#define _USE_MATH_DEFINES  //math定数を使うのに必要.
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <time.h>
#include "DxLib.h"
#endif

#if !defined DEF_INT_XY
#define DEF_INT_XY
//int型の凝縮xy.
struct INT_XY
{
	int x;
	int y;
};
#endif

#if !defined DEF_DBL_XY
#define DEF_DBL_XY
//double型の凝縮xy.
struct DBL_XY
{
	double x;
	double y;
};
#endif

#if !defined DEF_SHAPES
#define DEF_SHAPES
//円データ.
struct Circle
{
	DBL_XY pos;  //座標.
	int    r;    //半径.
	UINT   clr;  //色.
};
//四角形データ.
struct Box
{
	DBL_XY pos;  //座標.
	INT_XY size; //サイズ.
	UINT   clr;  //色.
};
//線データ.
struct Line
{
	DBL_XY stPos; //始点座標.
	DBL_XY edPos; //終点座標.
	UINT   clr;   //色.
};
#endif

#if !defined DEF_VARTYPE_MACRO
#define DEF_VARTYPE_MACRO
#define _int(n)   (int)(round(n))            //int型変換マクロ.
#define _intXY(n) {_int(n.x), _int(n.y)}     //INT_XY型変換マクロ.
#define _dblXY(n) {(double)n.x, (double)n.y} //DBL_XY型変換マクロ.
#endif

// - 列挙体 -
enum Scene
{
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_END,
};

// - ゲームデータ -
struct GameData
{
	Scene scene;  //シーンの記録用.
	BOOL  isSlow; //スローモードかどうか.
};

// - 定数 -
#define IS_WINDOW_MODE			(TRUE)			//ウィンドウモードにするか.

#define WINDOW_WID				(600)			//ウィンドウの横幅.
#define WINDOW_HEI				(480)			//ウィンドウの縦幅.
#define WINDOW_COLOR_BIT		(32)			//ウィンドウのカラーbit数.

#define WAIT_LOOP_MS			(10)			//ループ処理の待機時間(m秒)

#define SLOW_MODE_SPEED			(0.25)			//スローモード速度倍率.

#define PLAYER_SIZE				(20)			//プレイヤーサイズ.
#define PLAYER_MOVE_SPEED		(4)				//プレイヤー移動速度.
#define PLAYER_HIT_R			(10)			//プレイヤーの当たり判定円の半径.

#define OBSTACLE2_SPAN			(50)			//障害物の発射間隔.
#define OBSTACLE2_SPEED			(4.0)			//障害物の速度.
#define OBSTACLE2_LIM_F			(80)			//最大追跡フレーム数.

#define OBSTACLE3_SIZE			(20)			//障害物サイズ.
#define OBSTACLE3_TRACK_POW		(8)				//障害物の追尾力.
#define OBSTACLE3_SPEED			(3)				//障害物の速度.

#define OBSTACLE4_SHOT_RESET	(50)			//障害物の発射リセット時間.
#define OBSTACLE4_SHOT_START	(30)			//障害物の発射開始時間.
#define OBSTACLE4_SHOT_SPAN		(1)			//障害物の発射間隔時間.
#define OBSTACLE4_SPEED			(100)			//障害物の速度.
#define OBSTACLE4_MAX_L			(100)			//障害物が飛ぶ最大距離.
#define OBSTACLE4_LINE_MAX		(2000)			//障害物で描画する線の最大数.

// - 関数 -