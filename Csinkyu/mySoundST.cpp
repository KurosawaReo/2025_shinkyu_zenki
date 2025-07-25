/*
   - mySoundST.cpp - (original)
   ver.2025/07/24

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
//�T�E���h�X�V.
void SoundData::Update() {
	
	//���ʂ��ω�����Ȃ�.
	if (nowVol != aftVol) {
		//�ω����Ԃ�����.
		if (aftUS > 0) {

			LONGLONG us = timer.GetPassTime(); //�o�ߎ��ԓ���.

			//���݂̃{�����[�������߂�.
			assert(aftUS != 0);                                            //0���΍�.
			int vol = (int)(nowVol - (nowVol - aftVol) * (float)us/aftUS); //now + �ω��� * �ω����Ԋ���.

			//�ω����I�������.
			if (us >= aftUS) {
				vol    = aftVol; //�ڕW���ʂɌŒ�.
				nowVol = aftVol; //�ω���̉��ʂ�ݒ肵�Ă���.
				aftUS  = 0;      //�������ʕω����Ȃ�.
				//�t�F�[�h�A�E�g�Ȃ�.
				if (isFadeOut) {
					Stop(); //��~����.
				}
			}

			//�f�[�^���o�^����Ă����.
			if (handle >= 0) {
				assert(0 <= vol && vol <= 255);    //�͈͓��`�F�b�N.
				ChangeVolumeSoundMem(vol, handle); //���ʔ��f.
			}
		}
		//�ω����Ԃ��Ȃ�.
		else {
			ChangeVolumeSoundMem(aftVol, handle); //���ʔ��f.
			nowVol = aftVol;                      //�ω���̉��ʂɐݒ�.
		}
	}
}
//�T�E���h�Đ�.
void SoundData::Play(BOOL isLoop, int volume) {

	//�f�[�^���o�^����Ă����.
	if (handle >= 0) {
		//���ʕύX.
		int vol255 = GetVolumeRange(volume);  //0�`255�ɕϊ�.
		ChangeVolumeSoundMem(vol255, handle); //���ʔ��f.
		nowVol = aftVol = vol255;             //���ʂ�ۑ�.

		PlaySoundMem(handle, (isLoop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK));
	}
}
//�T�E���h��~.
void SoundData::Stop() {

	//�f�[�^���o�^����Ă����.
	if (handle >= 0) {
		//��~.
		StopSoundMem(handle);
		//���Z�b�g.
		nowVol = -1;
		aftVol = -1;
		isFadeOut = FALSE;
	}
}
//���ʕύX�ݒ�.
void SoundData::ChangeVolume(int volume, float sec) {
	
	nowVol = GetVolumeSoundMem2(handle); //���݂̉���.
	aftVol = GetVolumeRange(volume);     //�ω���̉���.
	aftUS  = (LONGLONG)(1000000 * sec);  //�ω�����.
	//�ω����Ԃ�����Ȃ�.
	if (aftUS > 0) {
		timer.Start(); //�^�C�}�[�J�n.
	}
}
//�{�����[���l��L���͈͂ɕϊ�.
int SoundData::GetVolumeRange(int volume) {

	int vol255 = 255 * volume/100;        //�L���͈�(0�`255)�ɕϊ�.
	assert(0 <= vol255 && vol255 <= 255); //�͈͓��`�F�b�N.
	return vol255;
}

//�f�X�g���N�^.
SoundST::~SoundST() {

	//�T�E���h�f�[�^��S�Ď��o��.
	for (auto& i : sound) {
		i.second.Release(); //�e�T�E���h�̉��.
	}
	sound.clear(); //�f�[�^����ɂ���.
}
//�T�E���h�ǂݍ���.
int SoundST::LoadFile(my_string fileName, my_string saveName) {
	
	//�ǂݍ���.
	int load = LoadSoundMem(fileName.c_str());
	if (load < 0) {
		return -1; //-1: �ǂݍ��ݎ��s.
	}
	//�n���h����ۑ�.
	sound[saveName].SetHandle(load);

	return 0; //����I��.
}
//�T�E���h�Đ�.
void SoundST::Play(my_string saveName, BOOL isLoop, int volume) {
	//���݂����.
	if (sound.count(saveName) > 0) {
		sound[saveName].Play(isLoop, volume); //�Đ�.
	}
}
//�T�E���h��~.
void SoundST::Stop(my_string saveName) {
	//���݂����.
	if (sound.count(saveName) > 0) {
		sound[saveName].Stop(); //��~.
	}
}
//�T�E���h�X�V.
void SoundST::Update() {

	//�T�E���h�f�[�^��S�Ď��o��.
	for (auto& i : sound) {
		i.second.Update(); //�e�T�E���h�̍X�V.
	}
}

//���ʂ�ύX.
void SoundST::ChangeVolume(my_string saveName, int volume, float sec) {
	
	sound[saveName].ChangeVolume(volume, sec); //�ύX�ݒ�.
}
//�t�F�[�h�C���Đ�.
void SoundST::FadeInPlay(my_string saveName, int volume, float sec, BOOL isLoop) {

	sound[saveName].Play(isLoop, 0);           //�ŏ��͉���0�ōĐ�.
	sound[saveName].ChangeVolume(volume, sec); //���X�ɑ傫��.
}
//�t�F�[�h�A�E�g����.
void SoundST::FadeOutPlay(my_string saveName, float sec) {

	sound[saveName].ChangeVolume(0, sec); //���X�ɏ�����.
	sound[saveName].SetIsFadeOut(TRUE);   //�t�F�[�h�A�E�g���[�h��.
}