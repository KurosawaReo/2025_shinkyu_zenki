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

   2025/06/09:
   "こわす"の方針決定。
   
   1.線で構成された多角形の隕石が定期的に降ってくる(全方向からランダム)
   2.アイテムを取るとレーザーを反射するようになり、拡散するように飛んでいく。
   3.近くに隕石がある場合、隕石に向かって飛んでいく。
   4.反射したレーザーが隕石に当たると壊れる(可能なら壊れるアニメーションを入れたい)
   課題点: どうやって隕石の座標を取得するか.

   小田島 →レーザーの反射
   黒澤　 →線で構成された多角形の隕石

   [余裕があれば]
   ・FPSはm秒待機ではなく、時間計測で測りたい.
/--------------------------------------------------------*/
//#define ALL_OBSTACLE //これを定義すると全ての障害物を出す.

#include "Player.h"
#include "Obstacle4.h"
#include "Item.h"
#if defined ALL_OBSTACLE
#include "Obstacle.h"
#include "Obstacle2.h"
#endif

#include "GameManager.h"

#if defined ALL_OBSTACLE
Obstacle obstacle[] = {
	Obstacle( 80, 1,   0x00FF00),
	Obstacle( 60, 0.5, 0x00FF00),
	Obstacle(100, 1,   0x00FF00),
	Obstacle(200, 1,   0x00FF00)
};
Obstacle2 obstacle2;
#endif

//障害物の実体.
Obstacle4 obstacle4;
Obstacle5 obstacle5;
//アイテムの実体.
Item item;
//プレイヤーの実体.
Player player;

//初期化(一回のみ行う)
void GameManager::Init() {

	srand((unsigned)time(NULL)); //乱数初期化.

	data.scene = SCENE_TITLE; //タイトル.

#if defined ALL_OBSTACLE
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Init(&data, &player);
	}
	obstacle2.Init(&data, &player);
#endif

	//障害物class.
	
		obstacle4.Init(&data, &player);
		obstacle5.Init(&data, &player);
	//アイテムclass.
	item.Init(&data, &player);
	//プレイヤーclass.
	player.Init(&data);

	Reset();
}

//リセット(何回でも行う)
void GameManager::Reset() {

	data.isSlow = FALSE; //スローモード解除.

#if defined ALL_OBSTACLE
	obstacle[0].Reset({ 150, 150 }, 0);
	obstacle[1].Reset({ 400, 150 }, 30);
	obstacle[2].Reset({ 300, 300 }, 60);
	obstacle[3].Reset({ 500, 300 }, 90);
	obstacle2.Reset();
#endif

	//障害物class.
	obstacle4.Reset(0, 30, 3);
	obstacle5.Reset(0, 30, 3);
	//アイテムclass.
	item.Reset();
	//プレイヤーclass.
	player.Reset({ 100, 100 }, TRUE);
}

//更新.
void GameManager::Update() {

	UpdateKey();    //キー入力更新.
	UpdatePadBtn(); //コントローラのボタン入力更新.

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
	//特定の操作でゲーム開始.
	if (IsPushKeyTime(KEY_INPUT_SPACE) == 1 || 
		IsPushPadBtnTime(PAD_INPUT_A) == 1) 
	{
		tmGame.Start();          //タイマー開始.
		data.scene = SCENE_GAME; //ゲームシーンへ.
	}
}
void GameManager::UpdateGame() {
	
#if false
	//稼働してなければ.
	if (!tmSlowMode.GetIsMove()) {
		//Lボタンでスローモードに(仮)
		if (IsPushKeyTime(KEY_INPUT_L) == 1) {
			data.isSlow = TRUE;
			tmSlowMode.Start();
		}
	}
#endif
	if (tmSlowMode.GetIsMove()) {
		//時間切れで解除.
		if(tmSlowMode.GetTime() == 0){
			data.isSlow = FALSE;
			tmSlowMode.Reset();
		}
	}

#if defined ALL_OBSTACLE
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Update();
	}
	obstacle2.Update();
#endif
		obstacle4.Update();
		obstacle5.Update();
	//障害物class.
	//obstacle4.Update();
	//アイテムclass.
	item.Update();
	//プレイヤーclass.
	player.Update();
}
void GameManager::UpdateEnd() {

	//特定の操作でタイトルへ.
	if (IsPushKeyTime(KEY_INPUT_SPACE) == 1 || 
		IsPushPadBtnTime(PAD_INPUT_A) == 1) 
	{
		data.scene = SCENE_TITLE; //ゲームシーンへ.
		Reset();
	}
}

//シーン別描画.
void GameManager::DrawTitle() {
	//ゲームが開始されていない場合は開始案内を表示
	DrawFormatString(260, 160, 0xFFFFFF, _T("PUSH SPACE"));
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

#if defined ALL_OBSTACLE
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Draw();
	}
	obstacle2.Draw();
#endif
		obstacle4.Draw();
		obstacle5.Draw();

	//障害物class.
	//obstacle4.Draw();
	//アイテムclass.
	item.Draw();
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
//アイテムを取った時.
void GameManager::TakeItem() {

	data.isSlow = TRUE; //スローモードにする.
	tmSlowMode.Start(); //タイマー開始.
}