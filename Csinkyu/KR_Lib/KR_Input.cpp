/*
   - KR_Input.cpp - (DxLib)
   ver: 2025/09/24

   ���͑���@�\��ǉ����܂��B
   (�I�u�W�F�N�g�w��ver �� KR_Object)
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.h�ɓ����ĂȂ���΂����œ���.
#endif
#include "KR_Input.h"

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	//�L�[���͂̔���.
	bool InputMng::IsPushKey(KeyID id) {
		return tmKey[_int(id)] > 0;
	}
	int  InputMng::IsPushKeyTime(KeyID id) {
		return tmKey[_int(id)];
	}
	//�}�E�X���͂̔���.
	bool InputMng::IsPushMouse(MouseID id) {
		return tmMouse[_int(id)] > 0;
	}
	int  InputMng::IsPushMouseTime(MouseID id) {
		return tmMouse[_int(id)];
	}
	//�R���g���[�����͂̔���.
	bool InputMng::IsPushPadBtn(PadXboxID id) {
		return tmPadBtn[_int(id)] > 0;
	}
	bool InputMng::IsPushPadBtn(PadSwitchID id) {
		return tmPadBtn[_int(id)] > 0;
	}
	bool InputMng::IsPushPadBtn(PadArcadeID id) {
		return tmPadBtn[_int(id)] > 0;
	}
	int  InputMng::IsPushPadBtnTime(PadXboxID id) {
		return tmPadBtn[_int(id)];
	}
	int  InputMng::IsPushPadBtnTime(PadSwitchID id) {
		return tmPadBtn[_int(id)];
	}
	int  InputMng::IsPushPadBtnTime(PadArcadeID id) {
		return tmPadBtn[_int(id)];
	}
	//�A�N�V��������.
	bool InputMng::IsPushAction(MY_STRING name) {
		return actions[name].time > 0; //�����Ă鎞�Ԃ������true.
	}
	int  InputMng::IsPushActionTime(MY_STRING name) {
		return actions[name].time;     //���Ԃ�Ԃ�.
	}

	//�A�N�V�����ǉ�.
	void InputMng::AddAction(MY_STRING name, KeyID id) {
		actions[name].inputs.push_back({ InputType::Key,       _int(id) }); //Key����œo�^.
	}
	void InputMng::AddAction(MY_STRING name, MouseID id) {
		actions[name].inputs.push_back({ InputType::Mouse,     _int(id) }); //Mouse����œo�^.
	}
	void InputMng::AddAction(MY_STRING name, PadXboxID id) {
		actions[name].inputs.push_back({ InputType::PadXbox,   _int(id) }); //Pad����(xbox)�œo�^.
	}
	void InputMng::AddAction(MY_STRING name, PadSwitchID id) {
		actions[name].inputs.push_back({ InputType::PadSwitch, _int(id) }); //Pad����(switch)�œo�^.
	}
	void InputMng::AddAction(MY_STRING name, PadArcadeID id) {
		actions[name].inputs.push_back({ InputType::PadArcade, _int(id) }); //Pad����(arcade)�œo�^.
	}

	//�L�[�{�[�h:�\���L�[����.
	void InputMng::MoveKey4Dir(DBL_XY* pos, float speed) {

		INT_XY pow{}; //�ړ���.

		//�L�[���͂ɉ����Ĉړ��͂�^����.
		if (IsPushKey(KeyID::Up)   ||IsPushKey(KeyID::W)) {
			pow.y += -1;
		}
		if (IsPushKey(KeyID::Down) ||IsPushKey(KeyID::S)) {
			pow.y += +1;
		}
		if (IsPushKey(KeyID::Left) ||IsPushKey(KeyID::A)) {
			pow.x += -1;
		}
		if (IsPushKey(KeyID::Right)||IsPushKey(KeyID::D)) {
			pow.x += +1;
		}

		//���W�ړ�.
		pos->x += GetVector4Dir(pow).x * speed;
		pos->y += GetVector4Dir(pow).y * speed;
	}
	//�R���g���[��:�\���L�[����.
	void InputMng::MovePad4Dir(DBL_XY* pos, float speed) {

		INT_XY pow{}; //�ړ���.

		//�L�[���͂ɉ����Ĉړ��͂�^����.
		if (IsPushPadBtn(PadXboxID::Up)) {
			pow.y += -1;
		}
		if (IsPushPadBtn(PadXboxID::Down)) {
			pow.y += +1;
		}
		if (IsPushPadBtn(PadXboxID::Left)) {
			pow.x += -1;
		}
		if (IsPushPadBtn(PadXboxID::Right)) {
			pow.x += +1;
		}

		//���W�ړ�.
		pos->x += GetVector4Dir(pow).x * speed;
		pos->y += GetVector4Dir(pow).y * speed;
	}
	//�R���g���[��:�X�e�B�b�N����.
	void InputMng::MovePadStick(DBL_XY* pos, float speed) {
	
		//���͎擾.
		DBL_XY vec = GetPadStickXY();
		//���W�ړ�.
		pos->x += vec.x * speed;
		pos->y += vec.y * speed;
	}
	//�ړ�4��������(�΂ߌv�Z)
	DBL_XY InputMng::GetVector4Dir(INT_XY pow){

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

	//�}�E�X���W�擾.
	DBL_XY InputMng::GetMousePos(bool isValidX, bool isValidY) {
	
		DBL_XY pos{};

		//x�𔽉f������.
		if (isValidX) {
			pos.x = _dbl(mPos.x); //double�^�ɂ��Ĕ��f.
		}
		//y�𔽉f������.
		if (isValidY){
			pos.y = _dbl(mPos.y); //double�^�ɂ��Ĕ��f.
		}
		return pos;
	}
	//�R���g���[���X�e�B�b�N����擾.
	DBL_XY InputMng::GetPadStickXY() {
		//�͈�-1000�`1000��-1.0�`1.0�ɕϊ�.
		return { _dbl(stickVec.x)/1000, _dbl(stickVec.y)/1000 };
	}

	//�{�^���̍X�V����.
	void InputMng::UpdateKey() {
	
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
	void InputMng::UpdateMouse() {

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
	void InputMng::UpdatePad() {

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
	//�A�N�V�����̍X�V����.
	void InputMng::UpdateAction() {

		//ActionData��S���[�v.
		for (auto& i : actions) {

			bool isPush = false; //�����������Ă��邩�ǂ���.

			//�o�^���ꂽInputData��S���[�v.
			for (auto& j : i.second.inputs) {

				switch (j.type)
				{
					case InputType::Key:       isPush = IsPushKey   (static_cast<KeyID>      (j.id)); break;
					case InputType::Mouse:     isPush = IsPushMouse (static_cast<MouseID>    (j.id)); break;
					case InputType::PadXbox:   isPush = IsPushPadBtn(static_cast<PadXboxID>  (j.id)); break;
					case InputType::PadSwitch: isPush = IsPushPadBtn(static_cast<PadSwitchID>(j.id)); break;
					case InputType::PadArcade: isPush = IsPushPadBtn(static_cast<PadArcadeID>(j.id)); break;

					default: assert(FALSE); break;
				}
				//�����Ă���Ȃ�.
				if (isPush) {
					break; //�I��.
				}
			}

			//����1�ł������Ă����Ȃ�.
			if (isPush) {
				i.second.time++;   //����.
			}
			else {
				i.second.time = 0; //���Z�b�g.
			}
		}
	}
}