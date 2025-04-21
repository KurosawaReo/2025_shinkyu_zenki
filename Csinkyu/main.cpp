#include "myDraw.h"
#include "GlovalConst.h"

float g_ang = 0;

void Init() {

}

void Update() {
	g_ang+=1;
}

void Draw() {
	INT_XY pos = { 100, 100 };
	DrawLineAng(pos, g_ang, 100, GetColor(0, 255, 0));
}

int WINAPI WinMain(
	_In_     HINSTANCE hinstance, 
	_In_opt_ HINSTANCE hPrevinstance,
	_In_     LPSTR     lpCmdLine, 
	_In_     int       nCmdShow
){
	ChangeWindowMode(IS_WINDOW_MODE);						//TRUE��window, FALSE�őS��ʂɂ���.
	SetGraphMode(WINDOW_WID, WINDOW_HEI, WINDOW_COLOR_BIT);	//window�T�C�Y�ƃJ���[bit���̎w��.
	SetDrawScreen(DX_SCREEN_BACK);							//����ʂ֕`��(�_�u���o�b�t�@)

	//DxLib�̏�����.
	if (DxLib_Init() == -1) {
		return -1; //�G���[�ŏI��.
	}

	//����������.
	Init();
	//ESC���������܂Ń��[�v.
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();		 //��ʃN���A.
		Update();				 //�X�V����.
		Draw();					 //�`�揈��.
		ScreenFlip();			 //�\��ʂ֕`��.
		WaitTimer(WAIT_LOOP_MS); //�ҋ@����(m�b)
	}

	DxLib_End(); //DX���C�u�����̏I������
	return 0;    //�I��
}