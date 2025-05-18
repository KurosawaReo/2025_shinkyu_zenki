/*
   - Player.cpp -
   プレイヤー管理.
*/
#include "Player.h"

//初期化.
void Player::Init()
{

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
		// 四角形を描画（プレイヤーの位置に）
		int x  = _int(hit.pos.x - PLAYER_SIZE/2);
		int y  = _int(hit.pos.y - PLAYER_SIZE/2);
		int dx = _int(hit.pos.x + PLAYER_SIZE/2);
		int dy = _int(hit.pos.y + PLAYER_SIZE/2);

		unsigned int Cr;
		Cr = GetColor(255, 255, 255); // 白色

		DrawBox(x, y, dx, dy, Cr, TRUE);
	}
}

//移動処理(斜め対応)
void Player::PlayerMove()
{
	//移動する.
	InputKey4Dir(&hit.pos, PLAYER_MOVE_SPEED);
	//移動限界.
	LimMovePos(&hit.pos, { PLAYER_SIZE, PLAYER_SIZE }, 0, 0, WINDOW_WID, WINDOW_HEI);
}