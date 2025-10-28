/*
   - KR_App.cpp - (DxLib)
   ver: 2025/10/09

   �v���O�����S��(�J�n,�I���Ȃ�)�̏������s���܂��B
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.h�ɓ����ĂȂ���΂����œ���.
  #include "KR_Timer.h"
#endif
#include "KR_App.h"

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	//DxLib�̏���������.
	int App::InitDx(int windowWid, int windowHei, bool isWindowMode, int fps, bool isVSync) {

		ChangeWindowMode(isWindowMode);				//TRUE��window, FALSE�őS��ʂɂ���.
		SetWindowSize   (windowWid, windowHei);		//�E�B���h�E�T�C�Y�̐ݒ�.
		SetGraphMode    (windowWid, windowHei, 32); //�𑜓x�̐ݒ�.
		SetWaitVSyncFlag((isVSync) ? TRUE : FALSE);	//FALSE��VSync�𖳌���(FPS�����Ȃ�)
		SetDrawScreen   (DX_SCREEN_BACK);			//����ʂ֕`��(�_�u���o�b�t�@)
		SetOutApplicationLogValidFlag(FALSE);		//FALSE��Log.txt�Ƀ��O���������܂Ȃ�.

		//DxLib�̏�����.
		if (DxLib_Init() == -1) {
			return -1; //-1: �������G���[.
		}

		//fps�v���p�^�C�}�[.
		tmFps = TimerMicro(TimerMode::CountDown, 1000000/fps);
		tmFps.Start();
		//�ϐ��̐ݒ�.
		windowSize = { windowWid, windowHei };
		this->fps = fps;
		isQuit = false;

		Init(); //����������(main.cpp��)

		return 0; //����I��.
	}
	//DxLib�̃��[�v����.
	void App::LoopDx() {

		//���C�����[�v.
		//ESC��������邩�A�I���T�C��������ΏI��.
		while (ProcessMessage() == 0 && !isQuit) {
			//��莞�Ԃ��Ƃɏ���.
			if (tmFps.IntervalTime()) {
				ClearDrawScreen(); //��ʃN���A.
				Update();          //�X�V����(main.cpp��)
				Draw();			   //�`�揈��(main.cpp��)
				ScreenFlip();      //�\��ʂ֕`��.
			}
		}

		DxLib_End();               //DxLib�̏I������.
		DeleteFile(_T("Log.txt")); //Log.txt�����������̂ŏ�������.
	}
	//�Q�[�����I������.
	void App::Quit() {
		isQuit = true;
	}
}