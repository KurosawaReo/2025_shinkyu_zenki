/*
   - myInputST.cpp - (original)

   DxLib�Ŏg���p�̃I���W�i�����͊֐�.
   2025/05/14
*/
#if false
  #include "stdafx.h" //stdafx������Ȃ炱�������g��.
#else
  #include <math.h>
  #include "DxLib.h"
#endif

#include "myInputST.h"

//int�^�ϊ��}�N��.
#define _int(n) (int)(round(n))

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

//4�����ړ�����.
void InputMove4Dir(DBL_XY* pos, int speed) {

	INT_XY pow{};  //�ړ���.
	DBL_XY move{}; //���߂��ړ���.

	//�L�[���͂ɉ����Ĉړ��͂�^����.
	if (CheckHitKey(KEY_INPUT_UP)) {
		pow.y += -1;
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		pow.y += +1;
	}
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		pow.x += -1;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		pow.x += +1;
	}

	//�ړ��͂������.
	if (pow.x != 0 || pow.y != 0) {

		//�p�x�ɂ���.
		double theta = atan2(pow.y, pow.x);
		//�ړ��ʂ����߂�.
		move = { cos(theta), sin(theta) };
		//�ق�0�̒l�Ȃ�0�ƌ��Ȃ�(�v�Z��덷�����邽��)
		if (fabs(move.x) < 0.0001) { move.x = 0; }
		if (fabs(move.y) < 0.0001) { move.y = 0; }
	}

	//���W�ړ�.
	pos->x += move.x * speed;
	pos->y += move.y * speed;
}
//�ړ��\�͈͓��ɕ␳����.
void MoveLimPos(DBL_XY* pos, INT_XY size, int lLim, int uLim, int rLim, int dLim) {

	if (pos->x < lLim + size.x/2) { pos->x = lLim + size.x/2; }
	if (pos->y < uLim + size.y/2) { pos->y = uLim + size.y/2; }
	if (pos->x > rLim - size.x/2) { pos->x = rLim - size.x/2; }
	if (pos->y > dLim - size.y/2) { pos->y = dLim - size.y/2; }
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