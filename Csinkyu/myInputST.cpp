/*
   - myInputST.cpp - (original)
   ver.2025/06/05

   DxLibで使う用のオリジナル入力関数.
*/
#if !defined DEF_GLOBAL_H
#include "Global.h" //stdafxがなければここで定義.
#endif

#include "myInputST.h"

#define KEY_MAX     256
#define MOUSE_MAX   3
#define PAD_BTN_MAX 3

int g_tmKey   [KEY_MAX];     //キーを押している時間.
int g_tmMouse [MOUSE_MAX];   //マウスを押下している時間.
int g_tmPadBtn[PAD_BTN_MAX]; //コントローラボタンを押下している時間.

//キー入力の判定.
BOOL IsPushKey(int keyNum) {
	return (g_tmKey[keyNum] > 0);     //押してるならTRUE.
}
int  IsPushKeyTime(int keyNum) {
	return g_tmKey[keyNum];           //押している時間.
}
//マウス入力の判定.
BOOL IsPushMouse(int mouseNum) {
	return (g_tmMouse[mouseNum] > 0); //押してるならTRUE.
}
int  IsPushMouseTime(int mouseNum) {
	return g_tmMouse[mouseNum];       //押している時間.
}
//コントローラ入力の判定.
BOOL IsPushPadBtn(int btnNum) {
	return (g_tmPadBtn[btnNum] > 0);  //押してるならTRUE.
}
int  IsPushPadBtnTime(int btnNum) {
	return g_tmPadBtn[btnNum];        //押している時間.
}

//マウス座標取得.
void GetMousePos(DBL_XY* pos, BOOL isValidX, BOOL isValidY) {

	INT_XY mPos{};
	GetMousePoint(&mPos.x, &mPos.y); //取得.
	
	//xを反映させる.
	if (isValidX) {
		pos->x = (double)mPos.x; //double型にして反映.
	}
	if (isValidY){
		pos->y = (double)mPos.y; //double型にして反映.
	}
}
//コントローラ操作取得.
void GetJoyPadStick() {

}

//4方向移動(キー操作)
void InputKey4Dir(DBL_XY* pos, float speed) {

	INT_XY pow{};  //移動力.

	//キー入力に応じて移動力を与える.
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

	//座標移動.
	pos->x += Move4Dir(pow).x * speed;
	pos->y += Move4Dir(pow).y * speed;
}
//4方向移動(コントローラ操作)
void InputPad4Dir(DBL_XY* pos, float speed) {

	INT_XY pow{};  //移動力.

	//キー入力に応じて移動力を与える.
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

	//座標移動.
	pos->x += Move4Dir(pow).x * speed;
	pos->y += Move4Dir(pow).y * speed;
}
//移動4方向処理(斜め計算)
DBL_XY Move4Dir(INT_XY pow){

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

//移動可能範囲内に補正する.
void FixPosInArea(DBL_XY* pos, INT_XY size, int left, int up, int right, int down) {

	if (pos->x < left  + size.x/2) { pos->x = left  + size.x/2; }
	if (pos->y < up    + size.y/2) { pos->y = up    + size.y/2; }
	if (pos->x > right - size.x/2) { pos->x = right - size.x/2; }
	if (pos->y > down  - size.y/2) { pos->y = down  - size.y/2; }
}

//ボタンの更新処理.
void UpdateKeys() {
	
	char key[KEY_MAX];
	GetHitKeyStateAll(key); //押しているキー情報を取得.
	
	for (int i = 0; i < KEY_MAX; i++) {
		//押されているなら.
		if (key[i] != 0) {
			g_tmKey[i]++;   //カウント.
		}
		else {
			g_tmKey[i] = 0; //0秒にリセット.
		}
	}
}
//マウスの更新処理.
void UpdateMouse() {

	for (int i = 0; i < MOUSE_MAX; i++) {
		//押されているなら.
		if ((GetMouseInput() & i) != 0) { //And演算.
			g_tmMouse[i]++;   //カウント.
		}
		else {
			g_tmMouse[i] = 0; //0秒にリセット.
		}
	}
}
//コントローラの更新処理.
void UpdatePadBtn() {

	for (int i = 0; i < PAD_BTN_MAX; i++) {
		//押されているなら.
		if (GetJoypadInputState(DX_INPUT_PAD1) & (2 >> i)) { //And演算.
			g_tmPadBtn[i]++;   //カウント.
		}
		else {
			g_tmPadBtn[i] = 0; //0秒にリセット.
		}
	}
}