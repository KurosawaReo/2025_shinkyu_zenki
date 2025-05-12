/*
   - GameManager.cpp -
   ゲーム全体管理.
*/
#include "GameManager.h"
#include "Player.h"
#include "Obstacle.h"
#include "Obstacle3.h"

//他classの実体.
Player    player;
Obstacle  obstacle;
Obstacle3 obstacle3;

//get.
float GameManager::GetTime() {
	return (float)(nowTime - stTime)/1000; //時刻の差.
}

//初期化.
void GameManager::Init() {

	srand((unsigned)time(NULL)); //乱数初期化.

	stTime = clock(); //開始時刻.

	player.Init();
	//obstacle.Init();
	obstacle3.Init(&player);
}

//更新.
void GameManager::Update() {

	//生存中のみ更新.
	if (player.GetActive()) {
		nowTime = clock(); //現在時刻.
	}

	player.Update();
	//obstacle.Update();
	obstacle3.Update();
}

//描画.
void GameManager::Draw() {
	player.Draw();
	//obstacle.Draw();
	obstacle3.Draw();

	//タイマー表示.
	DrawFormatString(0, 0, 0xFFFFFF, _T("time:%.3f"), GetTime());
}