/*
   - GameManager.cpp -
   ゲーム全体管理.
*/
#include "GameManager.h"

//依存関係.
#include "GameData.h"
#include "BGManager.h"
#include "LaserManager.h"
#include "Obst_NormalLaser.h"
#include "Obst_StraightLaser.h"
#include "Obst_MeteorManager.h"
#include "Obst_Ripples.h"
#include "Obst_Fireworks.h"
#include "Item.h"
#include "UIManager.h"
#include "EffectManager.h"
#include "Stage_Tutorial.h"
#include "Stage_Endless.h"
//参照.
static GameData         &gameData     = GameData::GetInst();
static BGManager        &bg           = BGManager::GetInst();
static UIManager        &uiMng        = UIManager::GetInst();
static TutorialStage    &tutorialStg  = TutorialStage::GetInst();

using namespace Calc; //計算機能を使用.

// ▼*---=[ GameManager ]=---*▼ //

GameManager GameManager::inst; //自身のインスタンス.

//初期化(一回のみ行う)
void GameManager::Init() {

	srand((unsigned)time(NULL)); //乱数初期化.

	//[KrLib] カメラ.
	Camera::SetPos(App::GetWindowSize().ToDbl()/2);

	//[KrLib] 画像.
	DrawImgMng::SetPath(_T("Resources/Images/")); //共通パスの設定.
	DrawImgMng::LoadFile(_T("logo_text_only.png"),		"logo");
	DrawImgMng::LoadFile(_T("logo_all.png"),			"logo_all");
	DrawImgMng::LoadFile(_T("new_record.png"),			"new_record");
	DrawImgMng::LoadFile(_T("gameover.png"),			"gameover");
	DrawImgMng::LoadFile(_T("reflect.png"),				"reflect");
	DrawImgMng::LoadFile(_T("player_normal.png"),		"player_nor");
	DrawImgMng::LoadFile(_T("player_reflect.png"),		"player_ref");
	DrawImgMng::LoadFile(_T("item.png"),				"item");
	DrawImgMng::LoadFile(_T("light_color_ref.png"),		"item_light");
	DrawImgMng::LoadFile(_T("light_color_nor.png"),		"player_light_nor");
	DrawImgMng::LoadFile(_T("light_color_ref.png"),		"player_light_ref");
	DrawImgMng::LoadFile(_T("menu_endless.png"),		"menu0");	//ゲーム開始.
	DrawImgMng::LoadFile(_T("menu_tutorial.png"),		"menu1");	//チュートリアル.
	DrawImgMng::LoadFile(_T("menu_title.png"),			"menu2");	//タイトルに戻る.
	DrawImgMng::LoadFile(_T("bg_normal.png"),			"bg_normal");
	DrawImgMng::LoadFile(_T("bg_reflect.png"),			"bg_reflect");
	DrawImgMng::LoadFile(_T("reflect_mode_frame.png"),	"reflect_mode_frame");
	DrawImgMng::LoadFile(_T("ui_back_level.png"),		"ui_back_level");
	DrawImgMng::LoadFile(_T("ui_back_best_score.png"),	"ui_back_best_score");
	DrawImgMng::LoadFile(_T("ui_back_score.png"),		"ui_back_score");
	DrawImgMng::LoadFile(_T("ui_back_time.png"),		"ui_back_time");
	DrawImgMng::LoadFile(_T("score100.png"),			"score100");
	DrawImgMng::LoadFile(_T("score500.png"),			"score500");
	
	//[KrLib] サウンド.
	SoundMng::SetPath(_T("Resources/Sounds/")); //共通パスの設定.
	SoundMng::LoadFile(_T("bgm/Virtual Terminal.mp3"),	    "BGM_Menu");     //メニューBGM.
	SoundMng::LoadFile(_T("bgm/audiostock_1603723.mp3"),	"BGM_Tutorial"); //チュートリアルBGM.
	SoundMng::LoadFile(_T("bgm/Scarlet Radiance.mp3"),		"BGM_Endless");  //耐久モードBGM.
	SoundMng::LoadFile(_T("bgm/命ナキ者ノ詩.mp3"),		    "BGM_Over");     //ゲームオーバーBGM.
	SoundMng::LoadFile(_T("se/audiostock_1636674.mp3"),		"MenuCursor");	 //メニューカーソル音.
	SoundMng::LoadFile(_T("se/audiostock_1636651.mp3"),		"MenuOK");		 //メニュー決定音.
	SoundMng::LoadFile(_T("se/audiostock_461339.mp3"),		"ItemUse"); 	 //アイテム発動.
	SoundMng::LoadFile(_T("se/audiostock_1116927_cut.mp3"), "CountDown");	 //カウントダウン.
	SoundMng::LoadFile(_T("se/audiostock_63721.mp3"),		"PowerDown");	 //アイテム解除.
	SoundMng::LoadFile(_T("se/audiostock_1296254.mp3"),		"Laser1");		 //レーザー(発射)
	SoundMng::LoadFile(_T("se/audiostock_1296256.mp3"),		"Laser2");		 //レーザー(強発射)
	SoundMng::LoadFile(_T("se/audiostock_218404.mp3"),		"Laser3");		 //レーザー(反射)
	SoundMng::LoadFile(_T("se/audiostock_936158.mp3"),		"Ripples");		 //波紋.
	SoundMng::LoadFile(_T("se/audiostock_104974.mp3"),		"Break");		 //隕石破壊.
	SoundMng::LoadFile(_T("se/audiostock_981051.mp3"),		"PlayerDeath");
	SoundMng::LoadFile(_T("se/audiostock_1688971.mp3"),     "PlayerDash");   //プレイヤーのダッシュ音.
	SoundMng::LoadFile(_T("se/決定ボタンを押す23.mp3"),		"LevelUp");
	SoundMng::LoadFile(_T("se/audiostock_184924.mp3"),		"BestScore");	 //最高スコア更新.

	//[KrLib] アクション.
	{
		//キー操作.
		InputMng::AddAction("GameNext",   KeyID::Space);
		InputMng::AddAction("GamePause",  KeyID::P);
		InputMng::AddAction("PlayerDash", KeyID::ShiftL); //固定キー機能を切っておくこと推奨.
		InputMng::AddAction("PlayerDash", KeyID::ShiftR);
#if defined INPUT_CHANGE_ARCADE
		//アーケード操作.
		InputMng::AddAction("GameNext",   PadArcadeID::BtnUpper1);
		InputMng::AddAction("GamePause",  PadArcadeID::BtnUpper2);
		InputMng::AddAction("PlayerDash", PadArcadeID::BtnUpper3);
		InputMng::AddAction("GameQuit",   PadArcadeID::BtnStart);
#else
		//コントローラ操作.
		InputMng::AddAction("GameNext",   PadXboxID::A);
		InputMng::AddAction("GamePause",  PadXboxID::X);
		InputMng::AddAction("PlayerDash", PadXboxID::B);
		InputMng::AddAction("GameQuit",   PadXboxID::Menu);
#endif
	}
	//[KrLib] シーン.
	ManagerInsts::GetInst().Get<SceneMng>()->SetOrder(ORDER_SCENE_MNG); //実行順の設定.
	SceneMng::AddScene(&titleScene, "Title");
	SceneMng::AddScene(&menuScene,  "Menu");
	SceneMng::AddScene(&gameScene,  "Game");
	SceneMng::AddScene(&endScene,   "End");

	//フォント.
	gameData.fonts["size18"].CreateFontH(_T(""), 20, 1, FontTypeID::Anti);
	gameData.fonts["size26"].CreateFontH(_T(""), 26, 1, FontTypeID::Anti);
	gameData.fonts["size30"].CreateFontH(_T(""), 30, 1, FontTypeID::Anti);
	gameData.fonts["size35"].CreateFontH(_T(""), 35, 1, FontTypeID::Anti);
	gameData.fonts["size40"].CreateFontH(_T(""), 40, 1, FontTypeID::Anti);

	//スコア読み込み.
	try {
		File file;
		file.Open(FILE_DATA, _T("r"));             //ファイルを開く.
		gameData.bestScore = file.ReadInt();       //数字を読み込んで登録.
		uiMng.SetDisBestScore(gameData.bestScore); //ベストスコア表示更新.
	}
	catch (const ErrorMsg& err) {
		Debug::Log(_T("スコア読み込み"), err.GetResult());
	}

	//fps表示用.
#if defined DEBUG_SHOW_FPS
	tmFps = TimerMicro(TimerMode::CountUp, 0);
	tmFps.Start();
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

	//最初はタイトルシーン.
	SceneMng::SetScene("Title");

	//管理クラスリセット.
	StopObjects();

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

	//ポーズ操作.
	if (InputMng::IsPushActionTime("GamePause") == 1) {
		//ゲームシーンのみポーズ可.
		if (SceneMng::GetSceneName() == "Game"){

			if (gameData.isPause) {
				GamePauseEnd(); //ポーズ解除.
			}
			else {
				GamePause();    //ポーズする.
			}
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

//ポーズする.
void GameManager::GamePause() {

	gameData.isPause = true;
	bg.Pause();        //背景のポーズ.
	gameScene.Pause(); //ゲームシーンのポーズ.

	SceneMng::SetAutoExeMode(MngAutoExe::DrawOnly); //シーン      : 描画のみ.
	DrawOnlyObjects();                              //オブジェクト: 描画のみ.
}
//ポーズ解除.
void GameManager::GamePauseEnd() {

	gameData.isPause = false;
	bg.PauseEnd();        //背景のポーズ解除.
	gameScene.PauseEnd(); //ゲームシーンのポーズ解除.

	SceneMng::SetAutoExeMode(MngAutoExe::Active);   //シーン      : 稼働.
	RestartObjects();                               //オブジェクト: 稼働.
}
//ポーズ画面.
void GameManager::DrawPause() {

#if !defined NO_SHOW_PAUSE
	DrawStr str(_T("PAUSE"), App::GetWindowRect().GetMid(), 0xffffff);
	str.Draw(Anchor::Mid, gameData.fonts["size40"].GetFont());
#endif
}

//ゲーム終了(死亡)
void GameManager::GameOver() {

	//念のため2重実行されることを防ぐ用.
	if (SceneMng::GetSceneName() != "End") {

		//ステージ別.
		switch (gameData.stage)
		{
			case Stage_Tutorial:
			{
				SceneMng::SetScene("End"); //終了シーンへ.
			}
			break;

			case Stage_Endless:
			{
				SceneMng::SetScene("End"); //終了シーンへ.

				gameData.speedRate = 1.0;                             //速度倍率を100%に戻す.
				gameData.scoreBef = gameData.score;                   //時間加算前のスコアを記録.
				gameData.score += _int(gameScene.GetGameTime() * 10); //時間ボーナス加算.

				//ハイスコア更新.
				if (gameData.score > gameData.bestScore) {

					File file;
					try {
						file.Open(FILE_DATA, _T("w"), true); //ファイルを開く.
						file.WriteInt(gameData.score);       //スコアを保存.
						gameData.bestScore = gameData.score; //スコア更新.
						endScene.SignBestScore();            //ハイスコアのサイン送信.
					}
					catch (const ErrorMsg& err) {
						Debug::Log(_T("ハイスコア更新"), err.GetResult());
					}
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
	gameScene.ItemUsed();          //アイテム使用処理.
	
	//チュートリアルなら指示送信.
	if (gameData.stage == Stage_Tutorial) {
		tutorialStg.SetTakeItem(true);       //指示を送る.
		tutorialStg.SetReflectFinish(false); //falseにする(指示取り消し)
	}
}

//オブジェクト停止.
void GameManager::StopObjects() {

	//管理クラス取得.
	vector<ManagerBase*> mngs = {
		ManagerInsts::GetInst().Get<Player>(),
		ManagerInsts::GetInst().Get<LaserManager>(),
		ManagerInsts::GetInst().Get<ItemManager>(),
		ManagerInsts::GetInst().Get<NormalLaser>(),
		ManagerInsts::GetInst().Get<MeteorManager>(),
		ManagerInsts::GetInst().Get<StraightLaser>(),
		ManagerInsts::GetInst().Get<Ripples>(),
		ManagerInsts::GetInst().Get<Fireworks>(),
		ManagerInsts::GetInst().Get<EndlessStage>(),
		ManagerInsts::GetInst().Get<TutorialStage>()
	};
	//全ループ.
	for (auto& i : mngs) {
		i->SetAutoExeMode(MngAutoExe::Stop);
	}
}
//オブジェクト描画のみ.
void GameManager::DrawOnlyObjects() {

	//管理クラス取得.
	vector<ManagerBase*> mngs = {
		ManagerInsts::GetInst().Get<Player>(),
		ManagerInsts::GetInst().Get<LaserManager>(),
		ManagerInsts::GetInst().Get<ItemManager>(),
		ManagerInsts::GetInst().Get<NormalLaser>(),
		ManagerInsts::GetInst().Get<MeteorManager>(),
		ManagerInsts::GetInst().Get<StraightLaser>(),
		ManagerInsts::GetInst().Get<Ripples>(),
		ManagerInsts::GetInst().Get<Fireworks>(),
		ManagerInsts::GetInst().Get<EndlessStage>(),
		ManagerInsts::GetInst().Get<TutorialStage>()
	};
	//全ループ.
	for (auto& i : mngs) {
		//稼働してるクラスをDrawOnlyに変更.
		if (i->GetAutoExeMode() != MngAutoExe::Stop) {
			i->SetAutoExeMode(MngAutoExe::DrawOnly);
		}
	}
}
//オブジェクト稼働再開.
void GameManager::RestartObjects() {

	//管理クラス取得.
	vector<ManagerBase*> mngs = {
		ManagerInsts::GetInst().Get<Player>(),
		ManagerInsts::GetInst().Get<LaserManager>(),
		ManagerInsts::GetInst().Get<ItemManager>(),
		ManagerInsts::GetInst().Get<NormalLaser>(),
		ManagerInsts::GetInst().Get<MeteorManager>(),
		ManagerInsts::GetInst().Get<StraightLaser>(),
		ManagerInsts::GetInst().Get<Ripples>(),
		ManagerInsts::GetInst().Get<Fireworks>(),
		ManagerInsts::GetInst().Get<EndlessStage>(),
		ManagerInsts::GetInst().Get<TutorialStage>()
	};
	//全ループ.
	for (auto& i : mngs) {
		if (i->GetAutoExeMode() != MngAutoExe::Stop) {
			i->BackAutoExeMode(); //元のモードへ.
		}
	}
}