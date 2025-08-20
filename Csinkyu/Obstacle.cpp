/*
   - Obstacle.cpp -
   ��Q���Ǘ�.
*/
#include "Player.h"
#include "Obstacle.h"

void Obstacle::Init(GameData* _data, Player* _player) {
	//���̂̃A�h���X�����炤.
	data   = _data;
	player = _player;
}

void Obstacle::Reset(DBL_XY _pos, float _ang) {
	line.stPos = _pos;
	ang        = _ang;
}

void Obstacle::Update() {

	//��]���x.
	ang += speed * (float)((data->isSlow) ? SLOW_MODE_SPEED : 1);
	//���̉�].
	line.edPos = CalcArcPos(line.stPos, ang, len);

	//���������玀�S.
	if (HitCheckLine(&line, player->GetHit())) {
		player->PlayerDeath();
	}
}

void Obstacle::Draw() {

	//�f�o�b�O�\��.
	if (CheckHitKey(KEY_INPUT_0)) {
		
		DBL_XY mdPos = CalcMidPos(line.stPos, line.edPos);
		DrawCircle(_int45(mdPos.x), _int45(mdPos.y), _int45(len/2), 0x303030);

		Line debugLine1 = {line.stPos, CalcArcPos(line.stPos, ang, 1000),       0x303030};
		Line debugLine2 = {line.stPos, CalcArcPos(line.stPos, ang + 180, 1000), 0x303030};
		DrawLineST(&debugLine1);
		DrawLineST(&debugLine2);

		
		
		(0, 455, _T("[Debug] ���̓����蔻���\��"), 0xFFFFFF);
	}

	//���̕`��.
	DrawLineST(&line);
}