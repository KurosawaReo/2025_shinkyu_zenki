/*
   - KR_Sound.h - (DxLib)
   ver: 2025/08/24

   �T�E���h�@�\��ǉ����܂�.
*/
#pragma once

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	class TimerMicro; //�O���錾.

	//�T�E���h�f�[�^.
	class SoundData
	{
	private:
		int         handle{};    //�T�E���h�n���h��.
		
		int         nowVol{};    //���݂̉���.
		int         aftVol{};    //�ω���̉���.
		LONGLONG    aftUS{};     //�ω�����(�}�C�N���b)
		TimerMicro* timer{};     //�^�C�}�[�v���p.
		bool        isFadeOut{}; //�t�F�[�h�A�E�g�ŉ���������.

	public:
		//constructor, destructor.
		SoundData();
		~SoundData();
		//set.
		void SetHandle(int _handle) {
			handle = _handle;
		}
		void SetIsFadeOut(bool _isFadeOut) {
			isFadeOut = _isFadeOut;
		}

		void Release(); //���.
		void Update();  //�X�V.

		void Play(bool isLoop, int volume);       //�Đ�.
		void Stop();                              //��~.
		void ChangeVolume(int volume, float sec); //���ʕύX�ݒ�.

		int  GetVolumeRange(int volume);          //�{�����[���l��L���͈͂ɕϊ�.
	};

	//�T�E���h�Ǘ��N���X[�p���s��]
	class SoundMng final
	{
	private: //����.
		static SoundMng inst; //���g�̃C���X�^���X.

	private: //�f�[�^.
		map<MY_STRING, SoundData> sound;

	public:
		//���̂̎擾.
		static SoundMng* GetPtr() {
			return &inst;
		}
		//destructor.
		~SoundMng();

		int  LoadFile(MY_STRING fileName, MY_STRING saveName);
		void Play    (MY_STRING saveName, bool isLoop, int volume = 100);
		void Stop    (MY_STRING saveName);
		void Update  ();

		void ChangeVolume(MY_STRING saveName, int volume, float sec = 0);	       //���ʂ�ύX.
		void FadeInPlay  (MY_STRING saveName, bool isLoop, int volume, float sec); //�t�F�[�h�C���Đ�.
		void FadeOutPlay (MY_STRING saveName, float sec);						   //�t�F�[�h�A�E�g����.
	};
}