#include "DxLib.h"
#include "Player.h"
//WinMain�֐�
int PlayerX , PlayerY, PlayerGraph; // �������ɏ����l��ݒ�
int i = 0; // i�ɂ������l��ݒ�
void Player()
{

	unsigned int Cr;
	Cr = GetColor(0, 0, 255);

	PlayerGraph = DrawBox(270, 430, 270 + 50, 430 + 50, Cr, TRUE);//�l�p�`��`��
	PlayerX = 320; PlayerY = 400;
	
}
void PlayerMove()
{
	
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
			PlayerY = 3;
		}
		DrawGraph(PlayerX, PlayerY, PlayerGraph, FALSE);
	
}