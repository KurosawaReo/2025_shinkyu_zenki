/*
   - Player.cpp -
   �v���C���[�Ǘ�.
*/
#include "Player.h"

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
}
//�`��.
void Player::Draw()
{
	unsigned int Cr;
	Cr = GetColor(255, 255, 255); // ���F

	// �l�p�`��`��i�v���C���[�̈ʒu�Ɂj
	DrawBox(PlayerX, PlayerY, PlayerX + 30, PlayerY + 30, Cr, TRUE);
}
void Player::PlayerMove()
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
    if (PlayerX > 640 - 30) PlayerX = 640 - 30; // ��ʃT�C�Y��640x480�Ɖ���
    if (PlayerY > 480 - 30) PlayerY = 480 - 30;
}