/*
   - GameManager.cpp -
   ゲーム全体管理.
*/
//#define ODAZIMA //これを定義すると小田島作の障害物に切り替え.

#include "GameManager.h"
#include "Player.h"
#include "Obstacle.h"
#if defined ODAZIMA
#include "Obstacle2.h"
#else
#include "Obstacle3.h"
#endif

//プレイヤーの実体.
Player    player;
//障害物の実体.
Obstacle  obstacle[] = {
	Obstacle({150, 150}, 0, 50),
	Obstacle({400, 150}, 30, 50),
	Obstacle({300, 300}, 60, 80)
};

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

	//プレイヤーclass.
	player.Init();
	//障害物class.
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Init(&player);
	}
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

	//プレイヤーclass.
	player.Update();
	//障害物class.
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Update();
	}
#if defined ODAZIMA
	obstacle2.Update();
#else
	obstacle3.Update();
#endif
}

//描画.
void GameManager::Draw() {

	//プレイヤーclass.
	player.Draw();
	//障害物class.
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Draw();
	}
#if defined ODAZIMA
	obstacle2.Draw();
#else
	obstacle3.Draw();
#endif

	//タイマー表示.
	DrawFormatString(0, 0, 0xFFFFFF, _T("time:%.3f"), GetTime());
}