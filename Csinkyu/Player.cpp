
#include "DxLib.h"
//WinMain�֐�
int PlayerX = 320, PlayerY = 400, PlayerGraph = -1; // �������ɏ����l��ݒ�
int i = 0; // i�ɂ������l��ݒ�
void Player();
int main()
{
	ChangeWindowMode(TRUE);
	//��ʃ��[�h�ݒ�.
	SetGraphMode(640, 480, 16);

	//DX���C�u������������.
	if (DxLib_Init() == -1)return -1;
	//�O���t�B�b�N�̉�ʐ�𗠉�ʂɃZ�b�g.
	SetDrawScreen(DX_SCREEN_BACK);
	PlayerGraph = LoadGraph(_T("Player.png"));
	if (PlayerGraph == -1)
	{
		return -1;
	}
	//�����ʒu�̐ݒ�
	PlayerX = 320; // ��ʒ�����X���W
	PlayerY = 400; // ��ʉ�����Y���W
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//��ʃN���A.
		ClearDrawScreen();
		//�v���C���[�̕`��.
		Player();
		//����ʂ̓��e��\��ʂɔ��f.
		ScreenFlip();
	}
	//DX���C�u�����̏I������
	DxLib_End();
	return 0;
}
void Player()
{
   DrawExtendGraph(270, 430, 270 + 50, 430 + 50, PlayerGraph, TRUE);

   // ����ʂ̓��e��\��ʂɃR�s�[����
   ScreenFlip();
}
