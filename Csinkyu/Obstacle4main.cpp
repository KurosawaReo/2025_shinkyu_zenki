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
	Hx      = _Hx;                  // �C���X���W�����l�i��ʒ����j
	Hy      = _Hy;                  // �C���Y���W�����l�i��ʏ㕔�j
	Hm      = _Hm;                  // �C��̈ړ����x
	Hsc     = OBSTACLE4_SHOT_RESET; // �C��̔��˃J�E���^�����l
	HscTm   = OBSTACLE4_SHOT_START; // �C��̔��˃^�C�~���O�����l
	moveDir = _moveDir;             // �����������E�ɐݒ�.
}
//�X�V.
void Obstacle4main::Update()
{
//	if (p_player->GetActive()) {  // �v���C���[���A�N�e�B�u�ȏꍇ�̂�
	if (p_data->scene == SCENE_GAME) {  // �Q�[�����̂�
		enemy4Move();					// ��Q���̈ړ����������s
	}
}
//�`��.
void Obstacle4main::Draw()
{
	DrawObstFlash(); // ���˃G�t�F�N�g�̏���.
	
	// �����C���`��.
	//Box box = { {Hx, Hy}, {10, 10}, GetColor(100, 100, 100) }; //{pos}, {size}, color.
	//DrawBoxST(&box, TRUE, FALSE);
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

		//�G�t�F�N�g�̈ʒu�����Ԍo�߂ƂƂ��Ƀv���C���[�����Ɉړ�
		float progress = flashEffect[i].Counter / flashEffect[i].Duration;
		double currentX = flashEffect[i].x + cos(flashEffect[i].angle) * progress * 60; // 30�s�N�Z�����ړ�
		double currentY = flashEffect[i].y + sin(flashEffect[i].angle) * progress * 60;

		//�O�p�`�̒��_���v�Z(�v���C���[�̕���������).
		double angle = flashEffect[i].angle;
		double cos_a = cos(angle);
		double sin_a = sin(angle);
		//�O���̎O�p�`(�傫��)(�Ȃ񂩂������Ȃ��������)
		int x1 = _int(currentX + cos_a * effectSize);//��[.
		int y1 = _int(currentY + sin_a * effectSize);
		int x2 = _int(currentX - cos_a * effectSize / 3 + sin_a * effectSize / 2);//����.
		int y2 = _int(currentY - sin_a * effectSize / 3 - cos_a * effectSize / 2);
		int x3 = _int(currentX - cos_a * effectSize / 3 - sin_a * effectSize / 2);//�E��.
		int y3 = _int(currentY - sin_a * effectSize / 3 + cos_a * effectSize / 2);
		//�����̎O�p�`(������)
		int ix1 = _int(currentX + cos_a * effectSize);//��[.
		int iy1 = _int(currentY + sin_a * effectSize);
		int ix2 = _int(currentX - cos_a * effectSize / 3 + sin_a * effectSize / 2);
		int iy2 = _int(currentY - sin_a * effectSize / 3 - cos_a * effectSize / 2);
		int ix3 = _int(currentX - cos_a * effectSize / 3 - sin_a * effectSize / 2);
		int iy3 = _int(currentY - sin_a * effectSize / 3 + cos_a * effectSize / 2);

		//���˃G�t�F�N�g���~�`�ŕ`��(��������)
		SetDrawBlendMode(DX_BLENDMODE_ADD, alphaValue);

		//�O���̎O�p�`.
		DrawTriangle(x1, y1, x2, y2, x3, y3, GetColor(0, 255, 255), FALSE);

		//�����ɂ�薾�邢�O�p�`��`��.
		//DrawTriangle(ix1, iy1, ix2, iy2, ix3, iy3, GetColor(0, 255, 200), FALSE);

		//�G�t�F�N�g����3�́���`��
		int dotSize = effectSize / 10; // �O�p�`�̃T�C�Y�ɉ����ā��̃T�C�Y�𒲐�
		int dotAlpha = alphaValue / 1; // ���������x��������
		SetDrawBlendMode(DX_BLENDMODE_ADD, dotAlpha);

		// 3�́����O�p�`�̓����ɔz�u
		DrawCircle(_int(currentX + cos_a * effectSize / 3), _int(currentY + sin_a * effectSize / 3), dotSize, GetColor(0, 255, 255), FALSE);
		DrawCircle(_int(currentX - cos_a * effectSize / 6 + sin_a * effectSize / 4), _int(currentY - sin_a * effectSize / 6 - cos_a * effectSize / 4), dotSize, GetColor(0, 255, 255), FALSE);
		DrawCircle(_int(currentX - cos_a * effectSize / 6 - sin_a * effectSize / 4), _int(currentY - sin_a * effectSize / 6 + cos_a * effectSize / 4), dotSize, GetColor(0, 255, 255), FALSE);

		//�G�t�F�N�g�̃J�E���^���X�V
		flashEffect[i].Counter += (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		//�G�t�F�N�g���Ԃ��I�������疳����
		if (flashEffect[i].Counter >= flashEffect[i].Duration)
		{
			flashEffect[i].ValidFlag = 0;
		}
	}

	//�ʏ�̕`�惂�[�h�ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
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

		// ���˃J�E���^������
		Hsc -= (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		// �^�C�~���O�������烌�[�U�[����
		if (Hsc <= HscTm)
		{
			BOOL ret = p_laserMng->SpawnLaser(Hx, Hy); //���[�U�[����.
			//���ː���������.
			if (ret) {
				CreateFlashEffect(Hx, Hy); //�G�t�F�N�g���o��.
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