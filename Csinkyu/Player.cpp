/*
   - Player.cpp -
   プレイヤー管理.
*/
#include "Player.h"

//初期化.
void Player::Init()
{
	pos    = { 100, 100 }; //初期位置.
	active = TRUE;
}
//更新.
void Player::Update()
{
	//有効なら.
	if (active) {
		PlayerMove();
	}
}
//描画.
void Player::Draw()
{
	//有効なら.
	if (active) {
		unsigned int Cr;
		Cr = GetColor(255, 255, 255); // 白色

		// 四角形を描画（プレイヤーの位置に）
		int x  = _int(pos.x - PLAYER_SIZE/2);
		int y  = _int(pos.y - PLAYER_SIZE/2);
		int dx = _int(pos.x + PLAYER_SIZE/2);
		int dy = _int(pos.y + PLAYER_SIZE/2);
		DrawBox(x, y, dx, dy, Cr, TRUE);
	}
}

//移動処理(斜め対応)
void Player::PlayerMove()
{	
	INT_XY pow{};  //移動力.
	DBL_XY move{}; //求めた移動量.

	//キー入力に応じて移動力を与える.
	if (CheckHitKey(KEY_INPUT_UP))
	{
		pow.y += -1;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		pow.y += +1;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		pow.x += -1;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		pow.x += +1;
	}

	//移動力があれば.
	if (pow.x != 0 || pow.y != 0) {

		//角度にする.
		double theta = atan2(pow.y, pow.x);
		//移動量を求める.
		move = { cos(theta), sin(theta) };
		//ほぼ0の値なら0と見なす(計算上誤差があるため)
		if (fabs(move.x) < 0.0001) { move.x = 0; }
		if (fabs(move.y) < 0.0001) { move.y = 0; }
	}

	//座標移動.
	pos.x += move.x * PLAYER_MOVE_SPEED;
	pos.y += move.y * PLAYER_MOVE_SPEED;
	//移動限界.
	if (pos.x < 0 + PLAYER_SIZE/2) pos.x = PLAYER_SIZE/2;
	if (pos.y < 0 + PLAYER_SIZE/2) pos.y = PLAYER_SIZE/2;
	if (pos.x > WINDOW_WID - PLAYER_SIZE/2) pos.x = WINDOW_WID - PLAYER_SIZE/2;
	if (pos.y > WINDOW_HEI - PLAYER_SIZE/2) pos.y = WINDOW_HEI - PLAYER_SIZE/2;
}