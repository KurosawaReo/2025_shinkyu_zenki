/*
   - myInputST.cpp - (original)

   DxLib�Ŏg���p�̃I���W�i�����͊֐�.
*/
#if false
#include "stdafx.h" //stdafx������Ȃ炱�������g��.
#else
#include "DxLib.h"
#endif

#include "myInputST.h"

#define KEY_MAX 256

int g_tmKey[KEY_MAX]; //�L�[�������Ă��鎞��.

//�}�E�X���͂̔���.
BOOL IsPushMouse(int num) {
	return ((GetMouseInput() & num) != 0); //And���Z.
}
//�L�[���͂̔���.
BOOL IsPushKey(int num) {
	return (g_tmKey[num] > 0); //�����Ă�Ȃ�TRUE.
}
int  IsPushKeyTime(int num) {
	return g_tmKey[num];       //�����Ă��鎞��.
}

//�{�^���̍X�V����.
void UpdateKeys() {
	
	char key[KEY_MAX];
	GetHitKeyStateAll(key); //�����Ă���L�[�����擾.
	
	for (int i = 0; i < KEY_MAX; i++) {
		//������Ă���Ȃ�.
		if (key[i] != 0) {
			g_tmKey[i]++;   //�J�E���g.
		}
		else {
			g_tmKey[i] = 0; //0�b�Ƀ��Z�b�g.
		}
	}
}