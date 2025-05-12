/*
   - Obstacle3.cpp -
   ��Q���Ǘ�.
*/
#include "Player.h"
#include "Obstacle3.h"

void Obstacle3::Init(Player* _player)
{
	LoadGraphST(&img, _T("image/enemy.png"));
	//img.handle;
	//img.size.x;
	//img.size.y;

	player = _player; //�v���C���[�̎��̃A�h���X�����炤.

	for (int i = 0; i < MAX_M; i++)
	{
		Mv[i] = 0;
	}
	hsc = 30; //���˃J�E���g�l�����Z�b�g.
}
void Obstacle3::Update()
{
	enemyMove();
}
void Obstacle3::Draw()
{
	for (int i = 0; i < MAX_M; i++)
	{
		//�~�T�C���f�[�^���L���łȂ��ꍇ�͎��Ɉڂ�.
		if (Mv[i] == 0) continue;

		//�`��.
		IMG_DRAW_ROTA data = { img, {_int(Mx[i]), _int(My[i])}, 0.5, Ma[i], FALSE, TRUE };
		DrawRotaGraphST(&data);

#if false
		//��.
		int x = _int(Mx[i] - MISSILE_SIZE / 2);
		int y = _int(My[i] - MISSILE_SIZE / 2);
		int dx = _int(Mx[i] + MISSILE_SIZE / 2);
		int dy = _int(My[i] + MISSILE_SIZE / 2);
		DrawBox(x, y, dx, dy, 0x00FF00, TRUE);
#endif
	}
}

//�G�̈ړ�.
void Obstacle3::enemyMove()
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
		
				//�C���X���W.
				if (rand()%100 < 50) {
					Mx[i] = 0; //50%�ō�.
				}
				else {
					Mx[i] = WINDOW_WID; //50%�ŉE.
				}
				//�C���y���W.
				My[i] = rand() % WINDOW_HEI;

				//�p�x���Z�b�g.
				Ma[i] = M_PI / 2;

				//�ǔ��J�E���^���Z�b�g.
				Mc[i] = 0;

				//�V���b�g�f�[�^���g�p���ɃZ�b�g.
				Mv[i] = 1;

				break; 
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

		//�v���C���[�������̂�.
		if (player->GetActive()) {

			//�����蔻��.
			BOOL hit = IsHitBox(
				player->GetPos(), { PLAYER_SIZE,  PLAYER_SIZE  }, //�v���C���[.
				{ Mx[i], My[i] }, { MISSILE_SIZE, MISSILE_SIZE }  //�~�T�C��.
			);

			//player�ɓ���������~�T�C���f�[�^�𖳌��ɂ���.
			if (hit)
			{
				Mv[i] = 0;
				player->SetActive(FALSE);
				break;
			}
		}
		//�ǔ��J�E���^���K��l�ɗ��Ă��Ȃ���Βǔ�����.
		if (Mc[i] < 100)
		{
			double ax, ay, bx, by;

			//�����̐i��ł����.
			bx = cos(Ma[i]);
			by = sin(Ma[i]);
			//�{���i�ނׂ�����.
			ax = (player->GetPos().x) - Mx[i];
			ay = (player->GetPos().y) - My[i];

			//�O�ς𗘗p��������W�����Ɍ�����.
			if (ax * by - ay * bx < 0.0) {
				Ma[i] +=  (M_PI/180) * MISSILE_TRACK_POW;
			} 
			else {
				Ma[i] += -(M_PI/180) * MISSILE_TRACK_POW;
			}
		}
		//�ǔ��J�E���^���Z.
		Mc[i]++;
		//�ړ�����.
		Mx[i] += (int)(cos(Ma[i]) * MISSILE_SPEED);
		My[i] += (int)(sin(Ma[i]) * MISSILE_SPEED);

		//��ʊO�ɂł���~�T�C���f�[�^�𖳌��ɂ���.
		if (Mx[i] < -100 || Mx[i] > 740 || My[i] < -100 || My[i] > 500) Mv[i] = 0;
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