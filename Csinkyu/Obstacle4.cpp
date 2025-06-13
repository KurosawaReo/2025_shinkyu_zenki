/*
   - Obstacle4.cpp -
   障害物管理クラス (小田島作)
   プレイヤーを追尾するレーザーを発射する障害物を実装
*/
#include "Player.h"    // プレイヤークラスのヘッダーファイル
#include "Obstacle4.h" // 自身のヘッダーファイル

//obstacle4mainのInit関数をobstacle4用に上書き.
void Obstacle4_1::Init(GameData* _data, Player* _player)
{
	data   = _data;
	player = _player;  // プレイヤーオブジェクトを参照として保存
}
//obstacle4mainのReset関数をobstacle4用に上書き.
void Obstacle4_1::Reset(float _Hx, float _Hy, float _Hm)
{
	Hx      = _Hx;                  // 砲台のX座標初期値（画面中央）
	Hy      = _Hy;                  // 砲台のY座標初期値（画面上部）
	Hm      = _Hm;                  // 砲台の移動速度
	Hsc     = OBSTACLE4_SHOT_RESET; // 砲台の発射カウンタ初期値
	HscTm   = OBSTACLE4_SHOT_START; // 砲台の発射タイミング初期値
	moveDir = MOVE_RIGHT;           // 初期方向を右に設定.
	// レーザーデータの初期化
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
		laser[i].ValidFlag = 0;    // すべてのレーザーを無効状態に

	// レーザーの軌跡データの初期化
	for (int i = 0; i < OBSTACLE4_LINE_MAX; i++)
		line[i].ValidFlag = 0;  // すべての軌跡を無効状態に
 
}
//obstacle4mainのMove関数をobstacle4用に上書き.
void Obstacle4_1::Move()
{
	// 移動速度
	float moveSpeed = Hm * ((data->isSlow) ? (float)SLOW_MODE_SPEED : 1);

	// 矩形経路の移動(右回り)
	switch (moveDir)
	{
	case MOVE_LEFT:
		Hx -= moveSpeed;
		if (Hx < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hx = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_UP;
		}
		break;
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
	case MOVE_UP:
		Hy -= moveSpeed;
		if (Hy < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hy = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_RIGHT;
		}
		break;
	}
}

//obstacle4mainのInit関数をobstacle5用に上書き.
void Obstacle4_2::Init(GameData* _data, Player* _player)
{
	data   = _data;
	player = _player;  // プレイヤーオブジェクトを参照として保存
}
//obstacle4mainのReset関数をobstacle5用に上書き.
void Obstacle4_2::Reset(float _Hx, float _Hy, float _Hm)
{
	Hx      = _Hx;                  // 砲台のX座標初期値（画面中央）
	Hy      = _Hy;                  // 砲台のY座標初期値（画面上部）
	Hm      = _Hm;                  // 砲台の移動速度
	Hsc     = OBSTACLE4_SHOT_RESET; // 砲台の発射カウンタ初期値
	HscTm   = OBSTACLE4_SHOT_START; // 砲台の発射タイミング初期値
	moveDir = MOVE_LEFT;            // 初期方向を左に設定.
	// レーザーデータの初期化
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
		laser[i].ValidFlag = 0;    // すべてのレーザーを無効状態に

	// レーザーの軌跡データの初期化
	for (int i = 0; i < OBSTACLE4_LINE_MAX; i++)
		line[i].ValidFlag = 0;  // すべての軌跡を無効状態に
}
//obstacle4mainのMove関数をobstacle5用に上書き.
void Obstacle4_2::Move()
{
	// 移動速度
	float moveSpeed = Hm * ((data->isSlow) ? (float)SLOW_MODE_SPEED : 1);

	// 矩形経路の移動(左回り)
	switch (moveDir)
	{
	case MOVE_LEFT:
		Hx -= moveSpeed;
		if (Hx < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hx = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_DOWN;
		}
		break;
	case MOVE_RIGHT:
		Hx += moveSpeed;
		if (Hx > WINDOW_WID - OBSTACLE4_OUTER_MARGIN) {
			Hx = WINDOW_WID - OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_UP;
		}
		break;
	case MOVE_DOWN:
		Hy += moveSpeed;
		if (Hy > WINDOW_HEI - OBSTACLE4_OUTER_MARGIN) {
			Hy = WINDOW_HEI - OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_RIGHT;
		}
		break;
	case MOVE_UP:
		Hy -= moveSpeed;
		if (Hy < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hy = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_LEFT;
		}
		break;
	}
}
