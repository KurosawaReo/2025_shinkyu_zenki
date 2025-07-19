/*
   - mySoundST.h - (original)
   ver.2025/07/19

   DxLib: �I���W�i���T�E���h�@�\�̒ǉ�.
*/
#pragma once

//�T�E���h�N���X.
class SoundData
{
	friend class SoundST; //�Ǘ��N���X�̂݃A�N�Z�X����.

private:
	int handle;

public:
	SoundData() : handle(-1){};

	void Release();         //���.
	void Play(BOOL isLoop); //�Đ�.
	void Stop();            //��~.
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
	void Play    (const TCHAR saveName[], BOOL isLoop);
	void Stop    (const TCHAR saveName[]);
};