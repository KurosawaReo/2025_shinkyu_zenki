/*
   - Obstacle4.cpp -
   障害物管理クラス (小田島作)
   プレイヤーを追尾するレーザーを発射する障害物を実装
*/
#include "Player.h"    // プレイヤークラスのヘッダーファイル
#include "Obstacle4.h" // 自身のヘッダーファイル

//stdafx.hに入ってるため不要.
//#include <math.h>      // 数学関数を使用するためのヘッダーファイル
//#include "DxLib.h"     // DXライブラリのヘッダーファイルをインクルード
//#include "Global.h"

/**
 * @brief 障害物の初期化処理
 * @param _player プレイヤーオブジェクトへのポインタ
 */
/*
 * @brief 敵（障害物）の移動処理
 * レーザーの移動とプレイヤーへの追尾、砲台の移動とレーザー発射を管理
 */
void Obstacle4::Reset(float _Hx, float _Hy, float _Hm)
{
	Hx = _Hx;                    // 砲台のX座標初期値（画面中央）
	Hy = _Hy;                   // 砲台のY座標初期値（画面上部）
	Hm = _Hm;                    // 砲台の移動速度
	Hsc = OBSTACLE4_SHOT_RESET; // 砲台の発射カウンタ初期値
	moveDir = MOVE_RIGHT;       // 初期方向を右に設定.
	// レーザーデータの初期化
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
		ld[i].ValidFlag = 0;  // すべてのレーザーを無効状態に

	// レーザーの軌跡データの初期化
	for (int i = 0; i < OBSTACLE4_LASER_LINE_MAX; i++)
		line[i].ValidFlag = 0;  // すべての軌跡を無効状態に
 
}
	void Obstacle4:: idou()
	{
		// 移動速度
		float moveSpeed = Hm * ((data->isSlow) ? (float)SLOW_MODE_SPEED : 1);

		// 矩形経路の移動処理
		switch (moveDir)
		{
		case MOVE_RIGHT:
			Hx += moveSpeed;
			if (Hx > WINDOW_WID - OBSTACLE4_OUTER_MARGIN) {
				Hx = WINDOW_WID - OBSTACLE4_OUTER_MARGIN;
				moveDir = MOVE_DOWN;
			}
			break;

		case MOVE_DOWN:
			Hy += moveSpeed;
			if (Hy > WINDOW_HEI - OBSTACLE4_OUTER_MARGIN) {
				Hy = WINDOW_HEI - OBSTACLE4_OUTER_MARGIN;
				moveDir = MOVE_LEFT;
			}
			break;

		case MOVE_LEFT:
			Hx -= moveSpeed;
			if (Hx < 0 + OBSTACLE4_OUTER_MARGIN) {
				Hx = 0 + OBSTACLE4_OUTER_MARGIN;
				moveDir = MOVE_UP;
			}
			break;

		case MOVE_UP:
			Hy -= moveSpeed;
			if (Hy < 0 + OBSTACLE4_OUTER_MARGIN) {
				Hy = 0 + OBSTACLE4_OUTER_MARGIN;
				moveDir = MOVE_RIGHT;
			}
			break;
		}
	}

	void Obstacle5::Reset(float _Hx, float _Hy, float _Hm)
	{
		Hx = _Hx;                    // 砲台のX座標初期値（画面中央）
		Hy = _Hy;                   // 砲台のY座標初期値（画面上部）
		Hm = _Hm;                    // 砲台の移動速度
		Hsc = OBSTACLE4_SHOT_RESET; // 砲台の発射カウンタ初期値
		moveDir = MOVE_LEFT;       // 初期方向を左に設定.
		// レーザーデータの初期化
		for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
			ld[i].ValidFlag = 0;  // すべてのレーザーを無効状態に

		// レーザーの軌跡データの初期化
		for (int i = 0; i < OBSTACLE4_LASER_LINE_MAX; i++)
			line[i].ValidFlag = 0;  // すべての軌跡を無効状態に
	}

	void Obstacle5::idou()
	{
		// 移動速度
		float moveSpeed = Hm * ((data->isSlow) ? (float)SLOW_MODE_SPEED : 1);

		// 矩形経路の移動処理
		switch (moveDir)
		{
		case MOVE_DOWN:
			Hy += moveSpeed;
			if (Hy < WINDOW_HEI - OBSTACLE4_OUTER_MARGIN) {
				Hy = WINDOW_HEI - OBSTACLE4_OUTER_MARGIN;
				moveDir = MOVE_RIGHT;
			}
			break;
		case MOVE_LEFT:
			Hx -= moveSpeed;
			if (Hx > 0 + OBSTACLE4_OUTER_MARGIN) {
				Hx = 0 + OBSTACLE4_OUTER_MARGIN;
				moveDir = MOVE_DOWN;
			}
			break;
		case MOVE_UP:
			Hy -= moveSpeed;
			if (Hy < 0 + OBSTACLE4_OUTER_MARGIN) {
				Hy = 0 + OBSTACLE4_OUTER_MARGIN;
				moveDir = MOVE_LEFT;
			}
			break;
		case MOVE_RIGHT:
			Hx += moveSpeed;
			if (Hx > WINDOW_WID - OBSTACLE4_OUTER_MARGIN) {
				Hx = WINDOW_WID - OBSTACLE4_OUTER_MARGIN;
				moveDir = MOVE_UP;
			}
			break;
		
		}
	}
