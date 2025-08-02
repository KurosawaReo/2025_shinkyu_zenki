/*
   - Global.h -
   ver.2025/07/27

   DxLib: 共通で使う型や定数を入れる所.
*/
#pragma once

//このGlobal.hが定義されているか判別する用.
#define DEF_GLOBAL_H

//c言語用.
#define _USE_MATH_DEFINES  //math定数を使うのに必要.
#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
//c++用.
#include <vector>
#include <map>
#include <string>
using namespace std;
//DxLib.
#include "DxLib.h"

//文字コードで切り替え.
#if defined UNICODE
  typedef wstring MY_STRING; //wchar_t型.
#else
  typedef string  MY_STRING; //char型.
#endif

//xとyの凝縮.
template<typename T> //型を<>で入力して使う.
struct XY
{
	T x;
	T y;

	//演算子で計算できるように.
	XY<T> operator+(XY<T>& xy) {       //+の右側が引数に入り、返り値が左側に入る.
		return { x + xy.x, y + xy.y }; //xとyを加算して返す.
	}
	XY<T> operator-(XY<T>& xy) {
		return { x - xy.x, y - xy.y };
	}
	XY<T> operator*(XY<T>& xy) {
		return { x * xy.x, y * xy.y };
	}
	XY<T> operator*(int n) {
		return { x * n, y * n };
	}
	XY<T> operator*(double n) {
		return { x * n, y * n };
	}
	XY<T> operator/(XY<T>& xy) {
		return { x / xy.x, y / xy.y };
	}
	XY<T> operator/(int n) {
		return { x / n, y / n };
	}
	XY<T> operator/(double n) {
		return { x / n, y / n };
	}
};
typedef XY<int>    INT_XY; //int型.
typedef XY<double> DBL_XY; //double型.

//円データ.
struct Circle
{
	DBL_XY pos;  //座標.
	float  r;    //半径.
	UINT   clr;  //色.
};
//四角形データ.
struct Box
{
	DBL_XY pos;  //座標.
	DBL_XY size; //サイズ.
	UINT   clr;  //色.
};
//三角形データ.
struct Triangle
{
	DBL_XY pos[3]; //3点の座標.
	UINT   clr;    //色.
};
//線データ.
struct Line
{
	DBL_XY stPos; //始点座標.
	DBL_XY edPos; //終点座標.
	UINT   clr;   //色.
};

//型変換マクロ.
#define _int(n)   (int)(round(n))            //int型変換マクロ.
#define _intXY(n) {_int(n.x), _int(n.y)}     //INT_XY型変換マクロ.
#define _dblXY(n) {(double)n.x, (double)n.y} //DBL_XY型変換マクロ.

#define _if_check(n) assert(n); if(n)        //if文の前に同条件のassertを挟む.

// - 列挙体 -
enum Scene
{
	SCENE_TITLE,
	SCENE_READY,
	SCENE_GAME,
	SCENE_END,
	SCENE_PAUSE, //ポーズ画面.

	SCENE_COUNT, //総数.
};
//レーザー移動列挙.
enum MoveDir 
{
	MOVE_RIGHT,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_UP
};

// - ゲームデータ -
struct GameData
{
	Scene scene;      //シーンの記録用.
	int   score;      //スコア.
	int   scoreBef;   //スコア(時間加算前)
	int   bestScore;  //ベストスコア.
	int   level;	  //レベル.

	float spawnRate;  //障害物の出現時間割合.
	float counter;    //経過時間カウンター(スローの影響を受ける)

	int   font1;      //フォント.
	int   font2;      //フォント.
	int   font3;      //フォント.
	int   font4;      //フォント.

	BOOL  isSlow;     //スローモードかどうか.
};

// - Debug -
//定義するとデバッグ表示ON.
//#define DEBUG_LASER_ACTIVE
//#define DEBUG_SPAWN_RATE

// - 定数 -
#define IS_WINDOW_MODE					(FALSE)			//ウィンドウモードにするか.

#define WINDOW_WID						(1920)			//ウィンドウの横幅.
#define WINDOW_HEI						(1080)			//ウィンドウの縦幅.
#define WINDOW_COLOR_BIT				(32)			//ウィンドウのカラーbit数.

#define FILE_DATA_PATH					(_T("score.data"))	//データを保存するtxtファイル.

#define FPS								(80)			//フレームレート.

#define SLOW_MODE_TIME					(8)             //スローモード制限時間.
#define SLOW_MODE_SPEED					(0.20f)			//スローモード速度倍率.

#define GAME_START_TIME					(1.0)			//ゲーム開始するまでの遅延.

#define LEVEL_UP_ANIM_TIME				(120)			//レベルアップアニメーション時間.

#define PLAYER_SIZE						(30)			//プレイヤーサイズ.
#define PLAYER_MOVE_SPEED				(8)				//プレイヤー移動速度.
#define PLAYER_HIT_R					(10)			//プレイヤーの当たり判定円の半径.
#define PLAYER_AFT_IMG_NUM				(7)             //残像データの数.
#define PLAYER_DEATH_ANIM_TIME			(10)			//プレイヤー死亡アニメ時間.

#define ITEM_SIZE						(20)			//アイテムサイズ.
#define ITEM_SPEED						(3)				//アイテム移動スピード.  
#define ITEM_RESPAWN_TIME				(400)           //アイテム復活時間.

#define OBSTACLE2_SPAN					(80)			//障害物の発射間隔.
#define OBSTACLE2_SPEED					(3.0)			//障害物の速度.
#define	OBSTACLE2_ROT_MAX				(5.0)			//障害物の追尾力(1フレームで回転できる最大度数)
#define OBSTACLE2_LIM_F					(80)			//最大追跡フレーム数.

#define OBSTACLE4_OUTER_MARGIN			(0)				//砲台の周回時の外側余白.
#define OBSTACLE4_SHOT_RESET			(300)			//砲台の発射リセット時間.
#define OBSTACLE4_SHOT_START			(20)			//砲台の発射開始時間.
#define OBSTACLE4_SHOT_SPAN				(5)				//砲台の発射間隔時間.

#define OBSTACLE4_FLASH_MAX				(30)            //最大フラッシュエフェクト数
#define OBSTACLE4_FLASH_SIZE_INIT		(3.0f)          //フラッシュエフェクトの初期サイズ.
#define OBSTACLE4_FLASH_SIZE_SPREAD		(-7)            //フラッシュエフェクトの拡大量.
#define OBSTACLE4_FLASH_VALID_TM		(100)           //フラッシュエフェクトの持続フレーム.
#define OBSTACLE4_FLASH_ALPHA_TM		(2)             //フラッシュエフェクトの透明化速度.
#define OBSTACLE4_PRE_LASER1_SIZE		(50)            //発射前エフェクト1のサイズ.
#define OBSTACLE4_PRE_LASER2_SIZE		(20)            //発射前エフェクト2のサイズ.

#define OBSTACLE5_FLASH_MAX				(30)            //最大フラッシュエフェクト数
#define OBSTACLE5_FLASH_SIZE_INIT		(5.0f)          //フラッシュエフェクトの初期サイズ.
#define OBSTACLE5_FLASH_SIZE_SPREAD		(3)             //フラッシュエフェクトの拡大量.
#define OBSTACLE5_FLASH_VALID_TM		(50)            //フラッシュエフェクトの持続フレーム.
#define OBSTACLE5_FLASH_ALPHA_TM		(2)             //フラッシュエフェクトの透明化速度.
#define OBSTACLE5_STATE_WARNING			(0)				//予告状態.
#define OBSTACLE5_STATE_ACTIVE			(1)				//アクティブ状態.
#define OBSTACLE5_WARNING_DURATION		(120.0f)		//2秒間の予告.
#define OBSTACLE5_ACTIVE_DURATION		(60.0f)			//1秒間のアクティブ.
#define OBSTACLE5_SPAWN_SPAN			(350)			//出現間隔.
#define OBSTACLE5_MAX_SIMULTANEOUS		(3)				//最大同時出現数.
#define OBSTACLE5_MIN_DISTANCE			(100)			//最小距離.

#define MGL_LASER_SPAWN_SPAN			(350)			//直線レーザーの出現間隔.
#define MGL_LASER_PREDICTION_TIME		(60)			//直線レーザーの予測線の出る時間.

//#define LASER_NOR_ROT_MAX				(0.1)			//レーザー(normal)   の曲がる限界角度.
#define LASER_REF_ROT_MAX				(10)			//レーザー(reflected)の曲がる限界角度.
#define LASER_REF_TRACK_ST_TM			(10)			//レーザー(reflected)の追尾開始時間.
#define LASER_REF_TRACK_ED_TM			(30)			//レーザー(reflected)の追尾終了時間.
#define LASER_NOR_SPEED					(0.1)		    //レーザー(normal)   の速度.
#define LASER_STR_SPEED					(50.0)		    //レーザー(straight) の速度.
#define LASER_REF_SPEED					(0.5)		    //レーザー(reflected)の速度.
#define LASER_CNT_MAX					(50)			//レーザーの最大数.
#define LASER_LINE_CNT_MAX				(12000)			//レーザー描画線の最大数.
#define LASER_LINE_DRAW_LEN				(2)				//レーザー描画線を描く最低の長さ(DrawLineAAの関係上)
#define LASER_REF_ANIM_TIME				(20)			//反射アニメーション時間.

#define METEO_CNT_MAX					(50)			//隕石の最大出現数.
#define METEO_SPAWN_SPAN				(150)			//隕石の出現時間間隔.
#define METEO_SPEED						(2)				//移動速度.
#define METEO_DEST_OUT_DIS				(50)			//隕石が画面外で消える距離.
#define METEO_DEST_TIME					(20)			//隕石の破壊時間.
#define METEO_GOAL_RAND_RANGE			(500)			//隕石の目標地点の乱数範囲.
#define METEO_BREAK_ANIM_TIME			(50)			//隕石破壊アニメーション時間.

#define METEO_LINE_CNT_MIN				(5)				//最低n角形.
#define METEO_LINE_CNT_MAX				(16)			//最大n角形.
#define METEO_LINE_DIS_MIN				(40)			//頂点の最短距離.
#define METEO_LINE_DIS_MAX				(60)			//頂点の最大距離.

#define EFFECT_MAX						(50)			//エフェクトの最大出現数.

#define SCORE_TAKE_ITEM					(100)			//アイテムを取った時のスコア.
#define SCORE_BREAK_METEO				(500)			//隕石を壊した時のスコア.
#define SCORE_ANIM_TIME					(50)			//スコアのアニメーション時間.

#define COLOR_PLY_REFLECT				(GetColor(255, 155, 255))
#define COLOR_PLY_DEBUG					(GetColor(255, 150, 150))
#define COLOR_PLY_AFT_NOR				(GetColor(105, 105, 105)) //プレイヤーの残像色(通常)
#define COLOR_PLY_AFT_REF				(GetColor(255,   0, 255)) //プレイヤーの残像色(反射)
#define COLOR_ITEM						(GetColor( 60, 255,  60))
#define COLOR_PRE_LINE					(GetColor(128, 128, 128))                            //予測線.
#define COLOR_METEO(pos)				(GetColor(0, _int(255 * fabs(sin(pos.x/200))), 255)) //隕石.
#define COLOR_BEST_SCORE				(0x20F7DE)
#define COLOR_SCORE						(0x00FFA0)
#define COLOR_TIME						(0x80FF9C)