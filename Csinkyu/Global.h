/*
   - Global.h -
   定数などをまとめる所.
*/
#pragma once

#if !defined DEF_INT_XY
#define DEF_INT_XY 
//xとyの凝縮体.
struct INT_XY
{
	int x;
	int y;
};
#endif

#if !defined DEF_DBL_XY
#define DEF_DBL_XY 
//xとyの凝縮体.
struct DBL_XY
{
	double x;
	double y;
};
#endif

// - マクロ -
#define _int(n)	((int)round(n))			//int型変換マクロ.

// - 定数 -
#define IS_WINDOW_MODE		(TRUE)		//ウィンドウモードにするか.

#define WINDOW_WID			(600)		//ウィンドウの横幅.
#define WINDOW_HEI			(480)		//ウィンドウの縦幅.
#define WINDOW_COLOR_BIT	(32)		//ウィンドウのカラーbit数.

#define WAIT_LOOP_MS		(10)		//ループ処理の待機時間(m秒)

#define PLAYER_SIZE			(20)		//プレイヤーサイズ.
#define PLAYER_MOVE_SPEED	(4)			//プレイヤー移動速度.

#define MISSILE_SIZE		(20)		//ミサイルサイズ.
#define MISSILE_TRACK_POW	(8)			//ミサイルの追尾力.
#define MISSILE_SPEED		(3)			//ミサイルの速度.

// - 関数 -
BOOL IsHitBox(DBL_XY pos1, INT_XY size1, DBL_XY pos2, INT_XY size2);
BOOL IsHitCircle(DBL_XY pos1, int r1, DBL_XY pos2, int r2);