/*
   - KR_Input.cpp - (DxLib)
   ver: 2025/09/24

   入力操作機能を追加します。
   (オブジェクト指向ver → KR_Object)
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.hに入ってなければここで導入.
#endif
#include "KR_Input.h"

//KR_Libに使う用.
namespace KR_Lib
{
	//キー入力の判定.
	bool InputMng::IsPushKey(KeyID id) {
		return tmKey[_int(id)] > 0;
	}
	int  InputMng::IsPushKeyTime(KeyID id) {
		return tmKey[_int(id)];
	}
	//マウス入力の判定.
	bool InputMng::IsPushMouse(MouseID id) {
		return tmMouse[_int(id)] > 0;
	}
	int  InputMng::IsPushMouseTime(MouseID id) {
		return tmMouse[_int(id)];
	}
	//コントローラ入力の判定.
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
	//アクション判定.
	bool InputMng::IsPushAction(MY_STRING name) {
		return actions[name].time > 0; //押してる時間があればtrue.
	}
	int  InputMng::IsPushActionTime(MY_STRING name) {
		return actions[name].time;     //時間を返す.
	}

	//アクション追加.
	void InputMng::AddAction(MY_STRING name, KeyID id) {
		actions[name].inputs.push_back({ InputType::Key,       _int(id) }); //Key操作で登録.
	}
	void InputMng::AddAction(MY_STRING name, MouseID id) {
		actions[name].inputs.push_back({ InputType::Mouse,     _int(id) }); //Mouse操作で登録.
	}
	void InputMng::AddAction(MY_STRING name, PadXboxID id) {
		actions[name].inputs.push_back({ InputType::PadXbox,   _int(id) }); //Pad操作(xbox)で登録.
	}
	void InputMng::AddAction(MY_STRING name, PadSwitchID id) {
		actions[name].inputs.push_back({ InputType::PadSwitch, _int(id) }); //Pad操作(switch)で登録.
	}
	void InputMng::AddAction(MY_STRING name, PadArcadeID id) {
		actions[name].inputs.push_back({ InputType::PadArcade, _int(id) }); //Pad操作(arcade)で登録.
	}

	//キーボード:十字キー操作.
	void InputMng::MoveKey4Dir(DBL_XY* pos, float speed) {

		INT_XY pow{}; //移動力.

		//キー入力に応じて移動力を与える.
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

		//座標移動.
		pos->x += GetVector4Dir(pow).x * speed;
		pos->y += GetVector4Dir(pow).y * speed;
	}
	//コントローラ:十字キー操作.
	void InputMng::MovePad4Dir(DBL_XY* pos, float speed) {

		INT_XY pow{}; //移動力.

		//キー入力に応じて移動力を与える.
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

		//座標移動.
		pos->x += GetVector4Dir(pow).x * speed;
		pos->y += GetVector4Dir(pow).y * speed;
	}
	//コントローラ:スティック操作.
	void InputMng::MovePadStick(DBL_XY* pos, float speed) {
	
		//入力取得.
		DBL_XY vec = GetPadStickXY();
		//座標移動.
		pos->x += vec.x * speed;
		pos->y += vec.y * speed;
	}
	//移動4方向処理(斜め計算)
	DBL_XY InputMng::GetVector4Dir(INT_XY pow){

		DBL_XY move{}; //求めた移動量.

		//移動力があれば.
		if (pow.x != 0 || pow.y != 0) {
			//角度にする.
			double theta = atan2(pow.y, pow.x);
			//移動量を求める.
			move = { cos(theta), sin(theta) };
			//ほぼ0の値なら0と見なす(計算上誤差があるため)
			if (fabs(move.x) < 0.0001) { move.x = 0; }
			if (fabs(move.y) < 0.0001) { move.y = 0; }
		}

		return move;
	}

	//マウス座標取得.
	DBL_XY InputMng::GetMousePos(bool isValidX, bool isValidY) {
	
		DBL_XY pos{};

		//xを反映させる.
		if (isValidX) {
			pos.x = _dbl(mPos.x); //double型にして反映.
		}
		//yを反映させる.
		if (isValidY){
			pos.y = _dbl(mPos.y); //double型にして反映.
		}
		return pos;
	}
	//コントローラスティック操作取得.
	DBL_XY InputMng::GetPadStickXY() {
		//範囲-1000～1000を-1.0～1.0に変換.
		return { _dbl(stickVec.x)/1000, _dbl(stickVec.y)/1000 };
	}

	//ボタンの更新処理.
	void InputMng::UpdateKey() {
	
		char key[KEY_MAX];
		GetHitKeyStateAll(key); //押しているキー情報を取得.
	
		for (int i = 0; i < KEY_MAX; i++) {
			//押されているなら.
			if (key[i] != 0) {
				tmKey[i]++;   //カウント.
			}
			else {
				tmKey[i] = 0; //0秒にリセット.
			}
		}
	}
	//マウスの更新処理.
	void InputMng::UpdateMouse() {

		//マウス座標取得.
		GetMousePoint(&mPos.x, &mPos.y);

		for (int i = 0; i < MOUSE_MAX; i++) {
			//押されているなら.
			if ((GetMouseInput() & (1 << i)) != 0) { //And演算で抽出.
				tmMouse[i]++;   //カウント.
			}
			else {
				tmMouse[i] = 0; //0秒にリセット.
			}
		}
	}
	//コントローラの更新処理.
	void InputMng::UpdatePad() {

		//スティック入力取得.
		GetJoypadAnalogInput(&stickVec.x, &stickVec.y, DX_INPUT_PAD1);

		for (int i = 0; i < PAD_BTN_MAX; i++) {
			//押されているなら.
			if (GetJoypadInputState(DX_INPUT_PAD1) & (1 << i)) { //And演算で抽出.
				tmPadBtn[i]++;   //カウント.
			}
			else {
				tmPadBtn[i] = 0; //0秒にリセット.
			}
		}
	}
	//アクションの更新処理.
	void InputMng::UpdateAction() {

		//ActionDataを全ループ.
		for (auto& i : actions) {

			bool isPush = false; //何かを押しているかどうか.

			//登録されたInputDataを全ループ.
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
				//押しているなら.
				if (isPush) {
					break; //終了.
				}
			}

			//何か1つでも押していたなら.
			if (isPush) {
				i.second.time++;   //足す.
			}
			else {
				i.second.time = 0; //リセット.
			}
		}
	}
}