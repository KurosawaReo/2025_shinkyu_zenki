/*
   - Scene_Game.cpp -
*/
#include "Scene_Game.h"

//依存関係.
#include "GameData.h"
#include "GameManager.h"
#include "Player.h"
#include "BGManager.h"
#include "UIManager.h"
#include "Stage_Tutorial.h"
#include "Stage_Endless.h"
//参照.
static GameData&		gameData	= GameData::GetInst();
static GameManager&		gameMng		= GameManager::GetInst();
static Player&			player		= Player::GetInst();
static BGManager&		bgMng		= BGManager::GetInst();
static UIManager&		uiMng		= UIManager::GetInst();
static TutorialStage&	tutorialStg = TutorialStage::GetInst();

//初期化.
void GameScene::Init() {
	timer         = Timer(TimerMode::CountUp, 0);
	tmGameTime    = Timer(TimerMode::CountUp, 0);
	tmReflectMode = Timer(TimerMode::CountDown, REFLECT_MODE_TIME);
}
//リセット.
void GameScene::Reset() {

	//タイマーリセット.
	timer.Reset();
	tmGameTime.Reset();
	tmReflectMode.Reset();

	itemSoundCnt = 0;
	isGameStart = false;
}
//入った瞬間.
void GameScene::Enter() {
	//まだ動いてなければ.
	if (timer.GetState() != TimerState::Active) {
		timer.Start(); //タイマー開始.
	}
}
//抜けた瞬間.
void GameScene::Exit() {
	//チュートリアル以外のみ.
	if (gameData.stage != Stage_Tutorial) {
		itemSoundCnt = 0;
		timer.Stop();          //演出用タイマー停止.
		tmGameTime.Stop();     //ゲーム時間停止.
		tmReflectMode.Reset(); //反射モードリセット.

		//オブジェクトの動作停止.
		gameMng.DrawOnlyObjects();
	}
}
//更新.
void GameScene::Update() {

	//ゲーム開始前.
	if (!isGameStart) {

		ManagerInsts::GetInst().Get<Player>()->SetAutoExeMode(MngAutoExe::Active);
		ManagerInsts::GetInst().Get<UIManager>()->SetAutoExeMode(MngAutoExe::Active);

		//一定時間経ったら.
		if (timer.GetPassTime() >= GAME_START_TIME) {
			tmGameTime.Start(); //ゲーム時間計測開始.
			isGameStart = true; //ゲーム開始.
			//ステージ別.
			switch (gameData.stage)
			{
				case Stage_Tutorial: 
					ManagerInsts::GetInst().Get<TutorialStage>()->SetAutoExeMode(MngAutoExe::Active);
					break;
				case Stage_Endless:  
					ManagerInsts::GetInst().Get<EndlessStage>()-> SetAutoExeMode(MngAutoExe::Active);
					break;

				default: assert(false); break;
			}
		}
	}
	//ゲーム開始後.
	else {
		UpdateReflectMode(); //反射モード.
	}
}
//描画.
void GameScene::Draw() {
	DrawReflectMode();  //反射モード演出.
}

//ポーズ.
void GameScene::Pause() {
	tmGameTime.Pause();
	tmReflectMode.Pause();
}
//ポーズ解除.
void GameScene::PauseEnd() {
	//稼働中だったタイマーは再開.
	if (tmGameTime.GetState() == TimerState::Pause) {
		tmGameTime.Start();
	}
	if (tmReflectMode.GetState() == TimerState::Pause) {
		tmReflectMode.Start();
	}
}

//反射モードの更新.
void GameScene::UpdateReflectMode() {

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

		switch (itemSoundCnt) {
			case 0:
				//3秒以下になったばかりの時.
				if (tmReflectMode.GetPassTime() <= 3) {
					if (auto i = SoundMng::Get("CountDown")){
						i->Play(false, 78); //再生.
					}
					itemSoundCnt++; //次へ.
				}
				break;
			case 1:
				//2秒以下になったばかりの時.
				if (tmReflectMode.GetPassTime() <= 2) {
					if (auto i = SoundMng::Get("CountDown")) {
						i->Play(false, 78); //再生.
					}
					itemSoundCnt++; //次へ.
				}
				break;
			case 2:
				//1秒以下になったばかりの時.
				if (tmReflectMode.GetPassTime() <= 1) {
					if (auto i = SoundMng::Get("CountDown")) {
						i->Play(false, 78); //再生.
					}
					itemSoundCnt++; //次へ.
				}
				break;
			case 3:
				//時間切れで解除.
				if (tmReflectMode.GetPassTime() <= 0) {
					ReflectModeEnd();
				}
				break;
		}
	}
}
//反射モードの描画.
void GameScene::DrawReflectMode() {

	//カウントダウン中.
	if (tmReflectMode.GetState() == TimerState::Active &&
		tmReflectMode.GetPassTime() > 0)
	{
		//テキストの設定.
		MY_STRING text = _to_mystr((int)ceil(tmReflectMode.GetPassTime()));
		DrawStr str(text, { WINDOW_WID / 2, WINDOW_HEI / 2 }, COLOR_ITEM);

		//画面中央に数字を表示.
		{
			double dec  = Calc::GetDecimal(tmReflectMode.GetPassTime()); //小数だけ取り出す.
			double anim = Calc::AnimEase(EaseType::OutQuad, dec);
			{
				//1秒ごとに薄くなる演出.
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * dec);

				//最初の1秒.
				if (tmReflectMode.GetPassTime() > REFLECT_MODE_TIME - 1) {
					DrawImgMng::Get("reflect")->DrawExtend({ WINDOW_WID / 2, WINDOW_HEI / 2 }, { 0.3 + 0.2 * anim, 0.3 + 0.2 * anim });
				}
				//最後の3秒.
				if (tmReflectMode.GetPassTime() <= 3) {
					str.Draw(Anchor::Mid, gameData.fonts["size40"].GetFont()); //数字.
				}
			}
		}
	}
}
//反射モード終了.
void GameScene::ReflectModeEnd() {

	tmReflectMode.Reset();

	gameData.isReflectMode = false; //反射モード解除.
	gameData.speedRate = 1.0;		//速度倍率を100%に戻す.
	gameData.slowBufCntr = 0;		//カウンターを0に.
	itemSoundCnt = 0;
	player.SetMode(Player_Normal);  //通常状態に戻す.

	//効果終了音.
	if (auto i = SoundMng::Get("PowerDown")) {
		i->Play(false, 78); //再生.
	}
	//チュートリアルなら指示送信.
	if (gameData.stage == Stage_Tutorial) {
		tutorialStg.SetReflectFinish(true); //指示を送る.
	}
}

//アイテム使用.
void GameScene::ItemUsed() {
	tmReflectMode.Start(); //反射タイマー開始.
	itemSoundCnt = 0;
}