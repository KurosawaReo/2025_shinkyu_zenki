/*
   - Obstacle2.cpp -
   ��Q���Ǘ��N���X�i�ǔ��~�T�C���j�̎����t�@�C��
   �v���C���[��ǐՂ���~�T�C���̐����E����E�Փ˔�����Ǘ�����
*/
#include "Player.h"    // �v���C���[�N���X�̃w�b�_�[���C���N���[�h
#include "Obstacle2.h" // ��Q���N���X�̃w�b�_�[���C���N���[�h

// �������֐�
void Obstacle2::Init(Player* _player)
{
	// �G�̉摜��ǂݍ���.
	LoadGraphST(&img, _T("image/enemy.png"));
	// img.handle;  �ǂݍ��񂾉摜.
	// img.size.x;  �摜�̕�
	// img.size.y;/ �摜�̍���

	player = _player; // �v���C���[�̃|�C���^��ۑ�

	// ���ׂẴ~�T�C���̏�Ԃ�������.
	for (int i = 0; i < MAX_M; i++)
	{
		Mv[i] = 0; // �~�T�C���̗L���t���O�����Z�b�g.
	}

	// �~�T�C�����˃J�E���g�����Z�b�g.
	hsc = 30;
}

// �X�V�֐�
void Obstacle2::Update()
{
	enemyMove(); // �G�̈ړ����������s
}

// �`��֐�
void Obstacle2::Draw()
{
	// �L���ȃ~�T�C�������ׂĕ`��.
	for (int i = 0; i < MAX_M; i++)
	{
		// �~�T�C���������iMv[i]=0�j�Ȃ�A���̃~�T�C���̕`������Ȃ�.
		if (Mv[i] == 0) continue;

		double size = 0.1; // �`��T�C�Y���̒l
		// �~�T�C������]�����ĕ`�悷��ʒu�A�T�C�Y�A�p�x�A�摜�n���h���A���߃t���O
		DrawRotaGraph(Mx[i], My[i], size, Ma[i], img.handle, TRUE);
	}
}

// �G�i�~�T�C���j�̈ړ��E���ˁE�Փ˔������������֐�.
void Obstacle2::enemyMove()
{

	// extern Player player;

	// �~�T�C�����˃J�E���^�����Ȃ�����.
	hsc--;

	// �J�E���^��0�ɂȂ�����~�T�C���𔭎�.
	if (hsc == 0)
	{
		// �g���Ă��Ȃ��~�T�C���f�[�^�iMv[i]=0�j��T��.
		for (int i = 0; i < MAX_M; i++)
		{
			// �g���Ă��Ȃ��~�T�C���f�[�^���������珉����
			if (Mv[i] == 0) {
				// �~�T�C�����ˈʒu��ݒ�i��ʒ����㕔�̖C�䂩��.
				Mx[i] = 320 + 16; // �C���X���W.
				My[i] = 30 + 16;  // �C���Y���W.

				// �v���C���[�̒��S���W���v�Z.
				double px = player->GetPos().x + PLAYER_SIZE / 2.0; // �v���C���[�̒��SX���W.
				double py = player->GetPos().y + PLAYER_SIZE / 2.0; // �v���C���[�̒��SY���W.

				// �v���C���[�Ɍ������p�x���v�Z�iatan2�֐��ŕ��������߂�j
				Ma[i] = atan2(py - My[i], px - Mx[i]);

				// �ȑO�͌Œ�p�x���������̂��v���C���[�ǔ��ɕύX
				// Ma[i] = M_PI / 2;

				// �ǔ��J�E���^��������
				Mc[i] = 0;

				// �~�T�C����L����
				Mv[i] = 1;

				// �ꔭ�������˂��邽�߃��[�v�𔲂���
				break;
			}
		}

		// ���̃~�T�C�����˂܂ł̃J�E���^�����Z�b�g
		hsc = 30;
	}

	// ���ׂẴ~�T�C���̈ړ�����
	for (int i = 0; i < MAX_M; i++)
	{
		// �~�T�C���������Ȃ�X�L�b�v
		if (Mv[i] == 0) continue;

		// �v���C���[�ƃ~�T�C���̏Փ˔���
		bool isCollison = false;

		// �Փ˔���̏����`�F�b�N�i��`���m�̌�������j
		int x = Mx[i] < player->GetPos().x + PLAYER_SIZE;    // �~�T�C���̍��[���v���C���[�̉E�[��荶�ɂ��邩
		int x2 = Mx[i] + 16 > player->GetPos().x;           // �~�T�C���̉E�[���v���C���[�̍��[���E�ɂ��邩
		int y = My[i] < player->GetPos().y + PLAYER_SIZE;    // �~�T�C���̏�[���v���C���[�̉��[����ɂ��邩
		int y2 = My[i] + 16 > player->GetPos().y;           // �~�T�C���̉��[���v���C���[�̏�[��艺�ɂ��邩

		// ���ׂĂ̏������^�Ȃ�Փ˂��Ă���
		if (x && x2 && y && y2)
		{
			isCollison = true;
		}

		// �Փ˂��Ă�����~�T�C���𖳌������Ď��̃~�T�C����
		if (isCollison)
		{
			Mv[i] = 0;
			continue;
		}

		// �ǔ������i���ˌ�100�t���[���܂Œǔ�����j
		if (Mc[i] < 100)
		{
			// �v���C���[�̒��S���W���v�Z
			double px = player->GetPos().x + PLAYER_SIZE / 2.0;
			double py = player->GetPos().y + PLAYER_SIZE / 2.0;

			// �v���C���[�ւ̖ڕW�p�x���v�Z
			//�֐��̐���atan2�́A2�̓_�̊Ԃ̊p�x�����߂邽�߂֗̕��Ȋ֐�
			//�~�T�C������v���C���[�ւ�y���W����x���W���v�Z����v���C���[���ǂ��ɂ��邩�킩��
			double targetAngle = atan2(py - My[i], px - Mx[i]);

			// ���݂̊p�x�ƖڕW�p�x�̍����v�Z
			double angleDiff = targetAngle - Ma[i];

			// �p�x����-�΂���΂͈̔͂ɐ��K���i�p�x�̊������ݖh�~�j
			while (angleDiff > M_PI) angleDiff -= 2 * M_PI;
			while (angleDiff < -M_PI) angleDiff += 2 * M_PI;

			// ��x�ɉ�]�ł���ő�p�x�𐧌����Ċ��炩�Ȓǔ�������
			double turnSpeed = (M_PI / 180.0) * 5.0; // 1�t���[��������ő�5�x��]

			// �p�x���X�V�i�����ق�0�Ȃ璲�����Ȃ��A�������Ȃ�E���A���Ȃ獶���ɒ����j
			if (fabs(angleDiff) < 0.001)
			{
				// �p�x�����ق�0�̏ꍇ�͒������Ȃ�
				// �������Ȃ�
			}
			else if (angleDiff > 0)
			{
				// �E���ɒ����i�������ő�turnSpeed�x�܂Łj
				Ma[i] += fmin(turnSpeed, angleDiff);
			}
			else
			{
				// �����ɒ����i�������ő�turnSpeed�x�܂Łj
				Ma[i] += fmax(-turnSpeed, angleDiff);
			}
		}

		// �ǔ��J�E���^�𑝉�
		Mc[i]++;

		// ���݂̊p�x�Ɋ�Â��ă~�T�C�����ړ�������
		double speed = 4.0; // �~�T�C���̑��x
		Mx[i] += (int)(cos(Ma[i]) * speed); // X�����̈ړ�
		My[i] += (int)(sin(Ma[i]) * speed); // Y�����̈ړ�

		// ��ʊO�ɏo����~�T�C���𖳌���
		if (Mx[i] < -100 || Mx[i] > 740 || My[i] < -100 || My[i] > 500)
		{
			Mv[i] = 0;
		}
	}
}