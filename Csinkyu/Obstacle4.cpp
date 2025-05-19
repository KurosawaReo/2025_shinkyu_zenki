/*
   - Obstacle4.cpp -
   ��Q���Ǘ��N���X (���c����)
   �v���C���[��ǔ����郌�[�U�[�𔭎˂����Q��������
*/
#include "DxLib.h"     // DX���C�u�����̃w�b�_�[�t�@�C�����C���N���[�h
#include <math.h>      // ���w�֐����g�p���邽�߂̃w�b�_�[�t�@�C��
#include "Player.h"    // �v���C���[�N���X�̃w�b�_�[�t�@�C��
#include "Obstacle4.h" // ���g�̃w�b�_�[�t�@�C��

// �Q�[�����̒萔��`
#define PLAYER_SIZE 32  // �v���C���[�̃T�C�Y�i���ƍ����j
#define WINDOW_WID 640  // �E�B���h�E�̕�
#define WINDOW_HEI 480  // �E�B���h�E�̍���

/**
 * @brief ��Q���̏���������
 * @param _player �v���C���[�I�u�W�F�N�g�ւ̃|�C���^
 */
void Obstacle4::Init(Player* _player)
{
	player = _player;  // �v���C���[�I�u�W�F�N�g���Q�ƂƂ��ĕۑ�
	Reset();
}

//���Z�b�g.
void Obstacle4::Reset() {

	Hx = 320;             // �C���X���W�����l�i��ʒ����j
	Hy = 30;              // �C���Y���W�����l�i��ʏ㕔�j
	Hm = 3;               // �C��̈ړ����x
	Hsc = OBSTACLE4_SPAN; // �C��̔��˃J�E���^�����l

	// ���[�U�[�f�[�^�̏�����
	for (int i = 0; i < MAX_L; i++)
		Ld[i].ValidFlag = 0;  // ���ׂẴ��[�U�[�𖳌���Ԃ�

	// ���[�U�[�̋O�Ճf�[�^�̏�����
	for (int i = 0; i < LINE_MAXNUM; i++)
		Line[i].ValidFlag = 0;  // ���ׂĂ̋O�Ղ𖳌���Ԃ�
}

/**
 * @brief ��Q���̍X�V����
 * �v���C���[���L���ȏꍇ�̂ݏ�Q���̓������X�V
 */
void Obstacle4::Update()
{
	if (player->GetActive()) {  // �v���C���[���A�N�e�B�u�ȏꍇ�̂�
		enemy4Move();           // ��Q���̈ړ����������s
	}
}

/**
 * @brief ��Q���̕`�揈��
 * ���[�U�[�̋O�ՂƖC���`��
 */
void Obstacle4::Draw()
{
	// ���Z�������[�h�ŋO�Ղ�`��i�����G�t�F�N�g�j
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// ���[�U�[�̋O�Ղ̕`�揈��
	for (int i = 0; i < LINE_MAXNUM; i++)
	{
		if (Line[i].ValidFlag == 0) continue;  // �����ȋO�Ղ̓X�L�b�v

		// �O�Ղ̐���`��i���Ԍo�߂ŐF���ω��j
		DrawLine(Line[i].x1, Line[i].y1,
			Line[i].x2, Line[i].y2,
			GetColor(0, 255 - Line[i].Counter * 4, 0));  // �ΐF�ŁA���Ԍo�߂ŏ��X�ɔ����Ȃ�

		Line[i].Counter++;  // �o�ߎ��ԃJ�E���^����
		if (Line[i].Counter == 64) Line[i].ValidFlag = 0;  // 64�t���[���o�߂�����O�Ղ𖳌���
	}

	// �ʏ�̕`�惂�[�h�ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// �C������F�̎l�p�`�ŕ`��
	DrawBox(Hx - 8, Hy - 8, Hx + 8, Hy + 8, GetColor(100, 100, 100), TRUE);
}

/**
 * @brief �G�i��Q���j�̈ړ�����
 * ���[�U�[�̈ړ��ƃv���C���[�ւ̒ǔ��A�C��̈ړ��ƃ��[�U�[���˂��Ǘ�
 */
void Obstacle4::enemy4Move()
{
	// �e���[�U�[�̏���
	for (int i = 0; i < MAX_L; i++)
	{
		int xb, yb;  // �O��ʒu��ۑ�����ϐ�
		if (Ld[i].ValidFlag == 0) continue;  // �����ȃ��[�U�[�̓X�L�b�v

		// �v���C���[�̌��݈ʒu���擾
		DBL_XY playerPos = player->GetPos();
		double Px = playerPos.x;
		double Py = playerPos.y;
		double halfSize = PLAYER_SIZE / 2.0;  // �v���C���[�̓����蔻��T�C�Y�̔���

		// �v���C���[�ƃ��[�U�[�̓����蔻��
		if ((Ld[i].x > Px - halfSize && Ld[i].x < Px + halfSize) &&
			(Ld[i].y > Py - halfSize && Ld[i].y < Py + halfSize))
		{
			Ld[i].ValidFlag = 0;  // ���������烌�[�U�[�𖳌���
			player->PlayerDeath();
			continue;
		}

		// ���[�U�[�̒ǔ������i���ˌ��莞�Ԃ̂݁j
		if (Ld[i].Counter < 200)  // 200�t���[���i��3.3�b�j�ȓ��̂ݒǔ�
		{
			// ���݂̃v���C���[�����ւ̊p�x���v�Z
			double targetAngle = atan2(Py - Ld[i].y, Px - Ld[i].x);
			// ���[�U�[�̌��݂̈ړ������̊p�x
			double currentAngle = atan2(Ld[i].sy, Ld[i].sx);
			// �p�x�̍������v�Z
			double angleDiff = targetAngle - currentAngle;

			// �p�x������-PI�`PI�͈̔͂ɐ��K��
			while (angleDiff > PI) angleDiff -= 2 * PI;
			while (angleDiff < -PI) angleDiff += 2 * PI;

			// �ő����p�x�𐧌��i1�t���[����15�x�܂Łj
			const double maxTurn = PI / 180 * 15;
			if (angleDiff > maxTurn) angleDiff = maxTurn;
			if (angleDiff < -maxTurn) angleDiff = -maxTurn;

			// �V�����p�x���v�Z���đ��x���X�V
			double newAngle = currentAngle + angleDiff;
			Ld[i].sx += (int)(cos(newAngle) * 30);  // X�������x���X�V
			Ld[i].sy += (int)(sin(newAngle) * 30);  // Y�������x���X�V
		}

		Ld[i].Counter++;  // ���[�U�[�̌o�ߎ��ԃJ�E���^�𑝉�

		// �ړ��O�̍��W��ۑ�
		xb = Ld[i].x;
		yb = Ld[i].y;

		// ���[�U�[�̈ʒu���X�V�i���x�Ɋ�Â��Ĉړ��j
		Ld[i].x = (Ld[i].x * 100 + Ld[i].sx) / 100;
		Ld[i].y = (Ld[i].y * 100 + Ld[i].sy) / 100;

		// ���[�U�[�̋O�Ղ𐶐�
		for (int j = 0; j < LINE_MAXNUM; j++)
		{
			if (Line[j].ValidFlag == 0)  // ���g�p�̋O�ՃX���b�g��T��
			{
				// �O�Ճf�[�^�̐ݒ�
				Line[j].x1 = xb;           // �J�n�_X���W
				Line[j].y1 = yb;           // �J�n�_Y���W
				Line[j].x2 = Ld[i].x;      // �I���_X���W
				Line[j].y2 = Ld[i].y;      // �I���_Y���W
				Line[j].Counter = 0;       // �o�ߎ��ԃJ�E���^������
				Line[j].ValidFlag = 1;     // �O�Ղ�L����
				break;
			}
		}

		// ��ʊO�ɏo�����[�U�[�𖳌���
		if (Ld[i].x < -100 || Ld[i].x > WINDOW_WID + 100 ||
			Ld[i].y < -100 || Ld[i].y > WINDOW_HEI + 100)
		{
			Ld[i].ValidFlag = 0;
		}
	}

	// �C��̈ړ��ƃ��[�U�[���ˏ���
	{
		Hx += Hm;  // �C���X�����Ɉړ�

		// ��ʒ[�Ŕ���
		if (Hx > WINDOW_WID - 16 || Hx < 0) Hm *= -1;

		Hsc--;  // ���˃J�E���^������
		// �^�C�~���O�������烌�[�U�[����
		if (Hsc == 0 || Hsc == 15 || Hsc == 30)
		{
			// ���g�p�̃��[�U�[�X���b�g��T���ă��[�U�[�𔭎�
			for (int i = 0; i < MAX_L; i++)
			{
				if (Ld[i].ValidFlag == 0)  // ���g�p�̃��[�U�[�X���b�g��������
				{
					// �v���C���[���W�擾
					DBL_XY playerPos = player->GetPos();
					double Px = playerPos.x;
					double Py = playerPos.y;

					// ���ˈʒu�i�C��̏���������j
					double startX = Hx + 16;
					double startY = Hy + 16;

					// �v���C���[�����ւ̏����p�x�v�Z
					double angle = atan2(Py - startY, Px - startX);

					// ���[�U�[�f�[�^�̏�����
					Ld[i].x = startX;       // ����X���W
					Ld[i].y = startY;       // ����Y���W
					Ld[i].sx = (int)(cos(angle) * 30);  // X�����������x
					Ld[i].sy = (int)(sin(angle) * 30);  // Y�����������x
					Ld[i].Counter = 0;      // �o�ߎ��ԃJ�E���^������
					Ld[i].LogNum = 0;       // �O�ՃJ�E���^������
					Ld[i].ValidFlag = 1;    // ���[�U�[��L����
					break;
				}
			}
		}
		if (Hsc == 0) {
			Hsc = OBSTACLE4_SPAN;  // ���˃J�E���^�����Z�b�g�i���̔��˂܂ł̑ҋ@���ԁj
		}
	}
}