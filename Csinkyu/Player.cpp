/*
   - Player.cpp -
   プレイヤー管理.
*/
#include "GameManager.h"
#include "Player.h"

//初期化(一回のみ行う)
void Player::Init(GameData* _data)
{
	p_data = _data;
}
//リセット(何回でも行う)
void Player::Reset(DBL_XY _pos, BOOL _active) 
{
	hit    = {_pos, PLAYER_HIT_R, 0x000000};
	active = _active;
}
//更新.
void Player::Update()
{
	//デバッグモード切り替え.
	if (IsPushKeyTime(KEY_INPUT_M) == 1) {
		isDebug = !isDebug;
	}
	//有効なら.
	if (active) {
		PlayerMove();
	}
}
//描画.
void Player::Draw()
{
	//デバッグ表示.
	if (isDebug) {
		DrawString(0, 430, _T("[Debug] 無敵モード"), 0xFFFFFF);
	}
	//有効なら.
	if (active) {
		//四角形.
		Box box1 = { hit.pos, { PLAYER_SIZE,   PLAYER_SIZE   }, 0xFFFFFF };
		Box box2 = { hit.pos, { PLAYER_SIZE-2, PLAYER_SIZE-2 }, 0xA0A0A0 };

		//デバッグモード中.
		if (isDebug) {
			box1.clr = box2.clr = GetColor(255, 150, 150); //赤色.
		}

		DrawBoxST(&box1, TRUE, FALSE);
		DrawBoxST(&box2, TRUE, FALSE);
	}
}

//移動処理(斜め対応)
void Player::PlayerMove()
{
	//移動する.
	if (p_data->isSlow) {
		InputKey4Dir(&hit.pos, PLAYER_MOVE_SPEED * SLOW_MODE_SPEED);
		InputPad4Dir(&hit.pos, PLAYER_MOVE_SPEED * SLOW_MODE_SPEED); //コントローラ移動(仮)
	}
	else {
		InputKey4Dir(&hit.pos, PLAYER_MOVE_SPEED);
		InputPad4Dir(&hit.pos, PLAYER_MOVE_SPEED); //コントローラ移動(仮)
	}
	//移動限界.
	FixPosInArea(&hit.pos, { PLAYER_SIZE, PLAYER_SIZE }, 0, 0, WINDOW_WID, WINDOW_HEI);
}

//死亡処理.
void Player::PlayerDeath() {

	//デバッグモード中は無敵.
	if (isDebug) { return; }

	active = FALSE;
	//GamaManagerの関数実行(includeだけすれば使える)
	GameManager::GetPtr()->GameEnd(); //ゲーム終了.
}