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
Obstacle4_1 obstacle4_1;
Obstacle4_2 obstacle4_2;
//アイテムの実体.
Item item;
//プレイヤーの実体.
Player player;

//初期化(一回のみ行う)
void GameManager::Init() {

	srand((unsigned)time(NULL)); //乱数初期化.

	//タイトル.
	data.scene = SCENE_TITLE;
	//フォント作成.
	data.font1 = CreateFontToHandle(NULL, 30, 1, DX_FONTTYPE_NORMAL);
	data.font2 = CreateFontToHandle(NULL, 20, 1, DX_FONTTYPE_NORMAL);

#if defined ALL_OBSTACLE
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Init(&data, &player);
	}
	obstacle2.Init(&data, &player);
#endif

	//障害物class.
	obstacle4_1.Init(&data, &player);
	obstacle4_2.Init(&data, &player);
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
	obstacle4_1.Reset(WINDOW_WID/2, 0, 3);
	obstacle4_2.Reset(WINDOW_WID/2, 0, 3);
	//アイテムclass.
	item.Reset();
	//プレイヤーclass.
	player.Reset({ 100, 100 }, TRUE);
}

//更新.
void GameManager::Update() {

	InputST* input = InputST::GetPtr();

	input->UpdateKey();    //キー入力更新.
	input->UpdatePadBtn(); //コントローラのボタン入力更新.

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
	InputST* input = InputST::GetPtr();

	//特定の操作でゲーム開始.
	if (input->IsPushKeyTime(KEY_SPACE) == 1 || input->IsPushPadBtnTime(PAD_BTN_X) == 1)
	{
		tmGame.Start();          //タイマー開始.
		data.scene = SCENE_GAME; //ゲームシーンへ.
	}
}
void GameManager::UpdateGame() {
	
	DrawFormatString(30, 200, 0xFFFFFF, _T("%d"), GetJoypadInputState(DX_INPUT_PAD1));

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

	//障害物class.
	obstacle4_1.Update();
	obstacle4_2.Update();
	//アイテムclass.
	item.Update();
	//プレイヤーclass.
	player.Update();
}
void GameManager::UpdateEnd() {

	InputST* input = InputST::GetPtr();

	//特定の操作でタイトルへ.
	if (input->IsPushKeyTime(KEY_SPACE) == 1 || input->IsPushPadBtnTime(PAD_BTN_A) == 1)
	{
		data.scene = SCENE_TITLE; //ゲームシーンへ.
		Reset();
	}
}

//シーン別描画.
void GameManager::DrawTitle() {
	//ゲームが開始されていない場合は開始案内を表示
	{
		//テキストの設定.
		STR_DRAW str = { _T("PUSH SPACE"), {WINDOW_WID/2, 160}, 0xFFFFFF };
		//画面中央に文字を表示.
		DrawStringST(&str, TRUE, data.font2); //fontあり.
	}
}
void GameManager::DrawGame() {

	DrawObjests();

	//タイマー表示.
	DrawFormatStringToHandle(
		0, 0, 0xFFFFFF, data.font2, _T("time:%.3f"), tmGame.GetTime()
	);
	//カウントダウン中.
	if (tmSlowMode.GetIsMove() && tmSlowMode.GetTime() > 0) 
	{
		//テキストの設定.
		STR_DRAW str = { _T(""), {WINDOW_WID/2, WINDOW_HEI/2}, 0xFFFFFF };
		sprintf((char*)str.text, "%d", (int)ceil(tmSlowMode.GetTime()));

		//画面中央に数字を表示.
		DrawStringST(&str, TRUE, data.font1); //fontあり.
	}
}
void GameManager::DrawEnd() {
	
	DrawObjests();

	//タイマー表示.
	DrawFormatStringToHandle(
		0, 0, 0xFFFFFF, data.font2, _T("time:%.3f"), tmGame.GetTime()
	);
	//終了案内.
	{
		//テキストの設定.
		STR_DRAW str = { _T("GAME OVER"), {WINDOW_WID/2, 160}, 0xFF0000 };
		//画面中央に文字を表示.
		DrawStringST(&str, TRUE, data.font2); //fontあり.
	}
}

//オブジェクトの描画.
void GameManager::DrawObjests() {

#if defined ALL_OBSTACLE
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Draw();
	}
	obstacle2.Draw();
#endif

	//障害物class.
	obstacle4_1.Draw();
	obstacle4_2.Draw();
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