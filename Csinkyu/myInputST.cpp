/*
   - myInputST.cpp - (original)
   ver.2025/06/18

   DxLib�Ŏg���p�̃I���W�i�����͊֐�.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx���Ȃ���΂����Œ�`.
#endif

#include "myInputST.h"

InputST InputST::self; //���̂̐錾.

//�L�[���͂̔���.
BOOL InputST::IsPushKey(KEY_ID id) {
	return (tmKey[id] > 0);     //�����Ă�Ȃ�TRUE.
}
int  InputST::IsPushKeyTime(KEY_ID id) {
	return tmKey[id];           //�����Ă��鎞��.
}
//�}�E�X���͂̔���.
BOOL InputST::IsPushMouse(MOUSE_ID id) {
	int num = (int)log2(id);    //2�i��bit�������ڂ��ɕϊ�.
	return (tmMouse[num] > 0);  //�����Ă�Ȃ�TRUE.
}
int  InputST::IsPushMouseTime(MOUSE_ID id) {
	int num = (int)log2(id);    //2�i��bit�������ڂ��ɕϊ�.
	return tmMouse[num];        //�����Ă��鎞��.
}
//�R���g���[�����͂̔���.
BOOL InputST::IsPushPadBtn(PAD_BTN_ID id) {
	int num = (int)log2(id);    //2�i��bit�������ڂ��ɕϊ�.
	return (tmPadBtn[num] > 0); //�����Ă��鎞��.
}
int  InputST::IsPushPadBtnTime(PAD_BTN_ID id) {
	int num = (int)log2(id);    //2�i��bit�������ڂ��ɕϊ�.
	return tmPadBtn[num];       //�����Ă��鎞��.
}

//�}�E�X���W�擾.
void InputST::GetMousePos(DBL_XY* pos, BOOL isValidX, BOOL isValidY) {
	
	//x�𔽉f������.
	if (isValidX) {
		pos->x = (double)mPos.x; //double�^�ɂ��Ĕ��f.
	}
	//y�𔽉f������.
	if (isValidY){
		pos->y = (double)mPos.y; //double�^�ɂ��Ĕ��f.
	}
}
//�R���g���[���X�e�B�b�N����擾.
void InputST::GetPadStick() {

}

//4�����ړ�(�L�[����)
void InputST::InputKey4Dir(DBL_XY* pos, float speed) {

	INT_XY pow{}; //�ړ���.

	//�L�[���͂ɉ����Ĉړ��͂�^����.
	if (IsPushKey(KEY_UP)   ||IsPushKey(KEY_W)) {
		pow.y += -1;
	}
	if (IsPushKey(KEY_DOWN) ||IsPushKey(KEY_S)) {
		pow.y += +1;
	}
	if (IsPushKey(KEY_LEFT) ||IsPushKey(KEY_A)) {
		pow.x += -1;
	}
	if (IsPushKey(KEY_RIGHT)||IsPushKey(KEY_D)) {
		pow.x += +1;
	}

	//���W�ړ�.
	pos->x += Move4Dir(pow).x * speed;
	pos->y += Move4Dir(pow).y * speed;
}
//4�����ړ�(�R���g���[������)
void InputST::InputPad4Dir(DBL_XY* pos, float speed) {

	INT_XY pow{};  //�ړ���.

	//�L�[���͂ɉ����Ĉړ��͂�^����.
	if (IsPushPadBtn(PAD_BTN_UP)) {
		pow.y += -1;
	}
	if (IsPushPadBtn(PAD_BTN_DOWN)) {
		pow.y += +1;
	}
	if (IsPushPadBtn(PAD_BTN_LEFT)) {
		pow.x += -1;
	}
	if (IsPushPadBtn(PAD_BTN_RIGHT)) {
		pow.x += +1;
	}

	//���W�ړ�.
	pos->x += Move4Dir(pow).x * speed;
	pos->y += Move4Dir(pow).y * speed;
}
//�ړ�4��������(�΂ߌv�Z)
DBL_XY InputST::Move4Dir(INT_XY pow){

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
void InputST::FixPosInArea(DBL_XY* pos, INT_XY size, int left, int up, int right, int down) {

	if (pos->x < left  + size.x/2) { pos->x = left  + size.x/2; }
	if (pos->y < up    + size.y/2) { pos->y = up    + size.y/2; }
	if (pos->x > right - size.x/2) { pos->x = right - size.x/2; }
	if (pos->y > down  - size.y/2) { pos->y = down  - size.y/2; }
}

//�{�^���̍X�V����.
void InputST::UpdateKey() {
	
	char key[KEY_MAX];
	GetHitKeyStateAll(key); //�����Ă���L�[�����擾.
	
	for (int i = 0; i < KEY_MAX; i++) {
		//������Ă���Ȃ�.
		if (key[i] != 0) {
			tmKey[i]++;   //�J�E���g.
		}
		else {
			tmKey[i] = 0; //0�b�Ƀ��Z�b�g.
		}
	}
}
//�}�E�X�̍X�V����.
void InputST::UpdateMouse() {

	GetMousePoint(&mPos.x, &mPos.y); //�}�E�X���W�擾.

	for (int i = 0; i < MOUSE_MAX; i++) {
		//������Ă���Ȃ�.
		if ((GetMouseInput() & (1 << i)) != 0) { //And���Z�Œ��o.
			tmMouse[i]++;   //�J�E���g.
		}
		else {
			tmMouse[i] = 0; //0�b�Ƀ��Z�b�g.
		}
	}
}
//�R���g���[���̍X�V����.
void InputST::UpdatePadBtn() {

	for (int i = 0; i < PAD_BTN_MAX; i++) {
		//������Ă���Ȃ�.
		if (GetJoypadInputState(DX_INPUT_PAD1) & (1 << i)) { //And���Z�Œ��o.
			tmPadBtn[i]++;   //�J�E���g.
		}
		else {
			tmPadBtn[i] = 0; //0�b�Ƀ��Z�b�g.
		}
	}
}