/*
   - Scene_End.cpp -
*/
#include "Scene_End.h"

//依存関係.
#include "GameManager.h"
#include "GameData.h"
#include "Player.h"
#include "UIManager.h"
//参照.
static GameManager* gameMng;
static GameData*    gameData;
static Player*      player;
static UIManager*   uiMng;
//参照(KRライブラリ)
static SoundMng*    soundMng;
static InputMng*    inputMng;
static SceneMng*    sceneMng;

//初期化.
void EndScene::Init() {
	//参照取得.
	gameMng  = ManagerInsts::Get<GameManager>();
	gameData = ManagerInsts::Get<GameData>();
	player   = ManagerInsts::Get<Player>();
	uiMng    = ManagerInsts::Get<UIManager>();
	soundMng = ManagerInsts::Get<SoundMng>();
	inputMng = ManagerInsts::Get<InputMng>();
	sceneMng = ManagerInsts::Get<SceneMng>();

	timer = Timer(TimerMode::CountUp, 0);
}

//リセット.
void EndScene::Reset() {
	isBestScore      = false;
	isBestScoreSound = false;
}

//入った瞬間.
void EndScene::Enter() {

	timer.Start(); //タイマー開始.

	//チュートリアル限定.
	if (gameData->stage == Stage_Tutorial) {

		//一定時間経過したら.
		ManagerInsts::Get<TimerMng>()->ReservExe(
			TUTORIAL_RESPAWN_TIME,
			[this]() {
				sceneMng->SetScene("Game"); //ゲームシーンへ戻る.
			}
		);
	}
}

//抜けた瞬間.
void EndScene::Exit() {
	timer.Reset(); //タイマーリセット.
}

//更新.
void EndScene::Update() {

	//チュートリアル限定.
	if (gameData->stage == Stage_Tutorial) {
		//ゲームシーンと同じ動作をする.
		gameMng->GetGameScene()->Update();
	}
	//チュートリアル以外.
	else {
		//特定の操作でタイトルへ.
		if (inputMng->IsPushActionTime("GameNext") == 1)
		{
			uiMng->SetBestScore(gameData->bestScore);	//ベストスコア更新.
			sceneMng->SetScene("Title");				//ゲームシーンへ戻る.
		}
	}
}

//描画.
void EndScene::Draw() {

	//黒フィルター.
	{
		double anim = Calc::AnimEase(EaseType::InOutQuad, timer.GetPassTime()); //アニメーション値.
		Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x000000, 1.0f };

		//描画.
		DrawMode::Exe(
			DrawModeID::None, DrawBlendModeID::Alpha, _int(128 * anim),
			[&]() {
				DrawBoxKR(box, Anchor::LU); //画面を暗くする(UI以外)
			}
		);
	}

	//チュートリアルの場合.
	if (gameData->stage == Stage_Tutorial) {

		//アニメーション値.
		double anim = Calc::AnimEase(EaseType::OutQuad, timer.GetPassTime());
		//テキスト.
		DrawStr str(_T("チュートリアルではその場で復活します..."), { WINDOW_WID / 2, WINDOW_HEI / 2 }, 0x00FFFF);

		//描画.
		DrawMode::Exe(
			DrawModeID::None, DrawBlendModeID::Alpha, _int(255 * anim),
			[&]() {
				//GAME OVER.
				DrawImgMng::Get("gameover")->DrawExtend({ WINDOW_WID / 2, 370 + 30 * anim }, { 0.5, 0.5 }, Anchor::Mid, true, true);
				//テキスト.
				str.Draw(Anchor::Mid, gameData->fonts["size30"].GetFont());
			}
		);
	}
	//チュートリアル以外の場合.
	else {
		//終了案内.
		{
			//アニメーション値.
			const double anim     = Calc::AnimEase(EaseType::OutQuad, timer.GetPassTime());
			const float  gameTime = gameMng->GetGameScene()->GetGameTime();

			//スコア表示.
			TCHAR text[256];
			_stprintf(
				text, _T("%d + %d(%.1f秒) = %d点"),
				gameData->scoreBef, _int(gameTime * 10), gameTime, gameData->score
			);
			//テキストの設定.
			DrawStr str1(_T("Time Bonus"), { WINDOW_WID / 2, WINDOW_HEI / 2 - 20 }, 0xFFFFFF);
			DrawStr str2(text, { WINDOW_WID / 2, WINDOW_HEI / 2 + 20 }, 0xFFFFFF);

			//描画.
			DrawMode::Exe(
				DrawModeID::None, DrawBlendModeID::Alpha, _int(255 * anim),
				[&]() {
					DrawImgMng::Get("gameover")->DrawExtend({ WINDOW_WID / 2, 370 + 30 * anim }, { 0.5, 0.5 }, Anchor::Mid, true, true); //GAME OVER
					//画面中央に文字を表示.
					str1.Draw(Anchor::Mid, gameData->fonts["size26"].GetFont());
					str2.Draw(Anchor::Mid, gameData->fonts["size26"].GetFont());
				}
			);
		}

		const float delay1 = 1.2f;
		const float delay2 = 1.5f;

		//一定時間が経ったら.
		if (timer.GetPassTime() > delay1) {
			//ベストスコア更新.
			if (isBestScore) {

				//アニメーション値.
				double anim = Calc::AnimEase(EaseType::OutQuad, (timer.GetPassTime() - delay1) * 2);
				//描画.
				DrawMode::Exe(
					DrawModeID::None, DrawBlendModeID::Alpha, _int(255 * anim),
					[&]() {
						//NEW RECORD
						DrawImgMng::Get("new_record")->DrawExtend(
							{ WINDOW_WID / 2, WINDOW_HEI / 2 - 330 + anim * 20 }, { 0.4, 0.4 }, Anchor::Mid, true, true
						);
					}
				);
				//サウンド.
				if (!isBestScoreSound) {
					if (auto i = soundMng->Get("BestScore")) {
						i->Play(false, 65); //再生.
					}
					isBestScoreSound = true; //一度のみ.
				}
			}
		}
		//一定時間が経ったら.
		if (timer.GetPassTime() > delay2) {

			//アニメーション値.
			double anim = Calc::AnimWave(WaveType::CosLoop, timer.GetPassTime() - delay2);
			//テキスト.
			DrawStr str(_T("Push SPACE or Ⓐ"), { WINDOW_WID / 2 - 5, WINDOW_HEI / 2 + 145 }, 0xFFFFFF);

			//描画.
			DrawMode::Exe(
				DrawModeID::None, DrawBlendModeID::Alpha, _int(255 * anim),
				[&]() {
					str.Draw(Anchor::Mid, gameData->fonts["size26"].GetFont()); //テキスト.
				}
			);
		}
	}
}