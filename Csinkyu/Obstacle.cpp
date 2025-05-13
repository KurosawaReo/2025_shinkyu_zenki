/*
   - Obstacle.cpp -
   ��Q���Ǘ�.
*/
#include "Player.h"
#include "Obstacle.h"

#define PLAYER_HIT_R 10 //�v���C���[�̓����蔻��~�̔��a.

void Obstacle::Init(Player* _player) {
	//�v���C���[���̂̃A�h���X�����炤.
	player = _player;
}

void Obstacle::Update() {

	//���̉�].
	ang += 1;
	line.edPos = CalcLineAng(line.stPos, ang, len);

	//�v���C���[�̓����蔻��~.
	Circle circle = { player->GetPos(), PLAYER_HIT_R, 0x000000 };
	//���������玀�S.
	if (IsHitLine(&line, &circle)) {
		player->SetActive(FALSE);
	}
}

void Obstacle::Draw() {

	//�����蔻��̉���.
	if (CheckHitKey(KEY_INPUT_0)) {
		
		DBL_XY mdPos = CalcMidPos(line.stPos, line.edPos);
		DrawCircle(mdPos.x, mdPos.y, _int(len), 0x303030);

		Line debugLine1 = {line.stPos, CalcLineAng(line.stPos, ang, 1000),       0x303030};
		Line debugLine2 = {line.stPos, CalcLineAng(line.stPos, ang + 180, 1000), 0x303030};
		DrawLineST(&debugLine1);
		DrawLineST(&debugLine2);
	}

	//���̕`��.
	DrawLineST(&line);
}