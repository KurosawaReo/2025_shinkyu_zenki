/*
   - GameManager.cpp -
   ゲーム全体管理.
*/
/*--------------------------------------------------------/
   [TODO]
   2025/05/20:
   仮でスローモードを実装したが、レーザーの動きが怪しい。
   
   2025/05/26:
   スローモード完成。レーザーの動きの怪しさも解決。
   ・アイテムの実装
   ・スローモードの時間制限 <<< now
   ・障害物4の砲台を画面一周動かす(ゲーム時間??秒以降)

   2025/06/02:
   スローモードの解除まで完成。
   ・アイテムの落下速度、定数いじっても変わらない。
   ・とる、こわすをどうするか考える。
/--------------------------------------------------------*/
#define ODAZIMA //これを定義すると小田島作の障害物に切り替え.

#include "Player.h"
#include "Obstacle.h"
#if defined ODAZIMA
#include "Obstacle2.h"
#include "Obstacle4.h"
#include "Item.h"
#else
#include "Obstacle3.h"
#endif

#include "GameManager.h"

//プレイヤーの実体.
Player   player;
//障害物の実体.
Obstacle obstacle[] = {
	Obstacle( 80, 1,   0x00FF00),
	Obstacle( 60, 0.5, 0x00FF00),
	Obstacle(100, 1,   0x00FF00),
	Obstacle(200, 1,   0x00FF00)
};

#if defined ODAZIMA
Obstacle2 obstacle2;
Obstacle4 obstacle4;
Item  item;
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
	item.Init(&data);
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
	item.Reset();
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
	switch (data.scene) 
	{
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
	switch (data.scene) 
	{
		case SCENE_TITLE: DrawTitle(); break;
		case SCENE_GAME:  DrawGame();  break;
		case SCENE_END:   DrawEnd();   break;

		default: assert(FALSE); break;
	}
}

//シーン別更新.
void GameManager::UpdateTitle() 
{
	//SPACEが押された瞬間、ゲーム開始.
	if (IsPushKeyTime(KEY_INPUT_SPACE) == 1) {
		tmGame.Start();          //タイマー開始.
		data.scene = SCENE_GAME; //ゲームシーンへ.
	}
}
void GameManager::UpdateGame() {

	//稼働してなければ.
	if (!tmSlowMode.GetIsMove()) {
		//Lボタンでスローモードに(仮)
		if (IsPushKeyTime(KEY_INPUT_L) == 1) {
			data.isSlow = TRUE;
			tmSlowMode.Start();
		}
	}
	//時間切れで解除.
	else if(tmSlowMode.GetTime() == 0){
		data.isSlow = FALSE;
		tmSlowMode.Reset();
	}

	//障害物class.
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Update();
	}
#if defined ODAZIMA
	obstacle2.Update();
	obstacle4.Update();
	item.Update();
	item.ItemMove();
	item.CheckHitPlayer(&player);
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
	//ゲームが開始されていない場合は開始案内を表示
	DrawFormatString(260, 160, GetColor(255, 255, 255), _T("PUSH SPACE"));
}
void GameManager::DrawGame() {

	DrawObjests();

	//タイマー表示.
	DrawFormatString(0, 0, 0xFFFFFF, _T("time:%.3f"), tmGame.GetTime());
	//カウントダウン中.
	if (tmSlowMode.GetIsMove() && tmSlowMode.GetTime() > 0) 
	{
		//画面中央に数字を表示.
		DrawFormatString(WINDOW_WID/2, WINDOW_HEI/2, 0xFFFFFF, _T("%d"), (int)ceil(tmSlowMode.GetTime()));
	}
}
void GameManager::DrawEnd() {
	
	DrawObjests();

	//タイマー表示.
	DrawFormatString(0, 0, 0xFFFFFF, _T("time:%.3f"), tmGame.GetTime());
	//終了案内.
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
	item.Draw();
#else
	obstacle3.Draw();
#endif
	//プレイヤーclass.
	player.Draw();
}

//ゲーム終了.
void GameManager::GameEnd() {
	
	data.scene = SCENE_END; //ゲーム終了へ.
	
	tmGame.Stop(); //停止.
	data.isSlow = FALSE;
	tmSlowMode.Reset();
}