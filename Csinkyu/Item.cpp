/*
   - Item.cpp -
   Item�Ǘ�.
*/
#include "Item.h"
#include "Player.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>  // sqrt�֐��̂���
#include"Global.h"
//������.
GameData gamedata;
void Item::Init()
{
	// �����_���V�[�h��ݒ�i����̂݁j
	static bool seedSet = false;
	if (!seedSet) {
		srand((unsigned int)time(NULL));
		seedSet = true;
	}

	Reset(); // ���Z�b�g�֐����Ăяo��
}

// �A�C�e���̃��Z�b�g�i�Đ����p�j
void Item::Reset()
{
	// ���W�̏�����
	itemX = (double)(rand() % 600 + 20);  // X���W�������_���ɐݒ�i20�`620�͈̔́j
	itemY = -20.0;                        // ��ʏ㕔�̏����ォ��J�n
	Ix = (float)itemX;
	Iy = (float)itemY;

	// pos�\���̂̐ݒ�
	pos.x = itemX;
	pos.y = itemY;

	// �T�C�Y�ƐF�̐ݒ�
	size.x = 20;
	size.y = 20;
	clr = GetColor(0, 255, 250);

	// �A�C�e���̏�Ԑݒ�
	active = TRUE;
	itemFlag = 1;                         // �A�N�e�B�u�t���O
	itemCounter = 0;                      // �J�E���^�[������
	itemW = 20;
	itemH = 20;
	// itemGraph = LoadGraph("item.png"); // �摜���g�p����ꍇ
}

//�X�V.
void Item::Update()
{
	if (active && itemFlag) {
		ItemMove();
		itemCounter++;

		// ��ʉ����𒴂�����Đ���
		if (itemY > 480) {
			Reset(); // �V�����A�C�e���Ƃ��čĐ���
		}
	}
	else
	{
		//�A�C�e������������ĂȂ����ł��`�F�b�N.
		itemCounter++;
		if (itemCounter > ITEM_RESPAWN_TIME)//�t���[��1�b�ɐ���.
		{
			Reset();
		}
	}
}

// �v���C���[�Ƃ̓����蔻��
BOOL Item::CheckHitPlayer(Player* player)
{
	if (!active || !itemFlag || !player->GetActive()) {
		return FALSE;
	}

	// �v���C���[�̈ʒu�Ɠ����蔻��~���擾
	Circle* playerHit = player->GetHit();

	// �A�C�e���̋�`�ƃv���C���[�̉~�̓����蔻��
	double dx = itemX - playerHit->pos.x;
	double dy = itemY - playerHit->pos.y;
	double distance = sqrt(dx * dx + dy * dy);

	// �A�C�e���̃T�C�Y���l�����������蔻��
	double itemRadius = (itemW + itemH) / 4.0; // �A�C�e���̔��a�Ƃ��Čv�Z

	if (distance < (playerHit->r + itemRadius)) {
		// ���������ꍇ�̏���
		OnHitPlayer();
		return TRUE;
	}

	return FALSE;
}

// �v���C���[�Ɠ��������Ƃ��̏���
void Item::OnHitPlayer()
{
	// �h�b�g���O��\��
	printfDx(_T("������܂����I X:%.1f Y:%.1f\n"), itemX, itemY);

	

	// �A�C�e�����폜�i��A�N�e�B�u�ɂ���j
	active = FALSE;
	itemFlag = 0;
	itemCounter = 0;//�J�E���^�[�����Z�b�g���čĐ����^�C�}�[�J�n.


	// ���W����ʊO�Ɉړ��i�O�̂��߁j
	itemX = -100;
	itemY = -100;
	Ix = (float)itemX;
	Iy = (float)itemY;
	pos.x = itemX;
	pos.y = itemY;
}

//�`��.
void Item::Draw()
{
	if (active && itemFlag) {
		// ���W���X�V
		pos.x = itemX;
		pos.y = itemY;
		Ix = (float)itemX;
		Iy = (float)itemY;

		// �`��i�����̃R�[�h�����p�j
		Box box = { {Ix, Iy}, {itemW, itemH}, clr }; //{pos}, {size}, color.
		DrawBoxST(&box, TRUE);

		// �摜���g�p����ꍇ�̃R�[�h��
		// if (itemGraph != -1) {
		//     DrawGraph((int)itemX, (int)itemY, itemGraph, TRUE);
		// }
	}
}

void Item::ItemMove()
{
	if (active && itemFlag) {
		// ��{�I�ȗ�������
		double fallSpeed = 2.0 + (rand() % 3);  // 2.0�`4.0�̗������x
		itemY += fallSpeed;

		// ���E�ɂ����������_���ȓ�����ǉ��i�I�v�V�����j
		if (itemCounter % 20 == 0) {  // ���Ԋu�ō��E�Ɉړ�
			double moveX = ((rand() % 3) - 1) * 0.5;  // -0.5, 0, 0.5�̂����ꂩ
			itemX += moveX;

			// ��ʊO�ɏo�Ȃ��悤�ɐ���
			if (itemX < 0)   itemX = 0;
			if (itemX > 620) itemX = 620;
		}

		// ���W�̓���
		pos.x = itemX;
		pos.y = itemY;
		Ix = (float)itemX;
		Iy = (float)itemY;
	}
}