/*
   - LaserManager.cpp -
   ���XObstacle4main�Ƃ��Ă܂Ƃ߂��Ă����[�U�[.
*/
#include "Player.h"
#include "MeteoManager.h"

#include "LaserManager.h"

void LaserManager::Init(GameData* _data, Player* _player, MeteoManager* _meteoMng) {
	//���̎擾.
	p_data     = _data;
	p_player   = _player;
	p_meteoMng = _meteoMng;
}
void LaserManager::Reset() {

	//���[�U�[�f�[�^�̏�����.
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++) {
		laser[i].ValidFlag = 0; //���ׂẴ��[�U�[�𖳌���Ԃ�.
	}
	//���[�U�[�̋O�Ճf�[�^�̏�����.
	for (int i = 0; i < OBSTACLE4_LINE_MAX; i++) {
		line[i].ValidFlag = 0;  //���ׂĂ̋O�Ղ𖳌���Ԃ�.
	}
}
void LaserManager::Update() {

	DBL_XY plyPos = p_player->GetPos();        // �v���C���[�̌��݈ʒu���擾
	const double pSizeHalf = PLAYER_SIZE/2.0;  // �v���C���[�̓����蔻��T�C�Y�̔���

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
				if ((laser[i].x > plyPos.x - pSizeHalf && laser[i].x < plyPos.x + pSizeHalf) &&
					(laser[i].y > plyPos.y - pSizeHalf && laser[i].y < plyPos.y + pSizeHalf))
				{
					//���˂���.
					if (p_player->IsReflectionMode())
					{
						ReflectLaser(i);           //���[�U�[�𔽎�.
						p_player->UseReflection(); //�N�[���_�E���J�n.			
					}
					//���˂Ȃ�.
					else
					{
						DeleteLaser(i);
						p_player->PlayerDeath(); //�v���C���[���S.
					}
					isHit = true; //�����������Ƃ��L�^.
				}
				break;

			case Laser_Reflected:
			{
				// ���˂������[�U�[��覐Βǔ��������s��
				ReflectedLaserTracking(i);
			
				/*
				   �y���zTODO: ���[�U�[�̉~�`�����蔻��.
				*/
				Circle hit = { {laser[i].x, laser[i].y}, 10, {} };

				//覐΂Ɠ������Ă���Ȃ�.
				if (p_meteoMng->IsHitMeteos(&hit)) {
					DeleteLaser(i);
				}
			}
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
			double targetAngle = atan2(plyPos.y - laser[i].y, plyPos.x - laser[i].x);
			// ���[�U�[�̌��݂̈ړ������̊p�x
			double currentAngle = atan2(laser[i].sy, laser[i].sx);
			// �p�x�̍������v�Z
			double angleDiff = targetAngle - currentAngle;

			// �p�x������-PI�`PI�͈̔͂ɐ��K��
			while (angleDiff > M_PI) angleDiff -= 2 * M_PI;
			while (angleDiff < -M_PI) angleDiff += 2 * M_PI;

			// �ő����p�x�𐧌��i1�t���[����n�x�܂Łj
			const double maxTurn = M_PI / 180 * OBSTACLE4_ROT_LIMIT;
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
				line[j].x1 = befPos.x;		  // �J�n�_X���W
				line[j].y1 = befPos.y;		  // �J�n�_Y���W
				line[j].x2 = laser[i].x;	  // �I���_X���W
				line[j].y2 = laser[i].y;	  // �I���_Y���W
				line[j].Counter = 0;		  // �o�ߎ��ԃJ�E���^������
				line[j].ValidFlag = 1;		  // �O�Ղ�L����
				line[j].type = laser[i].type; //���[�U�[�̃^�C�v�ɍ��킹��.
				break;
			}
		}

		// ��ʊO�ɏo�����[�U�[�𖳌���
		if (laser[i].x < -100 || laser[i].x > WINDOW_WID + 100 ||
			laser[i].y < -100 || laser[i].y > WINDOW_HEI + 100)
		{
			DeleteLaser(i);
		}
	}
}
void LaserManager::Draw() {

#if defined DEBUG_LASER_ACTIVE
//�f�o�b�O�\��.
	for (int i = 0; i < OBSTACLE4_LINE_MAX; i++)
	{
		int x =   0 +  8 * (i%200);
		int y = 100 + 16 * (i/200);
		DrawString(0, 80, _T("���[�U�[���Ղ�active"), 0xFF00FF);
		DrawFormatString(x, y, 0xFF00FF, _T("%d"), line[i].ValidFlag);
	}
#endif

	// ���[�U�[�̋O�Ղ̕`�揈��.
	for (int i = 0; i < OBSTACLE4_LINE_MAX; i++)
	{
		if (line[i].ValidFlag == 0) continue;  // �����ȋO�Ղ̓X�L�b�v

		//���Ԍo�߂ŏ��X�ɔ�������.
		int clr = _int(255 - line[i].Counter * 4);
		clr = max(clr, 0); //�Œ�l��0�ɂ���.

		//���Z�������[�h�ŋO�Ղ�`��i�����G�t�F�N�g�j
		SetDrawBlendMode(DX_BLENDMODE_ADD, clr);

		//�O�Ղ̐��ݒ�.
		Line tmpLine = { {line[i].x1, line[i].y1}, {line[i].x2, line[i].y2}, {} };
		//���̐F(���Ԍo�߂ŐF���ω�)
		switch (line[i].type)
		{
			case Laser_Normal:    tmpLine.clr = GetColor(50, clr, 255); break;
			case Laser_Reflected: tmpLine.clr = GetColor(clr, 0, clr); break;

			default: assert(FALSE); break;
		}
		DrawLineST(&tmpLine); //�`��.

		// �o�ߎ��ԃJ�E���^����
		line[i].Counter += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;
		// 64�t���[���o�߂�����O�Ղ𖳌���
		if (line[i].Counter >= 64) line[i].ValidFlag = 0;
	}

	//�ʏ�̕`�惂�[�h�ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

//���[�U�[����.
BOOL LaserManager::SpawnLaser(float x, float y) {

	DBL_XY plyPos = p_player->GetPos(); //�v���C���[�̌��݈ʒu���擾.

	// ���g�p�̃��[�U�[�X���b�g��T���ă��[�U�[�𔭎�
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
	{
		if (laser[i].ValidFlag == 0)  // ���g�p�̃��[�U�[�X���b�g��������
		{
			// ���ˈʒu�i�C��̏���������j
			double startX = x;
			double startY = y;
			// �v���C���[�����ւ̏����p�x�v�Z
			double angle = atan2(plyPos.y - startY, plyPos.x - startX);

			// ���[�U�[�f�[�^�̏�����
			laser[i].x = startX;			// ����X���W
			laser[i].y = startY;			// ����Y���W
			laser[i].sx = cos(angle) * 30;  // X�����������x
			laser[i].sy = sin(angle) * 30;  // Y�����������x
			laser[i].Counter = 0;			// �o�ߎ��ԃJ�E���^������
			laser[i].LogNum = 0;			// �O�ՃJ�E���^������
			laser[i].ValidFlag = 1;			// ���[�U�[��L����
			
			return TRUE; //��������.
		}
	}
	return FALSE; //�������s.
}
//���[�U�[����.
void LaserManager::DeleteLaser(int idx) {

	laser[idx].ValidFlag = 0;       //�����ɂ���.
	laser[idx].type = Laser_Normal; //�m�[�}�����[�h�ɖ߂�.
}
//���[�U�[����.
void LaserManager::ReflectLaser(int idx)
{
	DBL_XY plyPos = p_player->GetPos(); //�v���C���[�̌��݈ʒu���擾.

	// ���[�U�[����v���C���[�ւ̃x�N�g�����v�Z
	double dx = plyPos.x - laser[idx].x;
	double dy = plyPos.y - laser[idx].y;

	// �x�N�g���̒������v�Z
	double length = sqrt(dx * dx + dy * dy);

	// ���K���i������1�ɂ���j
	if (length > 0)
	{
		dx /= length;
		dy /= length;
	}

	// ���[�U�[�̌��ݑ��x(x, y)
	double nowSpeedX = laser[idx].sx;
	double nowSpeedY = laser[idx].sy;
	// ���x�x�N�g�����v�Z.
	double speedVector = sqrt(pow(nowSpeedX, 2) + pow(nowSpeedY, 2)); //vector = ��(x*x + y*y)

	// ���ˌ�̑��x��ݒ�i���̑��x�̑傫����ێ��j
	// ���v���C���[����O�����̕����ɔ���.
	// �����˕��� = �v���C���[���烌�[�U�[�ւ̕����x�N�g��.
	laser[idx].sx = -dx * speedVector;
	laser[idx].sy = -dy * speedVector;

	// ���ˌ�͒ǔ��𖳌����i�J�E���^���ő�l�ɐݒ�j
	laser[idx].Counter = 200;

	// ���[�U�[���v���C���[���班�����ꂽ�ʒu�Ɉړ��i�d�������蔻���h���j
	double pushDistance = PLAYER_SIZE / 2.0 + 5; // �v���C���[�T�C�Y�̔��� + �]�T
	laser[idx].x = plyPos.x + -dx * pushDistance;
	laser[idx].y = plyPos.y + -dy * pushDistance;

	laser[idx].type = Laser_Reflected; //���˃��[�h��.
}

//���˃��[�U�[��覐Βǔ�.
//idx: �������郌�[�U�[�̃C���f�b�N�X.
void LaserManager::ReflectedLaserTracking(int idx)
{
	//���[�U�[�̌��݈ʒu.
	DBL_XY laserPos = { laser[idx].x, laser[idx].y };

	assert(p_meteoMng != nullptr); //�|�C���^����łȂ����Ƃ��m�F.

	//�ł��߂�覐΂̈ʒu���擾���邺.
	DBL_XY nearestMeteoPos{};
	bool hasMeteo = p_meteoMng->GetMeteoPosNearest(laserPos, &nearestMeteoPos);

	//覐΂�1�ł����݂����.
	if (hasMeteo)
	{
		//覐΂����݂���ꍇ��覐΂Ɍ������Ēǔ�����.
		//覐Ε����ւ̊p�x���v�Z(����ނ�����).
		double targetAngle = atan2(
			nearestMeteoPos.y - laser[idx].y,
			nearestMeteoPos.x - laser[idx].x);

		//���[�U�[�̌��݂̈ړ������̊p�x.
		double currentAngle = atan2(laser[idx].sy, laser[idx].sx);

		//�p�x�̍������v�Z.
		double angleDiff = targetAngle - currentAngle;

		// �p�x������-PI�`PI�͈̔͂ɐ��K��
		while (angleDiff > M_PI)
		{
			angleDiff -= 2 * M_PI;
		}
		while (angleDiff < -M_PI)
		{
			angleDiff += 2 * M_PI;
		}
		// ���˃��[�U�[�̐���p�x�i�ʏ탌�[�U�[��菭�������j
		const double maxTurn = M_PI / 180 * 20;//��\�x�܂�
		if (angleDiff > maxTurn)angleDiff = maxTurn;
		if (angleDiff < -maxTurn)angleDiff = -maxTurn;

		//�V�����p�x���v�Z���đ��x���X�V
		double newAngle = currentAngle + angleDiff;

		// ���݂̑��x�̑傫����ێ�
		double currentSpeed = sqrt(laser[idx].sx * laser[idx].sx +
			laser[idx].sy * laser[idx].sy);

		// �V���������ɑ��x��ݒ�
		laser[idx].sx = cos(newAngle) * currentSpeed;
		laser[idx].sy = sin(newAngle) * currentSpeed;
	}
}