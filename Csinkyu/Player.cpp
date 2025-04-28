/*
   - Player.cpp -
   プレイヤー管理.
*/
#include "Player.h"
#include"GlovalConst.h"
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
	if (PlayerX > WINDOW_WID - 30) PlayerX = WINDOW_WID - 30; // 画面サイズを640x480と仮定
	if (PlayerY > WINDOW_HEI- 30) PlayerY = WINDOW_HEI- 30;
}
//描画.
void Player::Draw()
{
	unsigned int Cr;
	Cr = GetColor(255, 255, 255); // 白色

	PlayerGraph = DrawBox(270, 430, 270 + 50, 430 + 50, Cr, TRUE);//四角形を描画
	PlayerX = 320; PlayerY = 400;

	// 四角形を描画（プレイヤーの位置に）
	DrawBox(PlayerX, PlayerY, PlayerX + 30, PlayerY + 30, Cr, TRUE);
}
//void Player::PlayerMove()
//{
//	
//}