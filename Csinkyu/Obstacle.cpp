/*
   - Obstacle.cpp -
   ��Q���Ǘ�.
*/
#include "Player.h"
#include "Obstacle.h"

void Obstacle::Init(Player* _player) {
	//�v���C���[���̂̃A�h���X�����炤.
	player = _player;
}

void Obstacle::Update() {

	//���̉�].
	ang += 1;
	line.edPos = CalcLineAng(line.stPos, ang, len);

	//���������玀�S.
	if (IsHitLine(&line, player->GetHit())) {
		player->SetActive(FALSE);
	}
}

void Obstacle::Draw() {

	//�����蔻��̉���.
	if (CheckHitKey(KEY_INPUT_0)) {
		
		DBL_XY mdPos = CalcMidPos(line.stPos, line.edPos);
		DrawCircle(_int(mdPos.x), _int(mdPos.y), _int(len/2), 0x303030);

		Line debugLine1 = {line.stPos, CalcLineAng(line.stPos, ang, 1000),       0x303030};
		Line debugLine2 = {line.stPos, CalcLineAng(line.stPos, ang + 180, 1000), 0x303030};
		DrawLineST(&debugLine1);
		DrawLineST(&debugLine2);
	}

	//���̕`��.
	DrawLineST(&line);
}