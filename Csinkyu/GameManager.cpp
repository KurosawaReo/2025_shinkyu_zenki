/*
   - GameManager.cpp -
   ゲームの全体管理.
*/
#include "GameManager.h"
#include "Player.h"

//初期化.
void InitGame() {
	InitPlayer();
}

//更新.
void UpdateGame() {
	UpdatePlayer();
}

//描画.
void DrawGame() {
	DrawPlayer();
}