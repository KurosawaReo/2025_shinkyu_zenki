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
#include "Obstacle4.h"
#else
#include "Obstacle3.h"
#endif

//プレイヤーの実体.
Player   player;
//障害物の実体.
Obstacle obstacle[] = {
	Obstacle(80, 1, 0x00FF00),
	Obstacle(60, 0.5, 0x00FF00),
	Obstacle(100, 1, 0x00FF00)
};

#if defined ODAZIMA
Obstacle2 obstacle2;
Obstacle4 obstacle4;
#else
Obstacle3 obstacle3;
#endif

//get.
float GameManager::GetTime() {
	return (float)(nowTime - stTime)/1000; //時刻の差.
}

//初期化(一回のみ行う)
void GameManager::Init() {

	srand((unsigned)time(NULL)); //乱数初期化.

	scene = SCENE_TITLE; //タイトル.

	//障害物class.
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Init(&player);
	}
#if defined ODAZIMA
	obstacle2.Init(&player);
	obstacle4.Init(&player);
#else
	obstacle3.Init(&player);
#endif
	//プレイヤーclass.
	player.Init(&scene);

	Reset();
}

//リセット(何回でも行う)
void GameManager::Reset() {

	//障害物class.
	obstacle[0].Reset({ 150, 150 }, 0);
	obstacle[1].Reset({ 400, 150 }, 30);
	obstacle[2].Reset({ 300, 300 }, 60);
#if !defined ODAZIMA
	obstacle3.Reset();
#endif
	//プレイヤーclass.
	player.Reset({ 100, 100 }, TRUE);
}

//更新.
void GameManager::Update() {

	UpdateKeys(); //キー入力更新.

	//シーン別.
	switch (scene) {
		case SCENE_TITLE: UpdateTitle(); break;
		case SCENE_GAME:  UpdateGame();  break;
		case SCENE_END:   UpdateEnd();   break;
	
		default: assert(FALSE); break;
	}
}

//描画.
void GameManager::Draw() {

	//シーン別.
	switch (scene) {
		case SCENE_TITLE: DrawTitle(); break;
		case SCENE_GAME:  DrawGame();  break;
		case SCENE_END:   DrawEnd();   break;

		default: assert(FALSE); break;
	}
}

//シーン別更新.
void GameManager::UpdateTitle() {

	//SPACEが押された瞬間、ゲーム開始.
	if (IsPushKeyTime(KEY_INPUT_SPACE) == 1) {
		stTime = clock();    //開始時刻.
		scene  = SCENE_GAME; //ゲームシーンへ.
	}
}
void GameManager::UpdateGame() {

	nowTime = clock(); //現在時刻.

	//障害物class.
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Update();
	}
#if defined ODAZIMA
	obstacle2.Update();
	obstacle4.Update();
#else
	obstacle3.Update();
#endif
	//プレイヤーclass.
	player.Update();
}
void GameManager::UpdateEnd() {

	//SPACEが押された瞬間、タイトルへ.
	if (IsPushKeyTime(KEY_INPUT_SPACE) == 1) {
		scene = SCENE_TITLE; //ゲームシーンへ.
		Reset();
	}
}

//シーン別描画.
void GameManager::DrawTitle() {
	// ゲームが開始されていない場合は開始案内を表示
	DrawFormatString(260, 160, GetColor(255, 255, 255), _T("PUSH SPACE"));
}
void GameManager::DrawGame() {

	DrawObjests();

	//タイマー表示.
	DrawFormatString(0, 0, 0xFFFFFF, _T("time:%.3f"), GetTime());
}
void GameManager::DrawEnd() {
	
	DrawObjests();

	//タイマー表示.
	DrawFormatString(0, 0, 0xFFFFFF, _T("time:%.3f"), GetTime());
	// 終了案内.
	DrawFormatString(260, 160, GetColor(255, 0, 0), _T("GAME OVER"));
}

//オブジェクトの描画.
void GameManager::DrawObjests() {

	//障害物class.
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Draw();
	}
#if defined ODAZIMA
	obstacle2.Draw();
	obstacle4.Draw();
#else
	obstacle3.Draw();
#endif
	//プレイヤーclass.
	player.Draw();
}