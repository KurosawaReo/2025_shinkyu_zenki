/*
   - mySoundST.cpp - (original)
   ver.2025/07/19

   DxLib: �I���W�i���T�E���h�@�\�̒ǉ�.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx���ɓ����ĂȂ���΂����œ���.
#endif
#include "mySoundST.h"

SoundST SoundST::self; //���̂̐錾.

//�T�E���h���.
void SoundData::Release() {
	//�f�[�^���o�^����Ă����.
	if (handle >= 0) {
		DeleteSoundMem(handle); //���.
	}
}
//�T�E���h�Đ�.
void SoundData::Play(BOOL isLoop) {
	//�f�[�^���o�^����Ă����.
	if (handle >= 0) {
		Stop();
		PlaySoundMem(handle, (isLoop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK));
	}
}
//�T�E���h��~.
void SoundData::Stop() {
	//�f�[�^���o�^����Ă����.
	if (handle >= 0) {
		StopSoundMem(handle);
	}
}

//�f�X�g���N�^.
SoundST::~SoundST() {

	//�T�E���h�f�[�^��S�Ď��o��.
	for (auto& i : sound) {
		i.second.Release(); //������s��.
	}
	sound.clear(); //�f�[�^����ɂ���.
}
//�T�E���h�ǂݍ���.
int SoundST::LoadFile(const TCHAR fileName[], const TCHAR saveName[]) {
	
	//�ǂݍ���.
	int load = LoadSoundMem(fileName);
	if (load < 0) {
		return -1; //-1: �ǂݍ��ݎ��s.
	}
	//�n���h����ۑ�.
	sound[(TCHAR*)saveName].handle = load;

	return 0; //����I��.
}
//�T�E���h�Đ�.
void SoundST::Play(const TCHAR saveName[], BOOL isLoop) {
	//���݂����.
	if (sound.count((TCHAR*)saveName) > 0) {
		sound[(TCHAR*)saveName].Play(isLoop); //�Đ�.
	}
}
//�T�E���h��~.
void SoundST::Stop(const TCHAR saveName[]) {
	//���݂����.
	if (sound.count((TCHAR*)saveName) > 0) {
		sound[(TCHAR*)saveName].Stop(); //��~.
	}
}