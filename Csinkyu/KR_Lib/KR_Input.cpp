/*
   - KR_Input.cpp - (DxLib)
   ver: 2025/08/27

   入力操作機能を追加します.
   (オブジェクト指向ver → KR_Object)
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.hに入ってなければここで導入.
  using namespace KR_Lib;
#endif
#include "KR_Input.h"

//KR_Libに使う用.
namespace KR_Lib
{
	InputMng InputMng::inst; //インスタンスを生成.

	//キー入力の判定.
	bool InputMng::IsPushKey(KeyID id) {
		return (tmKey[id] > 0);    //押してるならtrue.
	}
	int  InputMng::IsPushKeyTime(KeyID id) {
		return tmKey[id];          //押している時間.
	}
	//マウス入力の判定.
	bool InputMng::IsPushMouse(MouseID id) {
		return (tmMouse[id] > 0);  //押してるならtrue.
	}
	int  InputMng::IsPushMouseTime(MouseID id) {
		return tmMouse[id];        //押している時間.
	}
	//コントローラ入力の判定.
	bool InputMng::IsPushPadBtn(PadXboxID id) {
		return (tmPadBtn[id] > 0); //押してるならtrue.
	}
	bool InputMng::IsPushPadBtn(PadSwitchID id) {
		return (tmPadBtn[id] > 0); //押してるならtrue.
	}
	bool InputMng::IsPushPadBtn(PadArcadeID id) {
		return (tmPadBtn[id] > 0); //押してるならtrue.
	}
	int  InputMng::IsPushPadBtnTime(PadXboxID id) {
		return tmPadBtn[id];       //押している時間.
	}
	int  InputMng::IsPushPadBtnTime(PadSwitchID id) {
		return tmPadBtn[id];       //押している時間.
	}
	int  InputMng::IsPushPadBtnTime(PadArcadeID id) {
		return tmPadBtn[id];       //押している時間.
	}

	//マウス座標取得.
	void InputMng::GetMousePos(DBL_XY* pos, bool isValidX, bool isValidY) {
	
		//xを反映させる.
		if (isValidX) {
			pos->x = (double)mPos.x; //double型にして反映.
		}
		//yを反映させる.
		if (isValidY){
			pos->y = (double)mPos.y; //double型にして反映.
		}
	}
	//コントローラスティック操作取得.
	void InputMng::GetPadStickXY(DBL_XY* pos) {
		//範囲-1000～1000を-1.0～1.0に変換.
		pos->x = (double)stickVec.x/1000;
		pos->y = (double)stickVec.y/1000;
	}

	//キーボード:十字キー操作.
	void InputMng::MoveKey4Dir(DBL_XY* pos, float speed) {

		INT_XY pow{}; //移動力.

		//キー入力に応じて移動力を与える.
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

		//座標移動.
		pos->x += GetVector4Dir(pow).x * speed;
		pos->y += GetVector4Dir(pow).y * speed;
	}
	//コントローラ:十字キー操作.
	void InputMng::MovePad4Dir(DBL_XY* pos, float speed) {

		INT_XY pow{};  //移動力.

		//キー入力に応じて移動力を与える.
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

		//座標移動.
		pos->x += GetVector4Dir(pow).x * speed;
		pos->y += GetVector4Dir(pow).y * speed;
	}
	//コントローラ:スティック操作.
	void InputMng::MovePadStick(DBL_XY* pos, float speed) {
	
		DBL_XY vec;
		GetPadStickXY(&vec); //入力取得.

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
}