/*
   - Obstacle.cpp -
   ��Q���Ǘ�.
*/
#include"Obstacle2.h"
#include "myDraw.h"
#include"Player.h"


#define MAX_M 100
#define PI 3.14159//�~����

int hsc;                    //�G�l�~�[�̏o��Ԋu.
int Mg;                     //�G�l�~�[�̉摜.
int Mx[MAX_M], My[MAX_M];   //�~�T�C���̃O���t�B�b�N.
int Mv[MAX_M];              //�~�T�C���f�[�^�̎g�p���(1:�g�p��0:���g�p)
double Ma[MAX_M];           //�~�T�C���̊p�x.
int Mc[MAX_M];              //�~�T�C���̒ǔ��J�E���^

IMG img;
void eneyMove();
Player player;

void Obstacle2::Init()
{

	Mg = LoadGraphST(&img, _T("image/enemy.png"));
	img.handle;
	img.size.x;
	img.size.y;

	for (int i = 0; i < MAX_M; i++)
	{
		Mv[i] = 0;
	}
	//���˃J�E���g�l�����Z�b�g.
	hsc = 30;
}
void Obstacle2::Update()
{
	eneyMove();
}
void Obstacle2::Draw()
{
	for (int i = 0; i < MAX_M; i++)
	{
		//�~�T�C���f�[�^���L���łȂ��ꍇ�͎��Ɉڂ�.
		if (Mv[i] == 0)continue;
		DrawRotaGraph(Mx[i], My[i], 1.0, Ma[i], Mg, TRUE);
	}

	DrawGraph(0, 0, img.handle, TRUE);
}

void eneyMove()
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
			Ma[i] = PI / 2;

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

		int px = (Mx[i] > PlayerX && Mx[i] < PlayerX + 16);
		int px2 = (PlayerX > Mx[i] && PlayerX < Mx[i] + 16);
		int py = (My[i] > PlayerY && My[i] < PlayerY + 16);
		int py2 = (PlayerY > My[i] && PlayerY < My[i] + 16);

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
			ax = (PlayerX + 16) - Mx[i];
			ay = (PlayerY + 16) - My[i];

			//�O�ς𗘗p��������W�����Ɍ�����.
			Ma[i] += (ax * by - ay * bx < 0.0) ? +PI / 180 * 8 : -PI / 180 * 8;

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

