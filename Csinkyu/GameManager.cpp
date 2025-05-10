/*
   - GameManager.cpp -
   ゲーム全体管理.
*/
#include "GameManager.h"
#include "Player.h"
#include "Obstacle.h"
#include "Obstacle2.h"

//他classの実体.
Player player;
Obstacle  obstacle;
Obstacle2 obstacle2;

//初期化.
void GameManager::Init() {
	player.Init();
	obstacle.Init();
	obstacle2.Init();
}

//更新.
void GameManager::Update() {
	player.Update();
	obstacle.Update();
	obstacle2.Update();
}

//描画.
void GameManager::Draw() {
	player.Draw();
	obstacle.Draw();
	obstacle2.Draw();
}