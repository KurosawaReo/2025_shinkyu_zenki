/*
   - KR_App.h - (DxLib)
   ver: 2025/09/23

   �v���O�����S��(�J�n,�I���Ȃ�)�̏������s���܂��B
*/
#pragma once

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	class TimerMicro; //�O���錾.

	//�v���O�����S�̏����N���X[�p���s��]
	class App final
	{
	//�����̊֌W.
	public:
		//���̎擾�p.
		static App& GetInst() {
			static App inst; //���g�̃C���X�^���X.
			return inst;
		}
		//�g�p�֎~.
		App(const App&) = delete;
		App& operator=(const App&) = delete;
	private: 
		//constructor(�V�K�쐬���ł��Ȃ�����)
		App(){}

	//���f�[�^.
	private:
		TimerMicro tmFps{};  //fps�v���p�^�C�}�[.
		
		INT_XY windowSize{}; //��ʃT�C�Y.    (�L�^�p)
		int    fps{};        //�t���[�����[�g.(�L�^�p)

		bool   isEnd{};      //�Q�[�����I�����邩.

	public:
		//get.
		INT_XY GetWindowSize() const { return windowSize; }
		int    GetFps()        const { return fps; }

		int  InitDx(int windowWid, int windowHei, bool isWindowMode, int fps, bool isVSync = TRUE);
		void LoopDx();

		void Init();
		void Update();
		void Draw();

		void GameOver(); //�Q�[�����I������.
	};
	//����.
	static App& InstApp = App::GetInst();	
}