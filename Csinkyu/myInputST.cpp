/*
   - myInputST.cpp - (original)
   ver.2025/06/02

   DxLibで使う用のオリジナル入力関数.
*/
#if !defined DEF_GLOBAL_H
#include "Global.h" //stdafxがなければここで定義.
#endif

#include "myInputST.h"

#define KEY_MAX   256
#define MOUSE_MAX 3

int g_tmKey  [KEY_MAX];   //キーを押している時間.
int g_tmMouse[MOUSE_MAX]; //マウスを押下している時間.

//マウス入力の判定.
BOOL IsPushMouse(int num) {
	return (g_tmMouse[num] > 0); //押してるならTRUE.
}
int  IsPushMouseTime(int num) {
	return g_tmMouse[num];       //押している時間.
}
//キー入力の判定.
BOOL IsPushKey(int num) {
	return (g_tmKey[num] > 0);   //押してるならTRUE.
}
int  IsPushKeyTime(int num) {
	return g_tmKey[num];         //押している時間.
}

//マウス座標取得.
void GetMousePos(DBL_XY* pos) {

	INT_XY mPos;
	GetMousePoint(&mPos.x, &mPos.y); //取得.
	
	*pos = _dblXY(mPos); //double型にして代入.
}

//4方向移動操作.
void InputKey4Dir(DBL_XY* pos, float speed) {

	INT_XY pow{};  //移動力.
	DBL_XY move{}; //求めた移動量.

	//キー入力に応じて移動力を与える.
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

	//座標移動.
	pos->x += move.x * speed;
	pos->y += move.y * speed;
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