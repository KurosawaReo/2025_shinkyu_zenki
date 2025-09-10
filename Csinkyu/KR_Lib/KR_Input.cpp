/*
   - KR_Input.cpp - (DxLib)
   ver: 2025/09/10

   入力操作機能を追加します。
   (オブジェクト指向ver → KR_Object)

   TODO: Actionをどれか1つの最長時間ではなく, どれか1つでも押した総時間に変えたい.
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
	//アクション判定.
	bool InputMng::IsPushAction(MY_STRING name) {
		return (IsPushActionTime(name) > 0); //押してるならtrue.
	}
	int  InputMng::IsPushActionTime(MY_STRING name) {

		const auto data = actionData.find(name); //mapから名前検索.
		int pushTime = 0; //押している最長時間を記録する.

		//登録されたActionInfoを全ループ.
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

		return pushTime; //最長時間を返す.
	}

	//アクション追加.
	void InputMng::AddAction(MY_STRING name, KeyID id) {
		
		ActionInfo info{ KEY, _int(id) };
		actionData[name].push_back(info); //Key操作で登録.
	}
	void InputMng::AddAction(MY_STRING name, MouseID id) {

		ActionInfo info{ MOUSE, _int(id) };
		actionData[name].push_back(info); //Mouse操作で登録.
	}
	void InputMng::AddAction(MY_STRING name, PadXboxID id) {

		ActionInfo info{ PAD_XBOX, _int(id) };
		actionData[name].push_back(info); //Pad操作(xbox)で登録.
	}
	void InputMng::AddAction(MY_STRING name, PadSwitchID id) {

		ActionInfo info{ PAD_SWT, _int(id) };
		actionData[name].push_back(info); //Pad操作(switch)で登録.
	}
	void InputMng::AddAction(MY_STRING name, PadArcadeID id) {

		ActionInfo info{ PAD_ACD, _int(id) };
		actionData[name].push_back(info); //Pad操作(arcade)で登録.
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

		INT_XY pow{}; //移動力.

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
}