/*
   - KR_Sound.h - (DxLib)
   ver: 2025/09/24

   �T�E���h�@�\��ǉ����܂��B
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
	//�����̊֌W.
	public:
		//���̎擾�p.
		static SoundMng& GetInst() {
			static SoundMng inst; //���g�̃C���X�^���X.
			return inst;
		}
		//�g�p�֎~.
		SoundMng(const SoundMng&) = delete;
		SoundMng& operator=(const SoundMng&) = delete;
	private: 
		//constructor(�V�K�쐬���ł��Ȃ�����)
		SoundMng(){}

	//���f�[�^.
	private: 
		map<MY_STRING, SoundData> sound;

	public:
		//destructor.
		~SoundMng();

		int  LoadFile(MY_STRING fileName, MY_STRING saveName);
		int  Play    (MY_STRING saveName, bool isLoop, int volume = 100);
		int  Stop    (MY_STRING saveName);
		void StopAll ();
		void Update  ();

		void ChangeVolume(MY_STRING saveName, int volume, float sec = 0);	       //���ʂ�ύX.
		void FadeInPlay  (MY_STRING saveName, bool isLoop, int volume, float sec); //�t�F�[�h�C���Đ�.
		void FadeOutPlay (MY_STRING saveName, float sec);						   //�t�F�[�h�A�E�g����.
	};
	//����.
	static SoundMng& InstSoundMng = SoundMng::GetInst();
}