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

   2025/08/23:
   新障害物「花火」を追加する。Level4で登場予定。
   詳しくは後日相談, なおとに作ってもらう?

   2025/08/27:
   開始時、操作方法分岐を入れて以後の説明文を変えたい。
   ・KEY_SPACE を押したら⇒Push SPACE (キーボード操作)
   ・PAD_XBOX_Aを押したら⇒Push A     (パッド操作)
   など。

   2025/09/08:
   ・花火のバグ修正(スローモードに対応してない, たまに不発する)
   ・配列をvectorに変える。最初にreserveで必要分確保し、デストラクタで解放すればいい。
   ・Calc.hのCalcクラスはなくていい。関数群として置き、KR_Lib名前空間内にCalcという名前空間を置けばOK。

   2025/09/09:
   ・ゲームオーバー画面にヒントが1文出るやつを作りたい。そこでルール説明の補間をする。

   2025/09/16:
   タイトルからメニューに行くとき、パッと画面を変えずにフェードアウトで滑らかに移動するようにしたい。

   2025/09/21:
   [進捗]
   ・アイテムの使用タイミングを変更
   ・スローモードの対応を「speedRate」をかけるだけで良くしたこと
   　旧: counter -= (p_data->isSlow) ? SLOW_MODE_SPEED : 1;
	 新: counter -= p_data->speedRate;
   [改善点]
   ・LevelUp演出, Step演出もエフェクトのため、エフェクトが上限まで出てると表示が出なくなる問題

/---------------------------------------------------------/
   [チュートリアル配分]
   step1: さける 
　   一定時間耐えたら次へ。
   step2: とる
　   アイテムを1回取って解除されたら次へ。
   step3: こわす
　   まずは自動でアイテムを取ってレーザーが反射する様子をみせる。
　   その後、自分で操作させて実演させる。隕石をn個壊せたら次へ。
   step4: 一通りプレイ
　   最後に一通りプレイして確認させる。一定時間経ったらチュートリアル終了。

   ※スコアの説明はチュートリアルにはいらない
   ※メニューにモードごとの説明を入れる(ハイスコアを目指す～など)

   [現在のLevel配分]
   Level1: 通常レーザー×2, 隕石
   Level2: 直線レーザー×2
   Level3: 波紋
   Level4: 花火, アイテム×2
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

   [BGM]
   youtube「Tak_mfk」から使用。
   steam販売の時にはライセンスに注意。
/--------------------------------------------------------*/
/*
   - GameManager.cpp -
   ゲーム全体管理.
*/

#include "BackGround.h"
#include "MenuManager.h"
#include "Stage_Tutorial.h"
#include "Stage_Endless.h"

#include "LaserManager.h"
#include "Obst_NormalLaser.h"
#include "Obst_NormalLaserMain.h"
#include "Obst_StraightLaser.h"
#include "Obst_MeteorManager.h"
#include "Obst_Ripples.h"
#include "Obst_Fireworks.h"

#include "Item.h"
#include "Player.h"

#include "EffectManager.h"
#include "UIManager.h"

#include "GameManager.h"

//ポインタ.
GameData         *gameData     = GameData::GetPtr();
BackGround       *bg           = BackGround::GetPtr();
MenuManager      *menuMng      = MenuManager::GetPtr();
TutorialStage    *tutorialStg  = TutorialStage::GetPtr();
EndlessStage     *endlessStg   = EndlessStage::GetPtr();
LaserManager     *laserMng     = LaserManager::GetPtr();
MeteorManager    *meteorMng    = MeteorManager::GetPtr();
Ripples          *ripples      = Ripples::GetPtr();
FireworksManager *fireworksMng = FireworksManager::GetPtr();
ItemManager      *item         = ItemManager::GetPtr();
Player           *player       = Player::GetPtr();
EffectManager    *effectMng    = EffectManager::GetPtr();
UIManager        *uiMng        = UIManager::GetPtr();
//障害物の実体.
NormalLaser_1 laserNor1;
NormalLaser_2 laserNor2;
NormalLaser_3 laserNor3;
NormalLaser_4 laserNor4;
StraightLaser mgl[4];

using namespace Calc; //計算機能を使用.

//初期化(一回のみ行う)
void GameManager::Init() {

	srand((unsigned)time(NULL)); //乱数初期化.
	
	//実体取得.
	p_input = InputMng::GetPtr();
	p_sound = SoundMng::GetPtr();

	//フォント作成.
	gameData->font1 = CreateFontToHandle(NULL, 26, 1);
	gameData->font2 = CreateFontToHandle(NULL, 30, 1, DX_FONTTYPE_ANTIALIASING);
	gameData->font3 = CreateFontToHandle(NULL, 35, 1, DX_FONTTYPE_ANTIALIASING);
	gameData->font4 = CreateFontToHandle(NULL, 40, 1, DX_FONTTYPE_ANTIALIASING);
	//画像読み込み.
	imgLogo[0].  LoadFile(_T("Resources/Images/REFLINEロゴ_一部.png"));
	imgLogo[1].  LoadFile(_T("Resources/Images/REFLINEロゴ.png"));
	imgUI.       LoadFile(_T("Resources/Images/ui_back_best_score.png"));
	imgNewRecord.LoadFile(_T("Resources/Images/new_record.png"));
	imgGameOver. LoadFile(_T("Resources/Images/gameover.png"));
	imgReflect.  LoadFile(_T("Resources/Images/reflect.png"));
	//サウンド読み込み.
	p_sound->LoadFile(_T("Resources/Sounds/bgm/Virtual Terminal.mp3"),	    _T("BGM_Menu"));     //メニューBGM.
	p_sound->LoadFile(_T("Resources/Sounds/bgm/audiostock_1603723.mp3"),	_T("BGM_Tutorial")); //チュートリアルBGM.
	p_sound->LoadFile(_T("Resources/Sounds/bgm/Scarlet Radiance.mp3"),		_T("BGM_Endless"));  //耐久モードBGM.
	p_sound->LoadFile(_T("Resources/Sounds/bgm/命ナキ者ノ詩.mp3"),		    _T("BGM_Over"));     //ゲームオーバーBGM.

	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_461339.mp3"),		_T("ItemUse")); 	 //アイテム発動.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1116927_cut.mp3"),	_T("CountDown"));	 //カウントダウン.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_63721.mp3"),		_T("PowerDown"));	 //アイテム解除.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1296254.mp3"),		_T("Laser1"));		 //レーザー(発射)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1296256.mp3"),		_T("Laser2"));		 //レーザー(強発射)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_218404.mp3"),		_T("Laser3"));		 //レーザー(反射)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_936158.mp3"),		_T("Ripples"));		 //波紋.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_104974.mp3"),		_T("Break"));		 //隕石破壊.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_981051.mp3"),		_T("PlayerDeath"));
	p_sound->LoadFile(_T("Resources/Sounds/se/決定ボタンを押す23.mp3"),		_T("LevelUp"));
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_184924.mp3"),		_T("BestScore"));	 //最高スコア更新.
	
	//アクション登録.
	p_input->AddAction(_T("GameNext"),  KEY_SPACE);           //キー操作.
	p_input->AddAction(_T("GameNext"),  PAD_ACD_BTN_UPPER_1); //アーケード操作.
	p_input->AddAction(_T("GamePause"), KEY_P);               //キー操作.
	p_input->AddAction(_T("GamePause"), PAD_ACD_BTN_UPPER_2); //アーケード操作.

	//タイマー初期化.
	for(int i = 0; i < SCENE_COUNT; i++){
		tmScene[i] = Timer(COUNT_UP, 0);
	}
	tmGameTime = Timer(COUNT_UP, 0);
	tmSlowMode = Timer(COUNT_DOWN, REFLECT_MODE_TIME);

	//Init処理
	{
		//障害物.
		for (int i = 0; i < _countof(mgl); i++) {
			mgl[i].Init();
		}
		laserNor1.Init();
		laserNor2.Init();
		laserNor3.Init();
		laserNor4.Init();

		bg->Init();
		menuMng->Init();
		tutorialStg->Init();
		endlessStg->Init();
		laserMng->Init();
		meteorMng->Init();
		ripples->Init();
		fireworksMng->Init();
		item->Init();
		player->Init();
		effectMng->Init();
		uiMng->Init();
	}

	//スコア読み込み.
	{
		File file;
		file.Open(FILE_DATA, _T("r"));        //ファイルを開く.
		gameData->bestScore = file.ReadInt(); //数字を読み込んで登録.
	}

	Reset();
}

//リセット(何回でも行う)
void GameManager::Reset() {

	if (gameData->bestScore < gameData->score) {
		gameData->bestScore = gameData->score; //ハイスコア記録.
	}

	//データ.
	gameData->scoreBef      = 0;
	gameData->score         = 0;
	gameData->counter       = 0;
	gameData->speedRate     = 1.0;   //通常は100%
	gameData->spawnRate     = 1.0;   //最初は100%
	gameData->level         = 1;     //最初はLv1
	gameData->isReflectMode = false; //最初はLv1
	isTitleAnim             = false;
	isBestScoreSound        = false;
	isGameStart             = false;
	//サウンド.
	p_sound->StopAll();
	p_sound->Play(_T("BGM_Menu"), true, 90); //メニューBGMを流す.
	//タイマー(全シーン)
	for (int i = 0; i < SCENE_COUNT; i++) {
		tmScene[i].Reset();
	}
	tmGameTime.Reset();

	{
		//レーザー系.
		ResetNorLaser();
		ResetStrLaser();

		menuMng->Reset();
		tutorialStg->Reset();
		laserMng->Reset();
		meteorMng->Reset();
		ripples->Reset();
		fireworksMng->Reset();
		effectMng->Reset();
		item->Reset();
		player->Reset({ WINDOW_WID/2, WINDOW_HEI/2+250 }, true);
	}
}

//更新.
void GameManager::Update() {

	p_input->UpdateKey();    //キー入力更新.
	p_input->UpdatePad();    //コントローラ入力更新.
	p_input->UpdateAction(); //アクション更新.
	p_sound->Update();       //サウンド更新.

	//ポーズしてなければ.
	if (gameData->scene != SCENE_PAUSE) {
		bg->Update();        //背景.
		effectMng->Update(); //エフェクト.
	}

	//シーン別.
	switch (gameData->scene) 
	{
		case SCENE_TITLE:    UpdateTitle();    break;
		case SCENE_MENU:     UpdateMenu();     break;
		case SCENE_GAME:     UpdateGame();     break;
		case SCENE_END:      UpdateEnd();      break;
		case SCENE_PAUSE:    UpdatePause();    break;
	
		default: assert(FALSE); break;
	}

	//特定の操作でゲーム終了
	if (p_input->IsPushPadBtnTime(PAD_ACD_BTN_START) >= FPS * 1) {
		DxLibMain::GetPtr()->GameEnd(); //筐体STARTボタン長押しで終了.
	}
	else if (p_input->IsPushKey(KEY_ESC)) {
		DxLibMain::GetPtr()->GameEnd(); //ESCAPEキーを押したら即終了.
	}
}

//描画.
void GameManager::Draw() {

	bg->Draw(); //背景.

	//シーン別.
	switch (gameData->scene) 
	{
		case SCENE_TITLE:    DrawTitle();    break;
		case SCENE_MENU:     DrawMenu();     break;
		case SCENE_GAME:     DrawGame();     break;
		case SCENE_END:      DrawEnd();      break;
		case SCENE_PAUSE:    DrawPause();    break;

		default: assert(FALSE); break;
	}

	effectMng->Draw(); //エフェクト.
}

//通常レーザーのリセット.
void GameManager::ResetNorLaser() {

	laserNor1.Reset(WINDOW_WID/2, 0, 3, MOVE_RIGHT);
	laserNor2.Reset(WINDOW_WID/2, 0, 3, MOVE_LEFT);
	laserNor3.Reset(WINDOW_WID/2, WINDOW_HEI, 3, MOVE_RIGHT);
	laserNor4.Reset(WINDOW_WID/2, WINDOW_HEI, 3, MOVE_LEFT);
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
	//シーンタイマー開始.
	if (!tmScene[SCENE_TITLE].GetIsMove()) {
		tmScene[SCENE_TITLE].Start();
	}

	//特定の操作でゲーム開始.
	if (p_input->IsPushActionTime(_T("GameNext")) == 1)
	{
		gameData->scene = SCENE_MENU; //メニューシーンへ.

		//隕石破壊アニメーション.
		{
			double dig = -130; //角度.

			//エフェクトをいくつか出す.
			for (int i = 0; i < METEOR_BREAK_ANIM_CNT; i++) {

				double newDig = dig + (float)RandNum(-300, 300)/10; //少し角度をずらす.

				EffectData data{};
				data.type  = Effect_BreakMeteo;
				data.pos   = { 600, 338 };
				data.vec   = CalcVectorDeg(newDig);               //ずらした角度を反映.
				data.speed = ((float)RandNum(20, 100)/10) * 1.4f; //速度抽選.
				data.len   = ((float)RandNum(10, 150)/10) * 1.4f; //長さ抽選.
				data.ang   =  (float)RandNum(0, 3599)/10;         //角度抽選.
				//エフェクト召喚.
				effectMng->SpawnEffect(&data);
			}
			//サウンド.
			p_sound->Play(_T("Break"), false, 65);
		}
	}
}
void GameManager::UpdateMenu() {
	menuMng->Update();
}
void GameManager::UpdateGame() {
	
#if defined _DEBUG //Releaseでは入れない.
	//タイマー加速(Debug)
	if (p_input->IsPushKey(KEY_L) == 1) {
		gameData->counter += 30;
	}
#endif

	//シーンタイマー開始.
	if (!tmScene[SCENE_GAME].GetIsMove()) {
		tmScene[SCENE_GAME].Start();
	}

	//ゲーム開始前.
	if (!isGameStart) {
		//一定時間経ったら.
		if (tmScene[SCENE_GAME].GetPassTime() >= GAME_START_TIME) {

			tmGameTime.Start(); //ゲーム時間計測開始.
			isGameStart = true; //ゲーム開始.
		}
	}
	//ゲーム開始後.
	else{

		UpdateObjects();  //オブジェクト.
		UpdateSlowMode(); //スローモード.

		//ステージ別.
		switch (gameData->stage) 
		{
			case STAGE_TUTORIAL: tutorialStg->Update(); break;
			case STAGE_ENDLESS:  endlessStg->Update();  break;

			default: assert(FALSE); break;
		}
		//ポーズ.
		if (p_input->IsPushActionTime(_T("GamePause")) == 1) {
			gameData->scene = SCENE_PAUSE;
			tmGameTime.Stop(); //一時停止.
			tmSlowMode.Stop(); //一時停止.
		}
	}

	player->Update(); //プレイヤー.
}
void GameManager::UpdateEnd() {

	//シーンタイマー開始.
	if (!tmScene[SCENE_END].GetIsMove()) {
		tmScene[SCENE_END].Start();
	}

	//特定の操作でタイトルへ.
	if (p_input->IsPushActionTime(_T("GameNext")) == 1)
	{
		gameData->scene = SCENE_TITLE; //ゲームシーンへ.
		Reset();
	}
}
void GameManager::UpdatePause() {
	
	//ポーズ解除.
	if (p_input->IsPushActionTime(_T("GamePause")) == 1) {

		gameData->scene = SCENE_GAME;
		tmGameTime.Start(); //再開.
		//スローモード中だったなら.
		if (tmSlowMode.GetPassTime() < REFLECT_MODE_TIME) {
			tmSlowMode.Start(); //再開.
		}
	}
}

//オブジェクトの更新.
void GameManager::UpdateObjects() {

	//Lv1以上.
	laserMng->Update();
	laserNor1.Update();
	laserNor2.Update();
	meteorMng->Update();
	item->Update();

	//Lv2以上.
	if (gameData->level >= 2) {
		mgl[0].Update();
		mgl[1].Update();
	}
	//Lv3以上.
	if (gameData->level >= 3) {
		ripples->Update();
	}
	//Lv4以上.
	if (gameData->level >= 4) {
		fireworksMng->Update();
	}
	//Lv5以上.
	if (gameData->level >= 5) {
		laserNor3.Update();
		laserNor4.Update();
	}
}
//スローモードの更新.
void GameManager::UpdateSlowMode() {

	//スローモード時間判定.
	if (gameData->slowBufCntr > 0) {
		gameData->speedRate  = SLOW_MODE_SPEED; //速度倍率を遅くする.
		gameData->slowBufCntr--;                //カウントを減らす.
	}
	else {
		gameData->speedRate  = 1.0; //速度倍率を戻す.
	}

	//スローモード中.
	if (tmSlowMode.GetIsMove()) {
		//3秒以下になったばかりの時.
		if (tmSlowMode.GetPassTime() <= 3) {
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
			
			p_sound->Play(_T("PowerDown"), false, 78); //再生.
			
			gameData->isReflectMode = false; //反射モード解除.
			gameData->speedRate     = 1.0;   //速度倍率を100%に戻す.
			gameData->slowBufCntr   = 0;     //カウンターを0に.
			tmSlowMode.Reset();
			player->SetMode(Player_Normal);  //通常状態に戻す.
			
			for (int i = 0; i < _countof(isItemCountDownSound); i++) {
				isItemCountDownSound[i] = false;
			}
		}
	}
}

//シーン別描画.
void GameManager::DrawTitle() {
	
	//アニメーション切り替わりポイント.
	const float delay1 = 1;
	const float delay2 = 1.4f;
	const float delay3 = 1.6f;
	const float delay4 = 3;
	const float delay5 = 3;

	//画像の表示.
	{
		const int    logoY   = WINDOW_HEI/2 - 85;
		const DBL_XY imgSize = {0.7, 0.7};
	
		//切り替え前.
		if (tmScene[SCENE_TITLE].GetPassTime() < delay1) {
			//アニメーション値.
			double anim = CalcNumEaseInOut(tmScene[SCENE_TITLE].GetPassTime()/delay1);
			//ロゴ1枚目.
			SetDrawBlendModeST(MODE_ALPHA, 255 * anim);
			imgLogo[0].DrawExtend({WINDOW_WID/2, logoY}, imgSize, ANC_MID, true, true);
		}
		//切り替え後.
		else {
			//アニメーション値.
			double anim1 = CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay1    )/1.8);
			double anim2 = CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay1-0.4)/1.8); //少し遅延あり.
			//ロゴ1枚目.
			SetDrawBlendModeST(MODE_ALPHA, 255 * (1-anim2));
			imgLogo[0].DrawExtend({WINDOW_WID/2, logoY - anim1*100}, imgSize, ANC_MID, true, true);
			//ロゴ2枚目.
			SetDrawBlendModeST(MODE_ALPHA, 255 * anim1);
			imgLogo[1].DrawExtend({WINDOW_WID/2, logoY - anim1*100}, imgSize, ANC_MID, true, true);
		}
		//描画モードリセット.
		ResetDrawBlendMode();
	}

	//best score.
	if (tmScene[SCENE_TITLE].GetPassTime() > delay2) {

		const int drawY = WINDOW_HEI/2 + 130;

		//アニメーション値.
		double anim1 = CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay3)/1.5);
		double anim2 = CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay2)/1.5);
		//テキスト.
		TCHAR text[256];
		_stprintf(text, _T("BEST SCORE: %d"), gameData->bestScore); //ベストスコア.
		DrawStr str(text, {WINDOW_WID/2, drawY+1}, COLOR_BEST_SCORE);

		SetDrawBlendModeST(MODE_ALPHA, 255*anim1);
		str.Draw(ANC_MID, gameData->font2); //スコア値.
		SetDrawBlendModeST(MODE_ALPHA, 255*anim2);
		imgUI.DrawExtend({WINDOW_WID/2, drawY + (10+18*anim2)}, {0.45, 0.4}, ANC_MID, true, true);
		imgUI.DrawExtend({WINDOW_WID/2, drawY - (10+18*anim2)}, {0.45, 0.4}, ANC_MID, true, true);
		ResetDrawBlendMode();
	}
	//PUSH SPACE.
	if (tmScene[SCENE_TITLE].GetPassTime() > delay4) {

		const int drawY = WINDOW_HEI/2+310;

		//アニメーション値.
		double anim = CalcNumWaveLoop(tmScene[SCENE_TITLE].GetPassTime()-delay4);
		//テキスト.
		DrawStr str(_T("Push SPACE or  X"), {WINDOW_WID/2-5, drawY}, 0xFFFFFF);
		Circle cir = { {WINDOW_WID/2+92, drawY-2}, 18, 0xFFFFFF };
		
		SetDrawBlendModeST(MODE_ALPHA, 255*anim);
		str.Draw(ANC_MID, gameData->font1); //テキスト.
		DrawCircleST(&cir, false, false);   //Xボタンの円.
		ResetDrawBlendMode();
	}
}
void GameManager::DrawMenu() {
	menuMng->Draw();
}
void GameManager::DrawGame() {

	DrawObjects();      //オブジェクト.
	player->Draw();     //プレイヤー.
	DrawReflectMode();  //反射モード演出.
	uiMng->Draw();      //UI.
}
void GameManager::DrawEnd() {
	
	DrawObjects(); //オブジェクト.
	{
		float anim = min(tmScene[SCENE_END].GetPassTime(), 1); //アニメーション値.
		Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x000000 };

		SetDrawBlendModeST(MODE_ALPHA, 128*anim);
		DrawBoxST(&box, ANC_LU); //画面を暗くする(UI以外)
		ResetDrawBlendMode();
	}
	uiMng->Draw(); //UI.

	//終了案内.
	{
		//アニメーション値.
		double anim = CalcNumEaseOut(tmScene[SCENE_END].GetPassTime());

		//スコア表示.
		TCHAR text[256];
		_stprintf(
			text, _T("%d + %d(%.3f秒) = %d点"),
			gameData->scoreBef, _int(tmGameTime.GetPassTime() * 10), tmGameTime.GetPassTime(), gameData->score
		);
		//テキストの設定.
		DrawStr str1(_T("Time Bonus"), {WINDOW_WID/2, WINDOW_HEI/2-20}, 0xFFFFFF);
		DrawStr str2(text,             {WINDOW_WID/2, WINDOW_HEI/2+20}, 0xFFFFFF);
		//画面中央に文字を表示.
		SetDrawBlendModeST(MODE_ALPHA, 255*anim);
		imgGameOver.DrawExtend({WINDOW_WID/2, 370+30*anim}, {0.5, 0.5}, ANC_MID, true, true); //GAME OVER
		str1.Draw(ANC_MID, gameData->font1);
		str2.Draw(ANC_MID, gameData->font1);
		ResetDrawBlendMode();
	}

	const float delay1 = 1.2f;
	const float delay2 = 1.5f;

	//一定時間が経ったら.
	if (tmScene[SCENE_END].GetPassTime() > delay1) {
		//ベストスコア更新.
		if (gameData->score > gameData->bestScore) {

			//アニメーション値.
			double anim = CalcNumEaseOut((tmScene[SCENE_END].GetPassTime()-delay1)*2);
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
		double anim = CalcNumWaveLoop(tmScene[SCENE_END].GetPassTime()-delay2);
		//テキスト.
		DrawStr str(_T("Push SPACE or  A"), {WINDOW_WID/2-5, WINDOW_HEI/2+145}, 0xFFFFFF);
		Circle cir = { {WINDOW_WID/2+92, WINDOW_HEI/2+145-1}, 18, 0xFFFFFF };
		
		SetDrawBlendModeST(MODE_ALPHA, 255*anim);
		str.Draw(ANC_MID, gameData->font1); //テキスト.
		DrawCircleST(&cir, false, false);   //Aボタンの円.
		ResetDrawBlendMode();
	}
}
void GameManager::DrawPause() {

	DrawGame(); //ゲームシーンと同じ.
}

//オブジェクトの描画.
void GameManager::DrawObjects() {

	//Lv1以上.
	laserMng->Draw();
	laserNor1.Draw();
	laserNor2.Draw();
	meteorMng->Draw();
	item->Draw();
	//Lv2以上.
	if (gameData->level >= 2) {
		mgl[0].Draw();
		mgl[1].Draw();
	}
	//Lv3以上.
	if (gameData->level >= 3) {
		ripples->Draw();
	}
	//Lv4以上.
	if (gameData->level >= 4) {
		fireworksMng->Draw();
	}
	//Lv5以上.
	if (gameData->level >= 5) {
		laserNor3.Draw();
		laserNor4.Draw();
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
			double dec  = GetDecimal(tmSlowMode.GetPassTime()); //小数だけ取り出す.
			double anim = CalcNumEaseOut(dec);
			
			SetDrawBlendModeST(MODE_ALPHA, _int_r(255 * dec)); //1秒ごとに薄くなる演出.
			//最初の1秒.
			if (tmSlowMode.GetPassTime() > REFLECT_MODE_TIME-1) {
				imgReflect.DrawExtend({WINDOW_WID/2, WINDOW_HEI/2}, {0.3+0.2*anim, 0.3+0.2*anim});
			}
			//最後の3秒.
			if (tmSlowMode.GetPassTime() <= 3) {
				str.Draw(ANC_MID, gameData->font4); //数字.
			}
			ResetDrawBlendMode();
		}
	}
}

//ゲーム終了.
void GameManager::GameEnd() {
	
	//まだ終わってないなら(念のため2重実行されることを防ぐ)
	if (gameData->scene != SCENE_END) {

		gameData->scene = SCENE_END; //ゲーム終了へ.
	
		tmGameTime.Stop(); //停止.
		tmSlowMode.Reset();
		gameData->speedRate = 1.0; //速度倍率を100%に戻す.

		//記録リセット.
		for (int i = 0; i < _countof(isItemCountDownSound); i++) {
			isItemCountDownSound[i] = false;
		}

		gameData->scoreBef = gameData->score;                   //時間加算前のスコアを記録.
		gameData->score += _int(tmGameTime.GetPassTime() * 10); //時間ボーナス加算.

		//最高スコア更新なら保存.
		if (gameData->score > gameData->bestScore) {

			File file;
			file.MakeDir(FILE_DATA_PATH);   //フォルダ作成.
			file.Open(FILE_DATA, _T("w"));  //ファイルを開く.
			file.WriteInt(gameData->score); //スコアを保存.
		}

		//サウンド.
		switch (gameData->stage) 
		{
			case STAGE_TUTORIAL:
				p_sound->FadeOutPlay(_T("BGM_Tutorial"), 2);
				break;
			case STAGE_ENDLESS:
				p_sound->FadeOutPlay(_T("BGM_Endless"), 2);
				break;

			default: assert(FALSE); break;
		}
		//ゲームオーバーBGM.
		p_sound->Play(_T("BGM_Over"), true, 68);
	}
}
//アイテムを使用した時.
void GameManager::ItemUsed() {

	gameData->isReflectMode = true; //反射モードにする.
	tmSlowMode.Start();             //スローモード計測開始.

	//記録リセット.
	for (int i = 0; i < _countof(isItemCountDownSound); i++) {
		isItemCountDownSound[i] = false;
	}
}