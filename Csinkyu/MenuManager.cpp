/*
   - MenuManager.cpp -
   メニューシーン.
*/
#include "MenuManager.h"

//初期化.
void MenuManager::Init() {
	_debug_log_str(_T("init\n")); //デバッグ表示.

	Reset(); //リセット処理.
}
//リセット.
void MenuManager::Reset() {

}
//更新.
void MenuManager::Update() {
	_debug_log_str(_T("update\n")); //デバッグ表示.
}
//描画.
void MenuManager::Draw() {
	_debug_log_str(_T("draw\n")); //デバッグ表示.
}