/*
   - Player.cpp -
   �v���C���[�Ǘ�.
*/
#include "Player.h"
#include "GlovalConst.h"

void Player::Init()
{
	PlayerX = 100;
	PlayerY = 100;
}
//�X�V.
void Player::Update()
{

	Move();
}
//�`��.
void Player::Draw()
{
	unsigned int Cr;
	Cr = GetColor(255, 255, 255); // ���F

	// �l�p�`��`��i�v���C���[�̈ʒu�Ɂj
	DrawBox(PlayerX, PlayerY, PlayerX + 30, PlayerY + 30, Cr, TRUE);
}

//�Â��ړ��֐�.
void Player::Move()
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
		PlayerX += 3;
	}

	if (PlayerX < 0)
	{
		PlayerX = 0;
	}

	if (PlayerY < 0)
	{
		PlayerY = 0;
	}
	if (PlayerX > WINDOW_WID - 30)
	{
		PlayerX = WINDOW_WID - 30;
	}
	if (PlayerY > WINDOW_HEI - 30)
	{
		PlayerY = WINDOW_HEI - 30;
	}
}