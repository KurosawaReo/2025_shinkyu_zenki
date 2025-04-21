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
	Cr = GetColor(0, 0, 255);

	PlayerGraph = DrawBox(270, 430, 270 + 50, 430 + 50, Cr, TRUE);//四角形を描画
	PlayerX = 320; PlayerY = 400;
	
}

#if false
void PlayerMove()
{
	
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
			PlayerY = 3;
		}
		DrawGraph(PlayerX, PlayerY, PlayerGraph, FALSE);
	
}
#endif