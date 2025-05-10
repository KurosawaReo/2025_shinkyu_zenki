/*
   - GameManager.cpp -
   ゲーム全体管理.
*/
#include "GameManager.h"
#include "Player.h"
#include "Obstacle2.h"

Player player;
Obstacle2 obstacle2;

//初期化.
void GameManager::Init() {
	player.Init();
	obstacle2.Init();
}

//更新.
void GameManager::Update() {
	player.Update();
	obstacle2.Update();
}

//描画.
void GameManager::Draw() {
	player.Draw();
	obstacle2.Draw();
}