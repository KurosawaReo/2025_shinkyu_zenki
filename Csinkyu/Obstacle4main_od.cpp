/*
   - Obstacle4main_od.cpp -

   ���[�U�[�̌p�����N���X (���c����)
   �v���C���[��ǔ����郌�[�U�[�𔭎˂����Q��������
   ���[�U�[���ˋ@�\�ǉ�
*/
#include "Player.h"    // �v���C���[�N���X�̃w�b�_�[�t�@�C��
#include "Obstacle4.h" // ���g�̃w�b�_�[�t�@�C��

//���ꂪ��`����Ă���A�����炪ON.
#if defined ODAZIMA_LASER

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

		//�ΐF�̒l, ���Ԍo�߂ŏ��X�ɔ�������.
		int g = _int(255 - line[i].Counter * 4);
		g = max(g, 0); //�Œ�l��0�ɂ���.

		// �O�Ղ̐���`��i���Ԍo�߂ŐF���ω��j
		Line tmpLine = { {line[i].x1, line[i].y1}, {line[i].x2, line[i].y2}, GetColor(50, g, 255) };
		DrawLineST(&tmpLine);

		// �o�ߎ��ԃJ�E���^����
		line[i].Counter += (data->isSlow) ? (float)SLOW_MODE_SPEED : 1;
		// 64�t���[���o�߂�����O�Ղ𖳌���
		if (line[i].Counter >= 64) line[i].ValidFlag = 0;
	}

	// �ʏ�̕`�惂�[�h�ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// �����C���`��
	//Box box = { {Hx, Hy}, {10, 10}, GetColor(100, 100, 100) }; //{pos}, {size}, color.
	//DrawBoxST(&box, TRUE, FALSE);
}

/**
 * @brief �G�i��Q���j�̈ړ�����
 * ���[�U�[�̈ړ��ƃv���C���[�ւ̒ǔ��A�C��̈ړ��ƃ��[�U�[���˂��Ǘ�
 */
void Obstacle4main::enemy4Move()
{
	const DBL_XY pPos = player->GetPos();        // �v���C���[�̌��݈ʒu���擾
	const double pSizeHalf = PLAYER_SIZE / 2.0;  // �v���C���[�̓����蔻��T�C�Y�̔���

	// ���˃��[�h�����ǂ�������x��������
	bool isReflectionMode = player->IsReflectionMode();

	// �e���[�U�[�̏���
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
	{
		if (laser[i].ValidFlag == 0) continue;  // �����ȃ��[�U�[�̓X�L�b�v

		bool isHit = false; //�e�������������ǂ���.
	
		//���[�U�[�^�C�v��.
		switch (laser[i].type) 
		{
			case Laser_Normal:
				// �v���C���[�ƃ��[�U�[�̓����蔻��
				if ((laser[i].x > pPos.x - pSizeHalf && laser[i].x < pPos.x + pSizeHalf) &&
					(laser[i].y > pPos.y - pSizeHalf && laser[i].y < pPos.y + pSizeHalf))
				{
					//���˂���.
					if (player->IsReflectionMode())
					{
						ReflectLaser(i, pPos);   //���[�U�[�𔽎�.
						player->UseReflection(); //�N�[���_�E���J�n.
					}
					//���˂Ȃ�.
					else
					{
						laser[i].ValidFlag = 0; //���[�U�[�𖳌���.
						player->PlayerDeath();  //�v���C���[���S.
					}
					isHit = true; //�����������Ƃ��L�^.
				}
				break;

			case Laser_Reflected:
				break;

			//�z��O�̒l�G���[.
			default: assert(FALSE); break;
		}

		//���������珈���I��.
		if (isHit) {
			continue;
		}

		// ���[�U�[�̒ǔ������i���ˌ��莞�Ԃ̂݁j
		if (laser[i].Counter < 200)  // 200�t���[���i��3.3�b�j�ȓ��̂ݒǔ�
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
		DBL_XY befPos;  // �O��ʒu��ۑ�����ϐ�
		befPos = { laser[i].x, laser[i].y };

		// �~�T�C���̑��x
		double speed = OBSTACLE4_LASER_SPEED;
		if (data->isSlow) { speed /= SLOW_MODE_SPEED; }

		// ���[�U�[�̈ʒu���X�V�i���x�Ɋ�Â��Ĉړ��j
		laser[i].x = (laser[i].x * speed + laser[i].sx) / speed;
		laser[i].y = (laser[i].y * speed + laser[i].sy) / speed;

		// ���[�U�[�̋O�Ղ𐶐�
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
			laser[i].type = Laser_Normal; //�m�[�}�����[�h�ɖ߂�.
		}
	}

	// �C��̈ړ��ƃ��[�U�[���ˏ���
	{
		//�ړ�����.
		Move();

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
					laser[i].sx = cos(angle) * 30;  // X�����������x
					laser[i].sy = sin(angle) * 30;  // Y�����������x
					laser[i].Counter = 0;			// �o�ߎ��ԃJ�E���^������
					laser[i].LogNum = 0;			// �O�ՃJ�E���^������
					laser[i].ValidFlag = 1;			// ���[�U�[��L����
					break;
				}
			}
			HscTm -= OBSTACLE4_SHOT_SPAN; //���˃^�C�~���O��ύX.
		}
		//0�b�����������������.
		if (Hsc <= 0) {
			Hsc = OBSTACLE4_SHOT_RESET;  // ���˃J�E���^�����Z�b�g�i���̔��˂܂ł̑ҋ@���ԁj
			HscTm = OBSTACLE4_SHOT_START;
		}
	}
}

/**
 * @brief ���[�U�[���ˏ���
 * �v���C���[�̈ʒu����Ƀ��[�U�[�̐i�s�����𔽓]������
 * @param laserIndex ���˂��郌�[�U�[�̃C���f�b�N�X
 * @param playerPos �v���C���[�̈ʒu
 */
void Obstacle4main::ReflectLaser(int laserIndex, DBL_XY playerPos)
{
	// ���[�U�[����v���C���[�ւ̃x�N�g�����v�Z
	double dx = playerPos.x - laser[laserIndex].x;
	double dy = playerPos.y - laser[laserIndex].y;

	// �x�N�g���̒������v�Z
	double length = sqrt(dx * dx + dy * dy);

	// ���K���i������1�ɂ���j
	if (length > 0)
	{
		dx /= length;
		dy /= length;
	}

	// ���[�U�[�̌��݂̑��x�x�N�g��
	double currentSpeedX = laser[laserIndex].sx;
	double currentSpeedY = laser[laserIndex].sy;

	// ���݂̑��x�̑傫�����v�Z
	double speedMagnitude = sqrt(currentSpeedX * currentSpeedX + currentSpeedY * currentSpeedY);

	// �v���C���[����O�����̕����ɔ���
	// ���˕��� = �v���C���[���烌�[�U�[�ւ̕����x�N�g��
	double reflectDx = -dx; // �v���C���[���痣������
	double reflectDy = -dy;

	// ���ˌ�̑��x��ݒ�i���̑��x�̑傫����ێ��j
	laser[laserIndex].sx = reflectDx * speedMagnitude;
	laser[laserIndex].sy = reflectDy * speedMagnitude;

	// ���ˌ�͒ǔ��𖳌����i�J�E���^���ő�l�ɐݒ�j
	laser[laserIndex].Counter = 200;

#if 1
	// ���[�U�[���v���C���[���班�����ꂽ�ʒu�Ɉړ��i�d�������蔻���h���j
	double pushDistance = PLAYER_SIZE / 2.0 + 5; // �v���C���[�T�C�Y�̔��� + �]�T
	laser[laserIndex].x = playerPos.x + reflectDx * pushDistance;
	laser[laserIndex].y = playerPos.y + reflectDy * pushDistance;
#endif

	laser[laserIndex].type = Laser_Reflected; //���˃��[�h��.
}

#endif