/*
   - Player.cpp -
   �v���C���[�Ǘ�.
*/
#include "Player.h"
#include"GlovalConst.h"
//WinMain�֐�
int PlayerX , PlayerY, PlayerGraph; // �������ɏ����l��ݒ�
int i = 0; // i�ɂ������l��ݒ�

//������.
void Player::Init()
{
}
//�X�V.
void Player::Update()
{
	// �L�[���͂ɉ����ăv���C���[���ړ�
	if (CheckHitKey(KEY_INPUT_UP) == 1)
	{
		PlayerY -= 3;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		PlayerY += 3;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		PlayerX -= 3;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		PlayerX += 3; // �����͌��̃R�[�h�ł�PlayerY�ɑ�����Ă��܂������C��
	}

	if (PlayerX < 0) PlayerX = 0;
	if (PlayerY < 0) PlayerY = 0;
	if (PlayerX > WINDOW_WID - 30) PlayerX = WINDOW_WID - 30; // ��ʃT�C�Y��640x480�Ɖ���
	if (PlayerY > WINDOW_HEI- 30) PlayerY = WINDOW_HEI- 30;
}
//�`��.
void Player::Draw()
{
	unsigned int Cr;
	Cr = GetColor(255, 255, 255); // ���F

	PlayerGraph = DrawBox(270, 430, 270 + 50, 430 + 50, Cr, TRUE);//�l�p�`��`��
	PlayerX = 320; PlayerY = 400;

	// �l�p�`��`��i�v���C���[�̈ʒu�Ɂj
	DrawBox(PlayerX, PlayerY, PlayerX + 30, PlayerY + 30, Cr, TRUE);
}
//void Player::PlayerMove()
//{
//	
//}