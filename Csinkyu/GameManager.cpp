/*
   - GameManager.cpp -
   ゲーム全体管理.
*/
#define ODAZIMA //これを定義すると小田島作の障害物に切り替え.

#include "GameManager.h"
#include "Player.h"
#include "Obstacle.h"
#if defined ODAZIMA
#include "Obstacle2.h"
#else
#include "Obstacle3.h"
#endif

//他classの実体.
Player    player;
Obstacle  obstacle;

#if defined ODAZIMA
Obstacle2 obstacle2;
#else
Obstacle3 obstacle3;
#endif

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
#if defined ODAZIMA
	obstacle2.Init(&player);
#else
	obstacle3.Init(&player);
#endif
}

//更新.
void GameManager::Update() {

	//生存中のみ更新.
	if (player.GetActive()) {
		nowTime = clock(); //現在時刻.
	}

	player.Update();
	//obstacle.Update();
#if defined ODAZIMA
	obstacle2.Update();
#else
	obstacle3.Update();
#endif
}

//描画.
void GameManager::Draw() {
	player.Draw();
	//obstacle.Draw();
#if defined ODAZIMA
	obstacle2.Draw();
#else
	obstacle3.Draw();
#endif

	//タイマー表示.
	DrawFormatString(0, 0, 0xFFFFFF, _T("time:%.3f"), GetTime());
}