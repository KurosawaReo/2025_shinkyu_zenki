/*
   - main.cpp -
   �v���O�����̊J�n�n�_.
*/
#include "GameManager.h"

InputMng* p_input = InputMng::GetPtr(); //���̎擾.

TimerMicro tmFps(COUNT_DOWN, 1000000/FPS); //fps�v���p�^�C�}�[.

GameManager GameManager::inst; //�C���X�^���X�𐶐�.
GameManager* gm;               //���̂�����p.

void Init() {
	gm = GameManager::GetPtr(); //GameManager������̎擾.
	gm->Init();
}

bool Update() {
	return gm->Update();
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
	while (ProcessMessage() == 0) {
		//��莞�Ԃ��Ƃɏ���.
		if (tmFps.IntervalTime()) {
			ClearDrawScreen(); //��ʃN���A.
			if (Update()){     //�X�V����.
				break; //�Q�[���I��.
			};
			Draw();			   //�`�揈��.
			ScreenFlip();      //�\��ʂ֕`��.
		}
	}

	DxLib_End();               //DxLib�̏I������.
	DeleteFile(_T("Log.txt")); //Log.txt�����������̂ŏ�������.

	return 0;
}