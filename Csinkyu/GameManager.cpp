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
   ・FPSはm秒待機ではなく、時間計測で測りたい

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

   2025/07/14:
   あまり進捗なし。反射レーザーの回転問題は一旦直したが、挙動は怪しい。
   前期発表会までにこの辺はやっておきたい
   ・隕石が壊れる時、構成してる線がバラバラになるようにする
   ・追尾レーザーとは別に、直線レーザーを追加する
   ・サウンド関係

   2025/07/15:
   反射仮完成。このゲームの方針も見えてきた。
   「隕石を破壊するとスコアを得られ、そのスコアを競うゲーム」で行ける気がする。
/--------------------------------------------------------*/

#include "MeteoManager.h"
#include "LaserManager.h"
#include "MapGimmickLaserManager.h"
#include "MapGimmickLaser.h"
#include "Obstacle4.h"
#include "Obstacle4main.h"
#include "Obstacle5.h"

#include "Item.h"
#include "Player.h"

#include "GameManager.h"

//障害物の実体.
Obstacle4_1 obstacle4_1;
Obstacle4_2 obstacle4_2;
Obstacle4_3 obstacle4_3;
Obstacle4_4 obstacle4_4;
Obstacle5   obstacle5;
MapGimmickLaserManager mglMng;
MapGimmickLaser mgl;
//障害物管理の実体.
MeteoManager meteoMng;
LaserManager laserMng;
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
	//画像読み込み.
	int ret = LoadGraphST(&data.imgLogo, _T("Resources/Images/REFLINEロゴ.png"));
	//サウンド読み込み.
	SoundST* sound = SoundST::GetPtr();
	sound->LoadFile(_T("Resources/Sounds/audiostock_132563.mp3"),  _T("BGM1"));
	sound->LoadFile(_T("Resources/Sounds/audiostock_1535055.mp3"), _T("BGM2"));

	//障害物class.
	obstacle4_1.Init(&data, &player, &meteoMng, &laserMng);
	obstacle4_2.Init(&data, &player, &meteoMng, &laserMng);
	//obstacle4_3.Init(&data, &player, &meteoMng, &laserMng);
	//obstacle4_4.Init(&data, &player, &meteoMng, &laserMng);
	obstacle5.Init(&data, &player);
	//障害物管理class.
	meteoMng.Init(&data, &player);
	laserMng.Init(&data, &player, &meteoMng);
	mglMng.Init(&data, &player, &meteoMng);
	mgl.Init(&data, &player, &meteoMng);
	//アイテムclass.
	item.Init(&data, &player);
	//プレイヤーclass.
	player.Init(&data);

	Reset();
}

//リセット(何回でも行う)
void GameManager::Reset() {

	data.score  = 0;     //スコアリセット.
	data.isSlow = FALSE; //スローモード解除.

	SoundST* sound = SoundST::GetPtr();
	sound->FadeInPlay(_T("BGM1"), 80, 3, TRUE);

	//障害物class.
	obstacle4_1.Reset(WINDOW_WID/2,    0, 3, MOVE_RIGHT);
	obstacle4_2.Reset(WINDOW_WID/2,    0, 3, MOVE_LEFT);
	//obstacle4_3.Reset(WINDOW_WID/2, 1070, 3, MOVE_RIGHT);
	//obstacle4_4.Reset(WINDOW_WID/2, 1070, 3, MOVE_LEFT);
	//obstacle5.Reset(WINDOW_WID/2, WINDOW_HEI/1, 0, 0); // 画面中央に配置.
	mglMng.Reset();
	mgl.Reset();
	//隕石管理class.
	meteoMng.Reset();
	laserMng.Reset();
	//アイテムclass.
	item.Reset();
	//プレイヤーclass.
	player.Reset({ WINDOW_WID/2, WINDOW_HEI/2 }, TRUE);
}

//更新.
void GameManager::Update() {

	InputST* input = InputST::GetPtr(); //inputクラスを使えるように.
	SoundST* sound = SoundST::GetPtr(); //soundクラスを使えるように.

	input->UpdateKey();    //キー入力更新.
	input->UpdatePadBtn(); //コントローラのボタン入力更新.
	sound->Update();       //サウンド更新.

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
	
//	DrawFormatString(30, 200, 0xFFFFFF, _T("%d"), GetJoypadInputState(DX_INPUT_PAD1));

	if (tmSlowMode.GetIsMove()) {
		//時間切れで解除.
		if(tmSlowMode.GetPassTime() == 0){
			data.isSlow = FALSE;
			player.SetReflectionMode(FALSE); //反射モード終了.
			tmSlowMode.Reset();
		}
	}

	//障害物class.
	obstacle4_1.Update();
	obstacle4_2.Update();
	//obstacle4_3.Update();
	//obstacle4_4.Update();
	//obstacle5.Update();
	mglMng.Update();
	mgl.Update();
	//障害物管理class.
	meteoMng.Update();
	laserMng.Update();
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
	
	//画像の表示.
	IMG_DRAW_EXTEND img = { data.imgLogo, {WINDOW_WID/2, WINDOW_HEI/2}, {data.imgLogo.size.x/2, data.imgLogo.size.y/2} };
	DrawExtendGraphST(&img, TRUE);

	//テキストの表示..
	STR_DRAW str = { _T("PUSH SPACE"), {WINDOW_WID/2, 160}, 0xFFFFFF };
	DrawStringST(&str, TRUE, data.font2); //fontあり.
	
}
void GameManager::DrawGame() {

	DrawObjects();

	//UI表示.
	DrawFormatStringToHandle(
		0, 0, 0xFFFFFF, data.font2, _T("time:%.3f"), tmGame.GetPassTime()
	);
	DrawFormatStringToHandle(
		0, 20, 0xFFFFFF, data.font2, _T("score:%d"), data.score
	);
	//スローモード演出.
	DrawSlowMode();
}
void GameManager::DrawEnd() {
	
	DrawObjects();

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
void GameManager::DrawBG() {

	//背景デザイン.
	for (int x = 0; x < WINDOW_WID; x += 5) {

		int clr = _int(20 * fabs(sin((double)x / 200))); //色の変化.
		Line line = { {(double)x, 0},{(double)x, WINDOW_HEI}, GetColor(0, clr, clr) };
		DrawLineST(&line, 5);
	}
	//背景(スローモード).
	if (data.isSlow) {
		//背景色.
		{
			Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x303030 };
			DrawBoxST(&box, FALSE);
		}
		//枠線アニメーション.
		{
			//最初の0.5秒
			float time = 0.5f-(tmSlowMode.GetPassTime()-(SLOW_MODE_TIME-0.5f));
			time = CalcNumEaseOut(time); //値の曲線変動.
			
			Box box = { {WINDOW_WID/2, WINDOW_HEI/2}, {WINDOW_WID * time, WINDOW_HEI * time}, COLOR_PLY_REFLECT };
			DrawBoxST(&box, TRUE, FALSE);
		}
	}
}
//オブジェクトの描画.
void GameManager::DrawObjects() {

	//障害物class.
	obstacle4_1.Draw();
	obstacle4_2.Draw();
	//obstacle4_3.Draw();
	//obstacle4_4.Draw();
	//obstacle5.Draw();
	mglMng.Draw();
	mgl.Draw();
	//障害物管理class.
	meteoMng.Draw();
	laserMng.Draw();
	//アイテムclass.
	item.Draw();
	//プレイヤーclass.
	player.Draw();
}
//スローモード演出.
void GameManager::DrawSlowMode() {

	//カウントダウン中.
	if (tmSlowMode.GetIsMove() && tmSlowMode.GetPassTime() > 0)
	{
		//テキストを入れる用.
		STR_DRAW str = { {}, {WINDOW_WID / 2, WINDOW_HEI / 2}, 0x00FF00 };
		//テキストの設定.
		swprintf(str.text, _T("%d"), (int)ceil(tmSlowMode.GetPassTime())); //TCHAR型に変数を代入.

		//画面中央に数字を表示.
		{
			double dec = GetDecimal(tmSlowMode.GetPassTime()); //小数だけ取り出す.
			SetDrawBlendModeST(MODE_ADD, _int(255 * dec));     //1秒ごとに薄くなる演出.
			DrawStringST(&str, TRUE, data.font1);              //fontあり.
			ResetDrawBlendMode();                              //戻す.
		}
	}
}

//ゲーム終了.
void GameManager::GameEnd() {
	
	data.scene = SCENE_END; //ゲーム終了へ.
	
	tmGame.Stop(); //停止.
	data.isSlow = FALSE;
	tmSlowMode.Reset();

	SoundST* sound = SoundST::GetPtr();
	sound->FadeOutPlay(_T("BGM1"), 3);
}
//アイテムを取った時.
void GameManager::TakeItem() {

	data.isSlow = TRUE;             //スローモードにする.
	player.SetReflectionMode(TRUE); //反射モード開始.
	tmSlowMode.Start();             //タイマー開始.
}