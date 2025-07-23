/*
   - LaserManager.cpp -
   ���XObstacle4main�Ƃ��Ă܂Ƃ߂��Ă����[�U�[.
*/
#include "Player.h"
#include "MeteoManager.h"

#include "LaserManager.h"

//������.
void LaserManager::Init(GameData* _data, Player* _player, MeteoManager* _meteoMng, EffectManager* _effectMng) {
	
	//���̎擾.
	p_data      = _data;
	p_player    = _player;
	p_meteoMng  = _meteoMng; 
	p_effectMng = _effectMng;
}
//���Z�b�g.
void LaserManager::Reset() {

	//���[�U�[�f�[�^�̏�����.
	for (int i = 0; i < LASER_CNT_MAX; i++) {
		DeleteLaser(i); //�S�ď������Ă���.
	}
	//���[�U�[�̋O�Ճf�[�^�̏�����.
	for (int i = 0; i < LASER_LINE_CNT_MAX; i++) {
		line[i].ValidFlag = 0;  //���ׂĂ̋O�Ղ𖳌���Ԃ�.
	}
}
//�X�V.
void LaserManager::Update() {

	plyPos = p_player->GetPos(); //�v���C���[�̌��݈ʒu���擾.

	UpdateLaser();     //�e���[�U�[�̍X�V.
	UpdateLaserLine(); //�e���[�U�[�`����̍X�V.
}
//�`��.
void LaserManager::Draw() {

#if defined DEBUG_LASER_ACTIVE
	//�f�o�b�O�\��.
	for (int i = 0; i < LASER_LINE_CNT_MAX; i++)
	{
		int x =   0 +  8 * (i%200);
		int y = 100 + 16 * (i/200);
		DrawString(0, 80, _T("���[�U�[���Ղ�active"), 0xFF00FF);
		DrawFormatString(x, y, 0xFF00FF, _T("%d"), line[i].ValidFlag);
	}
#endif

	// ���[�U�[�̋O�Ղ̕`�揈��.
	for (int i = 0; i < LASER_LINE_CNT_MAX; i++)
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
			case Laser_Straight:  tmpLine.clr = GetColor(50, clr, 255); break;
			case Laser_Reflected: tmpLine.clr = GetColor(clr/2+128, 0, 255); break;

			default: assert(FALSE); break;
		}
		DrawLineST(&tmpLine); //�`��.
	}

	//�ʏ�̕`�惂�[�h�ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

//�e���[�U�[�̍X�V.
void LaserManager::UpdateLaser() {

	const double pSizeHalf = PLAYER_SIZE / 2.0;  // �v���C���[�̓����蔻��T�C�Y�̔���

	//�e���[�U�[�̍X�V.
	for (int i = 0; i < LASER_CNT_MAX; i++)
	{
		if (laser[i].ValidFlag == 0) continue;  // �����ȃ��[�U�[�̓X�L�b�v

		//�ړ��O�̍��W��ۑ�.
		DBL_XY befPos = { laser[i].x, laser[i].y };

		//���[�U�[�^�C�v��.
		switch (laser[i].type)
		{
			case Laser_Normal:
			{
				// �v���C���[�ƃ��[�U�[�̓����蔻��
				if ((laser[i].x > plyPos.x - pSizeHalf && laser[i].x < plyPos.x + pSizeHalf) &&
					(laser[i].y > plyPos.y - pSizeHalf && laser[i].y < plyPos.y + pSizeHalf))
				{
					//���˂���.
					if (p_player->IsReflectionMode())
					{
						ReflectLaser(i); //���[�U�[�𔽎�.		
					}
					//���˂Ȃ�.
					else
					{
						DeleteLaser(i);
						p_player->PlayerDeath(); //�v���C���[���S.
					}
				}
				else{
					//���x(���Ԍo�߂ő����Ȃ�)
					double speed = laser[i].Counter * LASER_NOR_SPEED * (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
					//���[�U�[�̈ړ�.
					laser[i].x += laser[i].vx * speed;
					laser[i].y += laser[i].vy * speed;
				
					//���[�U�[�̒ǔ�����.
					//LaserNorTracking(i);
				}
			}
			break;

			case Laser_Straight:
			{
				// �v���C���[�ƃ��[�U�[�̓����蔻��
				if ((laser[i].x > plyPos.x - pSizeHalf && laser[i].x < plyPos.x + pSizeHalf) &&
					(laser[i].y > plyPos.y - pSizeHalf && laser[i].y < plyPos.y + pSizeHalf))
				{
					//���˂���.
					if (p_player->IsReflectionMode())
					{
						ReflectLaser(i); //���[�U�[�𔽎�.		
					}
					//���˂Ȃ�.
					else
					{
						DeleteLaser(i);
						p_player->PlayerDeath(); //�v���C���[���S.
					}
				}
				else{
					//���x(�������[�U�[�Ȃ̂ň�葬�x)
					double speed = LASER_STR_SPEED * ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
					//���[�U�[�̈ړ�.
					laser[i].x += laser[i].vx * speed;
					laser[i].y += laser[i].vy * speed;
				}

			}
			break;

			case Laser_Reflected:
			{
				//��莞�ԂŖڕW�n�_�����߂�.
				if (laser[i].Counter >= LASER_REF_TRACK_ST_TM) {

					assert(p_meteoMng != nullptr); //�|�C���^����łȂ����Ƃ��m�F.

					DBL_XY laserPos = { laser[i].x, laser[i].y }; //���[�U�[�̌��݈ʒu.
					DBL_XY meteoPos{-1, -1};

					//�ł��߂�覐΂̈ʒu���擾����.
					bool hasMeteo = p_meteoMng->GetMeteoPosNearest(laserPos, &meteoPos);
					//覐΂��������ꍇ.
					if (hasMeteo) {
						laser[i].goalPos = meteoPos; //�o�^.
						laser[i].isGoGoal = true;
					}
				}

				Circle hit = { {laser[i].x, laser[i].y}, 10, {} }; //�����蔻��~(��)

				//覐΂Ɠ������Ă���Ȃ�.
				if (p_meteoMng->IsHitMeteos(&hit, TRUE)) {
					
					double dig = _dig(atan2(laser[i].vy, laser[i].vx)); //���݂̃��[�U�[�p�x.

					//�G�t�F�N�g���������o��.
					for(int j = 0; j < 8; j++){

						double newDig = dig + (float)RndNum(-400, 400)/10; //�����p�x�����炷.

						EffectData data{};
						data.type  = Effect_BreakMeteo;
						data.pos   = { laser[i].x, laser[i].y };
						data.vec   = CalcDigToPos(newDig);       //���炵���p�x�𔽉f.
						data.speed = (float)RndNum( 5,   40)/10; //���x���I.
						data.len   = (float)RndNum(30,  180)/10; //�������I.
						data.ang   = (float)RndNum( 0, 3599)/10; //�p�x���I.
						//�G�t�F�N�g����.
						p_effectMng->SpawnEffect(&data);
					}
					//����.
					DeleteLaser(i);
				}
				else{
					//���[�U�[�̒ǔ�����.
					LaserRefTracking(i);

					//���x(���Ԍo�߂ő����Ȃ�)
					double speed = laser[i].Counter * LASER_REF_SPEED * (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
					//���[�U�[�̈ړ�.
					laser[i].x += laser[i].vx * speed;
					laser[i].y += laser[i].vy * speed;
				}
			}
			break;

			//�z��O�̒l�G���[.
			default: assert(FALSE); break;
		}

		// ���[�U�[�̌o�ߎ��ԃJ�E���^�𑝉�
		laser[i].Counter += (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);

		// ���[�U�[�̋O�Ղ𐶐�
		for (int j = 0; j < LASER_LINE_CNT_MAX; j++)
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

		//��ʊO����.
		int _x = (laser[i].x < -100) || (laser[i].x > WINDOW_WID + 100);
		int _y = (laser[i].y < -100) || (laser[i].y > WINDOW_HEI + 100);
		//��ʊO�ɏo�����[�U�[�𖳌���.
		if (_x || _y)
		{
			DeleteLaser(i);
		}
	}
}
//�e���[�U�[�`����̍X�V.
void LaserManager::UpdateLaserLine() {

	for (int i = 0; i < LASER_LINE_CNT_MAX; i++) {

		// �o�ߎ��ԃJ�E���^����
		line[i].Counter += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;
		// 64�t���[���o�߂�����O�Ղ𖳌���
		if (line[i].Counter >= 64) line[i].ValidFlag = 0;
	}
}

//���[�U�[����.
BOOL LaserManager::SpawnLaser(DBL_XY pos, DBL_XY vel, LaserType type) {

	// ���g�p�̃��[�U�[�X���b�g��T���ă��[�U�[�𔭎�
	for (int i = 0; i < LASER_CNT_MAX; i++)
	{
		if (laser[i].ValidFlag == 0)  // ���g�p�̃��[�U�[�X���b�g��T��
		{
			// ���[�U�[�f�[�^�̏�����
			laser[i].x = pos.x;	    // �������Wx
			laser[i].y = pos.y;     // �������Wy
			laser[i].vx = vel.x;    // ��������x
			laser[i].vy = vel.y;    // ��������y
			laser[i].Counter = 0;	// �o�ߎ��ԃJ�E���^������
			laser[i].LogNum = 0;	// �O�ՃJ�E���^������
			laser[i].ValidFlag = 1;	// ���[�U�[��L����
			laser[i].type = type;   // �^�C�v�̓o�^

			//�T�E���h.
			SoundST* sound = SoundST::GetPtr();
			if (type == Laser_Normal){
				sound->Play(_T("Laser1"), FALSE, 58); //�ʏ탌�[�U�[.
			}
			if (type == Laser_Straight) {
				sound->Play(_T("Laser2"), FALSE, 60); //�������[�U�[.
			}

			return TRUE; //��������.
		}
	}
	return FALSE; //�������s.
}
//���[�U�[����.
void LaserManager::DeleteLaser(int idx) {

	laser[idx].type = Laser_Normal; //�m�[�}�����[�h�ɖ߂�.
	laser[idx].goalPos = {0, 0};    //�ڕW�n�_���Z�b�g.
	laser[idx].isGoGoal = false;    //�ڕW�n�_�Ȃ�.
	laser[idx].ValidFlag = 0;       //�����ɂ���.
}
//���[�U�[����.
void LaserManager::ReflectLaser(int idx)
{
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

	//���ˎ��̌��̊p�x.
	double ang = _dig(atan2(laser[idx].vy, laser[idx].vx));
	//�p�x���t������(�������������_���ł����)
	ang += 180 + (float)RndNum(-200, 200)/10;
	//�p�x���f.
	laser[idx].vx = cos(_rad(ang));
	laser[idx].vy = sin(_rad(ang));

	laser[idx].type    = Laser_Reflected; //���˃��[�h��.
	laser[idx].Counter = 0;               //�J�E���^�[�����Z�b�g.

	//�G�t�F�N�g.
	EffectData data{};
	data.type = Effect_ReflectLaser;
	data.pos = { laser[idx].x, laser[idx].y };
	p_effectMng->SpawnEffect(&data);
	//�T�E���h.
	SoundST* sound = SoundST::GetPtr();
	sound->Play(_T("Laser3"), FALSE, 58);
}

#if false
//���[�U�[(normal)��覐Βǔ�.
void LaserManager::LaserNorTracking(int idx) 
{
	//��莞�Ԃ̂ݒǔ�.
	if (laser[idx].Counter < 200)  // 200�t���[���i��3.3�b�j�ȓ��̂ݒǔ�
	{
		double targetAngle  = atan2(plyPos.y - laser[idx].y, plyPos.x - laser[idx].x); //�v���C���[�ւ̕���.
		double currentAngle = atan2(laser[idx].vy, laser[idx].vx);                     //�ړ�����.
		double angleDiff = targetAngle - currentAngle;                                 //�p�x�̍������v�Z.

		// �p�x������-PI�`PI�͈̔͂ɐ��K��
		while (angleDiff > +M_PI) angleDiff -= 2 * M_PI;
		while (angleDiff < -M_PI) angleDiff += 2 * M_PI;

		// �ő����p�x�𐧌��i1�t���[����n�x�܂Łj
		const double maxTurn = _rad(LASER_NOR_ROT_MAX) * (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		if (angleDiff > +maxTurn) angleDiff = +maxTurn;
		if (angleDiff < -maxTurn) angleDiff = -maxTurn;

		// �V�����p�x���v�Z.
		laser[idx].vx = cos(currentAngle + angleDiff);
		laser[idx].vy = sin(currentAngle + angleDiff);
	}
}
#endif
//���[�U�[(reflected)��覐Βǔ�.
void LaserManager::LaserRefTracking(int idx)
{
	//�ڕW�n�_�Ɍ������Ȃ�.
	if (laser[idx].isGoGoal) {
		//��莞�Ԃ̂ݒǔ�.
		if (laser[idx].Counter > LASER_REF_TRACK_ST_TM &&
		    laser[idx].Counter < LASER_REF_TRACK_ED_TM) 
		{
			//�ڕW�n�_�܂ł̍��W���ƕ��p.
			double targetAngle = atan2(laser[idx].goalPos.y - laser[idx].y, laser[idx].goalPos.x - laser[idx].x);
			//���[�U�[�̌��݂̈ړ������̊p�x.
			double currentAngle = atan2(laser[idx].vy, laser[idx].vx);
			//�p�x�̍������v�Z.
			double angleDiff = targetAngle - currentAngle;

			// �p�x������-PI�`PI�͈̔͂ɐ��K��.
			while (angleDiff > M_PI)
			{
				angleDiff -= 2 * M_PI;
			}
			while (angleDiff < -M_PI)
			{
				angleDiff += 2 * M_PI;
			}

			// ���˃��[�U�[�̐���p�x�i�ʏ탌�[�U�[��菭�������j.
			double maxTurn = _rad(LASER_REF_ROT_MAX) * (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
			if (angleDiff > +maxTurn) angleDiff = +maxTurn;
			if (angleDiff < -maxTurn) angleDiff = -maxTurn;

			//�V�����p�x���v�Z���đ��x���X�V
			double newAngle = currentAngle + angleDiff;

			// �������v�Z���Đݒ�.
			laser[idx].vx = cos(newAngle);
			laser[idx].vy = sin(newAngle);
		}
	}
}

//���[�U�[�̈ꊇ����.
void LaserManager::LaserReflectRange(Circle* cir) {
	
	for (int i = 0; i < LASER_CNT_MAX; i++) {
		//�L���ȃ��[�U�[.
		if (laser[i].ValidFlag) {

			Circle cir2 = { {laser[i].x, laser[i].y}, 1, {} };

			//�͈͓��Ȃ�.
			if (IsHitCircle(cir, &cir2)) {
				ReflectLaser(i); //���̏�Ŕ���.
			}
		}
	}
}