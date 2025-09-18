/*
   - LaserManager.cpp -
   ���XObstacle4main�Ƃ��Ă܂Ƃ߂��Ă����[�U�[.
*/
#include "Player.h"
#include "GameManager.h"
#include "Obst_MeteorManager.h"

#include "LaserManager.h"

using namespace Calc; //�v�Z�@�\���g�p.

//������.
void LaserManager::Init() {

	//���̎擾.
	p_data      = GameData::GetPtr();
	p_player    = Player::GetPtr();
	p_meteorMng = MeteorManager::GetPtr();
	p_effectMng = EffectManager::GetPtr();
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
		int x = 0 + 8 * (i % 200);
		int y = 100 + 16 * (i / 200);
		DrawString(0, 80, _T("���[�U�[���Ղ�active"), 0xFF00FF);
		DrawFormatString(x, y, 0xFF00FF, _T("%d"), line[i].ValidFlag);
	}
#endif

	// ���[�U�[�̋O�Ղ̕`�揈��.
	for (int i = 0; i < LASER_LINE_CNT_MAX; i++)
	{
		if (line[i].ValidFlag == 0) continue;  // �����ȋO�Ղ̓X�L�b�v

		//���Ԍo�߂ŏ��X�ɔ�������.
		int clr = _int_r(255 - line[i].Counter * 4);
		clr = max(clr, 0); //�Œ�l��0�ɂ���.

		//���Z�������[�h�ŋO�Ղ�`��i�����G�t�F�N�g�j
		SetDrawBlendMode(DX_BLENDMODE_ADD, clr);

		//�O�Ղ̐��ݒ�.
		Line tmpLine = { {line[i].x2, line[i].y2}, {line[i].x1, line[i].y1}, {} };
		//���̐F(���Ԍo�߂ŐF���ω�)
		switch (line[i].type)
		{
			case Laser_Normal:       tmpLine.color = GetColor(50, clr, 255);        break;
			case Laser_Straight:     tmpLine.color = GetColor(50, clr, 255);        break;
			case Laser_Reflect:      tmpLine.color = GetColor(clr/2+128, 0, 255);   break;
			case Laser_SuperReflect: tmpLine.color = GetColor(clr/2+128, 0, 255);   break;
			case Laser_Falling:      tmpLine.color = GetColor(50, clr, 255);        break;

			default: assert(FALSE); break;
		}

		DrawLineST(&tmpLine, true); //�`��.
	}

	//�ʏ�̕`�惂�[�h�ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

//�e���[�U�[�̍X�V.
void LaserManager::UpdateLaser() {

	//	const double pSizeHalf = PLAYER_SIZE / 2.0;  // �v���C���[�̓����蔻��T�C�Y�̔���

		//�e���[�U�[�̍X�V.
	for (int i = 0; i < LASER_CNT_MAX; i++)
	{
		if (laser[i].ValidFlag == 0) continue;  // �����ȃ��[�U�[�̓X�L�b�v

		//�v���C���[�����蔻��.
		Circle plyHit = p_player->GetHit();

		//���[�U�[�^�C�v��.
		switch (laser[i].type)
		{
		case Laser_Normal:
		{
			Line line = { {laser[i].x, laser[i].y}, {laser[i].bx, laser[i].by}, {} }; //���[�U�[�̓����蔻��.
			// �v���C���[�ƃ��[�U�[�̓����蔻��
			if (HitLineCir(&line, &plyHit)) {

				//���˂���.
				if (p_player->GetMode() == Player_Reflect)
				{
					laser[i].type = Laser_Reflect; //���˃��[�h��.
					laser[i].Counter = 0;          //���Z�b�g.
					ReflectLaser(i);               //���[�U�[�𔽎�.
				}
				//���˂���(������)
				else if (p_player->GetMode() == Player_SuperReflect)
				{
					laser[i].type = Laser_SuperReflect; //���˃��[�h��.
					laser[i].Counter = 0;               //���Z�b�g.
					ReflectLaser(i);                    //���[�U�[�𔽎�.		
				}
				//���˂Ȃ�.
				else
				{
					DeleteLaser(i);
					p_player->PlayerDeath(); //�v���C���[���S.
				}
			}
			else {
				//���x(���Ԍo�߂ő����Ȃ�)
				double speed = laser[i].Counter * LASER_NOR_SPEED * (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
				//���[�U�[�̈ړ�.
				laser[i].x += laser[i].vx * speed;
				laser[i].y += laser[i].vy * speed;
			}
		}
		break;

		case Laser_Straight:
		{
			Line line = { {laser[i].x, laser[i].y}, {laser[i].bx, laser[i].by}, {} }; //���[�U�[�̓����蔻��.
			// �v���C���[�ƃ��[�U�[�̓����蔻��
			if (HitLineCir(&line, &plyHit)) {

				//���˂���.
				if (p_player->GetMode() == Player_Reflect)
				{
					laser[i].type = Laser_Reflect; //���˃��[�h��.
					laser[i].Counter = 0;          //���Z�b�g.
					ReflectLaser(i);               //���[�U�[�𔽎�.
				}
				//���˂���(������)
				else if (p_player->GetMode() == Player_SuperReflect)
				{
					laser[i].type = Laser_SuperReflect; //���˃��[�h��.
					laser[i].Counter = 0;               //���Z�b�g.
					ReflectLaser(i);                    //���[�U�[�𔽎�.		
				}
				//���˂Ȃ�.
				else
				{
					DeleteLaser(i);
					p_player->PlayerDeath(); //�v���C���[���S.
				}
			}
			else {
				//���x(�������[�U�[�Ȃ̂ň�葬�x)
				double speed = LASER_STR_SPEED * ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
				//���[�U�[�̈ړ�.
				laser[i].x += laser[i].vx * speed;
				laser[i].y += laser[i].vy * speed;
			}

		}
		break;

		case Laser_Falling:
		{
			Line line = { {laser[i].x, laser[i].y}, {laser[i].bx, laser[i].by}, {} }; //���[�U�[�̓����蔻��.
			// �v���C���[�ƃ��[�U�[�̓����蔻��
			if (HitLineCir(&line, &plyHit)) {

				//���˂���.
				if (p_player->GetMode() == Player_Reflect)
				{
					laser[i].type = Laser_Reflect; //���˃��[�h��.
					laser[i].Counter = 0;          //���Z�b�g.
					ReflectLaser(i);               //���[�U�[�𔽎�.
				}
				//���˂���(������)
				else if (p_player->GetMode() == Player_SuperReflect)
				{
					laser[i].type = Laser_SuperReflect; //���˃��[�h��.
					laser[i].Counter = 0;               //���Z�b�g.
					ReflectLaser(i);                    //���[�U�[�𔽎�.		
				}
				//���˂Ȃ�.
				else
				{
					DeleteLaser(i);
					p_player->PlayerDeath(); //�v���C���[���S.
				}
			}
			else {
				// �d�͌��ʂ�K�p�i�������̉����x�j
				double gravity = 0.08 * ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
				laser[i].vy += gravity;

				// ��C��R���ʁi���������̑��x�����X�Ɍ����j
				double airResistance = 0.995;
				laser[i].vx *= airResistance;

				// ���x�����i�������x�������Ȃ肷���Ȃ��悤�Ɂj
				double maxSpeed = 8.0;
				if (laser[i].vy > maxSpeed) {
					laser[i].vy = maxSpeed;
				}

				// ���[�U�[�̈ړ�
				laser[i].x += laser[i].vx;
				laser[i].y += laser[i].vy;
			}
		}
		break;

		case Laser_Reflect:
		case Laser_SuperReflect:
		{
			//��莞�ԂŖڕW�n�_�����߂�.
			if (laser[i].Counter >= LASER_REF_TRACK_ST_TM) {

				assert(p_meteorMng != nullptr); //�|�C���^����łȂ����Ƃ��m�F.

				DBL_XY laserPos = { laser[i].x, laser[i].y }; //���[�U�[�̌��݈ʒu.
				DBL_XY meteoPos{ -1, -1 };

				//�ł��߂�覐΂̈ʒu���擾����.
				bool hasMeteo = p_meteorMng->GetMeteorPosNearest(laserPos, &meteoPos);
				//覐΂��������ꍇ.
				if (hasMeteo) {
					laser[i].goalPos = meteoPos; //�o�^.
					laser[i].isGoGoal = true;
				}
			}

			Circle hit = { {laser[i].x, laser[i].y}, 10, {} }; //�����蔻��~(��)

			//覐΂Ɠ������Ă���Ȃ�.
			if (p_meteorMng->IsHitMeteors(hit, true)) {

				double dig = _deg(atan2(laser[i].vy, laser[i].vx)); //���݂̃��[�U�[�p�x.

				//�G�t�F�N�g���������o��.
				for (int j = 0; j < METEOR_BREAK_ANIM_CNT; j++) {

					double newDig = dig + (float)RandNum(-300, 300)/10; //�����p�x�����炷.

					EffectData data{};
					data.type  = Effect_BreakMeteo;
					data.pos   = { laser[i].x, laser[i].y };
					data.vec   = CalcVectorDeg(newDig);      //���炵���p�x�𔽉f.
					data.speed = (float)RandNum(20, 100)/10; //���x���I.
					data.len   = (float)RandNum(10, 150)/10; //�������I.
					data.ang   = (float)RandNum(0, 3599)/10; //�p�x���I.
					//�G�t�F�N�g����.
					p_effectMng->SpawnEffect(&data);
				}

				//�ǂ����̃^�C�v���Ő؂�ւ�.
				if (laser[i].type == Laser_Reflect) {
					DeleteLaser(i);  //����.
				}
				else {
					laser[i].Counter = LASER_REF_TRACK_ED_TM; //�Ĕ��ˌ�͒ǔ����Ȃ�.
					ReflectLaser(i); //�Ĕ���.
				}
			}
			else {
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
		default: assert(false); break;
		}

		//�O��`�悵���ʒu����̋���.
		DBL_XY pos1 = { laser[i].x,  laser[i].y };
		DBL_XY pos2 = { laser[i].bx, laser[i].by };
		double dis = CalcDist(pos1, pos2);
		//���������ȏ゠��Ε`�悷��(DrawLineAA�̊֌W��)
		if (dis >= LASER_LINE_DRAW_LEN) {
			//���[�U�[�̋O�Ղ𐶐�.
			for (int j = 0; j < LASER_LINE_CNT_MAX; j++)
			{
				if (line[j].ValidFlag == 0)  //���g�p�̋O�ՃX���b�g��T��.
				{
					// �O�Ճf�[�^�̐ݒ�
					line[j].x1 = laser[i].bx;	  //�J�n�_X���W.
					line[j].y1 = laser[i].by;	  //�J�n�_Y���W.
					line[j].x2 = laser[i].x;	  //�I���_X���W.
					line[j].y2 = laser[i].y;	  //�I���_Y���W.
					line[j].Counter = 0;		  //�o�ߎ��ԃJ�E���^������.
					line[j].ValidFlag = 1;		  //�O�Ղ�L����.
					line[j].type = laser[i].type; //���[�U�[�̃^�C�v�ɍ��킹��.
					break;
				}
			}
			//���W���L�^.
			laser[i].bx = laser[i].x;
			laser[i].by = laser[i].y;
		}

		//��ʊO����.
		int _x = (laser[i].x < -100) || (laser[i].x > WINDOW_WID + 100);
		int _y = (laser[i].y < -100) || (laser[i].y > WINDOW_HEI + 100);
		//��ʊO�ɏo�����[�U�[�𖳌���.
		if (_x || _y)
		{
			DeleteLaser(i);
		}

		// ���[�U�[�̌o�ߎ��ԃJ�E���^�𑝉�
		laser[i].Counter += (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
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
bool LaserManager::SpawnLaser(DBL_XY pos, DBL_XY vel, LaserType type) {

	// ���g�p�̃��[�U�[�X���b�g��T���ă��[�U�[�𔭎�
	for (int i = 0; i < LASER_CNT_MAX; i++)
	{
		if (laser[i].ValidFlag == 0)  // ���g�p�̃��[�U�[�X���b�g��T��
		{
			// ���[�U�[�f�[�^�̏�����
			laser[i].x = pos.x;	// �������Wx
			laser[i].y = pos.y;    // �������Wy
			laser[i].bx = pos.x;    // �������Wy
			laser[i].by = pos.y;    // �������Wy
			laser[i].vx = vel.x;    // ��������x
			laser[i].vy = vel.y;    // ��������y
			laser[i].Counter = 0;	// �o�ߎ��ԃJ�E���^������
			laser[i].LogNum = 0;	// �O�ՃJ�E���^������
			laser[i].ValidFlag = 1;	// ���[�U�[��L����
			laser[i].type = type;   // �^�C�v�̓o�^

			//�T�E���h.
			SoundMng* sound = SoundMng::GetPtr();
			if (type == Laser_Normal) {
				sound->Play(_T("Laser1"), false, 58); //�ʏ탌�[�U�[.
			}
			if (type == Laser_Straight) {
				sound->Play(_T("Laser2"), false, 60); //�������[�U�[.
			}
			if (type == Laser_Falling) {
				sound->Play(_T("Laser1"), false, 45); //�������[�U�[�i�������ʏ����߁j.
			}

			return true; //��������.
		}
	}
	return false; //�������s.
}
//���[�U�[����.
void LaserManager::DeleteLaser(int idx) {

	laser[idx].type = Laser_Normal; //�m�[�}�����[�h�ɖ߂�.
	laser[idx].goalPos = { 0, 0 };    //�ڕW�n�_���Z�b�g.
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
	double ang = _deg(atan2(laser[idx].vy, laser[idx].vx));
	//�p�x���t������(�������������_���ł����)
	ang += 180 + (float)RandNum(-200, 200)/10;
	//�p�x���f.
	laser[idx].vx = cos(_rad(ang));
	laser[idx].vy = sin(_rad(ang));

	//�G�t�F�N�g.
	EffectData data{};
	data.type = Effect_ReflectLaser;
	data.pos = { laser[idx].x, laser[idx].y };
	p_effectMng->SpawnEffect(&data);
	//�T�E���h.
	SoundMng* sound = SoundMng::GetPtr();
	sound->Play(_T("Laser3"), false, 58);
}

#if false
//���[�U�[(normal)��覐Βǔ�.
void LaserManager::LaserNorTracking(int idx)
{
	//��莞�Ԃ̂ݒǔ�.
	if (laser[idx].Counter < 200)  // 200�t���[���i��3.3�b�j�ȓ��̂ݒǔ�
	{
		double targetAngle = atan2(plyPos.y - laser[idx].y, plyPos.x - laser[idx].x); //�v���C���[�ւ̕���.
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
			if (HitCirCir(cir, &cir2)) {
				ReflectLaser(i); //���̏�Ŕ���.
			}
		}
	}
}