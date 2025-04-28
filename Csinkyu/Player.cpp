/*
   - Player.cpp -
   プレイヤー管理.
*/
#include "Player.h"
<<<<<<< HEAD
=======
#include "GlovalConst.h"
>>>>>>> main

//WinMain関数
int PlayerX, PlayerY, PlayerGraph; // 中央下に初期値を設定
int i = 0; // iにも初期値を設定
void Move();
void atari();
//初期化.
void Player::Init()
{
}
//更新.
void Player::Update()
{
<<<<<<< HEAD
	PlayerMove();
=======

	Move();
>>>>>>> main
}
//描画.
void Player::Draw()
{
	unsigned int Cr;
	Cr = GetColor(255, 255, 255); // 白色
<<<<<<< HEAD
=======

	// 四角形を描画（プレイヤーの位置に）
	DrawBox(PlayerX, PlayerY, PlayerX + 30, PlayerY + 30, Cr, TRUE);
}
void Move()
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
		PlayerX += 3;
	}

	if (PlayerX < 0)
	{
		PlayerX = 0;
	}
>>>>>>> main

	if (PlayerY < 0)
	{
		PlayerY = 0;
	}
	if (PlayerX > WINDOW_WID - 30)
	{
		PlayerX = WINDOW_WID - 30;
	}
	if (PlayerY > WINDOW_HEI - 30)
	{
		PlayerY = WINDOW_HEI - 30;
	}
	
	
}
void atari()
{

<<<<<<< HEAD
	// 四角形を描画（プレイヤーの位置に）
<<<<<<< HEAD
	int x  = _int(pos.x);
	int y  = _int(pos.y);
	int dx = _int(pos.x + PLAYER_SIZE);
	int dy = _int(pos.y + PLAYER_SIZE);
	DrawBox(x, y, dx, dy, Cr, TRUE);
}

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
	if (pos.x < 0) pos.x = 0;
	if (pos.y < 0) pos.y = 0;
	if (pos.x > WINDOW_WID - PLAYER_SIZE) pos.x = WINDOW_WID - PLAYER_SIZE;
	if (pos.y > WINDOW_HEI - PLAYER_SIZE) pos.y = WINDOW_HEI - PLAYER_SIZE;
}
=======
	DrawBox(PlayerX, PlayerY, PlayerX + 30, PlayerY + 30, Cr, TRUE);
=======
>>>>>>> Player4
}
>>>>>>> main
