/*
   - GameManager.cpp -
   ゲーム全体管理.
*/
#include "GameManager.h"
#include "Player.h"
#include "Obstacle.h"

//他classの実体.
Player   player;
Obstacle obstacle;

//初期化.
void GameManager::Init() {
	player.Init();
    obstacle.Init();
}

//更新.
void GameManager::Update() {
	player.Update();
	obstacle.Update();
}

//描画.
void GameManager::Draw() {
	player.Draw();
	obstacle.Draw();
}