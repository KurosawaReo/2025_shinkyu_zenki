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

TimerMicro tmFps(CountUp, 0);  //fps�v���p�^�C�}�[.

void Init() {
	tmFps.Start();
	gm = GameManager::GetPtr(); //GameManager������̎擾.
	gm->Init();
}

BOOL Update() {

	if (tmFps.GetPassTime() < 1000000/FPS) {
		return FALSE;
	}
	tmFps.Start();
	
	gm->Update();
	return TRUE;
}

void Draw() {
	gm->Draw();
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
	SetWaitVSyncFlag(FALSE);                                //VSync�𖳌����iFPS�����Ȃ��j

	//DxLib�̏�����.
	if (DxLib_Init() == -1) {
		return -1; //�G���[�ŏI��.
	}

	//����������.
	Init();
	//ESC���������܂Ń��[�v.
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		if (Update()) {        // �X�V����
			ClearDrawScreen(); // ��ʃN���A
			Draw();			   // �`�揈��
			ScreenFlip();      // �\��ʂ֕`��
		}
	}

	DxLib_End(); //DX���C�u�����̏I������
	return 0;    //�I��
}