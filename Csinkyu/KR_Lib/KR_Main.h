/*
   - KR_Main.h - (DxLib)
   ver: 2025/09/10

   �v���O�����J�n�n�_�̏������s���܂��B
*/
#pragma once

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	class TimerMicro; //�O���錾.

	//DxLib�̊�{�����N���X.
	class DxLibMain
	{
	private: 
		TimerMicro tmFps{};  //fps�v���p�^�C�}�[.
		
		INT_XY windowSize{}; //��ʃT�C�Y.    (�L�^�p)
		int    fps{};        //�t���[�����[�g.(�L�^�p)

		bool   isEnd{};      //�Q�[�����I�����邩.

	public:
		//���̂̎擾.
		static DxLibMain* GetPtr() {
			static DxLibMain inst; //���g�̃C���X�^���X.
			return &inst;
		}
		//get.
		INT_XY GetWindowSize() const { return windowSize; }
		int    GetFps()        const { return fps; }

		int  InitDx(int windowWid, int windowHei, bool isWindowMode, int fps, bool isVSync = TRUE);
		void LoopDx();

		void Init();
		void Update();
		void Draw();

		void GameEnd(); //�Q�[�����I������.
	};
}