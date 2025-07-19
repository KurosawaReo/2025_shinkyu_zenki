/*
   - mySoundST.h - (original)
   ver.2025/07/19

   DxLib: �I���W�i���T�E���h�@�\�̒ǉ�.
*/
#pragma once

//�T�E���h�N���X.
class SoundData
{
private:
	int        handle{};                       //�T�E���h�n���h��.

	int        nowVol{};                       //���݂̉���.
	int        aftVol{};                       //�ω���̉���.
	LONGLONG   aftUS{};                        //�ω�����(�}�C�N���b)
	TimerMicro timer = TimerMicro(CountUp, 0); //�^�C�}�[�v���p.
	BOOL       isFadeOut{};                    //�t�F�[�h�A�E�g���ǂ���.

public:
	//�R���X�g���N�^.
	SoundData() : handle(-1), nowVol(-1), aftVol(-1) {};
	//set.
	void SetHandle(int _handle) {
		handle = _handle;
	}
	void SetIsFadeOut(BOOL _isFadeOut) {
		isFadeOut = _isFadeOut;
	}

	void Release(); //���.
	void Update();  //�X�V.

	void Play(BOOL isLoop, int volume);       //�Đ�.
	void Stop();                              //��~.
	void ChangeVolume(int volume, float sec); //���ʕύX�ݒ�.

	int  GetVolumeRange(int volume);          //�{�����[���l��L���͈͂ɕϊ�.
};

//�T�E���h�Ǘ��N���X.
class SoundST
{
private: //����.
	static SoundST self; //���g�̎���.

private: //�f�[�^.
	map<TCHAR*, SoundData> sound;

public:
	//���̂̎擾.
	static SoundST* GetPtr() {
		return &self;
	}
	//�f�X�g���N�^.
	~SoundST();

	int  LoadFile(const TCHAR fileName[], const TCHAR saveName[]);
	void Play    (const TCHAR saveName[], BOOL isLoop, int volume = 100);
	void Stop    (const TCHAR saveName[]);
	void Update  ();

	void ChangeVolume(const TCHAR saveName[], int volume, float sec = 0);	       //���ʂ�ύX.
	void FadeInPlay  (const TCHAR saveName[], int volume, float sec, BOOL isLoop); //�t�F�[�h�C���Đ�.
	void FadeOutPlay (const TCHAR saveName[], float sec);						   //�t�F�[�h�A�E�g����.
};