/*
   - Obstacle4main_od.cpp -

   ���[�U�[�̌p�����N���X (���c����)
   �v���C���[��ǔ����郌�[�U�[�𔭎˂����Q��������
   ���[�U�[���ˋ@�\�ǉ�
*/
#include "Player.h"    // �v���C���[�N���X�̃w�b�_�[�t�@�C��
#include "Obstacle4.h" // ���g�̃w�b�_�[�t�@�C��
#include "MeteoManager.h"//覐΂̂̃w�b�_�[�t�@�C��.

//���ꂪ��`����Ă���A�����炪ON.
#if defined ODAZIMA_LASER

/**
 * @brief ��Q���̍X�V����
 * �v���C���[���L���ȏꍇ�̂ݏ�Q���̓������X�V
 */
void Obstacle4main::Update()
{
	if (p_player->GetActive()) {  // �v���C���[���A�N�e�B�u�ȏꍇ�̂�
		enemy4Move();           // ��Q���̈ړ����������s
	}
}

/**
 * @brief ��Q���̕`�揈��
 * ���[�U�[�̋O�ՂƖC���`��
 */
void Obstacle4main::Draw()
{
	// ���[�U�[�̋O�Ղ̕`�揈��.
	DrawObstLine();

	// ���˃G�t�F�N�g�̏���.
	DrawObstFlash();

	// �����C���`��.
	//Box box = { {Hx, Hy}, {10, 10}, GetColor(100, 100, 100) }; //{pos}, {size}, color.
	//DrawBoxST(&box, TRUE, FALSE);
}

// ���[�U�[�̋O�Ղ̕`�揈��.
void Obstacle4main::DrawObstLine() {

	for (int i = 0; i < OBSTACLE4_LINE_MAX; i++)
	{
		if (line[i].ValidFlag == 0) continue;  // �����ȋO�Ղ̓X�L�b�v

		//���Ԍo�߂ŏ��X�ɔ�������.
		int g = _int(255 - line[i].Counter * 4);
		g = max(g, 0); //�Œ�l��0�ɂ���.

		// ���Z�������[�h�ŋO�Ղ�`��i�����G�t�F�N�g�j
//		SetDrawBlendMode(DX_BLENDMODE_ADD, g);
		SetDrawBlendModeST(MODE_ADD, g);

		// �O�Ղ̐���`��i���Ԍo�߂ŐF���ω��j
		Line tmpLine = { {line[i].x1, line[i].y1}, {line[i].x2, line[i].y2}, GetColor(50, g, 255) };
		DrawLineST(&tmpLine);

		// �o�ߎ��ԃJ�E���^����
		line[i].Counter += (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		// 64�t���[���o�߂�����O�Ղ𖳌���
		if (line[i].Counter >= 64) line[i].ValidFlag = 0;
	}

	//�ʏ�̕`�惂�[�h�ɖ߂�
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	ResetDrawBlendMode();
}

// ���˃G�t�F�N�g�̏���.
void Obstacle4main::DrawObstFlash() {

	for (int i = 0; i < OBSTACLE4_FLASH_MAX; i++)
	{
		if (flashEffect[i].ValidFlag == 0)
		{
			continue;//�����ȃG�t�F�N�g���X�L�b�v.
		}

		//�G�t�F�N�g�̓����x�����Ԃɉ����Čv�Z.
		float alpha = 1.0f - (
			flashEffect[i].Counter * OBSTACLE4_FLASH_ALPHA_TM / flashEffect[i].Duration
		);
		int alphaValue = _int(255 * alpha);
		alphaValue = max(alphaValue, 0); //������0.

		//�G�t�F�N�g�̃T�C�Y�����Ԃɉ����Ċg��.
		float sizeMultiplier = OBSTACLE4_FLASH_SIZE_INIT + (
			flashEffect[i].Counter * OBSTACLE4_FLASH_SIZE_SPREAD / flashEffect[i].Duration
		);
		int effectSize = _int(flashEffect[i].BaseSize * sizeMultiplier);
		int innerSize = effectSize / 2;

		//�O�p�`�̒��_���v�Z(�v���C���[�̕���������).
		double angle = flashEffect[i].angle;
		double cos_a = cos(angle);
		double sin_a = sin(angle);
		//�O���̎O�p�`(�傫��)
		int x1 = _int(flashEffect[i].x + cos_a * effectSize);//��[.
		int y1 = _int(flashEffect[i].y + sin_a * effectSize);
		int x2 = _int(flashEffect[i].x - cos_a * effectSize / 3 + sin_a * effectSize / 2);//����.
		int y2 = _int(flashEffect[i].y - sin_a * effectSize / 3 - cos_a * effectSize / 2);
		int x3 = _int(flashEffect[i].x - cos_a * effectSize / 3 - sin_a * effectSize / 2);//�E��.
		int y3 = _int(flashEffect[i].y - sin_a * effectSize / 3 + cos_a * effectSize / 2);
		//�����̎O�p�`(������)
		int ix1 = _int(flashEffect[i].x + cos_a * effectSize);//��[.
		int iy1 = _int(flashEffect[i].y + sin_a * effectSize);
		int ix2 = _int(flashEffect[i].x - cos_a * effectSize / 3 + sin_a * effectSize / 2);
		int iy2 = _int(flashEffect[i].y - sin_a * effectSize / 3 - cos_a * effectSize / 2);
		int ix3 = _int(flashEffect[i].x - cos_a * effectSize / 3 - sin_a * effectSize / 2);
		int iy3 = _int(flashEffect[i].y - sin_a * effectSize / 3 + cos_a * effectSize / 2);

		//���˃G�t�F�N�g���~�`�ŕ`��(��������)
//		SetDrawBlendMode(DX_BLENDMODE_ADD, alphaValue);
		SetDrawBlendModeST(MODE_ADD, alphaValue);

		//�O���̎O�p�`.
		DrawTriangle(x1, y1, x2, y2, x3, y3, GetColor(0, 255, 255), FALSE);

		//�����ɂ�薾�邢�O�p�`��`��.
		//DrawTriangle(ix1, iy1, ix2, iy2, ix3, iy3, GetColor(0, 255, 200), FALSE);


		//�G�t�F�N�g�̃J�E���^���X�V
		flashEffect[i].Counter += (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		//�G�t�F�N�g���Ԃ��I�������疳����
		if (flashEffect[i].Counter >= flashEffect[i].Duration)
		{
			flashEffect[i].ValidFlag = 0;
		}
	}

	//�ʏ�̕`�惂�[�h�ɖ߂�
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	ResetDrawBlendMode();
}

/**
 * @brief �G�i��Q���j�̈ړ�����
 * ���[�U�[�̈ړ��ƃv���C���[�ւ̒ǔ��A�C��̈ړ��ƃ��[�U�[���˂��Ǘ�
 */
void Obstacle4main::enemy4Move()
{
	pPos = p_player->GetPos();        // �v���C���[�̌��݈ʒu���擾
	const double pSizeHalf = PLAYER_SIZE / 2.0;  // �v���C���[�̓����蔻��T�C�Y�̔���

	// ���˃��[�h�����ǂ�������x��������
	bool isReflectionMode = p_player->IsReflectionMode();

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
					if (p_player->IsReflectionMode())
					{
						ReflectLaser(i, pPos);   //���[�U�[�𔽎�.
						p_player->UseReflection(); //�N�[���_�E���J�n.

					}
					//���˂Ȃ�.
					else
					{
						laser[i].ValidFlag = 0; //���[�U�[�𖳌���.
						p_player->PlayerDeath();  //�v���C���[���S.
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
		laser[i].Counter += (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);

		// �ړ��O�̍��W��ۑ�
		DBL_XY befPos;  // �O��ʒu��ۑ�����ϐ�
		befPos = { laser[i].x, laser[i].y };

		// �~�T�C���̑��x(���Ԍo�߂ő����Ȃ�)
		double speed = OBSTACLE4_LASER_SPEED / (laser[i].Counter * 0.01);
		if (p_data->isSlow) { speed /= SLOW_MODE_SPEED; }

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
		Hsc -= (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		// �^�C�~���O�������烌�[�U�[����
		if (Hsc <= HscTm)
		{
			// ���g�p�̃��[�U�[�X���b�g��T���ă��[�U�[�𔭎�
			for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
			{
				if (laser[i].ValidFlag == 0)  // ���g�p�̃��[�U�[�X���b�g��������
				{
					CreateFlashEffect(Hx,Hy);

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

//����effect�̐���.
void Obstacle4main::CreateFlashEffect(double fx, double fy)
{

	//���g�p�̃G�t�F�N�g�X���b�g��T��.
	for (int i = 0; i < OBSTACLE4_FLASH_MAX; i++)
	{
		if (flashEffect[i].ValidFlag == 0)
		{
			double dx = pPos.x - fx;
			double dy = pPos.y - fy;
			double angle = atan2(dy, dx);

			//�G�t�F�N�g�f�[�^�̐ݒ�.
			flashEffect[i].x = fx;
			flashEffect[i].y = fy;
			flashEffect[i].angle = angle; // �v���C���[�ւ̊p�x��ۑ�
			flashEffect[i].Counter = 0;
			flashEffect[i].Duration = OBSTACLE4_FLASH_VALID_TM; //���t���[������.
			flashEffect[i].BaseSize = 20; //��{�T�C�Y
			flashEffect[i].ValidFlag = 1;
			break;
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

#if 1
	// ���[�U�[�̌��ݑ��x(x, y)
	double nowSpeedX = laser[laserIndex].sx;
	double nowSpeedY = laser[laserIndex].sy;
	// ���x�x�N�g�����v�Z.
	double speedVector = sqrt(pow(nowSpeedX, 2) + pow(nowSpeedY,2)); //vector = ��(x*x + y*y)

	// ���ˌ�̑��x��ݒ�i���̑��x�̑傫����ێ��j
	// ���v���C���[����O�����̕����ɔ���.
	// �����˕��� = �v���C���[���烌�[�U�[�ւ̕����x�N�g��.
	laser[laserIndex].sx = -dx * speedVector;
	laser[laserIndex].sy = -dy * speedVector;
#else
	//���Ŕ��]���邾��.
	laser[laserIndex].sx *= -1;
	laser[laserIndex].sy *= -1;
#endif

	// ���ˌ�͒ǔ��𖳌����i�J�E���^���ő�l�ɐݒ�j
	laser[laserIndex].Counter = 200;

#if 1
	// ���[�U�[���v���C���[���班�����ꂽ�ʒu�Ɉړ��i�d�������蔻���h���j
	double pushDistance = PLAYER_SIZE / 2.0 + 5; // �v���C���[�T�C�Y�̔��� + �]�T
	laser[laserIndex].x = playerPos.x + -dx * pushDistance;
	laser[laserIndex].y = playerPos.y + -dy * pushDistance;
#endif

	laser[laserIndex].type = Laser_Reflected; //���˃��[�h��.
}

#endif;