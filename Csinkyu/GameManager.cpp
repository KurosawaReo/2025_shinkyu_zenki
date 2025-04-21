/*
   - GameManager.cpp -
   ゲーム全体管理.
*/
#include "GameManager.h"
#include "Player.h"

//初期化.
void GameManager::Init() {

}

//更新.
void GameManager::Update() {
	m_ang += 1;
}

//描画.
void GameManager::Draw() {
	INT_XY pos = { 100, 100 };
	DrawLineAng(pos, m_ang, 100, GetColor(0, 255, 0));
}