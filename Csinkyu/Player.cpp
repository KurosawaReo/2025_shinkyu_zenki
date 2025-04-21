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

	PlayerGraph = LoadGraph
	PlayerX = 320; PlayerY = 400;
	
}
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