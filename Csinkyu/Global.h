/*
   - Global.h -

   REFLINE用のグローバル.
   KR_Library用のグローバルは分類済み.
*/
#pragma once

//再定義防止用(TODO:なぜかこれを外すと再定義エラーになる)
#if !defined GLOBAL
#define GLOBAL

using namespace KR_Lib;

//====================================================================//
//【列挙体】

//シーン.
enum Scene
{
	SCENE_TITLE,
	SCENE_MENU,     //メニュー画面.
	SCENE_GAME,
	SCENE_END,
	SCENE_PAUSE,    //ポーズ画面.

	SCENE_COUNT,    //総数.
};
//移動方向.
//レーザー(normal)砲台用.
enum MoveDir
{
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN
};
//ステージ種類,
enum StageType
{
	STAGE_ENDLESS,
	STAGE_TUTORIAL,
};

//====================================================================//
//【Debug】

//定義するとデバッグ表示ON.
//#define DEBUG_LASER_ACTIVE
//#define DEBUG_SPAWN_RATE

//====================================================================//
//【定数】

//DxLib設定.
#define FILE_DATA_PATH	(_T("Data"))					//データを保存する場所.
#define FILE_DATA		(_T("Data/score.data"))			//データを保存するファイル.

#define IS_WINDOW_MODE					(FALSE)			//ウィンドウモードにするか.

#define WINDOW_WID						(1920)			//ウィンドウの横幅.
#define WINDOW_HEI						(1080)			//ウィンドウの縦幅.
#define WINDOW_COLOR_BIT				(32)			//ウィンドウのカラーbit数.

#define FPS								(80)			//フレームレート.

//ゲーム設定.
#define GAME_START_TIME					(1.0)			//ゲーム開始するまでの遅延.

#define SLOW_MODE_TIME					(8)             //スローモード制限時間.
#define SLOW_MODE_SPEED					(0.20f)			//スローモード速度倍率.

#define MIDDLE_ANIM_TIME				(120)			//レベルアップアニメーション時間.

//プレイヤー.
#define PLAYER_SIZE						(17)			//プレイヤーサイズ.
#define PLAYER_MOVE_SPEED				(8)				//プレイヤー移動速度.
#define PLAYER_AFT_IMG_NUM				(9)             //残像データの数.
#define PLAYER_DEATH_ANIM_TIME			(10)			//プレイヤー死亡アニメ時間.

//アイテム.
#define ITEM_SIZE						(25)			//アイテムサイズ.
#define ITEM_SPEED						(3)				//アイテム移動スピード.  
#define ITEM_RESPAWN_TIME				(400)           //アイテム復活時間.

//レーザー総合.
#define LASER_REF_ROT_MAX				(10)			//レーザー(reflected)の曲がる限界角度.
#define LASER_REF_TRACK_ST_TM			(10)			//レーザー(reflected)の追尾開始時間.
#define LASER_REF_TRACK_ED_TM			(30)			//レーザー(reflected)の追尾終了時間.
#define LASER_NOR_SPEED					(0.1)		    //レーザー(normal)   の速度.
#define LASER_STR_SPEED					(50.0)		    //レーザー(straight) の速度.
#define LASER_REF_SPEED					(0.5)		    //レーザー(reflected)の速度.
#define LASER_CNT_MAX					(80)			//レーザーの最大数.
#define LASER_LINE_CNT_MAX				(14000)			//レーザー描画線の最大数.
#define LASER_LINE_DRAW_LEN				(2)				//レーザー描画線を描く最低の長さ(DrawLineAAの関係上)
#define LASER_REF_ANIM_TIME				(20)			//反射アニメーション時間.

//障害物: 通常レーザー.
#define LASER_NOR_OUTER_MARGIN			(0)				//砲台の周回時の外側余白.
#define LASER_NOR_SHOT_RESET			(300)			//砲台の発射リセット時間.
#define LASER_NOR_SHOT_START			(20)			//砲台の発射開始時間.
#define LASER_NOR_SHOT_SPAN				(5)				//砲台の発射間隔時間.

#define LASER_NOR_FLASH_MAX				(30)            //最大フラッシュエフェクト数
#define LASER_NOR_FLASH_SIZE_INIT		(3.0f)          //フラッシュエフェクトの初期サイズ.
#define LASER_NOR_FLASH_SIZE_SPREAD		(-7)            //フラッシュエフェクトの拡大量.
#define LASER_NOR_FLASH_VALID_TM		(100)           //フラッシュエフェクトの持続フレーム.
#define LASER_NOR_FLASH_ALPHA_TM		(2)             //フラッシュエフェクトの透明化速度.
#define LASER_NOR_PRE_LASER1_SIZE		(50)            //発射前エフェクト1のサイズ.
#define LASER_NOR_PRE_LASER2_SIZE		(20)            //発射前エフェクト2のサイズ.

//障害物: 直前レーザー.
#define LASER_STR_SPAWN_SPAN			(350)			//直線レーザーの出現間隔.
#define LASER_STR_PREDICTION_TIME		(60)			//直線レーザーの予測線の出る時間.

//障害物: 隕石.
#define METEOR_CNT_MAX					(50)			//隕石の最大出現数.
#define METEOR_SPAWN_SPAN				(150)			//隕石の出現時間間隔.
#define METEOR_SPEED					(2)				//移動速度.
#define METEOR_DEST_OUT_DIS				(50)			//隕石が画面外で消える距離.
#define METEOR_DEST_TIME				(20)			//隕石の破壊時間.
#define METEOR_GOAL_RAND_RANGE			(500)			//隕石の目標地点の乱数範囲.
#define METEOR_BREAK_ANIM_TIME			(50)			//隕石破壊破片のアニメ時間.
#define METEOR_BREAK_ANIM_CNT			(10)			//隕石破壊破片の数.

#define METEOR_LINE_CNT_MIN				(5)				//最低n角形.
#define METEOR_LINE_CNT_MAX				(16)			//最大n角形.
#define METEOR_LINE_DIS_MIN				(40)			//頂点の最短距離.
#define METEOR_LINE_DIS_MAX				(60)			//頂点の最大距離.

//障害物: 波紋.
#define RIPPLES_FLASH_MAX				(30)            //最大フラッシュエフェクト数
#define RIPPLES_FLASH_SIZE_INIT			(5.0f)          //フラッシュエフェクトの初期サイズ.
#define RIPPLES_FLASH_SIZE_SPREAD		(3)             //フラッシュエフェクトの拡大量.
#define RIPPLES_FLASH_BLINK_TM			(15.0f)         //フラッシュエフェクトの点滅時間.
#define RIPPLES_FLASH_VALID_TM			(50)            //フラッシュエフェクトの持続フレーム.
#define RIPPLES_FLASH_ALPHA_TM			(2)             //フラッシュエフェクトの透明化速度.
#define RIPPLES_STATE_WARNING			(0)				//予告状態.
#define RIPPLES_STATE_ACTIVE			(1)				//アクティブ状態.
#define RIPPLES_WARNING_DURATION		(120.0f)		//予告の時間.
#define RIPPLES_ACTIVE_DURATION			(60.0f)			//アクティブの時間.
#define RIPPLES_SPAWN_SPAN				(350)			//出現間隔.
#define RIPPLES_MAX_SIMULTANEOUS		(3)				//最大同時出現数.
#define RIPPLES_MIN_DISTANCE			(100)			//最小距離.

//障害物: 花火.
#define FIREWORKS_CNT_MAX				(10)			//最大同時出現数
#define FIREWORKS_RND_MAX				(2)				//花火出現最大数
#define FIREWORKS_SPAWN_SPAN			(600)			//花火生成間隔（フレーム）
#define FIREWORKS_WARNING_DURATION		(120)			//予告を出す長さ（フレーム）
#define FIREWORKS_LAUNCH_HEIGHT			(50)			//打ち上げ高度
#define FIREWORKS_EXPLOSION_RADIUS		(100)			//爆発半径
#define FIREWORKS_SPARKS_COUNT			(16)			//火花の数（ベース）
#define FIREWORKS_MIN_DISTANCE			(120)			//花火同士の最小距離
#define FIREWORKS_GRAVITY				(0.3f)			//重力加速度

//エフェクト.
#define EFFECT_MAX						(50)			//エフェクトの最大出現数.

//スコア.
#define SCORE_TAKE_ITEM					(100)			//アイテムを取った時のスコア.
#define SCORE_BREAK_METEO				(500)			//隕石を壊した時のスコア.
#define SCORE_ANIM_TIME					(50)			//スコアのアニメーション時間.

//カラー.
#define COLOR_PLY_REFLECT				(GetColor(255, 155, 255))
#define COLOR_PLY_DEBUG					(GetColor(255, 150, 150))
#define COLOR_PLY_AFT_NOR				(GetColor(105, 105, 105))	//プレイヤーの残像色(通常)
#define COLOR_PLY_AFT_REF				(GetColor(255,   0, 255))	//プレイヤーの残像色(反射)
#define COLOR_ITEM						(GetColor( 60, 255,  60))
#define COLOR_PRE_EFFECT				(GetColor(128, 128, 128))                              //予測演出.
#define COLOR_METEO(pos)				(GetColor(0, _int_r(255 * fabs(sin(pos.x/200))), 255)) //隕石.
#define COLOR_BEST_SCORE				(0x20F7DE)
#define COLOR_SCORE						(0x00FFA0)
#define COLOR_TIME						(0x80FF9C)

#endif