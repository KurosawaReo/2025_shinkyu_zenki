/*
   - myInputST.cpp - (original)
   ver.2025/05/15

   DxLibで使う用のオリジナル入力関数.
*/
#if !defined DEF_GLOBAL_H
#include "Global.h" //stdafxがなければここで定義.
#endif

#include "myInputST.h"

#define KEY_MAX 256
int g_tmKey[KEY_MAX]; //キーを押している時間.

//マウス入力の判定.
BOOL IsPushMouse(int num) {
	return ((GetMouseInput() & num) != 0); //And演算.
}
//キー入力の判定.
BOOL IsPushKey(int num) {
	return (g_tmKey[num] > 0); //押してるならTRUE.
}
int  IsPushKeyTime(int num) {
	return g_tmKey[num];       //押している時間.
}

//4方向移動操作.
void InputMove4Dir(DBL_XY* pos, int speed) {

	INT_XY pow{};  //移動力.
	DBL_XY move{}; //求めた移動量.

	//キー入力に応じて移動力を与える.
	if (CheckHitKey(KEY_INPUT_UP)) {
		pow.y += -1;
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		pow.y += +1;
	}
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		pow.x += -1;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
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
void MoveLimPos(DBL_XY* pos, INT_XY size, int lLim, int uLim, int rLim, int dLim) {

	if (pos->x < lLim + size.x/2) { pos->x = lLim + size.x/2; }
	if (pos->y < uLim + size.y/2) { pos->y = uLim + size.y/2; }
	if (pos->x > rLim - size.x/2) { pos->x = rLim - size.x/2; }
	if (pos->y > dLim - size.y/2) { pos->y = dLim - size.y/2; }
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