/*
   - UIManager.cpp -
   UI管理.
*/
#include "UIManager.h"

//依存関係.
#include "Stage_Tutorial.h"
#include "GameData.h"
#include "GameManager.h"
//参照.
static GameManager&   gameMng       = GameManager::GetInst();
static GameData&      p_gameData    = GameData::GetInst();
static TutorialStage& p_tutorialStg = TutorialStage::GetInst();

// ▼*--=<[ UIManager ]>=--*▼ //

UIManager UIManager::inst;

//初期化.
void UIManager::Init() {
	//画像.
	DrawImgMng::LoadFile(_T("Resources/Images/ui_back_level.png"),      "ui_back_level");
	DrawImgMng::LoadFile(_T("Resources/Images/ui_back_best_score.png"), "ui_back_best_score");
	DrawImgMng::LoadFile(_T("Resources/Images/ui_back_score.png"),      "ui_back_score");
	DrawImgMng::LoadFile(_T("Resources/Images/ui_back_time.png"),       "ui_back_time");
}
//リセット.
void UIManager::Reset() {
	//自動実行設定.
	SetAutoExeMode(MngAutoExe::Stop);

	isShowScore = false;
}
//更新.
void UIManager::Update() {

}
//描画.
void UIManager::Draw() {

#if defined DEBUG_SPAWN_RATE
	//カウンター.
	DrawFormatStringToHandle(
		10, WINDOW_HEI-75, 0xFFFFFF, gameData->font2, _T("Counter: %.2f"), gameData->counter
	);
	//出現間隔割合.
	DrawFormatStringToHandle(
		10, WINDOW_HEI-40, 0xFFFFFF, gameData->font2, _T("Spawn  : %.2f%%"), gameData->spawnRate*100
	);
#endif

	//ゲームシーン経過時間.
	const float time = gameMng.GetGameScene()->GetSceneTime();
	
	//ステージ別.
	switch (p_gameData.stage) 
	{
		case Stage_Tutorial:
		{
			//アニメーション値.
			double alpha   = Calc::AnimEase(EaseType::InOutQuad, (time-1.0)*2);
			double alpha2  = Calc::AnimEase(EaseType::InOutQuad, time-0.2);
			double animSin = sin(M_PI * (time-0.2));
			//テキスト設定.
			DrawStr str1({}, { WINDOW_WID/2, 70+2 }, 0xFFFFFF);
			DrawStr str2({}, { WINDOW_WID/2,  150 }, COLOR_SCORE);
			
			TCHAR text[256];
			_stprintf(text, _T("STEP %d"), p_tutorialStg.GetStepNo());
			str1.text = text;
			_stprintf(text, _T("SCORE:%05d"), p_gameData.score);
			str2.text = text;

			//STEP.
			DrawImgMng::Get("ui_back_level")->DrawExtend({ WINDOW_WID/2, 70 }, {0.4, 0.35}); //背景画像.
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * alpha);
				str1.Draw(Anchor::Mid, p_gameData.fonts["size40"].GetFont());
			}
			//SCORE.
			if (isShowScore) {
				{
					DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * alpha2);

					str2.Draw(Anchor::Mid, p_gameData.fonts["size35"].GetFont());
		 			DrawImgMng::Get("ui_back_score")->DrawExtend({(double)str2.pos.x, (double)str2.pos.y+28}, {0.35, 0.4});
				}
				//テキスト(光沢用)
				{
					DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 100 * animSin);

					str2.color = 0xFFFFFF;
					str2.Draw(Anchor::Mid, p_gameData.fonts["size35"].GetFont());
				}
			}
		}
		break;

		case Stage_Endless:
		{
			//アニメーション値.
			double alpha1   = Calc::AnimEase(EaseType::InOutQuad,  time-0.1   );
			double alpha2   = Calc::AnimEase(EaseType::InOutQuad,  time-0.2   );
			double alpha3   = Calc::AnimEase(EaseType::InOutQuad,  time-0.3   );
			double alpha4   = Calc::AnimEase(EaseType::InOutQuad, (time-1.0)*2);
			double animSin1 = sin(M_PI* time-0.1);
			double animSin2 = sin(M_PI*(time-0.2));
			double animSin3 = sin(M_PI*(time-0.3));

			//テキスト設定.
			DrawStr str[4] = {
				DrawStr({}, {WINDOW_WID/2,      70+2}, 0xFFFFFF),
				DrawStr({}, {WINDOW_WID/2-350, 150  }, COLOR_BEST_SCORE),
				DrawStr({}, {WINDOW_WID/2,     150  }, COLOR_SCORE),
				DrawStr({}, {WINDOW_WID/2+350, 150  }, COLOR_TIME),
			};
			TCHAR text[256];
			_stprintf(text, _T("LEVEL %d"),        p_gameData.level);
			str[0].text = text;
			_stprintf(text, _T("BEST SCORE:%05d"), disBestScore);
			str[1].text = text;
			_stprintf(text, _T("SCORE:%05d"),      p_gameData.score);
			str[2].text = text;
			_stprintf(text, _T("TIME:%.1f"),       gameMng.GetGameScene()->GetGameTime());
			str[3].text = text;
		
			//[level]
			DrawImgMng::Get("ui_back_level")->DrawExtend({WINDOW_WID/2, 70}, {0.4, 0.35});
			//テキスト(main)
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * alpha4);
				str[0].Draw(Anchor::Mid, p_gameData.fonts["size40"].GetFont());
			}
			//[best score]
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * alpha1);

				str[1].Draw(Anchor::Mid, p_gameData.fonts["size35"].GetFont());
				DrawImgMng::Get("ui_back_best_score")->DrawExtend(str[1].pos.Add(0, 28).ToDbl(), {0.35, 0.4});
			}
			//[score]
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * alpha2);

				str[2].Draw(Anchor::Mid, p_gameData.fonts["size35"].GetFont());
				DrawImgMng::Get("ui_back_score")->DrawExtend(str[2].pos.Add(0, 28).ToDbl(), {0.35, 0.4});
			}			
			//[time]
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * alpha3);

				str[3].Draw(Anchor::Mid, p_gameData.fonts["size35"].GetFont());
				DrawImgMng::Get("ui_back_time")->DrawExtend(str[3].pos.Add(0, 28).ToDbl(), {0.35, 0.4});
			}
			//テキスト(光沢用)
			str[1].color = 0xFFFFFF;
			str[2].color = 0xFFFFFF;
			str[3].color = 0xFFFFFF;
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 100 * animSin1);
				str[1].Draw(Anchor::Mid, p_gameData.fonts["size35"].GetFont());
			}
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 100 * animSin2);
				str[2].Draw(Anchor::Mid, p_gameData.fonts["size35"].GetFont());
			}
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 100 * animSin3);
				str[3].Draw(Anchor::Mid, p_gameData.fonts["size35"].GetFont());
			}
		}
		break;
			
		default: assert(FALSE); break;
	}
}