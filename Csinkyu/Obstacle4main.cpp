/*
   - Obstacle4main.cpp -

   ���[�U�[�C��̌p�����N���X.

   �v���C���[��ǔ����郌�[�U�[�𔭎˂����Q��������.
   ���[�U�[���ˋ@�\�ǉ�.
*/
#include "Player.h"    // �v���C���[�N���X�̃w�b�_�[�t�@�C��
#include "Obstacle4.h" // ���g�̃w�b�_�[�t�@�C��

//������.
void Obstacle4main::Init(GameData* _data, Player* _player, MeteoManager* _meteoMng, LaserManager* _laserMng)
{
	// �I�u�W�F�N�g���Q�ƂƂ��ĕۑ�
	p_data     = _data;
	p_player   = _player;
	p_meteoMng = _meteoMng;
	p_laserMng = _laserMng;
}
//���Z�b�g.
void Obstacle4main::Reset(float _Hx, float _Hy, float _Hm, MoveDir _moveDir)
{
	Hx      = _Hx;                      // �C���X���W�����l�i��ʒ����j
	Hy      = _Hy;                      // �C���Y���W�����l�i��ʏ㕔�j
	Hm      = _Hm;                      // �C��̈ړ����x
	Hsc     = OBSTACLE4_SHOT_START+100; // �C��̔��˃J�E���^�����l 
	HscTm   = OBSTACLE4_SHOT_START;     // �C��̔��˃^�C�~���O�����l
	moveDir = _moveDir;                 // �����������E�ɐݒ�.

	//�t���b�V���𖳌���.
	for (int i = 0; i < OBSTACLE4_FLASH_MAX; i++) {
		flashEffect[i].ValidFlag = 0;
	}
}
//�X�V.
void Obstacle4main::Update()
{
//	if (p_player->GetActive()) {  // �v���C���[���A�N�e�B�u�ȏꍇ�̂�
	if (p_data->scene == SCENE_GAME) {  // �Q�[�����̂�
		
		//���˃J�E���^������.
		Hsc -= (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);

		//�G�t�F�N�g�̃J�E���^���X�V.
		for (int i = 0; i < OBSTACLE4_FLASH_MAX; i++) {
			//�L���Ȃ�.
			if (flashEffect[i].ValidFlag)
			{
				flashEffect[i].Counter += (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
			}
		}

		enemy4Move();					// ��Q���̈ړ�����
		UpdateObstFlash();              // ���˃G�t�F�N�g�̍X�V.
	}
}
//�`��.
void Obstacle4main::Draw()
{
	DrawObstFlash(); // ���˃G�t�F�N�g�̕`��.
	
	// �����C���`��.
	//Box box = { {Hx, Hy}, {10, 10}, GetColor(100, 100, 100) }; //{pos}, {size}, color.
	//DrawBoxST(&box, true, false);
}

//���˃G�t�F�N�g�̍X�V.
void Obstacle4main::UpdateObstFlash() {

}
//���˃G�t�F�N�g�̕`��.
void Obstacle4main::DrawObstFlash() {

	// ���[�U�[���ˑO�̗\������`��
	DrawPreLaserDots();

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
		int alphaValue = _int_r(255 * alpha);
		alphaValue = max(alphaValue, 0); //������0.

		//�G�t�F�N�g�̃T�C�Y�����Ԃɉ����Ċg��.
		float sizeMultiplier = OBSTACLE4_FLASH_SIZE_INIT + (
			flashEffect[i].Counter * OBSTACLE4_FLASH_SIZE_SPREAD / flashEffect[i].Duration
		);
		int effectSize = _int_r(flashEffect[i].BaseSize * sizeMultiplier);
		int innerSize = effectSize / 2;

		//�v���C���[�̕������v�Z.
		double angle = flashEffect[i].angle;
		double cos_a = cos(angle);
		double sin_a = sin(angle);

#if false
		//�G�t�F�N�g�����Ԍo�߂Ńv���C���[�̕��֐i�܂���.
		float progress = flashEffect[i].Counter / flashEffect[i].Duration;
		double currentX = flashEffect[i].x + cos_a * progress * 1000; // n�s�N�Z�����ړ�
		double currentY = flashEffect[i].y + sin_a * progress * 1000;
#else
		double currentX = flashEffect[i].x;
		double currentY = flashEffect[i].y;
#endif

		Triangle tri;
		//�O�p�`��3�_(�Ȃ񂩂������Ȃ��������)
		tri.pos[0].x = currentX + cos_a * effectSize; //��[.
		tri.pos[0].y = currentY + sin_a * effectSize;
		tri.pos[1].x = currentX - cos_a * effectSize/3 + sin_a * effectSize/2; //����.
		tri.pos[1].y = currentY - sin_a * effectSize/3 - cos_a * effectSize/2;
		tri.pos[2].x = currentX - cos_a * effectSize/3 - sin_a * effectSize/2; //�E��.
		tri.pos[2].y = currentY - sin_a * effectSize/3 + cos_a * effectSize/2;

		Line line1, line2;
		//�O�p�`��2�ӂ���ɂ���.
		line1.stPos = tri.pos[1];
		line1.edPos = tri.pos[0];
		line2.stPos = tri.pos[0];
		line2.edPos = tri.pos[2];
		line1.color = GetColor(0, 255, 255);
		line2.color = GetColor(0, 255, 255);

		//�`�惂�[�h�ݒ�(����)
		SetDrawBlendMode(DX_BLENDMODE_ADD, alphaValue);

		DrawLineST(&line1, true);
		DrawLineST(&line2, true);

		//�G�t�F�N�g���Ԃ��I�������疳����
		if (flashEffect[i].Counter >= flashEffect[i].Duration)
		{
			flashEffect[i].ValidFlag = 0;
		}
	}

	//�ʏ�̕`�惂�[�h�ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);  
}

// ���[�U�[���ˑO�̗\������`��
void Obstacle4main::DrawPreLaserDots() {

	// ���˃^�C�~���O���߂Â��Ă���ꍇ�̂݁���\��
	if (Hsc <= HscTm + 60) { // ����60�t���[���O����\��
		// �_�Ō��ʂ��쐬
		float blinkProgress = (HscTm + 60 - Hsc) / 60.0f; // 0.0����1.0
		int blinkAlpha = _int_r(128 + 127 * sin(blinkProgress * M_PI * 8)); // �_��

		//�T�C�Y�����X�ɑ傫��.
		float dotSize  = (float)(3 + CalcNumEaseOut(blinkProgress) * OBSTACLE4_PRE_LASER1_SIZE);
		float dotSize2 = (float)(3 + CalcNumEaseOut(blinkProgress) * OBSTACLE4_PRE_LASER2_SIZE);
		//�~���.
		Circle cir = {{Hx, Hy}, dotSize, GetColor(0, 255, 255)};
		SetDrawBlendMode(DX_BLENDMODE_ADD, blinkAlpha);

		// �C��̈ʒu�Ɂ���`��
		DrawCircleST(&cir, false, true);
		cir.r = dotSize2;
		DrawCircleST(&cir, false, true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

/**
 * @brief �G�i��Q���j�̈ړ�����
 * ���[�U�[�̈ړ��ƃv���C���[�ւ̒ǔ��A�C��̈ړ��ƃ��[�U�[���˂��Ǘ�
 */
void Obstacle4main::enemy4Move()
{
	// �C��̈ړ��ƃ��[�U�[���ˏ���
	{
		//�ړ�����.
		Move();

		// �^�C�~���O�������烌�[�U�[����
		if (Hsc <= HscTm)
		{
			//�v���C���[���W.
			DBL_XY plyPos = p_player->GetPos();
			//�v���C���[�����ւ̏����p�x�v�Z.
			double angle = atan2(plyPos.y - Hy, plyPos.x - Hx);
			DBL_XY vel = {cos(angle), sin(angle)};

			//�ʏ탌�[�U�[����.
			bool ret = p_laserMng->SpawnLaser({Hx, Hy}, vel, Laser_Normal);
			//���ː���������.
			if (ret) {
				CreateFlashEffect(Hx, Hy); //�G�t�F�N�g���o��.
			}

			HscTm -= OBSTACLE4_SHOT_SPAN; //���˃^�C�~���O��ύX.
		}
		//0�b�����������������.
		if (Hsc <= 0) {
			//�^�C�}�[�ĊJ(���X�ɒZ���Ȃ�)
			//���ˊJ�n���Ԃ��Z���Ȃ�Ȃ��悤���Ԃ�ݒ�.
			Hsc   = OBSTACLE4_SHOT_START + OBSTACLE4_SHOT_RESET * p_data->spawnRate;
			HscTm = OBSTACLE4_SHOT_START;
		}
	}
}

//����effect�̐���.
void Obstacle4main::CreateFlashEffect(double fx, double fy)
{
	DBL_XY pPos = p_player->GetPos(); //�v���C���[���W�擾.

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