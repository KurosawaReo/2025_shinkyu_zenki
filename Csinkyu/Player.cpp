/*
   - Player.cpp -
   �v���C���[�Ǘ�.
*/
#include "Player.h"
#include "GlovalConst.h"

//WinMain�֐�
void Move();
void atari();
//������.
int PlayerX, PlayerY, PlayerGraph;
int i = 0;
void Player::Init()
{
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
void Move()
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