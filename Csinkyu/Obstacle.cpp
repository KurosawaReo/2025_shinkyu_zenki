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
	//��].
	ang += 1;

	//���̎n�_�ƏI�_����X�������߂�.
	float katamuki;
	{
		int x = edPos.x - stPos.x;
		int y = edPos.y - stPos.y;
		if (x != 0) {
			katamuki = (float)y / x;
		}
		else {
			katamuki = 100; //0���΍�.
		}
	}
	//�ؕ�.
	float seppen = stPos.y - stPos.x * katamuki;
	//�����Ɖ~�̋���.
	double dis1;
	{
		//����: ax + by + c = 0
		float a = -katamuki;
		float b = 1;
		float c = -seppen;
		//d = |ax + by + c|/��(a^2 + b^2)
		dis1 = fabs(a * player->GetPos().x + b * player->GetPos().y + c) / sqrt(a * a + b * b);
	}

	//�����n�_�Ɖ~���_�̋���.
	double dis2;
	double ang2;
	{
		double x = player->GetPos().x - mdPos.x;
		double y = player->GetPos().y - mdPos.y;
		//d = ��(x^2 + y^2)
		dis2 = sqrt(x * x + y * y);
		//�p�x.
		ang2 = atan2(y, x) * 180 / M_PI;
	}

	//hit����.
	if (dis1 <= PLAYER_HIT_R &&  //�����ƃv���C���[���G��Ă���.
		dis2 <= len              //��]����~�̔��a�ȓ��ɓ����Ă���.
		) {
		player->SetActive(FALSE);
	}
}

void Obstacle::Draw() {

	//�����蔻��̉���.
	if (CheckHitKey(KEY_INPUT_0)) {
		DrawCircle (mdPos.x, mdPos.y, _int(len), 0x303030);
		DrawLineAng(stPos, ang,     1000, 0x303030);
		DrawLineAng(stPos, ang+180, 1000, 0x303030);
	}

	//���̕`��.
	mdPos = DrawLineAng(stPos, ang, len, 0x00FF00); //�n�_���璆�_�܂�.
	edPos = DrawLineAng(mdPos, ang, len, 0x00FF00); //���_����I�_�܂�.
}