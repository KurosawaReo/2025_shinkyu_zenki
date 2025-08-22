/*
   - KR_Input.cpp - (kurosawa original)
   ver: 2025/08/22

   DxLib�p�̓��͑���@�\.
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.h�ɓ����ĂȂ���΂����œ���.
  using namespace KR_Lib;
#endif
#include "KR_Input.h"

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	Input Input::inst; //�C���X�^���X�𐶐�.

	//�L�[���͂̔���.
	bool Input::IsPushKey(KeyID id) {
		return (tmKey[id] > 0);    //�����Ă�Ȃ�true.
	}
	int  Input::IsPushKeyTime(KeyID id) {
		return tmKey[id];          //�����Ă��鎞��.
	}
	//�}�E�X���͂̔���.
	bool Input::IsPushMouse(MouseID id) {
		return (tmMouse[id] > 0);  //�����Ă�Ȃ�true.
	}
	int  Input::IsPushMouseTime(MouseID id) {
		return tmMouse[id];        //�����Ă��鎞��.
	}
	//�R���g���[�����͂̔���.
	bool Input::IsPushPadBtn(PadXboxID id) {
		return (tmPadBtn[id] > 0); //�����Ă�Ȃ�true.
	}
	bool Input::IsPushPadBtn(PadSwitchID id) {
		return (tmPadBtn[id] > 0); //�����Ă�Ȃ�true.
	}
	int  Input::IsPushPadBtnTime(PadXboxID id) {
		return tmPadBtn[id];       //�����Ă��鎞��.
	}
	int  Input::IsPushPadBtnTime(PadSwitchID id) {
		return tmPadBtn[id];       //�����Ă��鎞��.
	}

	//�}�E�X���W�擾.
	void Input::GetMousePos(DBL_XY* pos, bool isValidX, bool isValidY) {
	
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
	void Input::GetPadStickVec(DBL_XY* pos) {
		//�͈�-1000�`1000��-1.0�`1.0�ɕϊ�.
		pos->x = (double)stickVec.x/1000;
		pos->y = (double)stickVec.y/1000;
	}

	//�L�[�{�[�h:�\���L�[����.
	void Input::InputKey4Dir(DBL_XY* pos, float speed) {

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
	//�R���g���[��:�\���L�[����.
	void Input::InputPad4Dir(DBL_XY* pos, float speed) {

		INT_XY pow{};  //�ړ���.

		//�L�[���͂ɉ����Ĉړ��͂�^����.
		if (IsPushPadBtn(PAD_XBOX_UP)) {
			pow.y += -1;
		}
		if (IsPushPadBtn(PAD_XBOX_DOWN)) {
			pow.y += +1;
		}
		if (IsPushPadBtn(PAD_XBOX_LEFT)) {
			pow.x += -1;
		}
		if (IsPushPadBtn(PAD_XBOX_RIGHT)) {
			pow.x += +1;
		}

		//���W�ړ�.
		pos->x += Move4Dir(pow).x * speed;
		pos->y += Move4Dir(pow).y * speed;
	}
	//�R���g���[��:�X�e�B�b�N����.
	void Input::InputPadStick(DBL_XY* pos, float speed) {
	
		DBL_XY vec;
		GetPadStickVec(&vec); //���͎擾.

		//���W�ړ�.
		pos->x += vec.x * speed;
		pos->y += vec.y * speed;
	}
	//�ړ�4��������(�΂ߌv�Z)
	DBL_XY Input::Move4Dir(INT_XY pow){

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

	//�{�^���̍X�V����.
	void Input::UpdateKey() {
	
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
	void Input::UpdateMouse() {

		//�}�E�X���W�擾.
		GetMousePoint(&mPos.x, &mPos.y);

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
	void Input::UpdatePad() {

		//�X�e�B�b�N���͎擾.
		GetJoypadAnalogInput(&stickVec.x, &stickVec.y, DX_INPUT_PAD1);

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
}