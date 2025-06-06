/*
   - main.cpp -
   �v���O�����̊J�n�n�_.
*/
#include "GameManager.h"

GameManager GameManager::self; //static�ϐ��̐錾.
GameManager* gm;               //���̂�����p.

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
		ClearDrawScreen(); // ��ʃN���A
		Update();          // �X�V����
		Draw();            // �`�揈��
		ScreenFlip();      // �\��ʂ֕`��
		WaitTimer(WAIT_LOOP_MS); // �ҋ@����(m�b)
	}

	DxLib_End(); //DX���C�u�����̏I������
	return 0;    //�I��
}