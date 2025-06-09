/*
   - myInputST.cpp - (original)
   ver.2025/06/02

   DxLib�Ŏg���p�̃I���W�i�����͊֐�.
*/
#if !defined DEF_GLOBAL_H
#include "Global.h" //stdafx���Ȃ���΂����Œ�`.
#endif

#include "myInputST.h"

#define KEY_MAX   256
#define MOUSE_MAX 3

int g_tmKey  [KEY_MAX];   //�L�[�������Ă��鎞��.
int g_tmMouse[MOUSE_MAX]; //�}�E�X���������Ă��鎞��.

//�}�E�X���͂̔���.
BOOL IsPushMouse(int num) {
	return (g_tmMouse[num] > 0); //�����Ă�Ȃ�TRUE.
}
int  IsPushMouseTime(int num) {
	return g_tmMouse[num];       //�����Ă��鎞��.
}
//�L�[���͂̔���.
BOOL IsPushKey(int num) {
	return (g_tmKey[num] > 0);   //�����Ă�Ȃ�TRUE.
}
int  IsPushKeyTime(int num) {
	return g_tmKey[num];         //�����Ă��鎞��.
}

//�}�E�X���W�擾.
void GetMousePos(DBL_XY* pos) {

	INT_XY mPos;
	GetMousePoint(&mPos.x, &mPos.y); //�擾.
	
	*pos = _dblXY(mPos); //double�^�ɂ��đ��.
}

//4�����ړ�����.
void InputKey4Dir(DBL_XY* pos, float speed) {

	INT_XY pow{};  //�ړ���.
	DBL_XY move{}; //���߂��ړ���.

	//�L�[���͂ɉ����Ĉړ��͂�^����.
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP ||CheckHitKey(KEY_INPUT_W)) {
		//printfDx(_T("a"));
		pow.y += -1;
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN ||CheckHitKey(KEY_INPUT_S)) {
		//printfDx(_T("b"));
		pow.y += +1;
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT ||CheckHitKey(KEY_INPUT_A)) {
		//printfDx(_T("c"));
		pow.x += -1;
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT ||CheckHitKey(KEY_INPUT_D)) {
		//printfDx(_T("d"));
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
void FixPosInArea(DBL_XY* pos, INT_XY size, int left, int up, int right, int down) {

	if (pos->x < left  + size.x/2) { pos->x = left  + size.x/2; }
	if (pos->y < up    + size.y/2) { pos->y = up    + size.y/2; }
	if (pos->x > right - size.x/2) { pos->x = right - size.x/2; }
	if (pos->y > down  - size.y/2) { pos->y = down  - size.y/2; }
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
//�}�E�X�̍X�V����.
void UpdateMouse() {

	for (int i = 0; i < MOUSE_MAX; i++) {
		//������Ă���Ȃ�.
		if ((GetMouseInput() & i) != 0) { //And���Z.
			g_tmMouse[i]++;   //�J�E���g.
		}
		else {
			g_tmMouse[i] = 0; //0�b�Ƀ��Z�b�g.
		}
	}
}