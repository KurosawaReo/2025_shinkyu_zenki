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
static GameManager& gameMng  = GameManager::GetInst();
static GameData&    gameData = GameData::GetInst();
static Player&      player   = Player::GetInst();
static UIManager&   uiMng    = UIManager::GetInst();

//初期化.
void EndScene::Init() {
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
}
//抜けた瞬間.
void EndScene::Exit() {
	timer.Reset(); //タイマーリセット.
}
//更新.
void EndScene::Update() {
	if (gameData.stage == Stage_Tutorial) {

		gameMng.GetGameScene()->Update(); //ゲームシーンと同じ動作をする.

		//死亡後一定時間経過したら.
		if (timer.GetPassTime() >= TUTORIAL_RESPAWN_TIME) {
			timer.Reset();              //タイマーリセット.
			player.PlayerRevival();     //復活.
			SceneMng::SetScene("Game"); //ゲームシーンへ戻る.
		}
	}
	//チュートリアル以外の場合.
	else {
		//特定の操作でタイトルへ.
		if (InputMng::IsPushActionTime("GameNext") == 1)
		{
			uiMng.SetDisBestScore(gameData.bestScore); //ベストスコア表示更新.
			SceneMng::SetScene("Title");               //ゲームシーンへ戻る.
			App::Reset();
		}
	}
}
//描画.
void EndScene::Draw() {

	//黒フィルター.
	{
		double anim = Calc::AnimEaseInOut(timer.GetPassTime()); //アニメーション値.
		Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x000000 };
		{
			DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 128 * anim);
			DrawBoxKR(box, Anchor::LU); //画面を暗くする(UI以外)
		}
	}
	uiMng.Draw(); //UI.

	//チュートリアルの場合.
	if (gameData.stage == Stage_Tutorial) {

		//アニメーション値.
		double anim = Calc::AnimEaseOut(timer.GetPassTime());
		//テキスト.
		DrawStr str(_T("チュートリアルではその場で復活します..."), { WINDOW_WID / 2, WINDOW_HEI / 2 }, 0x00FFFF);
		{
			DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim);

			//GAME OVER
			DrawImgMng::Get("gameover")->DrawExtend({ WINDOW_WID / 2, 370 + 30 * anim }, { 0.5, 0.5 }, Anchor::Mid, true, true);
			//テキスト.
			str.Draw(Anchor::Mid, gameData.fonts["size30"].GetFont());
		}
	}
	//チュートリアル以外の場合.
	else {
		//終了案内.
		{
			//アニメーション値.
			const double anim     = Calc::AnimEaseOut(timer.GetPassTime());
			const float  gameTime = gameMng.GetGameScene()->GetGameTime();

			//スコア表示.
			TCHAR text[256];
			_stprintf(
				text, _T("%d + %d(%.3f秒) = %d点"),
				gameData.scoreBef, _int(gameTime * 10), gameTime, gameData.score
			);
			//テキストの設定.
			DrawStr str1(_T("Time Bonus"), { WINDOW_WID / 2, WINDOW_HEI / 2 - 20 }, 0xFFFFFF);
			DrawStr str2(text, { WINDOW_WID / 2, WINDOW_HEI / 2 + 20 }, 0xFFFFFF);
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim);

				DrawImgMng::Get("gameover")->DrawExtend({ WINDOW_WID / 2, 370 + 30 * anim }, { 0.5, 0.5 }, Anchor::Mid, true, true); //GAME OVER
				//画面中央に文字を表示.
				str1.Draw(Anchor::Mid, gameData.fonts["size26"].GetFont());
				str2.Draw(Anchor::Mid, gameData.fonts["size26"].GetFont());
			}
		}

		const float delay1 = 1.2f;
		const float delay2 = 1.5f;

		//一定時間が経ったら.
		if (timer.GetPassTime() > delay1) {
			//ベストスコア更新.
			if (isBestScore) {

				//アニメーション値.
				double anim = Calc::AnimEaseOut((timer.GetPassTime() - delay1) * 2);
				//描画.
				{
					DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim);
					DrawImgMng::Get("new_record")->DrawExtend({ WINDOW_WID / 2, WINDOW_HEI / 2 - 330 + anim * 20 }, { 0.4, 0.4 }, Anchor::Mid, true, true); //NEW RECORD
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
		if (timer.GetPassTime() > delay2) {

			//アニメーション値.
			double anim = Calc::AnimWaveLoop(timer.GetPassTime() - delay2);
			//テキスト.
			DrawStr str(_T("Push SPACE or Ⓐ"), { WINDOW_WID / 2 - 5, WINDOW_HEI / 2 + 145 }, 0xFFFFFF);
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim);
				str.Draw(Anchor::Mid, gameData.fonts["size26"].GetFont()); //テキスト.
			}
		}
	}
}