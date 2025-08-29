/*--------------------------------------------------------/
   - REFLECT LINE -

   (日本語表記: リフレクトライン)
   (略称　　　: REFLINE/リフライン)
/---------------------------------------------------------/
   TODOメモ

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

   2025/08/02:
   UIに背景画像を仮で追加したが、端の方を透過させたい。

   2025/08/04:
   Exステージ実装してもいいかも。
   特定の条件で行くことができて、特別なルールがある感じで。
   特別感のあるBGMや背景に変える。

   2025/08/15:
   配列をvectorに変えたい。
   push_backという関数で要素の追加ができるため、生成するときはこれで追加する。

   最大サイズの定数はそのまま残していい気がする
   例: if (size() < MAX_SIZE) {}

   2025/08/23:
   新障害物「花火」を追加する。Level4で登場予定。
   詳しくは後日相談, なおとに作ってもらう?

   2025/08/27:
   開始時、操作方法分岐を入れて以後の説明文を変えたい。
   ・KEY_SPACE を押したら⇒Push SPACE (キーボード操作)
   ・PAD_XBOX_Aを押したら⇒Push A     (パッド操作)
   など。

/---------------------------------------------------------/
   前期発表会後 変更内容

   ・UIや演出に画像を追加。
   ・UIのレイアウト変更、装飾の追加。「TIME」や「LEVEL」をまとめた。
   ・背景画像を仮で用意。
   ・アイテムの終了タイミングが分かるよう、最後の3秒だけ表示し、音も追加。
   ・波紋の爆発するタイミングが分かるよう、演出を調整。
   ・隕石の破片の飛び散り方がリアルっぽくなるよう調整。
   ・ポーズ機能仮追加。(Pキー)
   ・図形や線のアンチエイリアス導入。滑らかで綺麗な描画になった。
   ・レーザーで短すぎる線を描画しないように。(処理軽減に繋がる)
   ・強化アイテム追加。反射レーザーが隕石に当たっても反射する。

   [現在のLevel配分]
   Level1: 通常レーザー×2, 隕石
   Level2: 直線レーザー×2
   Level3: 波紋
   Level4: 直線レーザー×4, アイテム×2
   Level5: 通常レーザー×4, アイテムが強化

/---------------------------------------------------------/
   【今後の制作予定】

   こわす発表まで:
   ・障害物「花火」追加
   ・タイトルロゴ変更(ゲーム名変更のため)

   TGS展示まで:
   ・開始時の操作方法分岐(できれば)
   ・ゲーム内チュートリアル
   ・SCOREランキング実装
   ・ポスターver2 & アンケート作る
   
   最終目標:
   ・SCORE世界ランキング化
   ・steam販売

   [チュートリアル配分] ※案
   tutorial1: 避ける
   tutorial2: 取る
   tutorial3: 壊す
   tutorial4: 敵
   Levelと同じような演出を出す。stepを踏んで練習させる。
/--------------------------------------------------------*/
/*
   - GameManager.cpp -
   ゲーム全体管理.
*/

#include "MeteoManager.h"
#include "LaserManager.h"
#include "EffectManager.h"

#include "Obstacle4.h"
#include "Obstacle4main.h"
#include "Obstacle5.h"
#include "MapGimmickLaser.h"

#include "Item.h"
#include "Player.h"

#include "BackGround.h"
#include "GameManager.h"

//管理クラスの実体.
BackGround    bg;
MeteoManager  meteoMng;
LaserManager  laserMng;
EffectManager effectMng;
//障害物の実体.
Obstacle4_1 obstacle4_1;
Obstacle4_2 obstacle4_2;
Obstacle4_3 obstacle4_3;
Obstacle4_4 obstacle4_4;
Obstacle5   obstacle5;
MapGimmickLaser mgl[4];
//アイテムの実体.
ItemManager item;
//プレイヤーの実体.
Player player;

//初期化(一回のみ行う)
void GameManager::Init() {

	srand((unsigned)time(NULL)); //乱数初期化.
	
	//実体取得.
	p_input = InputMng::GetPtr();
	p_sound = SoundMng::GetPtr();
	p_calc  = Calc    ::GetPtr();

	//タイトル.
	data.scene = SCENE_TITLE;
	//フォント作成.
	data.font1 = CreateFontToHandle(NULL, 26, 1);
	data.font2 = CreateFontToHandle(NULL, 30, 1, DX_FONTTYPE_ANTIALIASING);
	data.font3 = CreateFontToHandle(NULL, 35, 1, DX_FONTTYPE_ANTIALIASING);
	data.font4 = CreateFontToHandle(NULL, 40, 1, DX_FONTTYPE_ANTIALIASING);
	//画像読み込み.
	imgLogo[0].  LoadFile(_T("Resources/Images/REFLINEロゴ_一部.png"));
	imgLogo[1].  LoadFile(_T("Resources/Images/REFLINEロゴ.png"));
	imgUI[0].    LoadFile(_T("Resources/Images/ui_back_level.png"));
	imgUI[1].    LoadFile(_T("Resources/Images/ui_back_best_score.png"));
	imgUI[2].    LoadFile(_T("Resources/Images/ui_back_score.png"));
	imgUI[3].    LoadFile(_T("Resources/Images/ui_back_time.png"));
	imgNewRecord.LoadFile(_T("Resources/Images/new_record.png"));
	imgGameOver. LoadFile(_T("Resources/Images/gameover.png"));
	imgReflect.  LoadFile(_T("Resources/Images/reflect.png"));
	//サウンド読み込み.
	p_sound->LoadFile(_T("Resources/Sounds/bgm/Scarlet Radiance.mp3"),		_T("BGM1"));
	p_sound->LoadFile(_T("Resources/Sounds/bgm/audiostock_1603723.mp3"),	_T("BGM2"));
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_461339.mp3"),		_T("TakeItem"));	//アイテム取る.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1116927_cut.mp3"),	_T("CountDown"));	//カウントダウン.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_63721.mp3"),		_T("PowerDown"));	//アイテム解除.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1296254.mp3"),		_T("Laser1"));		//レーザー(発射)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1296256.mp3"),		_T("Laser2"));		//レーザー(強発射)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_218404.mp3"),		_T("Laser3"));		//レーザー(反射)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_936158.mp3"),		_T("Ripples"));		//波紋.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_104974.mp3"),		_T("Break"));		//隕石破壊.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_981051.mp3"),		_T("PlayerDeath"));
	p_sound->LoadFile(_T("Resources/Sounds/se/決定ボタンを押す23.mp3"),		_T("LevelUp"));
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_184924.mp3"),		_T("BestScore"));	//最高スコア更新.
	
	//Init処理
	{
		//管理class.
		bg.Init(&data);
		laserMng.Init(&data, &player, &meteoMng, &effectMng);
		meteoMng.Init(&data, &player, &effectMng);
		effectMng.Init(&data);
		//障害物class.
		for (int i = 0; i < _countof(mgl); i++) {
			mgl[i].Init(&data, &player, &laserMng, &meteoMng);
		}
		obstacle4_1.Init(&data, &player, &meteoMng, &laserMng);
		obstacle4_2.Init(&data, &player, &meteoMng, &laserMng);
		obstacle4_3.Init(&data, &player, &meteoMng, &laserMng);
		obstacle4_4.Init(&data, &player, &meteoMng, &laserMng);
		obstacle5.Init(&data, &player);
		//アイテムclass.
		item.Init(&data, &player, &effectMng);
		//プレイヤーclass.
		player.Init(&data, &effectMng);
	}

	//スコア読み込み.
	{
		File file;
		file.Open(FILE_DATA, _T("r"));   //ファイルを開く.
		data.bestScore = file.ReadInt(); //数字を読み込んで登録.
	}
	
	data.stage = 1; //test

	Reset();
}

//リセット(何回でも行う)
void GameManager::Reset() {

	if (data.bestScore < data.score) {
		data.bestScore = data.score; //ハイスコア記録.
	}

	//リセット.
	data.scoreBef = 0;
	data.score = 0;
	data.isSlow = false;
	data.counter = 0;
	data.spawnRate = 1.0; //最初は100%
	data.level = 1;       //最初はLv1
	isTitleAnim = false;
	isBestScoreSound = false;
	//サウンド.
	switch (data.stage) 
	{
		case 1:
			p_sound->Stop(_T("BGM1"));
			p_sound->Play(_T("BGM1"), true, 68);
			break;
		case 2:
			p_sound->Stop(_T("BGM2"));
			p_sound->FadeInPlay(_T("BGM2"), true, 68, 3);
			break;

		default: assert(false); break;
	}
	//タイマー.
	tmScene[SCENE_TITLE].Start();
	tmScene[SCENE_READY].Reset();
	tmScene[SCENE_GAME].Reset();
	tmScene[SCENE_END].Reset();

	{
		//管理class.
		laserMng.Reset();
		meteoMng.Reset();
		effectMng.Reset();
		//障害物class.
		ResetNorLaser();
		ResetStrLaser();
		obstacle5.Reset();
		//アイテムclass.
		item.Reset();
		//プレイヤーclass.
		player.Reset({ WINDOW_WID/2, WINDOW_HEI/2+185 }, true);
	}
}

//更新.
bool GameManager::Update() {

	p_input->UpdateKey(); //キー入力更新.
	p_input->UpdatePad(); //コントローラ入力更新.
	p_sound->Update();    //サウンド更新.

	bg.Update(); //背景.

	//シーン別.
	switch (data.scene) 
	{
		case SCENE_TITLE: UpdateTitle(); break;
		case SCENE_READY: UpdateReady(); break;
		case SCENE_GAME:  UpdateGame();  break;
		case SCENE_END:   UpdateEnd();   break;
		case SCENE_PAUSE: UpdatePause(); break;
	
		default: assert(FALSE); break;
	}

	//特定の操作でゲーム終了
	if (p_input->IsPushPadBtnTime(PAD_ACD_BTN_START) >= FPS * 1) {
		return true; //筐体STARTボタン長押しで終了
	}
	else if (p_input->IsPushKey(KEY_ESC)) {
		return true; //ESCAPEキーを押したら即終了.
	}
	return false; //続行.
}

//描画.
void GameManager::Draw() {

	bg.Draw(); //背景.

	//シーン別.
	switch (data.scene) 
	{
		case SCENE_TITLE: DrawTitle(); break;
		case SCENE_READY: DrawReady(); break;
		case SCENE_GAME:  DrawGame();  break;
		case SCENE_END:   DrawEnd();   break;
		case SCENE_PAUSE: DrawPause(); break;

		default: assert(FALSE); break;
	}
}

//通常レーザーのリセット.
void GameManager::ResetNorLaser() {

	obstacle4_1.Reset(WINDOW_WID/2, 0, 3, MOVE_RIGHT);
	obstacle4_2.Reset(WINDOW_WID/2, 0, 3, MOVE_LEFT);
	obstacle4_3.Reset(WINDOW_WID/2, WINDOW_HEI, 3, MOVE_RIGHT);
	obstacle4_4.Reset(WINDOW_WID/2, WINDOW_HEI, 3, MOVE_LEFT);
}
//直線レーザーのリセット.
void GameManager::ResetStrLaser() {

	for (int i = 0; i < _countof(mgl); i++) {
		mgl[i].Reset();
	}
}

//シーン別更新.
void GameManager::UpdateTitle() 
{
	player.Update();    //プレイヤー.
	effectMng.Update(); //エフェクト.

	//特定の操作でゲーム開始.
	if (p_input->IsPushKeyTime(KEY_SPACE) == 1 || p_input->IsPushPadBtnTime(PAD_ACD_BTN_UPPER_1) == 1)
	{
		tmScene[SCENE_READY].Start(); //タイマー開始.
		data.scene = SCENE_READY;     //準備シーンへ.
	}
}
void GameManager::UpdateReady() {

	player.Update();    //プレイヤー.
	effectMng.Update(); //エフェクト.
	
	//一定時間経ったら.
	if (tmScene[SCENE_READY].GetPassTime() >= GAME_START_TIME) {

		tmScene[SCENE_GAME].Start(); //ゲーム開始.
		data.scene = SCENE_GAME;     //ゲームシーンへ.
//		data.level = 1;              //Lv1にする.

		//サウンド.
		p_sound->Play(_T("LevelUp"), false, 100);
		//エフェクト.
		EffectData data{};
		data.type = Effect_Level1;
		data.pos = { WINDOW_WID/2, WINDOW_HEI/2 };
		effectMng.SpawnEffect(&data);
	}
}
void GameManager::UpdateGame() {
	
#if defined _DEBUG //Releaseでは入れない.
	//タイマー加速(Debug)
	if (p_input->IsPushKey(KEY_L) == 1) {
		data.counter += 10;
	}
#endif

	//カウンター増加.
	data.counter += ((data.isSlow) ? SLOW_MODE_SPEED : 1);
	//出現間隔.
	data.spawnRate = 1.0f/(1 + (data.counter/8000)); //100%から少しずつ減少.
	//レベル管理.
	switch (data.level)
	{
		case 1:
			if (data.counter >= 1500) { //1500 = 出現間隔約??%地点.
				data.level = 2; //Lv2へ.

				//サウンド.
				p_sound->Play(_T("LevelUp"), false, 100);
				//エフェクト.
				EffectData data{};
				data.type = Effect_Level2;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
			}
			break;
		case 2:
			if (data.counter >= 3500) { //3500 = 出現間隔約??%地点.
				data.level = 3; //Lv3へ.

				//サウンド.
				p_sound->Play(_T("LevelUp"), false, 100);
				//エフェクト.
				EffectData data{};
				data.type = Effect_Level3;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
			}
			break;
		case 3:
			if (data.counter >= 6000) { //6000 = 出現間隔約??%地点.
				data.level = 4; //Lv4へ.

				ResetStrLaser();
				item.AddItemCnt(); //アイテムを増やす.

				//サウンド.
				p_sound->Play(_T("LevelUp"), false, 100);
				//エフェクト.
				EffectData data{};
				data.type = Effect_Level4;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
			}
			break;
		case 4:
			if (data.counter >= 9000) { //9000 = 出現間隔約??%地点.
				data.level = 5; //Lv5へ.

				ResetNorLaser();

				//サウンド.
				p_sound->Play(_T("LevelUp"), false, 100);
				//エフェクト.
				EffectData data{};
				data.type = Effect_Level5;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
			}
			break;
		case 5:
			//最終レベル.
			break;

		default: assert(false); break;
	}

	//スローモード.
	if (tmSlowMode.GetIsMove()) {
		//3秒以下になったばかりの時.
		if (tmSlowMode.GetPassTime() <= 3){
			if (!isItemCountDownSound[2]) {
				p_sound->Play(_T("CountDown"), false, 78); //再生.
				isItemCountDownSound[2] = true;
			}
		}
		//2秒以下になったばかりの時.
		if (tmSlowMode.GetPassTime() <= 2) {
			if (!isItemCountDownSound[1]) {
				p_sound->Play(_T("CountDown"), false, 78); //再生.
				isItemCountDownSound[1] = true;
			}
		}
		//1秒以下になったばかりの時.
		if (tmSlowMode.GetPassTime() <= 1) {
			if (!isItemCountDownSound[0]) {
				p_sound->Play(_T("CountDown"), false, 78); //再生.
				isItemCountDownSound[0] = true;
			}
		}
		//時間切れで解除.
		if (tmSlowMode.GetPassTime() <= 0) {
			
			player.SetMode(Player_Normal); //反射モード終了.
			p_sound->Play(_T("PowerDown"), false, 78); //再生.
			
			//リセット.
			tmSlowMode.Reset();
			data.isSlow = false;
			for (int i = 0; i < _countof(isItemCountDownSound); i++) {
				isItemCountDownSound[i] = false;
			}
		}
	}

	UpdateObjects();    //オブジェクト.
	player.Update();    //プレイヤー.
	effectMng.Update(); //エフェクト.
	
	//ポーズする.
	if((p_input->IsPushKeyTime(KEY_P) == 1) || (p_input->IsPushPadBtnTime(PAD_ACD_BTN_UPPER_2) == 1)){
		data.scene = SCENE_PAUSE;
		tmScene[SCENE_GAME].Stop(); //一時停止.
		tmSlowMode.Stop();          //一時停止.
	}
}
void GameManager::UpdateEnd() {

	effectMng.Update(); //エフェクト.

	//特定の操作でタイトルへ.
	if ((p_input->IsPushKeyTime(KEY_SPACE) == 1) || (p_input->IsPushPadBtnTime(PAD_ACD_BTN_UPPER_1) == 1))
	{
		data.scene = SCENE_TITLE; //ゲームシーンへ.
		Reset();
	}
}
void GameManager::UpdatePause() {

	//ポーズ解除.
	if ((p_input->IsPushKeyTime(KEY_P) == 1) || (p_input->IsPushPadBtnTime(PAD_ACD_BTN_UPPER_2) == 1)) {

		data.scene = SCENE_GAME;
		tmScene[SCENE_GAME].Start(); //再開.
		//スローモード中だったなら.
		if (tmSlowMode.GetPassTime() < SLOW_MODE_TIME) {
			tmSlowMode.Start(); //再開.
		}
	}
}

//オブジェクトの更新.
void GameManager::UpdateObjects() {

	//Lv1以上.
	laserMng.Update();
	meteoMng.Update();
	obstacle4_1.Update();
	obstacle4_2.Update();
	item.Update();
	//Lv2以上.
	if (data.level >= 2) {
		mgl[0].Update();
		mgl[1].Update();
	}
	//Lv3以上.
	if (data.level >= 3) {
		obstacle5.Update();
	}
	//Lv4以上.
	if (data.level >= 4) {
		mgl[2].Update();
		mgl[3].Update();
	}
	//Lv5以上.
	if (data.level >= 5) {
		obstacle4_3.Update();
		obstacle4_4.Update();
	}
}

//シーン別描画.
void GameManager::DrawTitle() {
	
	player.Draw();    //プレイヤー. 
	effectMng.Draw(); //エフェクト管理.

	//アニメーション切り替わりポイント.
	const float delay1 = 1;
	const float delay2 = 1.4f;
	const float delay3 = 1.6f;
	const float delay4 = 3;
	const float delay5 = 3;

	//画像の表示.
	{
		const int logoY = WINDOW_HEI/2 - 75;
	
		//切り替え前.
		if (tmScene[SCENE_TITLE].GetPassTime() < delay1) {
			//アニメーション値.
			double anim = p_calc->CalcNumEaseInOut(tmScene[SCENE_TITLE].GetPassTime()/delay1);
			//ロゴ1枚目.
			SetDrawBlendModeST(MODE_ALPHA, 255 * anim);
			imgLogo[0].DrawExtend({WINDOW_WID/2, logoY}, {0.5, 0.5}, ANC_MID, true, true);
		}
		//切り替え後.
		else {
			//アニメーション値.
			double anim1 = p_calc->CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay1    )/1.8);
			double anim2 = p_calc->CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay1-0.4)/1.8); //少し遅延あり.
			//ロゴ1枚目.
			SetDrawBlendModeST(MODE_ALPHA, 255 * (1-anim2));
			imgLogo[0].DrawExtend({WINDOW_WID/2, logoY - anim1*100}, {0.5, 0.5}, ANC_MID, true, true);
			//ロゴ2枚目.
			SetDrawBlendModeST(MODE_ALPHA, 255 * anim1);
			imgLogo[1].DrawExtend({WINDOW_WID/2, logoY - anim1*100}, {0.5, 0.5}, ANC_MID, true, true);
		}
		//描画モードリセット.
		ResetDrawBlendMode();
	}

	//best score.
	if (tmScene[SCENE_TITLE].GetPassTime() > delay2) {

		const int scoreY = WINDOW_HEI/2 + 60;

		//アニメーション値.
		double anim1 = p_calc->CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay3)/1.5);
		double anim2 = p_calc->CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay2)/1.5);
		//テキスト.
		TCHAR text[256];
		_stprintf(text, _T("BEST SCORE: %d"), data.bestScore); //ベストスコア.
		DrawStr str(text, {WINDOW_WID/2, scoreY+1}, COLOR_BEST_SCORE);

		SetDrawBlendModeST(MODE_ALPHA, 255*anim1);
		str.Draw(ANC_MID, data.font2); //スコア値.
		SetDrawBlendModeST(MODE_ALPHA, 255*anim2);
		imgUI[1].DrawExtend({WINDOW_WID/2, scoreY + (10+18*anim2)}, {0.5, 0.4}, ANC_MID, true, true);
		imgUI[1].DrawExtend({WINDOW_WID/2, scoreY - (10+18*anim2)}, {0.5, 0.4}, ANC_MID, true, true);
		ResetDrawBlendMode();
	}
	//PUSH SPACE.
	if (tmScene[SCENE_TITLE].GetPassTime() > delay4) {
		//アニメーション値.
		double anim = p_calc->CalcNumWaveLoop(tmScene[SCENE_TITLE].GetPassTime()-delay4);
		//テキスト.
		DrawStr str(_T("Push SPACE or  X"), {WINDOW_WID/2-5, WINDOW_HEI/2+285}, 0xFFFFFF);
		Circle cir = { {WINDOW_WID/2+92, WINDOW_HEI/2+285-2}, 18, 0xFFFFFF };
		
		SetDrawBlendModeST(MODE_ALPHA, 255*anim);
		str.Draw(ANC_MID, data.font1);    //テキスト.
		DrawCircleST(&cir, false, false); //Xボタンの円.
		ResetDrawBlendMode();
	}
	//隕石破壊.
	if (tmScene[SCENE_TITLE].GetPassTime() > delay5) {
		//まだ出してなければ.
		if (!isTitleAnim) {
			isTitleAnim = true; //一度きり.

			double dig = -130; //角度.

			//エフェクトをいくつか出す.
			for (int i = 0; i < METEO_BREAK_ANIM_CNT; i++) {
				
				double newDig = dig + (float)p_calc->RandNum(-300, 300)/10; //少し角度をずらす.

				EffectData data{}; 
				data.type  = Effect_BreakMeteo;
				data.pos   = { 600, 338 };
				data.vec   = p_calc->CalcVectorDeg(newDig);               //ずらした角度を反映.
				data.speed = ((float)p_calc->RandNum( 20,  100)/10)*1.4f; //速度抽選.
				data.len   = ((float)p_calc->RandNum( 10,  150)/10)*1.4f; //長さ抽選.
				data.ang   =  (float)p_calc->RandNum(  0, 3599)/10;       //角度抽選.
				//エフェクト召喚.
				effectMng.SpawnEffect(&data);
			}
			//サウンド.
			p_sound->Play(_T("Break"), false, 65);
		}
	}
}
void GameManager::DrawReady() {
	
#if false
	bg.Draw(); //背景.
	{
		float anim = min(tmScene[SCENE_READY].GetPassTime(), 1); //アニメーション値.
		Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x000000 };

		SetDrawBlendModeST(MODE_ALPHA, 255*(1-anim));
		DrawBoxST(&box, ANC_LU);
		ResetDrawBlendMode();
	}
#endif

	player.Draw();    //プレイヤー.
	effectMng.Draw(); //エフェクト管理.
	DrawUI();

}
void GameManager::DrawGame() {

	DrawObjects();     //オブジェクト.
	player.Draw();     //プレイヤー.
	effectMng.Draw();  //エフェクト.
	DrawUI();
	DrawReflectMode(); //反射モード演出.

//	DrawFormatString(100, 300, 0xFFFFFF, _T("pad:%d"), GetJoypadInputState(DX_INPUT_PAD1));
}
void GameManager::DrawEnd() {
	
	DrawObjects();    //オブジェクト.
	effectMng.Draw(); //エフェクト.
	{
		float anim = min(tmScene[SCENE_END].GetPassTime(), 1); //アニメーション値.
		Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x000000 };

		SetDrawBlendModeST(MODE_ALPHA, 128*anim);
		DrawBoxST(&box, ANC_LU); //画面を暗くする(UI以外)
		ResetDrawBlendMode();
	}
	DrawUI();

	//終了案内.
	{
		//アニメーション値.
		double anim = p_calc->CalcNumEaseOut(tmScene[SCENE_END].GetPassTime());

		//スコア表示.
		TCHAR text[256];
		_stprintf(
			text, _T("%d + %d(%.3f秒) = %d点"),
			data.scoreBef, (int)(tmScene[SCENE_GAME].GetPassTime() * 10), tmScene[SCENE_GAME].GetPassTime(), data.score
		);
		//テキストの設定.
		DrawStr str1(_T("Time Bonus"), {WINDOW_WID/2, WINDOW_HEI/2-20}, 0xFFFFFF);
		DrawStr str2(text,             {WINDOW_WID/2, WINDOW_HEI/2+20}, 0xFFFFFF);
		//画面中央に文字を表示.
		SetDrawBlendModeST(MODE_ALPHA, 255*anim);
		imgGameOver.DrawExtend({WINDOW_WID/2, 370+30*anim}, {0.5, 0.5}, ANC_MID, true, true); //GAME OVER
		str1.Draw(ANC_MID, data.font1);
		str2.Draw(ANC_MID, data.font1);
		ResetDrawBlendMode();
	}

	const float delay1 = 1.2f;
	const float delay2 = 1.5f;

	//一定時間が経ったら.
	if (tmScene[SCENE_END].GetPassTime() > delay1) {
		//ベストスコア更新.
		if (data.score > data.bestScore) {

			//アニメーション値.
			double anim = p_calc->CalcNumEaseOut((tmScene[SCENE_END].GetPassTime()-delay1)*2);
			//描画.
			SetDrawBlendModeST(MODE_ALPHA, 255*anim);
			imgNewRecord.DrawExtend({WINDOW_WID/2, WINDOW_HEI/2-330+anim*20}, {0.4, 0.4}, ANC_MID, true, true); //NEW RECORD
			ResetDrawBlendMode();
			//サウンド.
			if (!isBestScoreSound) {
				p_sound->Play(_T("BestScore"), false, 65);
				isBestScoreSound = true; //一度のみ.
			}
		}
	}
	//一定時間が経ったら.
	if (tmScene[SCENE_END].GetPassTime() > delay2) {
		
		//アニメーション値.
		double anim = p_calc->CalcNumWaveLoop(tmScene[SCENE_END].GetPassTime()-delay2);
		//テキスト.
		DrawStr str(_T("Push SPACE or  A"), {WINDOW_WID/2-5, WINDOW_HEI/2+145}, 0xFFFFFF);
		Circle cir = { {WINDOW_WID/2+92, WINDOW_HEI/2+145-1}, 18, 0xFFFFFF };
		
		SetDrawBlendModeST(MODE_ALPHA, 255*anim);
		str.Draw(ANC_MID, data.font1);    //テキスト.
		DrawCircleST(&cir, false, false); //Aボタンの円.
		ResetDrawBlendMode();
	}
}
void GameManager::DrawPause() {

	DrawGame(); //ゲームシーンと同じ.
}

//UIの描画.
void GameManager::DrawUI() {

#if defined DEBUG_SPAWN_RATE
	//カウンター.
	DrawFormatStringToHandle(
		10, WINDOW_HEI-75, 0xFFFFFF, data.font2, _T("Counter: %.2f"), data.counter
	);
	//出現間隔割合.
	DrawFormatStringToHandle(
		10, WINDOW_HEI-40, 0xFFFFFF, data.font2, _T("Spawn  : %.2f%%"), data.spawnRate*100
	);
#endif

	//アニメーション値.
	double alpha1   = p_calc->CalcNumEaseInOut( tmScene[SCENE_READY].GetPassTime()-0.1);
	double alpha2   = p_calc->CalcNumEaseInOut( tmScene[SCENE_READY].GetPassTime()-0.2);
	double alpha3   = p_calc->CalcNumEaseInOut( tmScene[SCENE_READY].GetPassTime()-0.3);
	double alpha4   = p_calc->CalcNumEaseInOut((tmScene[SCENE_READY].GetPassTime()-1.0)*2);
	double animSin1 = sin(M_PI* tmScene[SCENE_READY].GetPassTime()-0.1);
	double animSin2 = sin(M_PI*(tmScene[SCENE_READY].GetPassTime()-0.2));
	double animSin3 = sin(M_PI*(tmScene[SCENE_READY].GetPassTime()-0.3));

	//テキスト設定.
	DrawStr str[4] = {
		DrawStr({}, {WINDOW_WID/2,      70+2}, 0xFFFFFF),
		DrawStr({}, {WINDOW_WID/2-350, 150  }, COLOR_BEST_SCORE),
		DrawStr({}, {WINDOW_WID/2,     150  }, COLOR_SCORE),
		DrawStr({}, {WINDOW_WID/2+350, 150  }, COLOR_TIME),
	};
	TCHAR text[256];
	_stprintf(text, _T("LEVEL %d"),        data.level);
	str[0].data.text = text;
	_stprintf(text, _T("BEST SCORE:%05d"), data.bestScore);
	str[1].data.text = text;
	_stprintf(text, _T("SCORE:%05d"),      data.score);
	str[2].data.text = text;
	_stprintf(text, _T("TIME:%.3f"),       tmScene[SCENE_GAME].GetPassTime());
	str[3].data.text = text;
		
	//背景画像.
	imgUI[0].DrawExtend({WINDOW_WID/2, 70}, {0.4, 0.35});
	//テキスト(main)
	SetDrawBlendModeST(MODE_ALPHA, 255 * alpha4);
	str[0].Draw(ANC_MID, data.font4);
	SetDrawBlendModeST(MODE_ALPHA, 255 * alpha1);
	str[1].Draw(ANC_MID, data.font3);
	imgUI[1].DrawExtend({(double)str[1].data.pos.x, (double)str[1].data.pos.y+28}, {0.4, 0.4});
	SetDrawBlendModeST(MODE_ALPHA, 255 * alpha2);
	str[2].Draw(ANC_MID, data.font3);
	imgUI[2].DrawExtend({(double)str[2].data.pos.x, (double)str[2].data.pos.y+28}, {0.4, 0.4});
	SetDrawBlendModeST(MODE_ALPHA, 255 * alpha3);
	str[3].Draw(ANC_MID, data.font3);
	imgUI[3].DrawExtend({(double)str[3].data.pos.x, (double)str[3].data.pos.y+28}, {0.4, 0.4});
	//テキスト(光沢用)
	str[1].data.color = 0xFFFFFF;
	str[2].data.color = 0xFFFFFF;
	str[3].data.color = 0xFFFFFF;
	SetDrawBlendModeST(MODE_ALPHA, 100 * animSin1);
	str[1].Draw(ANC_MID, data.font3);
	SetDrawBlendModeST(MODE_ALPHA, 100 * animSin2);
	str[2].Draw(ANC_MID, data.font3);
	SetDrawBlendModeST(MODE_ALPHA, 100 * animSin3);
	str[3].Draw(ANC_MID, data.font3);

	//描画モードリセット.
	ResetDrawBlendMode();
}
//オブジェクトの描画.
void GameManager::DrawObjects() {

	//Lv1以上.
	laserMng.Draw();
	meteoMng.Draw();
	obstacle4_1.Draw();
	obstacle4_2.Draw();
	item.Draw();
	//Lv2以上.
	if (data.level >= 2) {
		mgl[0].Draw();
		mgl[1].Draw();
	}
	//Lv3以上.
	if (data.level >= 3) {
		obstacle5.Draw();
	}
	//Lv4以上.
	if (data.level >= 4) {
		mgl[2].Draw();
		mgl[3].Draw();
	}
	//Lv5以上.
	if (data.level >= 5){
		obstacle4_3.Draw();
		obstacle4_4.Draw();
	}
}
//反射モード演出.
void GameManager::DrawReflectMode() {

	//カウントダウン中.
	if (tmSlowMode.GetIsMove() && tmSlowMode.GetPassTime() > 0)
	{
		//テキストの設定.
		TCHAR text[256];
		_stprintf(text, _T("%d"), (int)ceil(tmSlowMode.GetPassTime())); //TCHAR型に変数を代入.
		DrawStr str(text, {WINDOW_WID/2, WINDOW_HEI/2}, COLOR_ITEM);

		//画面中央に数字を表示.
		{
			double dec  = p_calc->GetDecimal(tmSlowMode.GetPassTime()); //小数だけ取り出す.
			double anim = p_calc->CalcNumEaseOut(dec);
			
			SetDrawBlendModeST(MODE_ALPHA, _int_r(255 * dec)); //1秒ごとに薄くなる演出.
			//最初の1秒.
			if (tmSlowMode.GetPassTime() > SLOW_MODE_TIME-1) {
				imgReflect.DrawExtend({WINDOW_WID/2, WINDOW_HEI/2}, {0.3+0.2*anim, 0.3+0.2*anim});
			}
			//最後の3秒.
			if (tmSlowMode.GetPassTime() <= 3) {
				str.Draw(ANC_MID, data.font4); //数字.
			}
			ResetDrawBlendMode();
		}
	}
}

//ゲーム終了.
void GameManager::GameEnd() {
	
	//まだ終わってないなら(念のため2重実行されることを防ぐ)
	if (data.scene != SCENE_END) {

		data.scene = SCENE_END; //ゲーム終了へ.
	
		tmScene[SCENE_GAME].Stop(); //停止.
		tmScene[SCENE_END].Start(); //開始.
		data.isSlow = false;
		tmSlowMode.Reset();

		//記録リセット.
		for (int i = 0; i < _countof(isItemCountDownSound); i++) {
			isItemCountDownSound[i] = false;
		}

		data.scoreBef = data.score;                                  //時間加算前のスコアを記録.
		data.score += (int)(tmScene[SCENE_GAME].GetPassTime() * 10); //時間ボーナス加算.

		//最高スコア更新なら保存.
		if (data.score > data.bestScore) {

			File file;
			file.MakeDir(FILE_DATA_PATH);  //フォルダ作成.
			file.Open(FILE_DATA, _T("w")); //ファイルを開く.
			file.WriteInt(data.score);     //スコアを保存.
		}

		//サウンド.
		switch (data.stage) 
		{
			case 1:
				p_sound->FadeOutPlay(_T("BGM1"), 2);
				break;
			case 2:
				p_sound->FadeOutPlay(_T("BGM2"), 2);
				break;

			default: assert(false); break;
		}
	}
}
//アイテムを取った時.
void GameManager::TakeItem() {

	data.isSlow = true;             //スローモードにする.
	data.score += SCORE_TAKE_ITEM;  //スコア加算.
	tmSlowMode.Start();             //スローモード計測開始.

	//記録リセット.
	for (int i = 0; i < _countof(isItemCountDownSound); i++) {
		isItemCountDownSound[i] = false;
	}
}