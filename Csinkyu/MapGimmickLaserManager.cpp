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
	p_data     = _data;
	p_player   = _player;
	p_meteoMng = _meteoMng;

	laserSpawnTimer = 0;
	nextLaserIndex  = 0;

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
	nextLaserIndex  = 0;
}
/// <summary>
/// �X�V���邺.
/// </summary>
void MapGimmickLaserManager::Update()
{
	plyPos = p_player->GetPos();//�v���C���[�̌��݈ʒu���擾.

	//���[�U�[���˃^�C�}�[�X�V.
	laserSpawnTimer += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;

	//180�t���[��(��3�b)���Ƃɒ������[�U�[�𔭎�.
	if (laserSpawnTimer >= 180)
	{
		SpawnStraightLaser();
		laserSpawnTimer = 0;
	}

	UpdateLaser();    //�e���[�U�[�̍X�V.
	UpdateLaserLine();//�e���[�U�[�`����̍X�V.

}
/// <summary>
/// �`�揈�������`
/// </summary>
void MapGimmickLaserManager::Draw()
{
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
		laser[i].Counter += (float)(p_data->isSlow) ? SLOW_MODE_SPEED : 1;
		
		//�ړ��O�̍��W��ۑ�.
		DBL_XY befPos = { laser[i].x,laser[i].y };

		//���x(�������[�U�[�Ȃ̂ň�葬�x)
		double speed = 8.0 * (float)(p_data->isSlow) ? SLOW_MODE_SPEED : 1;

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
				line[j].Counter   = 0;   //�ʉߎ��ԃJ�E���^������.
				line[j].ValidFlag = 1;   //�O�Ղ�L����.
				break;
			}
		}
		int _x = laser[i].x < -100 || laser[i].x>WINDOW_WID + 100;
		int _y = laser[i].y <-100 || laser[i].y>WINDOW_HEI + 100;
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
/// //�������[�U�[����(�R�[�h������[)
/// </summary>
void MapGimmickLaserManager::SpawnStraightLaser()
{
	// ��ʍ��[����E�Ɍ������Ĕ���.
	double startX = -50;  // ��ʍ��[�̏����O��.
	// ��ʂ�3�������āA��E���E���̈ʒu���甭��.
	double positions[3] = {
		WINDOW_HEI * 0.25,  // �㕔
		WINDOW_HEI * 0.5,   // ����
		WINDOW_HEI * 0.75   // ����
	};
	double startY = positions[nextLaserIndex];

	// �E�����ւ̈ړ��x�N�g��.
	double vx = 1.0;  // �E����
	double vy = 0.0;  // ����

	// ���[�U�[�f�[�^�̏�����
	laser[nextLaserIndex].x = startX;       // �������Wx
	laser[nextLaserIndex].y = startY;       // �������Wy
	laser[nextLaserIndex].vx = vx;          // ��������x
	laser[nextLaserIndex].vy = vy;          // ��������y
	laser[nextLaserIndex].Counter = 0;      // �o�ߎ��ԃJ�E���^������
	laser[nextLaserIndex].ValidFlag = 1;    // ���[�U�[��L����

	// ���̃��[�U�[�C���f�b�N�X���X�V�i0, 1, 2�����[�v�j
	nextLaserIndex = (nextLaserIndex + 1) % 3;
}
///���[�U�[����.
void MapGimmickLaserManager::DeleteLaser(int idx) {
	laser[idx].ValidFlag = 0;       //�����ɂ���.
	laser[idx].Counter = 0;         //�J�E���^�[���Z�b�g.
}