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

//get.
float GameManager::GetTime() {
	return (float)(nowTime - stTime)/1000; //時刻の差.
}

//初期化.
void GameManager::Init() {
	stTime = clock(); //開始時刻.

	player.Init();
	obstacle.Init();
	obstacle2.Init();
}

//更新.
void GameManager::Update() {

	nowTime = clock(); //現在時刻.

	player.Update();
	obstacle.Update();
	obstacle2.Update();
}

//描画.
void GameManager::Draw() {
	player.Draw();
	obstacle.Draw();
	obstacle2.Draw();

	//タイマー表示.
	DrawFormatString(0, 0, 0xFFFFFF, _T("time:%.3f"), GetTime());
}