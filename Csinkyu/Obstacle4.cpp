/*
   - Obstacle4.cpp -
   ��Q���Ǘ�.(���c����)
*/
#include "DxLib.h"
#include <math.h>
#include "Player.h"
#include "Obstacle4.h"

// �O����`������Βǉ�
#define PLAYER_SIZE 32
#define WINDOW_WID 640
#define WINDOW_HEI 480

void Obstacle4::Init(Player* _player)
{
	// �v���C���[�̎��̃A�h���X�����炤
	player = _player;

	// �C��̍��W�Z�b�g
	Hx = 320;
	Hy = 30;

	// �C��̈ړ������Z�b�g
	Hm = 3;

	// �C��̈ړ��Ԋu�J�E���^�Z�b�g
	Hsc = 30;

	// ���[�U�[�f�[�^�̏�����
	for (int i = 0; i < MAX_L; i++)
		Ld[i].ValidFlag = 0;

	// ���C���f�[�^�̏�����
	for (int i = 0; i < LINE_MAXNUM; i++)
		Line[i].ValidFlag = 0;
}

void Obstacle4::Update()
{
	// �v���C���[���L���ȂƂ��̂ݍX�V
	if (player->GetActive()) {
		// ���[�U�[�̈ړ������ƖC��̓������X�V
		enemy4Move();
	}
}

void Obstacle4::Draw()
{
	// �`��u�����h���[�h�����Z�������ɃZ�b�g
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// ���C���̕`��
	for (int i = 0; i < LINE_MAXNUM; i++)
	{
		// ���C���f�[�^���L���łȂ��ꍇ�͎��Ɉڂ�
		if (Line[i].ValidFlag == 0) continue;

		// ���C���̕`��
		DrawLine(Line[i].x1, Line[i].y1,
			Line[i].x2, Line[i].y2,
			GetColor(0, 255 - Line[i].Counter * 4, 0));

		// �J�E���^�����Z����
		Line[i].Counter++;

		// �����K��l�ɒB���Ă����烉�C���f�[�^�𖳌��ɂ���
		if (Line[i].Counter == 64) Line[i].ValidFlag = 0;
	}

	// �`��u�����h���[�h��ʏ�`�惂�[�h�ɃZ�b�g
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// �C��̕`��
	DrawBox(Hx - 8, Hy - 8, Hx + 8, Hy + 8, GetColor(255, 255, 0), TRUE);
}

// �G�̈ړ�
void Obstacle4::enemy4Move()
{
	// ���[�U�[�̈ړ�����
	for (int i = 0; i < MAX_L; i++)
	{
		int xb, yb;

		// ���[�U�[�f�[�^��������������X�L�b�v
		if (Ld[i].ValidFlag == 0) continue;

		// �v���C���[�̍��W���擾
		DBL_XY playerPos = player->GetPos();
		double Px = playerPos.x;
		double Py = playerPos.y;

		// �v���C���[����p�T�C�Y
		double halfSize = PLAYER_SIZE / 2.0;

		// �Ə��ɓ������Ă����烌�[�U�[�f�[�^�𖳌��ɂ���
		if ((Ld[i].x > Px - halfSize && Ld[i].x < Px + halfSize) &&
			(Ld[i].y > Py - halfSize && Ld[i].y < Py + halfSize))
		{
			Ld[i].ValidFlag = 0;
			// �����Ńv���C���[�ւ̃_���[�W������ǉ��ł��܂�
			// �v���C���[�N���X�Ƀ_���[�W���\�b�h���Ȃ��ꍇ�̓R�����g�A�E�g
			// player->SetActive(FALSE); // �v���C���[�𖳌��������

			continue;
		}

		// �ǔ��J�E���^���K��l�ɗ��Ă��Ȃ���Βǔ�����
		double Angle = atan2(Ld[i].sy, Ld[i].sx); // �p�x���v�Z
		if (Ld[i].Counter < 200)
		{
			double ax, ay, bx, by;

			// bx,by �����̐i��ł������ ax,ay �{���i�ނׂ�����  
			bx = cos(Angle);
			by = sin(Angle);
			ax = Px - Ld[i].x;
			ay = Py - Ld[i].y;

			// �O�ς𗘗p���������Ə����Ɍ�����
			Angle += (ax * by - ay * bx < 0.0) ? +PI / 180 * 15 : -PI / 180 * 15;
		}

		// �ǔ��J�E���^���Z
		Ld[i].Counter++;

		// ���x��ύX����
		Ld[i].sx += (int)(cos(Angle) * 30);
		Ld[i].sy += (int)(sin(Angle) * 30);

		// �ړ��O�̃A�h���X��ۑ�
		xb = Ld[i].x;
		yb = Ld[i].y;

		// �ړ�����
		Ld[i].x = (Ld[i].x * 100 + Ld[i].sx) / 100;
		Ld[i].y = (Ld[i].y * 100 + Ld[i].sy) / 100;

		// ���݂̏�Ԃ����C���f�[�^�ɕϊ�
		{
			int j;

			// �g���Ă��Ȃ����C���f�[�^��T��
			for (j = 0; j < LINE_MAXNUM; j++)
			{
				if (Line[j].ValidFlag == 0) break;
			}

			// ������̃f�[�^���������ꍇ�̂݃��C���f�[�^�ǉ�
			if (j != LINE_MAXNUM)
			{
				// ���C�������Z�b�g����

				// ���W�̃Z�b�g
				Line[j].x1 = xb; Line[j].y1 = yb;
				Line[j].x2 = Ld[i].x; Line[j].y2 = Ld[i].y;

				// �F����J�E���^��������
				Line[j].Counter = 0;

				// �f�[�^���g�p���ɃZ�b�g
				Line[j].ValidFlag = 1;
			}
		}

		// ��ʊO�ɏo�Ă����烌�[�U�[�f�[�^�𖳌��ɂ���
		if (Ld[i].x < -100 || Ld[i].x > WINDOW_WID + 100 ||
			Ld[i].y < -100 || Ld[i].y > WINDOW_HEI + 100) Ld[i].ValidFlag = 0;
	}

	// �C��̈ړ�����
	{
		Hx += Hm;

		// ��ʒ[�܂ŗ��Ă����甽�]
		if (Hx > WINDOW_WID - 16 || Hx < 0) Hm *= -1;

		// �V���b�g�J�E���^�����炷
		Hsc--;

		// �J�E���^���O�ɂȂ��Ă����烌�[�U�[����
		if (Hsc == 0)
		{
			int i;
			// �g���Ă��Ȃ����[�U�[�f�[�^��T��
			for (i = 0; i < MAX_L; i++)
			{
				if (Ld[i].ValidFlag == 0) break;
			}

			// �����g���Ă��Ȃ����[�U�[�f�[�^����������V���b�g���o��
			if (i != MAX_L)
			{
				// ���[�U�[�̈ʒu��ݒ�
				Ld[i].x = Hx + 16;
				Ld[i].y = Hy + 16;

				// ���[�U�[�̑��x��ݒ�
				Ld[i].sx = 0;
				Ld[i].sy = 0;

				// �J�E���^���Z�b�g
				Ld[i].LogNum = 0;
				Ld[i].Counter = 0;

				// ���[�U�[�f�[�^���g�p���ɃZ�b�g
				Ld[i].ValidFlag = 1;
			}

			// ���ˊԊu�J�E���^�l���Z�b�g
			Hsc = 30;
		}
	}
}