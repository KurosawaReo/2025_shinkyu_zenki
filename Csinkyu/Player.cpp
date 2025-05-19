/*
   - Player.cpp -
   プレイヤー管理.
*/
#include "Player.h"

//初期化(一回のみ行う)
void Player::Init(GameData* _data)
{
	p_data = _data;
}
//リセット(何回でも行う)
void Player::Reset(DBL_XY _pos, BOOL _active) {
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
		// 四角形を描画（プレイヤーの位置に）
		int x  = _int(hit.pos.x - PLAYER_SIZE/2);
		int y  = _int(hit.pos.y - PLAYER_SIZE/2);
		int dx = _int(hit.pos.x + PLAYER_SIZE/2);
		int dy = _int(hit.pos.y + PLAYER_SIZE/2);

		unsigned int Cr;
		//デバッグモード中.
		if (isDebug) {
			Cr = GetColor(255, 150, 150); //赤色.
		}
		else {
			Cr = GetColor(255, 255, 255); //白色.
		}

		DrawBox(x, y, dx, dy, Cr, TRUE);
	}
}

//移動処理(斜め対応)
void Player::PlayerMove()
{
	//移動する.
	if (p_data->isSlow) {
		InputKey4Dir(&hit.pos, PLAYER_MOVE_SPEED/3);
	}
	else {
		InputKey4Dir(&hit.pos, PLAYER_MOVE_SPEED);
	}
	//移動限界.
	LimMovePos(&hit.pos, { PLAYER_SIZE, PLAYER_SIZE }, 0, 0, WINDOW_WID, WINDOW_HEI);
}

//死亡処理.
void Player::PlayerDeath() {

	//デバッグモード中は無敵.
	if (isDebug) { return; }

	active = FALSE;
	p_data->scene = SCENE_END; //ゲーム終了へ.
}