/*
   - MapGimmickLaserManager.cpp -
   �}�b�v�M�~�b�N�p�̒������[�U�[�Ǘ�.
*/
#include "Player.h"
#include "MeteoManager.h"
#include "MapGimmickLaserManager.h"
/// <summary>
/// ���Z�b�g���邺.
/// </summary>
/// <param name="_data"></param>
/// <param name="_player"></param>
/// <param name="_meteoMng"></param>
void MapGimmickLaserManager::Init(GameData* _data, Player* _player, MeteoManager* _meteoMng)
{
	//���Ԏ擾���邺.
	p_data = _data;
	p_player = _player;
	p_meteoMng = _meteoMng;

	laserSpawnTimer = 0;
	nextLaserIndex = 0;
	predictionTimer = 0;
	showPrediction = false;
	currentDirection = 0;
	nextDirection = 0;
	// �d���폜: currentDirection = 0;
	// �d���폜: nextDirection = 0;
	nextCenterPos = 0;  // �ǉ�: ���̃��[�U�[���ˈʒu������

}
/// <summary>
/// ���Z�b�g�����`��
/// </summary>
void MapGimmickLaserManager::Reset()
{
	//���[�U�[�f�[�^�̏�����.
	for (int i = 0; i < 3; i++)
	{
		DeleteLaser(i);//�S�č폜���邺.

	}

	//���[�U�[�̋O�Ճf�[�^�̏�����.
	for (int i = 0; i < OBSTACLE6_LINE_MAX; i++)
	{
		line[i].ValidFlag = 0;//�S�Ă̋O�Ղ𖳌�����Ԃ�.
	}
	laserSpawnTimer = 0;
	nextLaserIndex = 0;
	predictionTimer = 0;
	showPrediction = false;
	nextCenterPos = 0;  // �ǉ�: ���̃��[�U�[���ˈʒu���Z�b�g
}
/// <summary>
/// �X�V���邺.
/// </summary>
void MapGimmickLaserManager::Update()
{
	plyPos = p_player->GetPos();//�v���C���[�̌��݈ʒu���擾.

	//���[�U�[���˃^�C�}�[�X�V.
	laserSpawnTimer += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;

	// �\�����\���^�C�}�[�X�V�i���[�U�[���˂�60�t���[���O����\���j
	if (laserSpawnTimer >= 180) // 240-60 = 180�t���[������\�����\��
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
		predictionTimer = laserSpawnTimer - 180; // �\�����\������̌o�ߎ���
	}
	else
	{
		showPrediction = false;
		predictionTimer = 0;
	}

	//240�t���[��(��4�b)���Ƃ�3�̒������[�U�[�𓯎�����.
	if (laserSpawnTimer >= 240)
	{
		SpawnStraightLaser();
		laserSpawnTimer = 0;
		showPrediction = false;
		predictionTimer = 0;
		currentDirection = nextDirection; // �\�����������Ŕ���
	}

	UpdateLaser();    //�e���[�U�[�̍X�V.
	UpdateLaserLine();//�e���[�U�[�`����̍X�V.

}
/// <summary>
/// �`�揈�������`
/// </summary>
void MapGimmickLaserManager::Draw()
{
	// �\�����̕`��i���[�U�[����ɕ`��j
	if (showPrediction)
	{
		DrawPredictionLine();
	}

	//���[�U�[�̋O�Ղ̕`�揈��.
	for (int i = 0; i < OBSTACLE6_LINE_MAX; i++)
	{
		if (line[i].ValidFlag == 0) continue;  // �����ȋO�Ղ̓X�L�b�v

		//���Ԍo�߂ŏ��X�ɔ�������.
		int clr = _int(255 - line[i].Counter * 4);
		clr = max(clr, 0); //�Œ�l��0�ɂ���.

		//���Z�������[�h�ŋO�Ղ�`��(�����G�t�F�N�g)
		SetDrawBlendMode(DX_BLENDMODE_ADD, clr);

		//�O�Ղ̐��ݒ�.
		Line tmpLine = { {line[i].x1,line[i].y1} , { line[i].x2,line[i].y2 }, {} };

		//�����̃��[�U�[(�F�ɂ�����)
		tmpLine.clr = GetColor(50, clr, 255);
		DrawLineST(&tmpLine);//�`��.

	}
	//�ʏ�̕`�惂�[�h�ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

/// <summary>
/// �\�����`�揈��
/// </summary>
void MapGimmickLaserManager::DrawPredictionLine()
{
	// ���̃��[�U�[���˕����ƈʒu���g�p
	double startX, startY, endX, endY;
	double centerPos = nextCenterPos;  // �C��: �\�����ꂽ�ʒu���g�p

	// �_�Ō��ʁi30�t���[�������œ_�Łj
	int blinkCycle = 30;
	int alpha = 128; // ��{�����x
	if ((predictionTimer / blinkCycle) % 2 == 0)
	{
		alpha = 64; // ��������
	}

	// �D�F�̗\������`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	// �����̗\�����݂̂�`��
	// ���˕����ɉ����ė\������`��
	switch (nextDirection)
	{
	case 0: // ������E��
		startX = -50;
		endX = WINDOW_WID + 50;
		{
			Line predictionLine = { {startX, centerPos}, {endX, centerPos}, {} };
			predictionLine.clr = GetColor(128, 128, 128); // �D�F
			DrawLineST(&predictionLine);
		}
		break;
	case 1: // �E���獶��
		startX = WINDOW_WID + 50;
		endX = -50;
		{
			Line predictionLine = { {startX, centerPos}, {endX, centerPos}, {} };
			predictionLine.clr = GetColor(128, 128, 128); // �D�F
			DrawLineST(&predictionLine);
		}
		break;
	case 2: // �ォ�牺��
		startY = -50;
		endY = WINDOW_HEI + 50;
		{
			Line predictionLine = { {centerPos, startY}, {centerPos, endY}, {} };
			predictionLine.clr = GetColor(128, 128, 128); // �D�F
			DrawLineST(&predictionLine);
		}
		break;
	case 3: // ��������
		startY = WINDOW_HEI + 50;
		endY = -50;
		{
			Line predictionLine = { {centerPos, startY}, {centerPos, endY}, {} };
			predictionLine.clr = GetColor(128, 128, 128); // �D�F
			DrawLineST(&predictionLine);
		}
		break;
	}

	// �`�惂�[�h��߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

/// <summary>
/// �e���[�U�[�̍X�V(�ނ�����)
/// </summary>
void MapGimmickLaserManager::UpdateLaser()
{
	const double pSizeHalf = PLAYER_SIZE / 2.0;//�v���C���[�̓����蔻��T�C�Y�̔���.

	//�e���[�U�[�̍X�V.
	for (int i = 0; i < 3; i++)
	{
		if (laser[i].ValidFlag == 0)continue; //�����ȃ��[�U�[�̓X�L�b�v.

		//�v���C���[�ƃ��[�U�[�̓����蔻��
		int x = (laser[i].x > plyPos.x - pSizeHalf && laser[i].x < plyPos.x + pSizeHalf);
		int y = (laser[i].y > plyPos.y - pSizeHalf && laser[i].y < plyPos.y + pSizeHalf);

		//�v���C���[�ƃ��[�U�[�̓����蔻��
		if (x && y)
		{
			DeleteLaser(i);
			p_player->PlayerDeath(); //�v���C���[���S.
			continue;
		}

		//���[�U�[�̒ʉߎ��ԃJ�E���^�𑝉�.
		laser[i].Counter += (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);

		//�ړ��O�̍��W��ۑ�.
		DBL_XY befPos = { laser[i].x,laser[i].y };

		//���x(�������[�U�[�Ȃ̂ň�葬�x) - �C��: ���ʂŗD�揇�ʂ𖾊m��
		double speed = 50.0 * ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);

		//���[�U�[�̈ړ�.
		laser[i].x += laser[i].vx * speed;
		laser[i].y += laser[i].vy * speed;

		//���[�U�[�̋O�Ղ𐶐�.
		for (int j = 0; j < OBSTACLE6_LINE_MAX; j++)
		{
			if (line[j].ValidFlag == 0) //���g�p�̋O�ՃX���b�g.
			{
				//�O�Ճf�[�^�̐ݒ�.
				line[j].x1 = befPos.x;   //�J�n�_X���W.
				line[j].y1 = befPos.y;   //�J�n�_Y���W.
				line[j].x2 = laser[i].x; //�I���_X���W.
				line[j].y2 = laser[i].y; //�I���_Y���W.
				line[j].Counter = 0;   //�ʉߎ��ԃJ�E���^������.
				line[j].ValidFlag = 1;   //�O�Ղ�L����.
				break;
			}
		}

		//��ʊO������C���i�������Z�q�D�揇�ʖ��j
		int _x = (laser[i].x < -100) || (laser[i].x > WINDOW_WID + 100);
		int _y = (laser[i].y < -100) || (laser[i].y > WINDOW_HEI + 100);

		//��ʊO�ɏo�����[�U�[�𖳌���.
		if (_x || _y)
		{
			DeleteLaser(i);
		}
	}

}
/// <summary>
/// �e���[�U�[�`����̍X�V(����ނ��ā`).
/// </summary>
void MapGimmickLaserManager::UpdateLaserLine()
{
	for (int i = 0; i < OBSTACLE6_LINE_MAX; i++)
	{
		if (line[i].ValidFlag == 0)continue;

		//�ʉߎ��ԃJ�E���^����.
		line[i].Counter += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;
		// 64�t���[���o�߂�����O�Ղ𖳌���
		if (line[i].Counter >= 64) line[i].ValidFlag = 0;
	}
}

/// <summary>
/// //�������[�U�[����(�R�[�h������[) - �����_�����˔�
/// </summary>
void MapGimmickLaserManager::SpawnStraightLaser()
{
	// �\�����ꂽ�����Ŕ���
	int direction = nextDirection;  // �C��: currentDirection�ł͂Ȃ�nextDirection���g�p

	double startX, startY, vx, vy;
	double centerPos = nextCenterPos;  // �C��: �\�����ꂽ�ʒu���g�p
	double spacing = 20;  // ���[�U�[�Ԃ̊Ԋu

	switch (direction)
	{
	case 0: // ������E�֔���
		startX = -50;
		vx = 1.0;
		vy = 0.0;
		break;
	case 1: // �E���獶�֔���
		startX = WINDOW_WID + 50;
		vx = -1.0;
		vy = 0.0;
		break;
	case 2: // �ォ�牺�֔���
		startY = -50;
		vx = 0.0;
		vy = 1.0;
		break;
	case 3: // �������֔���
		startY = WINDOW_HEI + 50;
		vx = 0.0;
		vy = -1.0;
		break;
	}

	// 3�̃��[�U�[�𓯎��ɔ���
	for (int i = 0; i < 3; i++)
	{
		// �����̃��[�U�[������΍폜
		if (laser[i].ValidFlag == 1)
		{
			DeleteLaser(i);
		}

		// ���[�U�[�f�[�^�̏�����
		if (direction == 0 || direction == 1) // ��������
		{
			laser[i].x = startX;
			laser[i].y = centerPos + (i - 1) * spacing; // -spacing, 0, +spacing
		}
		else // ��������
		{
			laser[i].x = centerPos + (i - 1) * spacing; // -spacing, 0, +spacing
			laser[i].y = startY;
		}

		laser[i].vx = vx;            // ��������x
		laser[i].vy = vy;            // ��������y
		laser[i].Counter = 0;        // �o�ߎ��ԃJ�E���^������
		laser[i].ValidFlag = 1;      // ���[�U�[��L����
	}

	nextLaserIndex = 0;
	currentDirection = nextDirection; // ���ˌ�Ɍ��݂̕������X�V
}
///���[�U�[����.
void MapGimmickLaserManager::DeleteLaser(int idx) {
	laser[idx].ValidFlag = 0;       //�����ɂ���.
	laser[idx].Counter = 0;         //�J�E���^�[���Z�b�g.
}