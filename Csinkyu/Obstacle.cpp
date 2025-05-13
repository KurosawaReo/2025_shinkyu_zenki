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

	//線の回転.
	ang += 1;
	line.edPos = CalcLineAng(line.stPos, ang, len);

	//プレイヤーの当たり判定円.
	Circle circle = { player->GetPos(), PLAYER_HIT_R, 0x000000 };
	//当たったら死亡.
	if (IsHitLine(&line, &circle)) {
		player->SetActive(FALSE);
	}
}

void Obstacle::Draw() {

	//当たり判定の可視化.
	if (CheckHitKey(KEY_INPUT_0)) {
		
		DBL_XY mdPos = CalcMidPos(line.stPos, line.edPos);
		DrawCircle(mdPos.x, mdPos.y, _int(len), 0x303030);

		Line debugLine1 = {line.stPos, CalcLineAng(line.stPos, ang, 1000),       0x303030};
		Line debugLine2 = {line.stPos, CalcLineAng(line.stPos, ang + 180, 1000), 0x303030};
		DrawLineST(&debugLine1);
		DrawLineST(&debugLine2);
	}

	//線の描画.
	DrawLineST(&line);
}