/*
   - Obstacle4.cpp -
   ��Q���Ǘ��N���X (���c����)
   �v���C���[��ǔ����郌�[�U�[�𔭎˂����Q��������
*/
#include "DxLib.h"     // DX���C�u�����̃w�b�_�[�t�@�C�����C���N���[�h
#include <math.h>      // ���w�֐����g�p���邽�߂̃w�b�_�[�t�@�C��
#include "Player.h"    // �v���C���[�N���X�̃w�b�_�[�t�@�C��
#include "Obstacle4.h" // ���g�̃w�b�_�[�t�@�C��
#include"Global.h"

//�ړ���`.
MoveDir moveDir;  // ���݂̈ړ�����
/**
 * @brief ��Q���̏���������
 * @param _player �v���C���[�I�u�W�F�N�g�ւ̃|�C���^
 */
void Obstacle4::Init(GameData* _data, Player* _player)
{
	data   = _data;
	player = _player;  // �v���C���[�I�u�W�F�N�g���Q�ƂƂ��ĕۑ�
	
	Reset();
}

//���Z�b�g.
void Obstacle4::Reset() {

	Hx  = 0;                  // �C���X���W�����l�i��ʒ����j
	Hy  = 30;                   // �C���Y���W�����l�i��ʏ㕔�j
	Hm  = 3;                    // �C��̈ړ����x
	Hsc = OBSTACLE4_SHOT_RESET; // �C��̔��˃J�E���^�����l
	moveDir = MOVE_RIGHT;     // �����������E�ɐݒ�.
	// ���[�U�[�f�[�^�̏�����
	for (int i = 0; i < OBSTACLE4_MAX_L; i++)
		ld[i].ValidFlag = 0;  // ���ׂẴ��[�U�[�𖳌���Ԃ�

	// ���[�U�[�̋O�Ճf�[�^�̏�����
	for (int i = 0; i < OBSTACLE4_LINE_MAX; i++)
		line[i].ValidFlag = 0;  // ���ׂĂ̋O�Ղ𖳌���Ԃ�
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
	for (int i = 0; i < OBSTACLE4_LINE_MAX; i++)
	{
		if (line[i].ValidFlag == 0) continue;  // �����ȋO�Ղ̓X�L�b�v

		//�ΐF�̒l, ���Ԍo�߂ŏ��X�ɔ�������.
		int g = _int(255 - line[i].Counter * 4);
		g = max(g, 0); //�Œ�l��0�ɂ���.

		// �O�Ղ̐���`��i���Ԍo�߂ŐF���ω��j
		Line tmpLine = { {line[i].x1, line[i].y1}, {line[i].x2, line[i].y2}, GetColor(0, g, 0)};
		DrawLineST(&tmpLine);

		// �o�ߎ��ԃJ�E���^����
		line[i].Counter += (data->isSlow) ? (float)SLOW_MODE_SPEED : 1;
		// 64�t���[���o�߂�����O�Ղ𖳌���
		if (line[i].Counter >= 64) line[i].ValidFlag = 0;
	}

	// �ʏ�̕`�惂�[�h�ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// �����C���`��
	Box box = { {Hx, Hy}, {8, 8}, GetColor(100, 100, 100) }; //{pos}, {size}, color.
	DrawBoxST(&box, TRUE);
}

/**
 * @brief �G�i��Q���j�̈ړ�����
 * ���[�U�[�̈ړ��ƃv���C���[�ւ̒ǔ��A�C��̈ړ��ƃ��[�U�[���˂��Ǘ�
 */
void Obstacle4::enemy4Move()
{
	DBL_XY pPos = player->GetPos(); // �v���C���[�̌��݈ʒu���擾
	double pSizeHalf = PLAYER_SIZE / 2.0;  // �v���C���[�̓����蔻��T�C�Y�̔���

	// �e���[�U�[�̏���
	for (int i = 0; i < OBSTACLE4_MAX_L; i++)
	{
		if (ld[i].ValidFlag == 0) continue;  // �����ȃ��[�U�[�̓X�L�b�v

		DBL_XY befPos;  // �O��ʒu��ۑ�����ϐ�

		// �v���C���[�ƃ��[�U�[�̓����蔻��
		if ((ld[i].x > pPos.x - pSizeHalf && ld[i].x < pPos.x + pSizeHalf) &&
			(ld[i].y > pPos.y - pSizeHalf && ld[i].y < pPos.y + pSizeHalf))
		{
			ld[i].ValidFlag = 0;  // ���������烌�[�U�[�𖳌���
			player->PlayerDeath();
			continue;
		}

		// ���[�U�[�̒ǔ������i���ˌ��莞�Ԃ̂݁j
		if (ld[i].Counter < 200)  // 200�t���[���i��3.3�b�j�ȓ��̂ݒǔ�
		{
			// ���݂̃v���C���[�����ւ̊p�x���v�Z
			double targetAngle  = atan2(pPos.y - ld[i].y, pPos.x - ld[i].x);
			// ���[�U�[�̌��݂̈ړ������̊p�x
			double currentAngle = atan2(ld[i].sy, ld[i].sx);
			// �p�x�̍������v�Z
			double angleDiff = targetAngle - currentAngle;

			// �p�x������-PI�`PI�͈̔͂ɐ��K��
			while (angleDiff >  M_PI) angleDiff -= 2 * M_PI;
			while (angleDiff < -M_PI) angleDiff += 2 * M_PI;

			// �ő����p�x�𐧌��i1�t���[����15�x�܂Łj
			const double maxTurn = M_PI/180 * 15;
			if (angleDiff > maxTurn) angleDiff = maxTurn;
			if (angleDiff < -maxTurn) angleDiff = -maxTurn;

			// �V�����p�x���v�Z���đ��x���X�V
			double newAngle = currentAngle + angleDiff;
			ld[i].sx += (int)(cos(newAngle) * 30);  // X�������x���X�V
			ld[i].sy += (int)(sin(newAngle) * 30);  // Y�������x���X�V
		}

		// ���[�U�[�̌o�ߎ��ԃJ�E���^�𑝉�
		ld[i].Counter += (data->isSlow) ? (float)SLOW_MODE_SPEED : 1;

		// �ړ��O�̍��W��ۑ�
		befPos = { ld[i].x, ld[i].y };

		// �~�T�C���̑��x
		double speed = OBSTACLE4_SPEED;
		if (data->isSlow) { speed /= SLOW_MODE_SPEED; }

		// ���[�U�[�̈ʒu���X�V�i���x�Ɋ�Â��Ĉړ��j
		ld[i].x = (ld[i].x * speed + ld[i].sx)/speed;
		ld[i].y = (ld[i].y * speed + ld[i].sy)/speed;

		// ���[�U�[�̋O�Ղ𐶐�
		for (int j = 0; j < OBSTACLE4_LINE_MAX; j++)
		{
			if (line[j].ValidFlag == 0)  // ���g�p�̋O�ՃX���b�g��T��
			{
				// �O�Ճf�[�^�̐ݒ�
				line[j].x1 = befPos.x;     // �J�n�_X���W
				line[j].y1 = befPos.y;     // �J�n�_Y���W
				line[j].x2 = ld[i].x;      // �I���_X���W
				line[j].y2 = ld[i].y;      // �I���_Y���W
				line[j].Counter = 0;       // �o�ߎ��ԃJ�E���^������
				line[j].ValidFlag = 1;     // �O�Ղ�L����
				break;
			}
		}

		// ��ʊO�ɏo�����[�U�[�𖳌���
		if (ld[i].x < -100 || ld[i].x > WINDOW_WID + 100 ||
			ld[i].y < -100 || ld[i].y > WINDOW_HEI + 100)
		{
			ld[i].ValidFlag = 0;
		}
	}

	// �C��̈ړ��ƃ��[�U�[���ˏ���
	{
		// �ړ����x
		float moveSpeed = Hm * ((data->isSlow) ? (float)SLOW_MODE_SPEED : 1);

		// ��`�o�H�̈ړ�����
		switch (moveDir)
		{
		case MOVE_RIGHT:
			Hx += moveSpeed;
			if (Hx > WINDOW_WID - 16) {
				Hx = WINDOW_WID - 16;
				moveDir = MOVE_DOWN;
			}
			break;

		case MOVE_DOWN:
			Hy += moveSpeed;
			if (Hy > WINDOW_HEI - 16) {
				Hy = WINDOW_HEI - 16;
				moveDir = MOVE_LEFT;
			}
			break;

		case MOVE_LEFT:
			Hx -= moveSpeed;
			if (Hx < 0) {
				Hx = 0;
				moveDir = MOVE_UP;
			}
			break;

		case MOVE_UP:
			Hy -= moveSpeed;
			if (Hy < 0) {
				Hy = 0;
				moveDir = MOVE_RIGHT;
			}
			break;
		}

		/*Hx += Hm *((data->isSlow) ? (float)SLOW_MODE_SPEED : 1);
		if (Hm > 0 && Hx > WINDOW_WID - 16)
		{
			Hm *= -1;
		}
		if (Hm < 0 && Hx<0)
		{
			Hm *= -1;
		}*/

		// ���˃J�E���^������
		Hsc -= (data->isSlow) ? (float)SLOW_MODE_SPEED : 1;
		// �^�C�~���O�������烌�[�U�[����
		if (Hsc <= HscTm)
		{
			// ���g�p�̃��[�U�[�X���b�g��T���ă��[�U�[�𔭎�
			for (int i = 0; i < OBSTACLE4_MAX_L; i++)
			{
				if (ld[i].ValidFlag == 0)  // ���g�p�̃��[�U�[�X���b�g��������
				{
					// ���ˈʒu�i�C��̏���������j
					double startX = Hx;
					double startY = Hy;
					
					// �v���C���[�����ւ̏����p�x�v�Z
					double angle = atan2(pPos.y - startY, pPos.x - startX);

					// ���[�U�[�f�[�^�̏�����
					ld[i].x = startX;			// ����X���W
					ld[i].y = startY;			// ����Y���W
					ld[i].sx = cos(angle) * 30; // X�����������x
					ld[i].sy = sin(angle) * 30; // Y�����������x
					ld[i].Counter = 0;			// �o�ߎ��ԃJ�E���^������
					ld[i].LogNum = 0;			// �O�ՃJ�E���^������
					ld[i].ValidFlag = 1;		// ���[�U�[��L����
					break;
				}
			}
			HscTm -= OBSTACLE4_SHOT_SPAN; //���˃^�C�~���O��ύX.
		}
		//0�b�����������������.
		if (Hsc <= 0) {
			Hsc   = OBSTACLE4_SHOT_RESET;  // ���˃J�E���^�����Z�b�g�i���̔��˂܂ł̑ҋ@���ԁj
			HscTm = OBSTACLE4_SHOT_START;
		}
	}
}