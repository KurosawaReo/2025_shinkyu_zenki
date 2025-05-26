/*
   - GameManager.cpp -
   ゲーム全体管理.
*/
/*--------------------------------------------------------/
   [TODO]
   2025/05/20:
   仮でスローモードを実装したが、レーザーの動きが怪しい。
   体力を実装したい。表示はゲージで。
/--------------------------------------------------------*/
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
	Obstacle(100, 1, 0x00FF00),
	Obstacle(200, 1, 0x00FF00)
};

#if defined ODAZIMA
Obstacle2 obstacle2;
Obstacle4 obstacle4;
#else
Obstacle3 obstacle3;
#endif

//初期化(一回のみ行う)
void GameManager::Init() {

	srand((unsigned)time(NULL)); //乱数初期化.

	data.scene = SCENE_TITLE; //タイトル.

	//障害物class.
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Init(&data, &player);
	}
#if defined ODAZIMA
	obstacle2.Init(&data, &player);
	obstacle4.Init(&data, &player);
#else
	obstacle3.Init(&player);
#endif
	//プレイヤーclass.
	player.Init(&data);

	Reset();
}

//リセット(何回でも行う)
void GameManager::Reset() {

	data.isSlow = FALSE; //スローモード解除.

	//障害物class.
	obstacle[0].Reset({ 150, 150 }, 0);
	obstacle[1].Reset({ 400, 150 }, 30);
	obstacle[2].Reset({ 300, 300 }, 60);
	obstacle[3].Reset({ 500, 300 }, 90);
#if defined ODAZIMA
	obstacle2.Reset();
	obstacle4.Reset();
#else
	obstacle3.Reset();
#endif
	//プレイヤーclass.
	player.Reset({ 100, 100 }, TRUE);
}

//更新.
void GameManager::Update() {

	UpdateKeys(); //キー入力更新.

	//シーン別.
	switch (data.scene) {
		case SCENE_TITLE: UpdateTitle(); break;
		case SCENE_GAME:  UpdateGame();  break;
		case SCENE_END:   UpdateEnd();   break;
	
		default: assert(FALSE); break;
	}
}

//描画.
void GameManager::Draw() {

	//背景色.
	if (data.isSlow) {
		Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x303030 };
		DrawBoxST(&box, FALSE);
	}

	//シーン別.
	switch (data.scene) {
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
		stTime = clock();        //開始時刻.
		data.scene = SCENE_GAME; //ゲームシーンへ.
	}
}
void GameManager::UpdateGame() {

	nowTime = clock(); //現在時刻.

	//スローモード切り替え.
	if (IsPushKeyTime(KEY_INPUT_L) == 1) {
		data.isSlow = !data.isSlow;
	}

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
		data.scene = SCENE_TITLE; //ゲームシーンへ.
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