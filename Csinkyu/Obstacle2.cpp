/*
   - Obstacle2.cpp -
   ��Q���Ǘ�.(���c����)
*/
#include "Player.h"
#include "Obstacle2.h"

void Obstacle2::Init()
{
	LoadGraphST(&img, _T("image/enemy.png"));
	//img.handle;
	//img.size.x;
	//img.size.y;

	for (int i = 0; i < MAX_M; i++)
	{
		Mv[i] = 0;
	}
	//���˃J�E���g�l�����Z�b�g.
	hsc = 30;
}
void Obstacle2::Update()
{
	enemyMove();
}
void Obstacle2::Draw()
{
	for (int i = 0; i < MAX_M; i++)
	{
		//�~�T�C���f�[�^���L���łȂ��ꍇ�͎��Ɉڂ�.
		if (Mv[i] == 0) continue;

		double size = 0.1; //��.
		DrawRotaGraph(Mx[i], My[i], size, Ma[i], img.handle, TRUE);
	}
}

//�G�̈ړ�.
void Obstacle2::enemyMove()
{
	//�V���b�g�J�E���^�����炷.
	hsc--;
	//�J�E���^��0�ɂȂ�����~�T�C������.
	if (hsc == 0)
	{
		//�g���ĂȂ��~�T�C���f�[�^��T��.
		for (int i = 0; i < MAX_M; i++)
		{
			//�g���ĂȂ��f�[�^����������.
			if (Mv[i] == 0) {
		
				//�~�T�C���̈ʒu��ݒ�.
				Mx[i] = 320 + 16; //�C���X���W.
				My[i] = 30 + 16;  //�C���y���W.

				//�p�x���Z�b�g.
				Ma[i] = M_PI / 2;

				//�ǔ��J�E���^���Z�b�g.
				Mc[i] = 0;

				//�V���b�g�f�[�^���g�p���ɃZ�b�g.
				Mv[i] = 1;
			}
		}
		//���˃J�E���^�l���Z�b�g.
		hsc = 30;
	}

	//�~�T�C���̈ړ�����.
	for (int i = 0; i < MAX_M; i++)
	{
		//�~�T�C���f�[�^��������������X�L�b�v.
		if (Mv[i] == 0) continue;

		int px  = (Mx[i] > player.GetX() && Mx[i] < player.GetX() + 16);
		int px2 = (player.GetX() > Mx[i] && player.GetX() < Mx[i] + 16);
		int py  = (My[i] > player.GetY() && My[i] < player.GetY() + 16);
		int py2 = (player.GetY() > My[i] && player.GetY() < My[i] + 16);

		//player�ɓ�������~�T�C���f�[�^�𖳌��ɂ���.
		if ((px || px2) && (py || py2))
		{
			Mv[i] = 0;
			continue;
		}
		//�ǔ��J�E���^���K��l�ɗ��Ă��Ȃ���Βǔ�����.
		if (Mc[i] < 100)
		{
			double ax, ay, bx, by;

			//�����̐i��ł����.
			bx = cos(Ma[i]);
			by = sin(Ma[i]);
			//�{���i�ނׂ�����.
			ax = (player.GetX() + 16) - Mx[i];
			ay = (player.GetY() + 16) - My[i];

			//�O�ς𗘗p��������W�����Ɍ�����.
			Ma[i] += (ax * by - ay * bx < 0.0) ? + (M_PI/180) * 8 : -(M_PI/180) * 8;
		}
		//�ǔ��J�E���^���Z.
		Mc[i]++;
		//�ړ�����.
		Mx[i] += (int)(cos(Ma[i]) * 6.0);
		My[i] += (int)(sin(Ma[i]) * 6.0);

		//��ʊO�ɂł���~�T�C���f�[�^�𖳌��ɂ���.
		if (Mx[i] < -100 || Mx[i]>740 || My[i] < -100 || My[i]>500) Mv[i] = 0;
	}
}

/*
//���c����̌��̃v���O����

void Obstacle2::enemyMove()
{
	//�V���b�g�J�E���^�����炷.
	hsc--;
	//�J�E���^��0�ɂȂ�����~�T�C������.
	if (hsc == 0)
	{
		//�g���ĂȂ��~�T�C���f�[�^��T��.
		int i;
		for (i = 0; i < MAX_M; i++)
		{
			if (Mv[i] == 0)break;
		}
		//�����g���ĂȂ��~�T�C���f�[�^����������V���b�g���o��.
		if (i != MAX_M)
		{
			//�~�T�C���̈ʒu��ݒ�.
			Mx[i] = 320 + 16;//�C���X���W.
			My[i] = 30 + 16;//�C���y���W.

			//�p�x���Z�b�g.
			Ma[i] = M_PI / 2;

			//�ǔ��J�E���^���Z�b�g.
			Mc[i] = 0;

			//�V���b�g�f�[�^���g�p���ɃZ�b�g.
			Mv[i] = 1;

		}
		//���˃J�E���^�l���Z�b�g.
		hsc = 30;
	}
	//�~�T�C���̈ړ�����.
	for (int i = 0; i < MAX_M; i++)
	{
		//�~�T�C���f�[�^��������������X�L�b�v.
		if (Mv[i] == 0)continue;

		int px  = (Mx[i] > player.GetX() && Mx[i] < player.GetX() + 16);
		int px2 = (player.GetX() > Mx[i] && player.GetX() < Mx[i] + 16);
		int py  = (My[i] > player.GetY() && My[i] < player.GetY() + 16);
		int py2 = (player.GetY() > My[i] && player.GetY() < My[i] + 16);

		//player�ɓ�������~�T�C���f�[�^�𖳌��ɂ���.
		if ((px || px2) && (py || py2))
		{
			Mv[i] = 0;
			continue;
		}
		//�ǔ��J�E���^���K��l�ɗ��Ă��Ȃ���Βǔ�����.
		if (Mc[i] < 100)
		{
			double ax, ay, bx, by;

			//bx,by�����̐i��ł����ax,ay�{���i�ނׂ�����.
			bx = cos(Ma[i]);
			by = sin(Ma[i]);
			ax = (player.GetX() + 16) - Mx[i];
			ay = (player.GetY() + 16) - My[i];

			//�O�ς𗘗p��������W�����Ɍ�����.
			Ma[i] += (ax * by - ay * bx < 0.0) ? + (M_PI/180) * 8 : -(M_PI/180) * 8;

		}
		//�ǔ��J�E���^���Z.
		Mc[i]++;
		//�ړ�����.
		Mx[i] += (int)(cos(Ma[i]) * 6.0);
		My[i] += (int)(sin(Ma[i]) * 6.0);

		//��ʊO�ɂł���~�T�C���f�[�^�𖳌��ɂ���.
		if (Mx[i] < -100 || Mx[i]>740 || My[i] < -100 || My[i]>500)Mv[i] = 0;
	}
}
*/