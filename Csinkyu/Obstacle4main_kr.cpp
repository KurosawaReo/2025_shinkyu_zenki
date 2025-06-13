/*
   - Obstacle4main_kr.cpp -

   ���[�U�[�̌p�����N���X (���V�C��)
   �v���C���[��ǔ����郌�[�U�[�𔭎˂����Q��������

   << 2025/06/13 >>
   ���˃��[�U�[�������Ȃ��o�O�̏C��ver.
   �Q�l�p�Ɏc���Ă���
*/
#include "Player.h"    // �v���C���[�N���X�̃w�b�_�[�t�@�C��
#include "Obstacle4.h" // ���g�̃w�b�_�[�t�@�C��

//���ꂪ��`����ĂȂ���΁A�����炪ON.
#if !defined ODAZIMA_LASER

/**
 * @brief ��Q���̍X�V����
 * �v���C���[���L���ȏꍇ�̂ݏ�Q���̓������X�V
 */
void Obstacle4main::Update()
{
	if (player->GetActive()) {  // �v���C���[���A�N�e�B�u�ȏꍇ�̂�
		enemy4Move();           // ��Q���̈ړ����������s
	}
}

/**
 * @brief ��Q���̕`�揈��
 * ���[�U�[�̋O�ՂƖC���`��
 */
void Obstacle4main::Draw()
{
	// ���Z�������[�h�ŋO�Ղ�`��i�����G�t�F�N�g�j
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// ���[�U�[�̋O�Ղ̕`�揈��
	for (int i = 0; i < OBSTACLE4_LINE_MAX; i++)
	{
		if (line[i].ValidFlag == 0) continue;  // �����ȋO�Ղ̓X�L�b�v

		// �ΐF�̒l, ���Ԍo�߂ŏ��X�ɔ�������.
		int g = _int(255 - line[i].Counter * 4);
		g = max(g, 0); //�Œ�l��0�ɂ���.

		// �O�Ղ̐���`��i���Ԍo�߂ŐF���ω��j
		Line tmpLine = { {line[i].x1, line[i].y1}, {line[i].x2, line[i].y2}, GetColor(0, g, 0) };
		DrawLineST(&tmpLine);

		// �o�ߎ��ԃJ�E���^����
		line[i].Counter += (data->isSlow) ? (float)SLOW_MODE_SPEED : 1;
		// 64�t���[���o�߂�����O�Ղ𖳌���
		if (line[i].Counter >= 64) line[i].ValidFlag = 0;
	}

	// �ʏ�̕`�惂�[�h�ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	/*
	//���[�U�[�̐F��ς��邽�߂ɂ́�����������K�v����.
	//�����͈�U�ۗ�.
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
	{
		//�����ȃ��[�U�[�̓X�L�b�v.
		if (laser[i].ValidFlag == 0)continue;

		// ���˃��[�U�[�͐ԐF�A�ʏ탌�[�U�[�͗ΐF�ŕ`��
		int color = laser[i].isReflected ? GetColor(255, 100, 100) : GetColor(100, 255, 100);
	}
	*/

	//[debug] ���[�U�[�̐�[�ɉ~��`��.
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
	{
		//���˃��[�U�[�͐ԐF�A�ʏ탌�[�U�[�͗ΐF.
		int color = laser[i].isReflected ? GetColor(255, 100, 100) : GetColor(100, 255, 100);
		DrawCircle(laser[i].x, laser[i].y, 5, color);
	}
}

/**
 * @brief �G�i��Q���j�̈ړ�����
 * ���[�U�[�̈ړ��ƃv���C���[�ւ̒ǔ��A�C��̈ړ��ƃ��[�U�[���˂��Ǘ�
 */
void Obstacle4main::enemy4Move()
{
	DBL_XY pPos = player->GetPos(); // �v���C���[�̌��݈ʒu���擾
	double pSizeHalf = PLAYER_SIZE / 2.0;  // �v���C���[�̓����蔻��T�C�Y�̔���

	// �e���[�U�[�̏���
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
	{
		if (laser[i].ValidFlag == 0) continue;  // �����ȃ��[�U�[�̓X�L�b�v

		DBL_XY befPos;  // �O��ʒu��ۑ�����ϐ�

		//�ʏ탌�[�U�[�Ȃ�.
		if (!laser[i].isReflected) {

			// �v���C���[�ƃ��[�U�[�̓����蔻��
			if ((laser[i].x > pPos.x - pSizeHalf && laser[i].x < pPos.x + pSizeHalf) &&
				(laser[i].y > pPos.y - pSizeHalf && laser[i].y < pPos.y + pSizeHalf))
			{
				//�v���C���[�����˃��[�h�Ȃ�.
				if (player->IsReflectionMode())
				{
					//���˃��[�U�[����.
					CreateReflectedLasers(
					  laser[i].x,
					  laser[i].y,
					  laser[i].sx,
					  laser[i].sy
					);
					//�v���C���[�̃N�[���_�E����ݒ�.
					player->UseReflection();

					//���̃��[�U�𖳌���.
					laser[i].ValidFlag = 0;
				}
				else {

					DrawString(0, 400, _T("���˃��[�h�ł͂���܂���"), 0xFFFFFF);

					laser[i].ValidFlag = 0;  //���������烌�[�U�[�𖳌���.
					player->PlayerDeath();   //�v���C���[���S.
				}
			}
		}
		//���˃��[�U�[�Ȃ�.
		else {
			//覐΂ƃ��[�U�[�̓����蔻��.
		}

		// ���[�U�[�̒ǔ������i���ˌ��莞�Ԃ̂݁A�����˃��[�U�[�ȊO�j
		if (laser[i].Counter < 200 && !laser[i].isReflected)  // 200�t���[���i��3.3�b�j�ȓ��̂ݒǔ��A���˃��[�U�[�͒ǔ����Ȃ�
		{
			// ���݂̃v���C���[�����ւ̊p�x���v�Z
			double targetAngle = atan2(pPos.y - laser[i].y, pPos.x - laser[i].x);
			// ���[�U�[�̌��݂̈ړ������̊p�x
			double currentAngle = atan2(laser[i].sy, laser[i].sx);
			// �p�x�̍������v�Z
			double angleDiff = targetAngle - currentAngle;

			// �p�x������-PI�`PI�͈̔͂ɐ��K��
			while (angleDiff > M_PI) angleDiff -= 2 * M_PI;
			while (angleDiff < -M_PI) angleDiff += 2 * M_PI;

			// �ő����p�x�𐧌��i1�t���[����15�x�܂Łj
			const double maxTurn = M_PI / 180 * 15;
			if (angleDiff > maxTurn) angleDiff = maxTurn;
			if (angleDiff < -maxTurn) angleDiff = -maxTurn;

			// �V�����p�x���v�Z���đ��x���X�V
			double newAngle = currentAngle + angleDiff;
			laser[i].sx += (int)(cos(newAngle) * 30);  // X�������x���X�V
			laser[i].sy += (int)(sin(newAngle) * 30);  // Y�������x���X�V
		}

		// ���[�U�[�̌o�ߎ��ԃJ�E���^�𑝉�
		laser[i].Counter += (data->isSlow) ? (float)SLOW_MODE_SPEED : 1;

		// �ړ��O�̍��W��ۑ�
		befPos = { laser[i].x, laser[i].y };

		// �~�T�C���̑��x
		double speed = OBSTACLE4_LASER_SPEED;
		if (data->isSlow) { speed /= SLOW_MODE_SPEED; }

		// ���[�U�[�̈ʒu���X�V�i���x�Ɋ�Â��Ĉړ��j
		laser[i].x = (laser[i].x * speed + laser[i].sx) / speed;
		laser[i].y = (laser[i].y * speed + laser[i].sy) / speed;

		DrawCircle(laser[i].x, laser[i].y, 8, 0xFF00FF); //debug.

		// ���[�U�[�̋O��(���C��)�𐶐�
		for (int j = 0; j < OBSTACLE4_LINE_MAX; j++)
		{
			if (line[j].ValidFlag == 0)  // ���g�p�̋O�ՃX���b�g��T��
			{
				// �O�Ճf�[�^�̐ݒ�
				line[j].x1 = befPos.x;     // �J�n�_X���W
				line[j].y1 = befPos.y;     // �J�n�_Y���W
				line[j].x2 = laser[i].x;   // �I���_X���W
				line[j].y2 = laser[i].y;   // �I���_Y���W
				line[j].Counter = 0;       // �o�ߎ��ԃJ�E���^������
				line[j].ValidFlag = 1;     // �O�Ղ�L����
				break;
			}
		}

		// ��ʊO�ɏo�����[�U�[�𖳌���
		if (laser[i].x < -100 || laser[i].x > WINDOW_WID + 100 ||
			laser[i].y < -100 || laser[i].y > WINDOW_HEI + 100)
		{
			laser[i].ValidFlag = 0;
		}
	}

	// �C��̈ړ��ƃ��[�U�[���ˏ���
	{
		Move(); //�ړ�����.
           
		// ���˃J�E���^������
		Hsc -= (data->isSlow) ? (float)SLOW_MODE_SPEED : 1;
		// �^�C�~���O�������烌�[�U�[����
		if (Hsc <= HscTm)
		{
			// ���g�p�̃��[�U�[�X���b�g��T���ă��[�U�[�𔭎�
			for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
			{
				if (laser[i].ValidFlag == 0)  // ���g�p�̃��[�U�[�X���b�g��������
				{
					// ���ˈʒu�i�C��̏���������j
					double startX = Hx;
					double startY = Hy;

					// �v���C���[�����ւ̏����p�x�v�Z
					double angle = atan2(pPos.y - startY, pPos.x - startX);

					// ���[�U�[�f�[�^�̏�����
					laser[i].x = startX;			// ����X���W
					laser[i].y = startY;			// ����Y���W
					laser[i].sx = cos(angle) * 30;	// X�����������x
					laser[i].sy = sin(angle) * 30;	// Y�����������x
					laser[i].Counter = 0;			// �o�ߎ��ԃJ�E���^������
					laser[i].LogNum = 0;			// �O�ՃJ�E���^������
					laser[i].ValidFlag = 1;			// ���[�U�[��L����
					laser[i].isReflected = FALSE;	// �ʏ탌�[�U�[�͔��˃t���O��FALSE�ɐݒ�
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

//BOOL Obstacle4main::HandleLaserHit(int laserIndex)
//{
//	DrawString(0, 440, _T("HandleLaserHit�֐����Ă΂�܂����B: %d\n", laserIndex), 0xFFFFFF);
//	//���˃��[�h���`�F�b�N.
//	if (!player->IsReflectionMode())
//	{
//		DrawString(0, 430, _T("�v���C���[�����˃��[�h�ł͂���܂���\n"), 0xFFFFFF);
//		return FALSE;//���˂��Ȃ�.
//	}
//
//	DrawString(0, 450, _T("���ˏ������J�n���܂��B���[�U�[�ʒu:(%.2f, %.2f) ���x:(%.2f, %.2f)\n",
//		laser[laserIndex].x, laser[laserIndex].y, laser[laserIndex].sx, laser[laserIndex].sy), 0xFFFFFF);
//
//	CreateReflectedLasers(
//		laser[laserIndex].x,
//		laser[laserIndex].y,
//		laser[laserIndex].sx,
//		laser[laserIndex].sy
//	);
//
//	//�v���C���[�̃N�[���_�E����ݒ�.
//	player->UseReflection();
//
//
//	//���̃��[�U�[�𖳌���.
//	laser[laserIndex].ValidFlag = 0;
//
//	return TRUE;//���ˏ�������.
//}

void Obstacle4main::CreateReflectedLasers(double reflectX, double reflectY, int originalSx, int originalSy)
{
	//8�����Ɋg�U���郌�[�U�[�𐶐�.
	const int numReflectedLasers = 8;
	const double angleStep = 2 * M_PI / numReflectedLasers;

	//���̃��[�U�[�̑��x����ɔ��˃��[�U�[�̊�{���x���v�Z
	double baseSpeed = sqrt(originalSx * originalSx + originalSy * originalSy) * 0.8;
	if (baseSpeed < 20)
	{
		baseSpeed = 30;
	}

	int createdCount = 0;
	//8�������[�v.
	for (int dir = 0; dir < numReflectedLasers && createdCount < numReflectedLasers; dir++)
	{
		// ���g�p�̃��[�U�[�X���b�g��T��
		bool foundSlot = false;
		for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
		{
			if (laser[i].ValidFlag == 0)
			{
				//printfDx(_T("���˃��[�U�[����: ����%d\n"), dir);
				double angle = dir * angleStep;

				laser[i].x = player->GetPos().x;
				laser[i].y = player->GetPos().y;
				laser[i].sx = cos(angle) * baseSpeed;
				laser[i].sy = sin(angle) * baseSpeed;
				laser[i].Counter = 300;  // �N�[���^�C���𖳌����i�ǔ����Ȃ��悤�ɑ傫�Ȓl��ݒ�j
				laser[i].LogNum = 0;
				laser[i].ValidFlag = 1;
				laser[i].isReflected = TRUE;

				createdCount++;
				foundSlot = true;
				break;  // 1�̃��[�U�[���쐬�����玟�̕�����
			}
		}
		if (!foundSlot) {
			printfDx(_T("���[�U�[�X���b�g��������܂���\n"));
		}
	}

	//printfDx(_T("���˃��[�U�[��������: %d�쐬\n"), createdCount);
}

#endif