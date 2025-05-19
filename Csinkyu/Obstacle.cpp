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

void Obstacle::Reset(DBL_XY _pos, float _ang) {
	line.stPos = _pos;
	ang        = _ang;
}

void Obstacle::Update() {

	//���̉�].
	ang += speed;
	line.edPos = CalcLineAng(line.stPos, ang, len);

	//���������玀�S.
	if (IsHitLine(&line, player->GetHit())) {
		player->PlayerDeath();
	}
}

void Obstacle::Draw() {

	//�f�o�b�O�\��.
	if (CheckHitKey(KEY_INPUT_0)) {
		
		DBL_XY mdPos = CalcMidPos(line.stPos, line.edPos);
		DrawCircle(_int(mdPos.x), _int(mdPos.y), _int(len/2), 0x303030);

		Line debugLine1 = {line.stPos, CalcLineAng(line.stPos, ang, 1000),       0x303030};
		Line debugLine2 = {line.stPos, CalcLineAng(line.stPos, ang + 180, 1000), 0x303030};
		DrawLineST(&debugLine1);
		DrawLineST(&debugLine2);

		DrawString(0, 455, _T("[Debug] ���̓����蔻���\��"), 0xFFFFFF);
	}

	//���̕`��.
	DrawLineST(&line);
}