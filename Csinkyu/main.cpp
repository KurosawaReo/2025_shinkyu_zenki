/*
   - main.cpp -
   �v���O�����̊J�n�n�_.
*/
#include "GameManager.h"

//stdafx������Ȃ炢��Ȃ�.
#if false
  #include "myTimerST.h"
#endif

GameManager GameManager::self; //static�ϐ��̐錾.
GameManager* gm;               //���̂�����p.

TimerMicro tmFps(COUNT_DOWN, 1000000/FPS); //fps�v���p�^�C�}�[.

void Init() {
	gm = GameManager::GetPtr(); //GameManager������̎擾.
	gm->Init();
}

void Update() {
	gm->Update();
}

void Draw() {
	gm->Draw();
}

#if false
int main() {
#else
int WINAPI WinMain(
	_In_     HINSTANCE hinstance, 
	_In_opt_ HINSTANCE hPrevinstance,
	_In_     LPSTR     lpCmdLine, 
	_In_     int       nCmdShow
){
#endif

	ChangeWindowMode(IS_WINDOW_MODE);						//TRUE��window, FALSE�őS��ʂɂ���.
	SetWindowSize(WINDOW_WID, WINDOW_HEI);					//�E�B���h�E�T�C�Y�̐ݒ�.
	SetGraphMode(WINDOW_WID, WINDOW_HEI, WINDOW_COLOR_BIT);	//�𑜓x�̐ݒ�.
	SetDrawScreen(DX_SCREEN_BACK);							//����ʂ֕`��(�_�u���o�b�t�@)
	SetOutApplicationLogValidFlag(FALSE);                   //FALSE��Log.txt�Ƀ��O���������܂Ȃ�.
	SetWaitVSyncFlag(FALSE);                                //FALSE��VSync�𖳌���(FPS�����Ȃ�)

	//DxLib�̏�����.
	if (DxLib_Init() == -1) {
		return -1; //�G���[�ŏI��.
	}

	//����������.
	Init();
	tmFps.Start();
	//���C�����[�v.
	//ESC��������邩�A�G���[����������ΏI��.
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		//��莞�Ԃ��Ƃɏ���.
		if (tmFps.IntervalTime()) {
			ClearDrawScreen(); //��ʃN���A.
			Update();          //�X�V����.
			Draw();			   //�`�揈��.
			ScreenFlip();      //�\��ʂ֕`��.
		}
	}

	DxLib_End();               //DxLib�̏I������.
	DeleteFileW(L"Log.txt");   //Log.txt�����������̂ŏ�������.

	return 0;
}