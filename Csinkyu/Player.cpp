/*
   - Player.cpp -
   プレイヤー管理.
*/
#include "Player.h"

//WinMain関数
int PlayerX , PlayerY, PlayerGraph; // 中央下に初期値を設定
int i = 0; // iにも初期値を設定

//初期化.
void Player::Init()
{
}
//更新.
void Player::Update()
{
}
//描画.
void Player::Draw()
{
	unsigned int Cr;
	Cr = GetColor(255, 255, 255); // 白色

	// 四角形を描画（プレイヤーの位置に）
	DrawBox(PlayerX, PlayerY, PlayerX + 30, PlayerY + 30, Cr, TRUE);
}
void Player::PlayerMove()
{
	// キー入力に応じてプレイヤーを移動
	if (CheckHitKey(KEY_INPUT_UP) == 1)
	{
		PlayerY -= 3;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		PlayerY += 3;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		PlayerX -= 3;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		PlayerX += 3; // ここは元のコードではPlayerYに代入していましたが修正
	}

	 if (PlayerX < 0) PlayerX = 0;
    if (PlayerY < 0) PlayerY = 0;
    if (PlayerX > 640 - 30) PlayerX = 640 - 30; // 画面サイズを640x480と仮定
    if (PlayerY > 480 - 30) PlayerY = 480 - 30;
}