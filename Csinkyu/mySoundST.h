/*
   - mySoundST.h - (original)
   ver.2025/07/24

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
	map<my_string, SoundData> sound;

public:
	//���̂̎擾.
	static SoundST* GetPtr() {
		return &self;
	}
	//�f�X�g���N�^.
	~SoundST();

	int  LoadFile(my_string fileName, my_string saveName);
	void Play    (my_string saveName, BOOL isLoop, int volume = 100);
	void Stop    (my_string saveName);
	void Update  ();

	void ChangeVolume(my_string saveName, int volume, float sec = 0);	       //���ʂ�ύX.
	void FadeInPlay  (my_string saveName, int volume, float sec, BOOL isLoop); //�t�F�[�h�C���Đ�.
	void FadeOutPlay (my_string saveName, float sec);						   //�t�F�[�h�A�E�g����.
};