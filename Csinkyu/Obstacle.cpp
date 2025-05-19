/*
   - Obstacle.cpp -
   障害物管理.
*/
#include "Player.h"
#include "Obstacle.h"

void Obstacle::Init(Player* _player) {
	//プレイヤー実体のアドレスをもらう.
	player = _player;
}

void Obstacle::Reset(DBL_XY _pos, float _ang) {
	line.stPos = _pos;
	ang        = _ang;
}

void Obstacle::Update() {

	//線の回転.
	ang += speed;
	line.edPos = CalcLineAng(line.stPos, ang, len);

	//当たったら死亡.
	if (IsHitLine(&line, player->GetHit())) {
		player->PlayerDeath();
	}
}

void Obstacle::Draw() {

	//デバッグ表示.
	if (CheckHitKey(KEY_INPUT_0)) {
		
		DBL_XY mdPos = CalcMidPos(line.stPos, line.edPos);
		DrawCircle(_int(mdPos.x), _int(mdPos.y), _int(len/2), 0x303030);

		Line debugLine1 = {line.stPos, CalcLineAng(line.stPos, ang, 1000),       0x303030};
		Line debugLine2 = {line.stPos, CalcLineAng(line.stPos, ang + 180, 1000), 0x303030};
		DrawLineST(&debugLine1);
		DrawLineST(&debugLine2);

		DrawString(0, 455, _T("[Debug] 線の当たり判定を表示"), 0xFFFFFF);
	}

	//線の描画.
	DrawLineST(&line);
}