/*
   - Obstacle.cpp -
   障害物管理.
*/
#include "Player.h"
#include "Obstacle.h"

#define PLAYER_HIT_R 10 //プレイヤーの当たり判定円の半径.

void Obstacle::Init(Player* _player) {
	//プレイヤー実体のアドレスをもらう.
	player = _player;
}

void Obstacle::Update() {
	//回転.
	ang += 1;

	//線の始点と終点から傾きを求める.
	float katamuki;
	{
		int x = edPos.x - stPos.x;
		int y = edPos.y - stPos.y;
		if (x != 0) {
			katamuki = (float)y / x;
		}
		else {
			katamuki = 100; //0割対策.
		}
	}
	//切片.
	float seppen = stPos.y - stPos.x * katamuki;
	//直線と円の距離.
	double dis1;
	{
		//直線: ax + by + c = 0
		float a = -katamuki;
		float b = 1;
		float c = -seppen;
		//d = |ax + by + c|/√(a^2 + b^2)
		dis1 = fabs(a * player->GetPos().x + b * player->GetPos().y + c) / sqrt(a * a + b * b);
	}

	//直線始点と円中点の距離.
	double dis2;
	double ang2;
	{
		double x = player->GetPos().x - mdPos.x;
		double y = player->GetPos().y - mdPos.y;
		//d = √(x^2 + y^2)
		dis2 = sqrt(x * x + y * y);
		//角度.
		ang2 = atan2(y, x) * 180 / M_PI;
	}

	//hit条件.
	if (dis1 <= PLAYER_HIT_R &&  //直線とプレイヤーが触れている.
		dis2 <= len              //回転する円の半径以内に入っている.
		) {
		player->SetActive(FALSE);
	}
}

void Obstacle::Draw() {

	//当たり判定の可視化.
	if (CheckHitKey(KEY_INPUT_0)) {
		DrawCircle (mdPos.x, mdPos.y, _int(len), 0x303030);
		DrawLineAng(stPos, ang,     1000, 0x303030);
		DrawLineAng(stPos, ang+180, 1000, 0x303030);
	}

	//線の描画.
	mdPos = DrawLineAng(stPos, ang, len, 0x00FF00); //始点から中点まで.
	edPos = DrawLineAng(mdPos, ang, len, 0x00FF00); //中点から終点まで.
}