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
static GameData*	  gameData;
static BGManager*	  bg;
static UIManager*	  uiMng;
static TutorialStage* tutorialStg;
//参照(KRライブラリ)
static SoundMng*      soundMng;
static InputMng*      inputMng;
static SceneMng*      sceneMng;

using namespace Calc; //計算機能を使用.

// ▼*---=[ GameManager ]=---*▼ //

//初期化(一回のみ行う)
void GameManager::Init() {

	//参照取得.
	gameData	= ManagerInsts::Get<GameData>();
	bg			= ManagerInsts::Get<BGManager>();
	uiMng		= ManagerInsts::Get<UIManager>();
	tutorialStg	= ManagerInsts::Get<TutorialStage>();
	soundMng	= ManagerInsts::Get<SoundMng>();
	inputMng	= ManagerInsts::Get<InputMng>();
	sceneMng	= ManagerInsts::Get<SceneMng>();

	srand((unsigned)time(NULL)); //乱数初期化.

	//[KrLib] カメラ.
	Camera::SetPos(App::GetWindowSize().ToDbl()/2);

	try {
		//[KrLib] 画像.
		DrawImgMng::SetPath(_T("Resources/Images/")); //共通パスの設定.
		DrawImgMng::LoadFile(_T("logo_text_only.png"),		_T("logo"));
		DrawImgMng::LoadFile(_T("logo_all.png"),			_T("logo_all"));
		DrawImgMng::LoadFile(_T("new_record.png"),			_T("new_record"));
		DrawImgMng::LoadFile(_T("gameover.png"),			_T("gameover"));
		DrawImgMng::LoadFile(_T("reflect.png"),				_T("reflect"));
		DrawImgMng::LoadFile(_T("player_normal.png"),		_T("player_nor"));
		DrawImgMng::LoadFile(_T("player_reflect.png"),		_T("player_ref"));
		DrawImgMng::LoadFile(_T("item.png"),				_T("item"));
		DrawImgMng::LoadFile(_T("light_color_ref.png"),		_T("item_light"));
		DrawImgMng::LoadFile(_T("light_color_nor.png"),		_T("player_light_nor"));
		DrawImgMng::LoadFile(_T("light_color_ref.png"),		_T("player_light_ref"));
		DrawImgMng::LoadFile(_T("menu_endless.png"),		_T("menu0"));				//ゲーム開始.
		DrawImgMng::LoadFile(_T("menu_tutorial.png"),		_T("menu1"));				//チュートリアル.
		DrawImgMng::LoadFile(_T("menu_title.png"),			_T("menu2"));				//タイトルに戻る.
		DrawImgMng::LoadFile(_T("bg_normal.png"),			_T("bg_normal"));
		DrawImgMng::LoadFile(_T("bg_reflect.png"),			_T("bg_reflect"));
		DrawImgMng::LoadFile(_T("reflect_mode_frame.png"),	_T("reflect_mode_frame"));
		DrawImgMng::LoadFile(_T("ui_back_level.png"),		_T("ui_back_level"));
		DrawImgMng::LoadFile(_T("ui_back_best_score.png"),	_T("ui_back_best_score"));
		DrawImgMng::LoadFile(_T("ui_back_score.png"),		_T("ui_back_score"));
		DrawImgMng::LoadFile(_T("ui_back_time.png"),		_T("ui_back_time"));
		DrawImgMng::LoadFile(_T("score100.png"),			_T("score100"));
		DrawImgMng::LoadFile(_T("score500.png"),			_T("score500"));

		//[KrLib] サウンド.
		soundMng->SetPath(_T("Resources/Sounds/")); //共通パスの設定.
		soundMng->LoadFile(_T("bgm/Virtual Terminal.mp3"),		_T("BGM_Menu"));		//メニューBGM.
		soundMng->LoadFile(_T("bgm/audiostock_1603723.mp3"),	_T("BGM_Tutorial"));	//チュートリアルBGM.
		soundMng->LoadFile(_T("bgm/Scarlet Radiance.mp3"),		_T("BGM_Endless_1"));	//エンドレスモードBGM1.
		soundMng->LoadFile(_T("bgm/CODE FROST.mp3"),            _T("BGM_Endless_2"));   //エンドレスモードBGM2.
		soundMng->LoadFile(_T("bgm/Frost Vector.mp3"),          _T("BGM_Endless_3"));   //エンドレスモードBGM3.
		soundMng->LoadFile(_T("bgm/Bullet Acceleration.mp3"),   _T("BGM_Endless_4"));   //エンドレスモードBGM4.
		soundMng->LoadFile(_T("bgm/Shattered Icefront.mp3"),    _T("BGM_Endless_5"));   //エンドレスモードBGM5.
		soundMng->LoadFile(_T("bgm/命ナキ者ノ詩.mp3"),			_T("BGM_Over"));		//ゲームオーバーBGM.

		soundMng->LoadFile(_T("se/audiostock_1636674.mp3"),		_T("MenuCursor"));		//メニューカーソル音.
		soundMng->LoadFile(_T("se/audiostock_1636651.mp3"),		_T("MenuOK"));			//メニュー決定音.
		soundMng->LoadFile(_T("se/audiostock_461339.mp3"),		_T("ItemUse")); 		//アイテム発動.
		soundMng->LoadFile(_T("se/player_dash.mp3"),			_T("PlayerDash")); 		//ダッシュ音.
		soundMng->LoadFile(_T("se/audiostock_1116927_cut.mp3"), _T("CountDown"));		//カウントダウン.
		soundMng->LoadFile(_T("se/audiostock_63721.mp3"),		_T("PowerDown"));		//アイテム解除.
		soundMng->LoadFile(_T("se/audiostock_1296254.mp3"),		_T("Laser1"));			//レーザー(発射)
		soundMng->LoadFile(_T("se/audiostock_1296256.mp3"),		_T("Laser2"));			//レーザー(強発射)
		soundMng->LoadFile(_T("se/audiostock_218404.mp3"),		_T("Laser3"));			//レーザー(反射)
		soundMng->LoadFile(_T("se/audiostock_936158.mp3"),		_T("Ripples"));			//波紋.
		soundMng->LoadFile(_T("se/fireworks.mp3"),				_T("Fireworks"));		//花火.
		soundMng->LoadFile(_T("se/audiostock_104974.mp3"),		_T("Break"));			//隕石破壊.
		soundMng->LoadFile(_T("se/audiostock_981051.mp3"),		_T("PlayerDeath"));
		soundMng->LoadFile(_T("se/決定ボタンを押す23.mp3"),		_T("LevelUp"));
		soundMng->LoadFile(_T("se/audiostock_184924.mp3"),		_T("BestScore"));		//最高スコア更新.
	}
	catch (const ErrorMsg& err){
		Debug::Log(_T("GameManager::Init"), err.GetMsg());
		return;
	}
	
	//[KrLib] アクション.
	{
		//キー操作.
		inputMng->AddAction(_T("GameNext"),		KeyID::Space);
		inputMng->AddAction(_T("GamePause"),	KeyID::P);
		inputMng->AddAction(_T("PlayerDash"),	KeyID::ShiftL); //固定キー機能を切っておくこと推奨.
		inputMng->AddAction(_T("PlayerDash"),	KeyID::ShiftR);
		inputMng->AddAction(_T("MenuUp"),		KeyID::W);
		inputMng->AddAction(_T("MenuUp"),		KeyID::Up);
		inputMng->AddAction(_T("MenuDown"),		KeyID::S);
		inputMng->AddAction(_T("MenuDown"),		KeyID::Down);
		inputMng->AddAction(_T("MenuNext"),		KeyID::Space);
		inputMng->AddAction(_T("MenuNext"),		KeyID::Enter);

#if defined INPUT_CHANGE_ARCADE
		//アーケード操作.
		inputMng->AddAction(_T("GameNext"),		PadArcadeID::BtnUpper1);
		inputMng->AddAction(_T("GamePause"),	PadArcadeID::BtnUpper2);
		inputMng->AddAction(_T("PlayerDash"),	PadArcadeID::BtnUpper3);
		inputMng->AddAction(_T("GameQuit"),		PadArcadeID::BtnStart);
		inputMng->AddAction(_T("MenuUp"),		PadArcadeID::Up);
		inputMng->AddAction(_T("MenuDown"),		PadArcadeID::Down);
		inputMng->AddAction(_T("MenuNext"),		PadArcadeID::BtnUpper1);
#else
		//コントローラ操作.
		inputMng->AddAction(_T("GameNext"),		PadXboxID::A);
		inputMng->AddAction(_T("GamePause"),	PadXboxID::X);
		inputMng->AddAction(_T("PlayerDash"),	PadXboxID::B);
		inputMng->AddAction(_T("GameQuit"),		PadXboxID::Menu);
		inputMng->AddAction(_T("MenuUp"),		PadXboxID::Up);
		inputMng->AddAction(_T("MenuDown"),		PadXboxID::Down);
		inputMng->AddAction(_T("MenuNext"),		PadXboxID::A);
#endif
	}

	//[KrLib] シーン.
	sceneMng->AddScene(&titleScene, _T("Title"));
	sceneMng->AddScene(&menuScene,  _T("Menu"));
	sceneMng->AddScene(&gameScene,  _T("Game"));
	sceneMng->AddScene(&endScene,   _T("End"));

	//フォント.
	gameData->fonts["size18"].CreateFontH(_T(""), 20, 1, FontTypeID::Anti);
	gameData->fonts["size26"].CreateFontH(_T(""), 26, 1, FontTypeID::Anti);
	gameData->fonts["size30"].CreateFontH(_T(""), 30, 1, FontTypeID::Anti);
	gameData->fonts["size35"].CreateFontH(_T(""), 35, 1, FontTypeID::Anti);
	gameData->fonts["size40"].CreateFontH(_T(""), 40, 1, FontTypeID::Anti);

	//[score.data]
	File file;
	//ファイルがあれば開く.
	if (file.Open(FILE_DATA_SCORE, FileOpenMode::Read)) {
		gameData->bestScore = file.ReadInt();		//数字を読み込んで登録.
		uiMng->SetBestScore(gameData->bestScore);	//ベストスコア反映.
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
	gameData->scoreBef      = 0;
	gameData->score         = 0;
	gameData->counter       = 0;
	gameData->speedRate     = 1.0;   //通常は100%
	gameData->spawnRate     = 1.0;   //最初は100%
	gameData->level         = 1;     //最初はLv1
	gameData->isReflectMode = false; //最初はLv1

	//最初はタイトルシーン.
	sceneMng->SetScene(_T("Title"));

	//管理クラスリセット.
	StopObjects();

	//サウンド.
	soundMng->StopAll();

#if !defined BGM_NONE
	//メニューBGMを流す.
	if (auto i = soundMng->Get(_T("BGM_Menu"))) {
		i->Play(true, 90);
	}
#endif

	//ゲームシーンのBGM抽選.
	{
		//抽選するBGM名.
		const vector<MY_STRING> bgmName = {
			_T("BGM_Endless_1"),
			_T("BGM_Endless_2"),
			_T("BGM_Endless_3"),
			_T("BGM_Endless_4"),
			_T("BGM_Endless_5"),
		};
		//何番目のBGMを使うか(bgmName配列の中から抽選)
		const int bgmNo = Calc::RandNum(0, _int(bgmName.size() - 1));
		//BGM名を保存.
		gameSceneBgm = bgmName[bgmNo];

		Debug::Log(_T("BGM"), bgmName[bgmNo]);
	}
}

//更新.
void GameManager::Update() {

	//ポーズ操作.
	if (inputMng->IsPushActionTime(_T("GamePause")) == 1) {
		//ゲームシーンのみポーズ可.
		if (sceneMng->GetSceneName() == _T("Game")){

			if (gameData->isPause) {
				GamePauseEnd(); //ポーズ解除.
			}
			else {
				GamePause();    //ポーズする.
			}
		}
	}
	//特定の操作でゲーム終了
	if (inputMng->IsPushActionTime(_T("GameQuit")) >= FPS * 1) {
		App::Quit(); //ボタン長押しで終了.
	}
	else if (inputMng->IsPushKey(KeyID::Esc)) {
		App::Quit(); //ESCAPEキーを押したら即終了.
	}
}

//描画.
void GameManager::Draw() {

	//ポーズ画面.
	if (gameData->isPause) {
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

	gameData->isPause = true;
	bg->Pause();       //背景のポーズ.
	gameScene.Pause(); //ゲームシーンのポーズ.

	sceneMng->SetAutoExeMode(MngAutoExe::DrawOnly); //シーン      : 描画のみ.
	DrawOnlyObjects();                              //オブジェクト: 描画のみ.
}
//ポーズ解除.
void GameManager::GamePauseEnd() {

	gameData->isPause = false;
	bg->PauseEnd();       //背景のポーズ解除.
	gameScene.PauseEnd(); //ゲームシーンのポーズ解除.

	sceneMng->SetAutoExeMode(MngAutoExe::Active);   //シーン      : 稼働.
	RestartObjects();                               //オブジェクト: 稼働.
}
//ポーズ画面.
void GameManager::DrawPause() {

#if !defined NO_SHOW_PAUSE
	DrawStr str(_T("PAUSE"), App::GetWindowRect().GetMid(), 0xffffff);
	str.Draw(Anchor::Mid, gameData->fonts["size40"].GetFont());
#endif
}

//ゲーム終了(死亡)
void GameManager::GameOver() {

	//念のため2重実行されることを防ぐ用.
	if (sceneMng->GetSceneName() != _T("End")) {

		//ステージ別.
		switch (gameData->stage)
		{
			case Stage_Tutorial:
			{
				sceneMng->SetScene(_T("End")); //終了シーンへ.
			}
			break;

			case Stage_Endless:
			{
				sceneMng->SetScene(_T("End")); //終了シーンへ.

				gameData->speedRate = 1.0;                             //速度倍率を100%に戻す.
				gameData->scoreBef = gameData->score;                  //時間加算前のスコアを記録.
				gameData->score += _int(gameScene.GetGameTime() * 10); //時間ボーナス加算.

				//[score.data]
				if (gameData->score > gameData->bestScore) {

					File file;
					//ファイルを開く.
					if (file.Open(FILE_DATA_SCORE, FileOpenMode::Write)) {
						file.WriteInt(gameData->score);			//スコアを保存.
						gameData->bestScore = gameData->score;	//スコア更新.
						endScene.SignBestScore();				//ハイスコアのサイン送信.
					}
				}

				//[playlog.data]
				{
					DATEDATA date;
					GetDateTime(&date); //現在時刻取得.

					MY_STRING dateStr = Format::StrFormat(
						//フォーマット.
						_T("[%d/%0.2d/%0.2d %0.2d:%0.2d.%0.2d] DeviceName:%s / Level:%d / Score:%0.5d / Time:%.1f\n"), 
						//変数挿入.
						date.Year, date.Mon, date.Day, date.Hour, date.Min, date.Sec, 
						Device::GetComputerNameStr(), gameData->level, gameData->score, gameScene.GetGameTime()
					);

					//ファイルへ追記.
					File file;
					//ファイルを開く.
					if (file.Open(FILE_DATA_PLAYLOG, FileOpenMode::Out | FileOpenMode::App)) {
						file.WriteString(dateStr);
					}
				}

#if !defined BGM_NONE
				//BGMフェードアウト.
				if (auto i = soundMng->Get(gameSceneBgm)) {
					i->FadeOutPlay(2); //再生.
				}
				//ゲームオーバーBGM.
				if (auto i = soundMng->Get(_T("BGM_Over"))) {
					i->Play(true, 68); //再生.
				}
#endif
			}
			break;

			default: assert(0); break;
		}
	}

}

//アイテムを使用した時.
void GameManager::ItemUsed() {

	gameData->isReflectMode = true; //反射モードにする.
	gameScene.ItemUsed();           //アイテム使用処理.
	
	//チュートリアルなら指示送信.
	if (gameData->stage == Stage_Tutorial) {
		tutorialStg->SetTakeItem(true);       //指示を送る.
		tutorialStg->SetReflectFinish(false); //falseにする(指示取り消し)
	}
}

//スローモード開始.
void GameManager::SlowModeStart() {

	//速度倍率を遅くする.
	gameData->speedRate = SLOW_MODE_SPEED;
	//一定時間スローにする.
	gameData->slowBufCntr = SLOW_MODE_BUF_F;
}

//オブジェクト停止.
void GameManager::StopObjects() {

	//管理クラス取得.
	vector<ManagerBase*> mngs = {
		ManagerInsts::Get<Player>(),
		ManagerInsts::Get<LaserManager>(),
		ManagerInsts::Get<ItemManager>(),
		ManagerInsts::Get<NormalLaser>(),
		ManagerInsts::Get<MeteorManager>(),
		ManagerInsts::Get<StraightLaser>(),
		ManagerInsts::Get<Ripples>(),
		ManagerInsts::Get<Fireworks>(),
		ManagerInsts::Get<EndlessStage>(),
		ManagerInsts::Get<TutorialStage>()
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
		ManagerInsts::Get<Player>(),
		ManagerInsts::Get<LaserManager>(),
		ManagerInsts::Get<ItemManager>(),
		ManagerInsts::Get<NormalLaser>(),
		ManagerInsts::Get<MeteorManager>(),
		ManagerInsts::Get<StraightLaser>(),
		ManagerInsts::Get<Ripples>(),
		ManagerInsts::Get<Fireworks>(),
		ManagerInsts::Get<EndlessStage>(),
		ManagerInsts::Get<TutorialStage>()
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
		ManagerInsts::Get<Player>(),
		ManagerInsts::Get<LaserManager>(),
		ManagerInsts::Get<ItemManager>(),
		ManagerInsts::Get<NormalLaser>(),
		ManagerInsts::Get<MeteorManager>(),
		ManagerInsts::Get<StraightLaser>(),
		ManagerInsts::Get<Ripples>(),
		ManagerInsts::Get<Fireworks>(),
		ManagerInsts::Get<EndlessStage>(),
		ManagerInsts::Get<TutorialStage>()
	};
	//全ループ.
	for (auto& i : mngs) {
		if (i->GetAutoExeMode() != MngAutoExe::Stop) {
			i->BackAutoExeMode(); //元のモードへ.
		}
	}
}