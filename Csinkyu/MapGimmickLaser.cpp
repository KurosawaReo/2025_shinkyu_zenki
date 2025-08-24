/*
   - MapGimmickLaserManager.cpp -
   �}�b�v�M�~�b�N�p�̒������[�U�[�Ǘ�.
*/
#include "Player.h"
#include "MeteoManager.h"
#include "LaserManager.h"

#include "MapGimmickLaser.h"

/// <summary>
/// ���Z�b�g���邺.
/// </summary>
void MapGimmickLaser::Init(GameData* _data, Player* _player, LaserManager* _laserMng, MeteoManager* _meteoMng)
{
	//���Ԏ擾���邺.
	p_data     = _data;
	p_player   = _player;
	p_laserMng = _laserMng;
	p_meteoMng = _meteoMng;
	p_calc     = Calc::GetPtr();

	currentDirection = 0;
	nextDirection = 0;
	// �d���폜: currentDirection = 0;
	// �d���폜: nextDirection = 0;
	
	Reset();
}
/// <summary>
/// ���Z�b�g�����`��
/// </summary>
void MapGimmickLaser::Reset()
{
	laserSpawnTimer = MGL_LASER_PREDICTION_TIME+80; //�\�������o��^�C�~���O����J�n.
	nextLaserIndex = 0;
	predictionTimer = 0;
	showPrediction = false;
	nextCenterPos = 0;  //���̃��[�U�[���ˈʒu���Z�b�g
}
/// <summary>
/// �X�V���邺.
/// </summary>
void MapGimmickLaser::Update()
{
	plyPos = p_player->GetPos();//�v���C���[�̌��݈ʒu���擾.

	//���[�U�[���˃^�C�}�[�X�V.
	laserSpawnTimer -= (p_data->isSlow) ? SLOW_MODE_SPEED : 1;

	// �\�����\���^�C�}�[�X�V�i���[�U�[���˂�60�t���[���O����\���j
	if (laserSpawnTimer <= MGL_LASER_PREDICTION_TIME)
	{
		if (!showPrediction)
		{
			// �\�����\���J�n���Ɏ��̔��˕����ƈʒu������
			nextDirection = rand() % 4;

			// ���̔��ˈʒu�������_���Ɍ���
			if (nextDirection == 0 || nextDirection == 1) // ��������
			{
				nextCenterPos = 100 + rand() % (WINDOW_HEI - 200);
			}
			else // ��������
			{
				nextCenterPos = 100 + rand() % (WINDOW_WID - 200);
			}

			showPrediction = true;
		}
		predictionTimer = MGL_LASER_PREDICTION_TIME - laserSpawnTimer; // �\�����\������̌o�ߎ���
	}
	else
	{
		showPrediction = false;
		predictionTimer = 0;
	}

	//�^�C�~���O�ɂȂ�����3�̒������[�U�[�𓯎�����.
	if (laserSpawnTimer <= 0)
	{
		SpawnStraightLaser();

		//�^�C�}�[�ĊJ(���X�ɒZ���Ȃ�)
		//�\�����̏o�鎞�Ԃ��Z���Ȃ�Ȃ��悤�ݒ�.
		laserSpawnTimer = MGL_LASER_PREDICTION_TIME + MGL_LASER_SPAWN_SPAN * p_data->spawnRate;

		showPrediction = false;
		predictionTimer = 0;
		currentDirection = nextDirection; // �\�����������Ŕ���
	}
}
/// <summary>
/// �`�揈�������`
/// </summary>
void MapGimmickLaser::Draw()
{
	// �\�����̕`��i���[�U�[����ɕ`��j
	if (showPrediction)
	{
		DrawPredictionLine();
	}
}

/// <summary>
/// �\�����`�揈��
/// </summary>
void MapGimmickLaser::DrawPredictionLine()
{
	// ���̃��[�U�[���˕����ƈʒu���g�p
	double startX, startY, endX, endY;
	double centerPos = nextCenterPos;  // �C��: �\�����ꂽ�ʒu���g�p

	//30�t���[���������Ƃ��������_�ł��ĂȂ�.
#if false
	// �_�Ō��ʁi30�t���[�������œ_�Łj
	int blinkCycle = 30;
	int alpha = 128; // ��{�����x
	if ((predictionTimer / blinkCycle) % 2 == 0)
	{
		alpha = 64; // ��������
	}
#endif

	// �\�����̓����x.
	double alpha = p_calc->CalcNumEaseIn((float)predictionTimer/MGL_LASER_PREDICTION_TIME); //0.0�`1.0�͈̔�.
	SetDrawBlendModeST(MODE_ALPHA, 255*(1-alpha));

	// �����̗\�����݂̂�`��
	// ���˕����ɉ����ė\������`��
	switch (nextDirection)
	{
	case 0: // ������E��
		startX = -50;
		endX = WINDOW_WID + 50;
		{
			Line predictionLine = { {startX, centerPos}, {endX, centerPos}, {} };
			predictionLine.color = COLOR_PRE_LINE;
			DrawLineST(&predictionLine, true);
		}
		break;
	case 1: // �E���獶��
		startX = WINDOW_WID + 50;
		endX = -50;
		{
			Line predictionLine = { {startX, centerPos}, {endX, centerPos}, {} };
			predictionLine.color = COLOR_PRE_LINE;
			DrawLineST(&predictionLine, true);
		}
		break;
	case 2: // �ォ�牺��
		startY = -50;
		endY = WINDOW_HEI + 50;
		{
			Line predictionLine = { {centerPos, startY}, {centerPos, endY}, {} };
			predictionLine.color = COLOR_PRE_LINE;
			DrawLineST(&predictionLine, true);
		}
		break;
	case 3: // ��������
		startY = WINDOW_HEI + 50;
		endY = -50;
		{
			Line predictionLine = { {centerPos, startY}, {centerPos, endY}, {} };
			predictionLine.color = COLOR_PRE_LINE;
			DrawLineST(&predictionLine, true);
		}
		break;
	}

	// �`�惂�[�h��߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

/// <summary>
/// //�������[�U�[����(�R�[�h������[) - �����_�����˔�
/// </summary>
void MapGimmickLaser::SpawnStraightLaser()
{
	// �\�����ꂽ�����Ŕ���
	int direction = nextDirection;  // �C��: currentDirection�ł͂Ȃ�nextDirection���g�p

	double centerPos = nextCenterPos;  // �C��: �\�����ꂽ�ʒu���g�p
	double spacing = 20;  // ���[�U�[�Ԃ̊Ԋu

	DBL_XY startPos{};
	DBL_XY vel{};

	switch (direction)
	{
	case 0: // ������E�֔���
		startPos.x = -50;
		vel = { +1.0, 0.0 };
		break;
	case 1: // �E���獶�֔���
		startPos.x = WINDOW_WID + 50;
		vel = { -1.0, 0.0 };
		break;
	case 2: // �ォ�牺�֔���
		startPos.y = -50;
		vel = { 0.0, +1.0 };
		break;
	case 3: // �������֔���
		startPos.y = WINDOW_HEI + 50;
		vel = { 0.0, -1.0 };
		break;
	}

	// 3�̃��[�U�[�𓯎��ɔ���
	for (int i = 0; i < 3; i++)
	{
		DBL_XY tmpPos{};
		// ���[�U�[�f�[�^�̏�����
		if (direction == 0 || direction == 1) // ��������
		{
			tmpPos.x = startPos.x;
			tmpPos.y = centerPos + (i-1) * spacing; // -spacing, 0, +spacing
		}
		else // ��������
		{
			tmpPos.x = centerPos + (i-1) * spacing; // -spacing, 0, +spacing
			tmpPos.y = startPos.y;
		}

		//�������[�U�[�𔭎�.
		p_laserMng->SpawnLaser(tmpPos, vel, Laser_Straight);
	}

	nextLaserIndex = 0;
	currentDirection = nextDirection; // ���ˌ�Ɍ��݂̕������X�V
}