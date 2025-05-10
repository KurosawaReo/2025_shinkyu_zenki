/*
   - myInputST.cpp - (original)

   DxLibで使う用のオリジナル入力関数.
*/
#if false
#include "stdafx.h" //stdafxがあるならこっちを使う.
#else
#include "DxLib.h"
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