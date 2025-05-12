/*
   - Obstacle2.cpp -
   ��Q���Ǘ�.(���c����)
*/
#include "Player.h"
#include "Obstacle2.h"

void Obstacle2::Init(Player* _player)
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
	//extrn�ϐ����g�p���ăv���C���[�ɃA�N�Z�X.
	//extern Player player;

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

				//�v���C���[�̕����֌������p�x���v�Z.
				double px = player->GetPos().x + PLAYER_SIZE / 2.0;//�v���C���[�̒��Sx.
				double py = player->GetPos().y + PLAYER_SIZE / 2.0;//�v���C���[�̒��Sy.
				Ma[i] = atan2(py - My[i], px - Mx[i]); // �v���C���[�ւ̊p�x���v�Z.
				//�p�x���Z�b�g.
				//Ma[i] = M_PI / 2;

				//�ǔ��J�E���^���Z�b�g.
				Mc[i] = 0;

				//�V���b�g�f�[�^���g�p���ɃZ�b�g.
				Mv[i] = 1;

				//�ꔭ�������˂��邽�߃��[�v�𔲂���.

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

		//�Փ˔���
		bool isCollison = false;

		int x = Mx[i] < player->GetPos().x + PLAYER_SIZE;
		int x2 = Mx[i] + 16 > player->GetPos().x;
		int y = My[i] < player->GetPos().y + PLAYER_SIZE;
		int y2 = My[i] + 16 > player->GetPos().y;
		//�v���C���[�ƃ~�T�C���̋������d�˂��Ă��邩�m�F.
		if (x && x2 && y && y2)
		{
			isCollison = true;
		}

		if (isCollison)
		{
			Mv[i] = 0;
			continue;
		}

		//�ǔ��J�E���^���K��l�ɗ��Ă��Ȃ���Βǔ�����.
		if (Mc[i] < 100)
		{

			//�v���C���[�ւ̒��S���W���v�Z.
			double px = player->GetPos().x + PLAYER_SIZE / 2.0;
			double py = player->GetPos().y + PLAYER_SIZE / 2.0;

			double targetAngle = atan2(py - My[i], px - Mx[i]);

			//�v���C���[�ւ̊p�x���v�Z.
			double angleDiff = targetAngle - Ma[i];

			//���݂̊p�x�ƖڕW�p�x�̍����v�Z.
			while (angleDiff > M_PI)angleDiff -= 2 * M_PI;
			while (angleDiff < -M_PI)angleDiff += 2 * M_PI;

			//�p�x�̕ω��ʂ𐧌����Ă炩�Ȓǔ�������.
			double turnSpeed = (M_PI / 180.0) * 5.0;//1�t���[��������̍ő��]�p�x.

			//�p�x���X�V.
			if (fabs(angleDiff) < 0.001)
			{
				// �p�x�����ق�0�̏ꍇ�͒������Ȃ�.
				// �������Ȃ�.
			}
			else if (angleDiff > 0)
			{
				Ma[i] += fmin(turnSpeed, angleDiff);
			}
			else
			{
				Ma[i] += fmax(-turnSpeed, angleDiff);
			}
		}
		//�ǔ��J�E���^���Z.
		Mc[i]++;
		//�ړ�����.
		double speed = 4.0; // �~�T�C���̑��x
		Mx[i] += (int)(cos(Ma[i]) * speed);
		My[i] += (int)(sin(Ma[i]) * speed);

		//��ʊO�ɂł���~�T�C���f�[�^�𖳌��ɂ���.
		if (Mx[i] < -100 || Mx[i]>740 || My[i] < -100 || My[i]>500)
		{
			Mv[i] = 0;
		}
	}
}

