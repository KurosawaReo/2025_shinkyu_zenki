/*
   - myInputST.cpp - (original)
   ver.2025/06/05

   DxLib�Ŏg���p�̃I���W�i�����͊֐�.
*/
#if !defined DEF_GLOBAL_H
#include "Global.h" //stdafx���Ȃ���΂����Œ�`.
#endif

#include "myInputST.h"

#define KEY_MAX     256
#define MOUSE_MAX   3
#define PAD_BTN_MAX 3

int g_tmKey   [KEY_MAX];     //�L�[�������Ă��鎞��.
int g_tmMouse [MOUSE_MAX];   //�}�E�X���������Ă��鎞��.
int g_tmPadBtn[PAD_BTN_MAX]; //�R���g���[���{�^�����������Ă��鎞��.

//�L�[���͂̔���.
BOOL IsPushKey(int keyNum) {
	return (g_tmKey[keyNum] > 0);     //�����Ă�Ȃ�TRUE.
}
int  IsPushKeyTime(int keyNum) {
	return g_tmKey[keyNum];           //�����Ă��鎞��.
}
//�}�E�X���͂̔���.
BOOL IsPushMouse(int mouseNum) {
	return (g_tmMouse[mouseNum] > 0); //�����Ă�Ȃ�TRUE.
}
int  IsPushMouseTime(int mouseNum) {
	return g_tmMouse[mouseNum];       //�����Ă��鎞��.
}
//�R���g���[�����͂̔���.
BOOL IsPushPadBtn(int btnNum) {
	return (g_tmPadBtn[btnNum] > 0);  //�����Ă�Ȃ�TRUE.
}
int  IsPushPadBtnTime(int btnNum) {
	return g_tmPadBtn[btnNum];        //�����Ă��鎞��.
}

//�}�E�X���W�擾.
void GetMousePos(DBL_XY* pos, BOOL isValidX, BOOL isValidY) {

	INT_XY mPos{};
	GetMousePoint(&mPos.x, &mPos.y); //�擾.
	
	//x�𔽉f������.
	if (isValidX) {
		pos->x = (double)mPos.x; //double�^�ɂ��Ĕ��f.
	}
	if (isValidY){
		pos->y = (double)mPos.y; //double�^�ɂ��Ĕ��f.
	}
}
//�R���g���[������擾.
void GetJoyPadStick() {

}

//4�����ړ�(�L�[����)
void InputKey4Dir(DBL_XY* pos, float speed) {

	INT_XY pow{};  //�ړ���.

	//�L�[���͂ɉ����Ĉړ��͂�^����.
	if (CheckHitKey(KEY_INPUT_UP)   ||CheckHitKey(KEY_INPUT_W)) {
		pow.y += -1;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) ||CheckHitKey(KEY_INPUT_S)) {
		pow.y += +1;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) ||CheckHitKey(KEY_INPUT_A)) {
		pow.x += -1;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)||CheckHitKey(KEY_INPUT_D)) {
		pow.x += +1;
	}

	//���W�ړ�.
	pos->x += Move4Dir(pow).x * speed;
	pos->y += Move4Dir(pow).y * speed;
}
//4�����ړ�(�R���g���[������)
void InputPad4Dir(DBL_XY* pos, float speed) {

	INT_XY pow{};  //�ړ���.

	//�L�[���͂ɉ����Ĉړ��͂�^����.
	if (IsPushPadBtn(PAD_INPUT_UP)) {
		pow.y += -1;
	}
	if (IsPushPadBtn(PAD_INPUT_DOWN)) {
		pow.y += +1;
	}
	if (IsPushPadBtn(PAD_INPUT_LEFT)) {
		pow.x += -1;
	}
	if (IsPushPadBtn(PAD_INPUT_RIGHT)) {
		pow.x += +1;
	}

	//���W�ړ�.
	pos->x += Move4Dir(pow).x * speed;
	pos->y += Move4Dir(pow).y * speed;
}
//�ړ�4��������(�΂ߌv�Z)
DBL_XY Move4Dir(INT_XY pow){

	DBL_XY move{}; //���߂��ړ���.

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

	return move;
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
//�R���g���[���̍X�V����.
void UpdatePadBtn() {

	for (int i = 0; i < PAD_BTN_MAX; i++) {
		//������Ă���Ȃ�.
		if (GetJoypadInputState(DX_INPUT_PAD1) & (2 >> i)) { //And���Z.
			g_tmPadBtn[i]++;   //�J�E���g.
		}
		else {
			g_tmPadBtn[i] = 0; //0�b�Ƀ��Z�b�g.
		}
	}
}