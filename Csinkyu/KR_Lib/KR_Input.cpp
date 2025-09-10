/*
   - KR_Input.cpp - (DxLib)
   ver: 2025/09/10

   ���͑���@�\��ǉ����܂��B
   (�I�u�W�F�N�g�w��ver �� KR_Object)

   TODO: Action���ǂꂩ1�̍Œ����Ԃł͂Ȃ�, �ǂꂩ1�ł������������Ԃɕς�����.
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
		return (tmKey[id] > 0);    //�����Ă�Ȃ�true.
	}
	int  InputMng::IsPushKeyTime(KeyID id) {
		return tmKey[id];          //�����Ă��鎞��.
	}
	//�}�E�X���͂̔���.
	bool InputMng::IsPushMouse(MouseID id) {
		return (tmMouse[id] > 0);  //�����Ă�Ȃ�true.
	}
	int  InputMng::IsPushMouseTime(MouseID id) {
		return tmMouse[id];        //�����Ă��鎞��.
	}
	//�R���g���[�����͂̔���.
	bool InputMng::IsPushPadBtn(PadXboxID id) {
		return (tmPadBtn[id] > 0); //�����Ă�Ȃ�true.
	}
	bool InputMng::IsPushPadBtn(PadSwitchID id) {
		return (tmPadBtn[id] > 0); //�����Ă�Ȃ�true.
	}
	bool InputMng::IsPushPadBtn(PadArcadeID id) {
		return (tmPadBtn[id] > 0); //�����Ă�Ȃ�true.
	}
	int  InputMng::IsPushPadBtnTime(PadXboxID id) {
		return tmPadBtn[id];       //�����Ă��鎞��.
	}
	int  InputMng::IsPushPadBtnTime(PadSwitchID id) {
		return tmPadBtn[id];       //�����Ă��鎞��.
	}
	int  InputMng::IsPushPadBtnTime(PadArcadeID id) {
		return tmPadBtn[id];       //�����Ă��鎞��.
	}
	//�A�N�V��������.
	bool InputMng::IsPushAction(MY_STRING name) {
		return (IsPushActionTime(name) > 0); //�����Ă�Ȃ�true.
	}
	int  InputMng::IsPushActionTime(MY_STRING name) {

		const auto data = actionData.find(name); //map���疼�O����.
		int pushTime = 0; //�����Ă���Œ����Ԃ��L�^����.

		//�o�^���ꂽActionInfo��S���[�v.
		for (auto& i : data->second) {
			switch (i.type)
			{
				case KEY: 
					pushTime = max(IsPushKeyTime   (static_cast<KeyID>      (i.id)), pushTime);
					break;
				case MOUSE: 
					pushTime = max(IsPushMouseTime (static_cast<MouseID>    (i.id)), pushTime);
					break;
				case PAD_XBOX:
					pushTime = max(IsPushPadBtnTime(static_cast<PadXboxID>  (i.id)), pushTime);
					break;
				case PAD_SWT:
					pushTime = max(IsPushPadBtnTime(static_cast<PadSwitchID>(i.id)), pushTime);
					break;
				case PAD_ACD:
					pushTime = max(IsPushPadBtnTime(static_cast<PadArcadeID>(i.id)), pushTime);
					break;

				default: assert(FALSE); break;
			}
		}

		return pushTime; //�Œ����Ԃ�Ԃ�.
	}

	//�A�N�V�����ǉ�.
	void InputMng::AddAction(MY_STRING name, KeyID id) {
		
		ActionInfo info{ KEY, _int(id) };
		actionData[name].push_back(info); //Key����œo�^.
	}
	void InputMng::AddAction(MY_STRING name, MouseID id) {

		ActionInfo info{ MOUSE, _int(id) };
		actionData[name].push_back(info); //Mouse����œo�^.
	}
	void InputMng::AddAction(MY_STRING name, PadXboxID id) {

		ActionInfo info{ PAD_XBOX, _int(id) };
		actionData[name].push_back(info); //Pad����(xbox)�œo�^.
	}
	void InputMng::AddAction(MY_STRING name, PadSwitchID id) {

		ActionInfo info{ PAD_SWT, _int(id) };
		actionData[name].push_back(info); //Pad����(switch)�œo�^.
	}
	void InputMng::AddAction(MY_STRING name, PadArcadeID id) {

		ActionInfo info{ PAD_ACD, _int(id) };
		actionData[name].push_back(info); //Pad����(arcade)�œo�^.
	}

	//�L�[�{�[�h:�\���L�[����.
	void InputMng::MoveKey4Dir(DBL_XY* pos, float speed) {

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
		pos->x += GetVector4Dir(pow).x * speed;
		pos->y += GetVector4Dir(pow).y * speed;
	}
	//�R���g���[��:�\���L�[����.
	void InputMng::MovePad4Dir(DBL_XY* pos, float speed) {

		INT_XY pow{}; //�ړ���.

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
}