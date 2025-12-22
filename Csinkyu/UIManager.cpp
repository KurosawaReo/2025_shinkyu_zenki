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
GameManager* p_gameMng{};
GameData* p_gameData{};
TutorialStage* p_tutorialStg{};

//初期化.
void UIManager::Init() {

	//実体取得.
	p_gameMng     = &GameManager::GetInst();
	p_gameData    = &GameData::GetInst();
	p_tutorialStg = &TutorialStage::GetInst();

	//画像.
	DrawImgMng::LoadFile(_T("Resources/Images/ui_back_level.png"),      "ui_back_level");
	DrawImgMng::LoadFile(_T("Resources/Images/ui_back_best_score.png"), "ui_back_best_score");
	DrawImgMng::LoadFile(_T("Resources/Images/ui_back_score.png"),      "ui_back_score");
	DrawImgMng::LoadFile(_T("Resources/Images/ui_back_time.png"),       "ui_back_time");
}
//リセット.
void UIManager::Reset() {
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

	//経過時間.
	const float time = p_gameMng->GetSceneTime(SCENE_GAME);
		
	//ステージ別.
	switch (p_gameData->stage) 
	{
		case STAGE_TUTORIAL:
		{
			//アニメーション値.
			double alpha   = Calc::AnimEaseInOut((time-1.0) * 2);
			double alpha2  = Calc::AnimEaseInOut(time-0.2);
			double animSin = sin(M_PI * (time-0.2));
			//テキスト設定.
			DrawStr str1({}, { WINDOW_WID/2, 70+2 }, 0xFFFFFF);
			DrawStr str2({}, { WINDOW_WID/2,  150 }, COLOR_SCORE);
			
			TCHAR text[256];
			_stprintf(text, _T("STEP %d"), p_tutorialStg->GetStepNo());
			str1.text = text;
			_stprintf(text, _T("SCORE:%05d"), p_gameData->score);
			str2.text = text;

			//STEP.
			DrawImgMng::Get("ui_back_level")->DrawExtend({ WINDOW_WID/2, 70 }, {0.4, 0.35}); //背景画像.
			SetDrawBlendModeKR(BlendModeID::Alpha, 255 * alpha);
			str1.Draw(Anchor::Mid, p_gameData->font4);

			//SCORE.
			if (isShowScore) {
				SetDrawBlendModeKR(BlendModeID::Alpha, 255 * alpha2);
				str2.Draw(Anchor::Mid, p_gameData->font3);
				DrawImgMng::Get("ui_back_score")->DrawExtend({(double)str2.pos.x, (double)str2.pos.y+28}, {0.35, 0.4});
				//テキスト(光沢用)
				str2.color = 0xFFFFFF;
				SetDrawBlendModeKR(BlendModeID::Alpha, 100 * animSin);
				str2.Draw(Anchor::Mid, p_gameData->font3);
			}

			//描画モードリセット.
			ResetDrawBlendMode();
		}
		break;

		case STAGE_ENDLESS:
		{
			//アニメーション値.
			double alpha1   = Calc::AnimEaseInOut( time-0.1);
			double alpha2   = Calc::AnimEaseInOut( time-0.2);
			double alpha3   = Calc::AnimEaseInOut( time-0.3);
			double alpha4   = Calc::AnimEaseInOut((time-1.0)*2);
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
			_stprintf(text, _T("LEVEL %d"),        p_gameData->level);
			str[0].text = text;
			_stprintf(text, _T("BEST SCORE:%05d"), disBestScore);
			str[1].text = text;
			_stprintf(text, _T("SCORE:%05d"),      p_gameData->score);
			str[2].text = text;
			_stprintf(text, _T("TIME:%.3f"),       p_gameMng->GetGameTime());
			str[3].text = text;
		
			//[level]
			DrawImgMng::Get("ui_back_level")->DrawExtend({WINDOW_WID/2, 70}, {0.4, 0.35});
			//テキスト(main)
			SetDrawBlendModeKR(BlendModeID::Alpha, 255 * alpha4);
			str[0].Draw(Anchor::Mid, p_gameData->font4);

			//[best score]
			SetDrawBlendModeKR(BlendModeID::Alpha, 255 * alpha1);
			str[1].Draw(Anchor::Mid, p_gameData->font3);
			DrawImgMng::Get("ui_back_best_score")->DrawExtend({(double)str[1].pos.x, (double)str[1].pos.y+28}, {0.35, 0.4});

			//[score]
			SetDrawBlendModeKR(BlendModeID::Alpha, 255 * alpha2);
			str[2].Draw(Anchor::Mid, p_gameData->font3);
			DrawImgMng::Get("ui_back_score")->DrawExtend({(double)str[2].pos.x, (double)str[2].pos.y+28}, {0.35, 0.4});
			
			//[time]
			SetDrawBlendModeKR(BlendModeID::Alpha, 255 * alpha3);
			str[3].Draw(Anchor::Mid, p_gameData->font3);
			DrawImgMng::Get("ui_back_time")->DrawExtend({(double)str[3].pos.x, (double)str[3].pos.y+28}, {0.35, 0.4});
			
			//テキスト(光沢用)
			str[1].color = 0xFFFFFF;
			str[2].color = 0xFFFFFF;
			str[3].color = 0xFFFFFF;
			SetDrawBlendModeKR(BlendModeID::Alpha, 100 * animSin1);
			str[1].Draw(Anchor::Mid, p_gameData->font3);
			SetDrawBlendModeKR(BlendModeID::Alpha, 100 * animSin2);
			str[2].Draw(Anchor::Mid, p_gameData->font3);
			SetDrawBlendModeKR(BlendModeID::Alpha, 100 * animSin3);
			str[3].Draw(Anchor::Mid, p_gameData->font3);

			//描画モードリセット.
			ResetDrawBlendMode();
		}
		break;
			
		default: assert(FALSE); break;
	}
}