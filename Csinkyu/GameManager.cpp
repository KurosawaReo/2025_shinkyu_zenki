/*
   - GameManager.cpp -
   ゲーム全体管理.
*/
#include "BGManager.h"
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

#include "GameData.h"
#include "GameManager.h"

using namespace Calc; //計算機能を使用.

//ポインタ.
static GameData         &gameData     = GameData::GetInst();
static BGManager        &bg           = BGManager::GetInst();
static MenuManager      &menuMng      = MenuManager::GetInst();
static TutorialStage    &tutorialStg  = TutorialStage::GetInst();
static EndlessStage     &endlessStg   = EndlessStage::GetInst();
static LaserManager     &laserMng     = LaserManager::GetInst();
static MeteorManager    &meteorMng    = MeteorManager::GetInst();
static Ripples          &ripples      = Ripples::GetInst();
static FireworksManager &fireworksMng = FireworksManager::GetInst();
static ItemManager      &item         = ItemManager::GetInst();
static Player           &player       = Player::GetInst();
static EffectManager    &effectMng    = EffectManager::GetInst();
static UIManager        &uiMng        = UIManager::GetInst();

//デストラクタ.
GameManager::~GameManager() {
	//解放.
	delete laserNor1;
	delete laserNor2;
	delete laserNor3;
	delete laserNor4;
	delete laserStr[0];
	delete laserStr[1];
}
//初期化(一回のみ行う)
void GameManager::Init() {

#if defined _DEBUG 
	//Debug::Log(L"[Debug] GameManager::Init() 開始");
#endif

	srand((unsigned)time(NULL)); //乱数初期化.

	//カメラ位置.
	Camera::SetPos(App::GetWindowRect().GetMid().ToDbl());
	
	//実体生成.
	laserNor1   = new NormalLaser_1();
	laserNor2   = new NormalLaser_2();
	laserNor3   = new NormalLaser_3();
	laserNor4   = new NormalLaser_4();
	laserStr[0] = new StraightLaser();
	laserStr[1] = new StraightLaser();

	//フォント作成.
	gameData.font1 = CreateFontToHandle(NULL, 26, 1);
	gameData.font2 = CreateFontToHandle(NULL, 30, 1, DX_FONTTYPE_ANTIALIASING);
	gameData.font3 = CreateFontToHandle(NULL, 35, 1, DX_FONTTYPE_ANTIALIASING);
	gameData.font4 = CreateFontToHandle(NULL, 40, 1, DX_FONTTYPE_ANTIALIASING);
	//画像読み込み.
	DrawImgMng::LoadFile(_T("Resources/Images/logo_text_only.png"),     "logo");
	DrawImgMng::LoadFile(_T("Resources/Images/logo_all.png"),           "logo_all");
	DrawImgMng::LoadFile(_T("Resources/Images/ui_back_best_score.png"), "ui_back_best_score");
	DrawImgMng::LoadFile(_T("Resources/Images/new_record.png"),         "new_record");
	DrawImgMng::LoadFile(_T("Resources/Images/gameover.png"),           "gameover");
	DrawImgMng::LoadFile(_T("Resources/Images/reflect.png"),            "reflect");
	//サウンド読み込み.
	SoundMng::LoadFile(_T("Resources/Sounds/bgm/Virtual Terminal.mp3"),	     "BGM_Menu");     //メニューBGM.
	SoundMng::LoadFile(_T("Resources/Sounds/bgm/audiostock_1603723.mp3"),	 "BGM_Tutorial"); //チュートリアルBGM.
	SoundMng::LoadFile(_T("Resources/Sounds/bgm/Scarlet Radiance.mp3"),		 "BGM_Endless");  //耐久モードBGM.
	SoundMng::LoadFile(_T("Resources/Sounds/bgm/命ナキ者ノ詩.mp3"),		     "BGM_Over");     //ゲームオーバーBGM.

	SoundMng::LoadFile(_T("Resources/Sounds/se/audiostock_1636674.mp3"),	 "MenuCursor");	  //メニューカーソル音.
	SoundMng::LoadFile(_T("Resources/Sounds/se/audiostock_1636651.mp3"),	 "MenuOK");		  //メニュー決定音.
	SoundMng::LoadFile(_T("Resources/Sounds/se/audiostock_461339.mp3"),		 "ItemUse"); 	  //アイテム発動.
	SoundMng::LoadFile(_T("Resources/Sounds/se/audiostock_1116927_cut.mp3"), "CountDown");	  //カウントダウン.
	SoundMng::LoadFile(_T("Resources/Sounds/se/audiostock_63721.mp3"),		 "PowerDown");	  //アイテム解除.
	SoundMng::LoadFile(_T("Resources/Sounds/se/audiostock_1296254.mp3"),	 "Laser1");		  //レーザー(発射)
	SoundMng::LoadFile(_T("Resources/Sounds/se/audiostock_1296256.mp3"),	 "Laser2");		  //レーザー(強発射)
	SoundMng::LoadFile(_T("Resources/Sounds/se/audiostock_218404.mp3"),		 "Laser3");		  //レーザー(反射)
	SoundMng::LoadFile(_T("Resources/Sounds/se/audiostock_936158.mp3"),		 "Ripples");	  //波紋.
	SoundMng::LoadFile(_T("Resources/Sounds/se/audiostock_104974.mp3"),		 "Break");		  //隕石破壊.
	SoundMng::LoadFile(_T("Resources/Sounds/se/audiostock_981051.mp3"),		 "PlayerDeath");
	SoundMng::LoadFile(_T("Resources/Sounds/se/決定ボタンを押す23.mp3"),	 "LevelUp");
	SoundMng::LoadFile(_T("Resources/Sounds/se/audiostock_184924.mp3"),		 "BestScore");	  //最高スコア更新.

	//アクション登録.
	{
		//キー操作.
		InputMng::AddAction("GameNext",   KeyID::Space);
		InputMng::AddAction("GamePause",  KeyID::P);
		InputMng::AddAction("PlayerDash", KeyID::ShiftL); //固定キー機能を切っておくこと推奨.
		InputMng::AddAction("PlayerDash", KeyID::ShiftR);
#if defined INPUT_CHANGE_ARCADE
		//アーケード操作.
		InputMng::AddAction("GameNext",   PadArcadeID::BtnUpper1);
//		InputMng::AddAction("GamePause",  PadArcadeID::BtnUpper2);
		InputMng::AddAction("PlayerDash", PadArcadeID::BtnUpper3);
		InputMng::AddAction("GameQuit",   PadArcadeID::BtnStart);
#else
		//コントローラ操作.
		InputMng::AddAction("GameNext",   PadXboxID::A);
//		InputMng::AddAction("GamePause",  PadXboxID::X);
		InputMng::AddAction("PlayerDash", PadXboxID::B);
		InputMng::AddAction("GameQuit",   PadXboxID::Menu);
#endif
	}

	//タイマー初期化.
	for(int i = 0; i < SCENE_COUNT; i++){
		tmScene[i] = Timer(TimerMode::CountUp, 0);
	}
	tmGameTime    = Timer(TimerMode::CountUp, 0);
	tmReflectMode = Timer(TimerMode::CountDown, REFLECT_MODE_TIME);

	//fps表示用.
#if defined DEBUG_SHOW_FPS
	tmFps = TimerMicro(TimerMode::CountUp, 0);
	tmFps.Start();
#endif

	//スコア読み込み.
	{
		File file;
		//ファイルを開く.
		if (file.Open(FILE_DATA, _T("r")).GetCode() == 0) {
			gameData.bestScore = file.ReadInt();        //数字を読み込んで登録.
			uiMng.SetDisBestScore(gameData.bestScore); //ベストスコア表示更新.
		}
	}

	App::Reset();

#if defined _DEBUG
	//Debug::Log(L"[Debug] GameManager::Init() 終了");
#endif
}

//リセット(何回でも行う)
void GameManager::Reset() {

	//データ.
	gameData.scoreBef      = 0;
	gameData.score         = 0;
	gameData.counter       = 0;
	gameData.speedRate     = 1.0;   //通常は100%
	gameData.spawnRate     = 1.0;   //最初は100%
	gameData.level         = 1;     //最初はLv1
	gameData.isReflectMode = false; //最初はLv1
	isTitleAnim             = false;
	isBestScoreSound        = false;
	isGameStart             = false;
	isBestScore             = false;
	for (int i = 0; i < 3; i++) {
		isItemCountDownSound[i] = false;
	}
	//タイマー.
	for (int i = 0; i < SCENE_COUNT; i++) {
		tmScene[i].Reset();
	}
	tmGameTime.Reset();
	tmReflectMode.Reset();

	//サウンド.
	SoundMng::StopAll();
#if !defined BGM_NONE
	//メニューBGMを流す.
	if (auto i = SoundMng::Get("BGM_Menu")) {
		i->Play(true, 90);
	}
#endif
}

//更新.
void GameManager::Update() {

	InputMng::UpdateKey();    //キー入力更新.
	InputMng::UpdatePad();    //コントローラ入力更新.
	InputMng::UpdateAction(); //アクション更新.
	SoundMng::Update();       //サウンド更新.

	//ポーズしてなければ更新.
	if (!gameData.isPause) {

		//背景, エフェクト.
		bg.Update();
		effectMng.Update(); 
		//シーン別.
		switch (gameData.scene) 
		{
			case SCENE_TITLE: UpdateTitle(); break;
			case SCENE_MENU:  UpdateMenu();  break;
			case SCENE_GAME:  UpdateGame();  break;
			case SCENE_END:   UpdateEnd();   break;
	
			default: assert(FALSE); break;
		}
	}

	//ポーズ操作.
	if (InputMng::IsPushActionTime("GamePause") == 1) {
		if (gameData.isPause) {
			GamePauseEnd(); //ポーズ解除.
		}
		else {
			GamePause();    //ポーズする.
		}
	}
	//特定の操作でゲーム終了
	if (InputMng::IsPushActionTime("GameQuit") >= FPS * 1) {
		App::Quit(); //ボタン長押しで終了.
	}
	else if (InputMng::IsPushKey(KeyID::Esc)) {
		App::Quit(); //ESCAPEキーを押したら即終了.
	}
}

//描画.
void GameManager::Draw() {

	bg.Draw(); //背景.

	//シーン別.
	switch (gameData.scene) 
	{
		case SCENE_TITLE: DrawTitle(); break;
		case SCENE_MENU:  DrawMenu();  break;
		case SCENE_GAME:  DrawGame();  break;
		case SCENE_END:   DrawEnd();   break;

		default: assert(FALSE); break;
	}
	effectMng.Draw(); //エフェクト.

	//ポーズ画面.
	if (gameData.isPause) {
		DrawPause();
	}
	
	//コントローラ操作表示.
#if defined DEBUG_CONTR_INPUT
	DrawFormatString(20, WINDOW_HEI-40, 0xFFFFFF, _T("Pad Input: %d"), GetJoypadInputState(DX_INPUT_PAD1));
#endif
	//fps表示用.
#if defined DEBUG_SHOW_FPS
	DrawFormatString(20, WINDOW_HEI-40, 0xFFFFFF, _T("FPS: %f"), tmFps.GetFps());
#endif
}

//通常レーザーのリセット.
void GameManager::ResetNorLaser() {

	laserNor1->Reset();
	laserNor2->Reset();
	laserNor3->Reset();
	laserNor4->Reset();
}
//直線レーザーのリセット.
void GameManager::ResetStrLaser() {

	for (int i = 0; i < _countof(laserStr); i++) {
		laserStr[i]->Reset();
	}
}

//シーン別更新.
void GameManager::UpdateTitle()
{
	//シーンタイマー開始.
	if (tmScene[SCENE_TITLE].GetState() != TimerState::Active) {
		tmScene[SCENE_TITLE].Start();
	}
	//特定の操作でゲーム開始.
	if (InputMng::IsPushActionTime("GameNext") == 1) {
		gameData.scene = SCENE_MENU; //メニューシーンへ.
	}
}
void GameManager::UpdateMenu() {
	menuMng.Update();
}
void GameManager::UpdateGame() {

	//シーンタイマー開始.
	if (tmScene[SCENE_GAME].GetState() != TimerState::Active) {
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

		UpdateReflectMode(); //反射モード.

		//ステージ別.
		switch (gameData.stage) 
		{
			case STAGE_TUTORIAL: tutorialStg.Update(); break;
			case STAGE_ENDLESS:  endlessStg.Update();  break;

			default: assert(FALSE); break;
		}
	}

	player.Update(); //プレイヤー.
}
void GameManager::UpdateEnd() {

	//シーンタイマー開始.
	if (tmScene[SCENE_END].GetState() != TimerState::Active) {
		tmScene[SCENE_END].Start();
	}

	//チュートリアルの場合.
	if (gameData.stage == STAGE_TUTORIAL) {

		UpdateGame(); //ゲームシーンと同じ動作をする.

		//死亡後一定時間経過したら.
		if (tmScene[SCENE_END].GetPassTime() >= TUTORIAL_RESPAWN_TIME) {
			tmScene[SCENE_END].Reset();   //タイマーリセット.
			player.PlayerRevival();      //復活.
			gameData.scene = SCENE_GAME; //ゲームシーンへ戻る.
		}
	}
	//チュートリアル以外の場合.
	else {
		//特定の操作でタイトルへ.
		if (InputMng::IsPushActionTime("GameNext") == 1)
		{
			gameData.scene = SCENE_TITLE;
			uiMng.SetDisBestScore(gameData.bestScore); //ベストスコア表示更新.
			Reset();
		}
	}
}

//反射モードの更新.
void GameManager::UpdateReflectMode() {

	//反射モード時間判定.
	if (gameData.slowBufCntr > 0) {
		gameData.speedRate = SLOW_MODE_SPEED; //速度倍率を遅くする.
		gameData.slowBufCntr--;               //カウントを減らす.
	}
	else {
		gameData.speedRate = 1.0; //速度倍率を戻す.
	}

	//反射モード中.
	if (tmReflectMode.GetState() == TimerState::Active) {
		//3秒以下になったばかりの時.
		if (tmReflectMode.GetPassTime() <= 3) {
			if (!isItemCountDownSound[2]) {
				if (auto i = SoundMng::Get("CountDown")){
					i->Play(false, 78); //再生.
				}
				isItemCountDownSound[2] = true;
			}
		}
		//2秒以下になったばかりの時.
		if (tmReflectMode.GetPassTime() <= 2) {
			if (!isItemCountDownSound[1]) {
				if (auto i = SoundMng::Get("CountDown")) {
					i->Play(false, 78); //再生.
				}
				isItemCountDownSound[1] = true;
			}
		}
		//1秒以下になったばかりの時.
		if (tmReflectMode.GetPassTime() <= 1) {
			if (!isItemCountDownSound[0]) {
				if (auto i = SoundMng::Get("CountDown")) {
					i->Play(false, 78); //再生.
				}
				isItemCountDownSound[0] = true;
			}
		}
		//時間切れで解除.
		if (tmReflectMode.GetPassTime() <= 0) {
			ReflectModeEnd();
		}
	}
}

//シーン別描画.
void GameManager::DrawTitle() {

	//操作方法明記.
	DrawStr howPlay(_T(""), {30, WINDOW_HEI - 30}, 0x00FFFF);
	{
#if defined INPUT_CHANGE_ARCADE
		howPlay.text = _T("アーケード操作");
#else
		howPlay.text = _T("コントローラ操作");
#endif
		howPlay.Draw(Anchor::LD);

		//枠線グラデーション.
		const DBL_XY howPlayPos  = howPlay.pos.ToDbl();
		const DBL_XY howPlaySize = howPlay.GetTextSize().ToDbl();
		const int margin = 5;

		GradLine line;
		line.AddPoint(howPlayPos.Add(-margin,              margin               ), { 0, 255, 255 });
 		line.AddPoint(howPlayPos.Add(howPlaySize.x+margin, margin               ), { 0, 100, 255 });
		line.AddPoint(howPlayPos.Add(howPlaySize.x+margin, -howPlaySize.y-margin), { 0, 255, 255 });
		line.AddPoint(howPlayPos.Add(-margin,              -howPlaySize.y-margin), { 0, 100, 255 });
		line.Draw(true);
	}

	//アニメーション切り替わりポイント.
	const float delay1 = 1;
	const float delay2 = 1.4f;
	const float delay3 = 1.6f;
	const float delay4 = 3;
	const float delay5 = 3;

	//画像の表示.
	{
		const int    logoY   = WINDOW_HEI/2 - 80;
		const DBL_XY imgSize = {0.7, 0.7};
	
		//切り替え前.
		if (tmScene[SCENE_TITLE].GetPassTime() < delay1) {
			//アニメーション値.
			double anim = AnimEaseInOut(tmScene[SCENE_TITLE].GetPassTime()/delay1);
			//ロゴ1枚目.
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim);
				DrawImgMng::Get("logo")->DrawExtend({WINDOW_WID/2, logoY}, imgSize, Anchor::Mid, true, true);
			}
		}
		//切り替え後.
		else {
			//アニメーション値.
			//1枚目と2枚目の切り替えが自然になるよう、anim2は遅延ありにする.
			double anim1 = AnimEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay1    )/1.8);
			double anim2 = AnimEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay1-0.4)/1.8);
			//ロゴ1枚目.
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * (1-anim2));
				DrawImgMng::Get("logo")->DrawExtend({WINDOW_WID/2, logoY - anim1*80}, imgSize, Anchor::Mid, true, true);
			}
			//ロゴ2枚目.
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim1);
				DrawImgMng::Get("logo_all")->DrawExtend({WINDOW_WID/2, logoY - anim1*80}, imgSize, Anchor::Mid, true, true);
			}
		}
	}

	//best score.
	if (tmScene[SCENE_TITLE].GetPassTime() >= delay2) {

		const int drawY = WINDOW_HEI/2 + 130;

		//アニメーション値.
		double anim1 = AnimEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay3)/1.5);
		double anim2 = AnimEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay2)/1.5);
		//テキスト.
		TCHAR text[256];
		_stprintf(text, _T("BEST SCORE: %d"), gameData.bestScore); //ベストスコア.
		DrawStr str(text, {WINDOW_WID/2, drawY+1}, COLOR_BEST_SCORE);
		{
			DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim1);
			str.Draw(Anchor::Mid, gameData.font2); //スコア値.
		}
		{
			DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim2);

			//UI
			DrawImgMng::Get("ui_back_best_score")->
				DrawExtend({WINDOW_WID/2, drawY + (10+18*anim2)}, {0.45, 0.4}, Anchor::Mid, true, true);
			DrawImgMng::Get("ui_back_best_score")->
				DrawExtend({WINDOW_WID/2, drawY - (10+18*anim2)}, {0.45, 0.4}, Anchor::Mid, true, true);
		}
	}
	//PUSH SPACE.
	if (tmScene[SCENE_TITLE].GetPassTime() >= delay4) {

		const int drawY = WINDOW_HEI/2+310;

		//アニメーション値.
		double anim = AnimWaveLoop(tmScene[SCENE_TITLE].GetPassTime()-delay4);
		//テキスト.
		DrawStr str(_T("Push SPACE or Ⓐ"), {WINDOW_WID/2-5, drawY}, 0xFFFFFF);
		{
			DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim);
			str.Draw(Anchor::Mid, gameData.font1); //テキスト.
		}
	}
	//隕石破壊アニメーション.
	if (!isTitleAnim) {
		if (tmScene[SCENE_TITLE].GetPassTime() >= delay5) {

			EffectData data{};
			data.type  = Effect_BreakMeteor;
			data.pos   = { 580, 310 };

			double dig = -130; //角度.

			//エフェクトをいくつか出す.
			for (int i = 0; i < METEOR_BREAK_ANIM_CNT; i++) {

				double newDig = dig + (float)RandNum(-300, 300)/10; //少し角度をずらす.
				data.vec   = VectorDeg(newDig);						//ずらした角度を反映.
				data.speed = ((float)RandNum(20, 100)/10) * 1.4f;   //速度抽選.
				data.len   = ((float)RandNum(10, 150)/10) * 1.4f;   //長さ抽選.
				data.ang   =  (float)RandNum(0, 3599)/10;           //角度抽選.
				effectMng.SpawnEffect(&data);						//エフェクト召喚.
			}
			//サウンド.
			if (auto i = SoundMng::Get("Break")) {
				i->Play(false, 65); //再生.
			}

			isTitleAnim = true;
		}
	}
}
void GameManager::DrawMenu() {
	menuMng.Draw();
}
void GameManager::DrawGame() {

	player.Draw();		//プレイヤー.
	DrawReflectMode();  //反射モード演出.
	uiMng.Draw();		//UI.

	//ゲームが開始したら.
	if (isGameStart) {
		//ステージ別.
		switch (gameData.stage)
		{
			case STAGE_TUTORIAL: tutorialStg.Draw(); break;
			case STAGE_ENDLESS:  endlessStg.Draw();  break;

			default: assert(FALSE); break;
		}
	}
}
void GameManager::DrawEnd() {
	
	//ステージ別.
	switch (gameData.stage) 
	{
		case STAGE_TUTORIAL: tutorialStg.Draw(); break;
		case STAGE_ENDLESS:  endlessStg.Draw();  break;

		default: assert(FALSE); break;
	}
	//黒フィルター.
	{
		double anim = AnimEaseInOut(tmScene[SCENE_END].GetPassTime()); //アニメーション値.
		Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x000000 };
		{
			DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 128 * anim);
			DrawBoxKR(box, Anchor::LU); //画面を暗くする(UI以外)
		}
	}
	uiMng.Draw(); //UI.

	//チュートリアルの場合.
	if (gameData.stage == STAGE_TUTORIAL) {
		
		//アニメーション値.
		double anim = AnimEaseOut(tmScene[SCENE_END].GetPassTime());
		//テキスト.
		DrawStr str(_T("チュートリアルではその場で復活します..."), {WINDOW_WID/2, WINDOW_HEI/2}, 0x00FFFF);
		{
			DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim);

			//GAME OVER
			DrawImgMng::Get("gameover")->DrawExtend({WINDOW_WID/2, 370+30*anim}, {0.5, 0.5}, Anchor::Mid, true, true);
			//テキスト.
			str.Draw(Anchor::Mid, gameData.font2);
		}
	}
	//チュートリアル以外の場合.
	else {
		//終了案内.
		{
			//アニメーション値.
			double anim = AnimEaseOut(tmScene[SCENE_END].GetPassTime());

			//スコア表示.
			TCHAR text[256];
			_stprintf(
				text, _T("%d + %d(%.3f秒) = %d点"),
				gameData.scoreBef, _int(tmGameTime.GetPassTime() * 10), tmGameTime.GetPassTime(), gameData.score
			);
			//テキストの設定.
			DrawStr str1(_T("Time Bonus"), {WINDOW_WID/2, WINDOW_HEI/2-20}, 0xFFFFFF);
			DrawStr str2(text,             {WINDOW_WID/2, WINDOW_HEI/2+20}, 0xFFFFFF);
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim);

				DrawImgMng::Get("gameover")->DrawExtend({WINDOW_WID/2, 370+30*anim}, {0.5, 0.5}, Anchor::Mid, true, true); //GAME OVER
				//画面中央に文字を表示.
				str1.Draw(Anchor::Mid, gameData.font1);
				str2.Draw(Anchor::Mid, gameData.font1);
			}
		}

		const float delay1 = 1.2f;
		const float delay2 = 1.5f;

		//一定時間が経ったら.
		if (tmScene[SCENE_END].GetPassTime() > delay1) {
			//ベストスコア更新.
			if (isBestScore) {

				//アニメーション値.
				double anim = AnimEaseOut((tmScene[SCENE_END].GetPassTime()-delay1)*2);
				//描画.
				{
					DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim);
					DrawImgMng::Get("new_record")->DrawExtend({WINDOW_WID/2, WINDOW_HEI/2-330+anim*20}, {0.4, 0.4}, Anchor::Mid, true, true); //NEW RECORD
				}
				//サウンド.
				if (!isBestScoreSound) {
					if (auto i = SoundMng::Get("BestScore")) {
						i->Play(false, 65); //再生.
					}
					isBestScoreSound = true; //一度のみ.
				}
			}
		}
		//一定時間が経ったら.
		if (tmScene[SCENE_END].GetPassTime() > delay2) {
		
			//アニメーション値.
			double anim = AnimWaveLoop(tmScene[SCENE_END].GetPassTime()-delay2);
			//テキスト.
			DrawStr str(_T("Push SPACE or Ⓐ"), {WINDOW_WID/2-5, WINDOW_HEI/2+145}, 0xFFFFFF);		
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim);
				str.Draw(Anchor::Mid, gameData.font1); //テキスト.
			}
		}
	}
}

//反射モード演出.
void GameManager::DrawReflectMode() {

	//カウントダウン中.
	if (tmReflectMode.GetState() == TimerState::Active && 
		tmReflectMode.GetPassTime() > 0)
	{
		//テキストの設定.
		MY_STRING text = _to_mystr((int)ceil(tmReflectMode.GetPassTime()));
		DrawStr str(text, {WINDOW_WID/2, WINDOW_HEI/2}, COLOR_ITEM);

		//画面中央に数字を表示.
		{
			double dec  = GetDecimal(tmReflectMode.GetPassTime()); //小数だけ取り出す.
			double anim = AnimEaseOut(dec);
			{
				//1秒ごとに薄くなる演出.
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * dec);

				//最初の1秒.
				if (tmReflectMode.GetPassTime() > REFLECT_MODE_TIME-1) {
					DrawImgMng::Get("reflect")->DrawExtend({WINDOW_WID / 2, WINDOW_HEI / 2}, {0.3 + 0.2 * anim, 0.3 + 0.2 * anim});
				}
				//最後の3秒.
				if (tmReflectMode.GetPassTime() <= 3) {
					str.Draw(Anchor::Mid, gameData.font4); //数字.
				}
			}
		}
	}
}

//ポーズする.
void GameManager::GamePause() {
	gameData.isPause = true;
	//稼働中のタイマーを一時停止.
	tmGameTime.Pause();
	tmReflectMode.Pause();
	bg.PauseAnim();
}
//ポーズ解除.
void GameManager::GamePauseEnd() {
	gameData.isPause = false;
	//稼働中だったタイマーは再開.
	if (tmGameTime.GetState() == TimerState::Pause) {
		tmGameTime.Start();
	}
	if (tmReflectMode.GetState() == TimerState::Pause) {
		tmReflectMode.Start();
	}
	bg.RestartAnim();
}
//ポーズ画面.
void GameManager::DrawPause() {
	DrawStr str(_T("PAUSE"), App::GetWindowRect().GetMid(), 0xffffff);
	str.Draw(Anchor::Mid, gameData.font4);
}

//ゲーム終了(死亡)
void GameManager::GameOver() {

	//ステージ別.
	switch (gameData.stage)
	{
		case STAGE_TUTORIAL:
		{
			gameData.scene = SCENE_END; //ゲーム終了へ.
		}
		break;

		case STAGE_ENDLESS:
		{
			//まだ終わってないなら(念のため2重実行されることを防ぐ)
			if (gameData.scene != SCENE_END) {
				gameData.scene = SCENE_END; //ゲーム終了へ.
	
				tmGameTime.Stop(); //停止.
				tmReflectMode.Reset();
				gameData.speedRate = 1.0; //速度倍率を100%に戻す.

				//記録リセット.
				for (int i = 0; i < _countof(isItemCountDownSound); i++) {
					isItemCountDownSound[i] = false;
				}

				gameData.scoreBef = gameData.score;                   //時間加算前のスコアを記録.
				gameData.score += _int(tmGameTime.GetPassTime() * 10); //時間ボーナス加算.

				//最高スコア更新なら.
				if (gameData.score > gameData.bestScore) {

					File file;
					//ファイルを開く.
					if (file.Open(FILE_DATA, _T("w"), true).GetCode() == 0) {
						file.WriteInt(gameData.score);    //スコアを保存.
					}
					gameData.bestScore = gameData.score; //スコア更新.
					isBestScore = true;
				}

#if !defined BGM_NONE
				//BGM停止.
				if (auto i = SoundMng::Get("BGM_Endless")) {
					i->FadeOutPlay(2); //再生.
				}
				//ゲームオーバーBGM.;
				if (auto i = SoundMng::Get("BGM_Over")) {
					i->Play(true, 68); //再生.
				}
#endif
			}
			break;

			default: assert(FALSE); break;
		}
	}
}
//アイテムを使用した時.
void GameManager::ItemUsed() {

	gameData.isReflectMode = true; //反射モードにする.
	tmReflectMode.Start();          //反射モード計測開始.

	//記録リセット.
	for (int i = 0; i < _countof(isItemCountDownSound); i++) {
		isItemCountDownSound[i] = false;
	}

	//チュートリアルなら指示送信.
	if (gameData.stage == STAGE_TUTORIAL) {
		tutorialStg.SetTakeItem(true);       //指示を送る.
		tutorialStg.SetReflectFinish(false); //falseにする(指示取り消し)
	}
}
//反射モード終了.
void GameManager::ReflectModeEnd() {

	tmReflectMode.Reset();

	gameData.isReflectMode = false; //反射モード解除.
	gameData.speedRate     = 1.0;   //速度倍率を100%に戻す.
	gameData.slowBufCntr   = 0;     //カウンターを0に.
	player.SetMode(Player_Normal);  //通常状態に戻す.
			
	//ゲームオーバーBGM.;
	if (auto i = SoundMng::Get("PowerDown")) {
		i->Play(false, 78); //再生.
	}
	
	//記録リセット.
	for (int i = 0; i < _countof(isItemCountDownSound); i++) {
		isItemCountDownSound[i] = false;
	}

	//チュートリアルなら指示送信.
	if (gameData.stage == STAGE_TUTORIAL) {
		tutorialStg.SetReflectFinish(true); //指示を送る.
	}
}