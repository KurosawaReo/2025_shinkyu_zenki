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

   2025/06/23:
   仮で隕石が降るのを作ったが、正常かどうかが怪しい。
   特にisSlowによりスローになる所でdouble型にうまくキャストできておらず
   一旦全ての速度調整をしてる所を確認したい。

   2025/06/26:
   隕石は大体正常にできたと思われる。
   レーザーの発射を、三角形の敵の先端から出るようにできたら良さそう。
   打つ方向に三角形を回転させる。

   2025/06/30:
   仮で多角形は完成した。
   ただ辺がうまく繋がらないため、そのロジックだけ見直す。
   (頂点の位置を回転を使って測れば行ける気がする)

   2025/07/01:
   当たると即死で難しく、ゲーム性の問題があるため
   プレイヤーの周りに小さな四角を並べたバリアを作りたい。(HPは作らない)
/--------------------------------------------------------*/
//#define ALL_OBSTACLE //これを定義すると全ての障害物を出す.

#include "MeteoManager.h"
#include "Obstacle4.h"
#include "Obstacle4main.h"
#include "Obstacle5.h"
#include "MeteoManager.h"
#include "Item.h"
#if defined ALL_OBSTACLE
#include "Obstacle.h"
#include "Obstacle2.h"
#endif
#include "Player.h"

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
Obstacle4_3 obstacle4_3;
Obstacle4_4 obstacle4_4;
Obstacle5   obstacle5;
//隕石管理の実体.
MeteoManager meteoMng;
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
	data.font1 = CreateFontToHandle(NULL, 30, 1);
	data.font2 = CreateFontToHandle(NULL, 20, 1);

#if defined ALL_OBSTACLE
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Init(&data, &player);
	}
	obstacle2.Init(&data, &player);
#endif

	//障害物class.
	obstacle4_1.Init(&data, &player);
	obstacle4_2.Init(&data, &player);
	obstacle4_3.Init(&data, &player);
	obstacle4_4.Init(&data, &player);
	obstacle5.Init(&data, &player);

	//隕石管理class.
	meteoMng.Init(&data, &player);
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

	obstacle4_1.Reset(WINDOW_WID /  2, 0, 3, MOVE_RIGHT);
	obstacle4_2.Reset(WINDOW_WID /  2, 0, 3, MOVE_LEFT);
	obstacle4_3.Reset(WINDOW_WID / 2, 1070, 3, MOVE_RIGHT);
	obstacle4_4.Reset(WINDOW_WID / 2, 1070, 3, MOVE_LEFT);
	obstacle5.Reset(WINDOW_WID / 2, WINDOW_HEI / 1, 0, 0); // 画面中央に配置

	//隕石管理class.
	meteoMng.Reset();
	//アイテムclass.
	item.Reset();
	//プレイヤーclass.
	player.Reset({ WINDOW_WID/2, WINDOW_HEI/2 }, TRUE);
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

	DrawBG();

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

	if (tmSlowMode.GetIsMove()) {
		//時間切れで解除.
		if(tmSlowMode.GetPassTime() == 0){
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
	obstacle4_3.Update();
	obstacle4_4.Update();
	obstacle5.Update();

	

	//隕石管理class.
	meteoMng.Update();
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
		0, 0, 0xFFFFFF, data.font2, _T("time:%.3f"), tmGame.GetPassTime()
	);
	//カウントダウン中.
	if (tmSlowMode.GetIsMove() && tmSlowMode.GetPassTime() > 0)
	{
		//テキストを入れる用.
		TCHAR    txt[256]{};
		STR_DRAW str = { {}, {WINDOW_WID/2, WINDOW_HEI/2}, 0xFFFFFF};

		//テキストの設定.
//		sprintf (txt,    "time:%d",  (int)ceil(tmSlowMode.GetPassTime())); //char型に変数を代入.
		wsprintf(txt, _T("time:%d"), (int)ceil(tmSlowMode.GetPassTime())); //TCHAR型に変数を代入.
//		strcpy (str.text, txt);	//char型の文字列をコピー.
		_tcscpy(str.text, txt); //TCHAR型の文字列をコピー.


		swprintf(str.text, _T("%d"), (int)ceil(tmSlowMode.GetPassTime())); //TCHAR型に変数を代入.
		//画面中央に数字を表示.
		DrawStringST(&str, TRUE, data.font1); //fontあり.
	}
}
void GameManager::DrawEnd() {
	
	DrawObjests();

	//タイマー表示.
	DrawFormatStringToHandle(
		0, 0, 0xFFFFFF, data.font2, _T("time:%.3f"), tmGame.GetPassTime()
	);
	//終了案内.
	{
		//テキストの設定.
		STR_DRAW str = { _T("GAME OVER"), {WINDOW_WID/2, 160}, 0xFF0000 };
		STR_DRAW str2 = { {}, {WINDOW_WID / 2, WINDOW_HEI / 2}, 0xFFFFFF };
		swprintf(str2.text, _T("time:%.3f"), tmGame.GetPassTime());


		//画面中央に文字を表示.
		DrawStringST(&str, TRUE, data.font2); //fontあり.
		DrawStringST(&str2, TRUE, data.font2);
	}
}

//背景の描画.
void GameManager::DrawBG() const {

	//背景デザイン.
	for (int x = 0; x < WINDOW_WID; x += 5) {

		int clr = _int(20 * fabs(sin((double)x / 200))); //色の変化.
		Line line = { {(double)x, 0},{(double)x, WINDOW_HEI}, GetColor(0, clr, clr) };
		DrawLineST(&line, 5);
	}
	//背景(スローモード).
	if (data.isSlow) {
		Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x303030 };
		DrawBoxST(&box, FALSE);
	}
}
//オブジェクトの描画.
void GameManager::DrawObjests() {

#if defined ALL_OBSTACLE
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Draw();
	}
	//obstacle2.Draw();
#endif

	//障害物class.
	obstacle4_1.Draw();
	obstacle4_2.Draw();
	obstacle4_3.Draw();
	obstacle4_4.Draw();
	obstacle5.Draw();
	//隕石管理class.
	meteoMng.Draw();
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