/*
   - Obstacle4.cpp -
   障害物管理.(小田島作)
*/
#include "Player.h"
#include "Obstacle4.h"

void Obstacle4::Init(Player* _player)
{
	LoadGraphST(&img, _T("image/enemy.png"));


	player = _player; //プレイヤーの実体アドレスをもらう.

	for (int i = 0; i < MAX_M; i++)
	{
		Mv[i] = 0;
	}
	//発射カウント値をリセット.
	hsc = 30;
}
void Obstacle4::Update()
{
	enemy4Move();
}
void Obstacle4::Draw()
{
	
}

//敵の移動.
void Obstacle4::enemy4Move()
{
	
}

