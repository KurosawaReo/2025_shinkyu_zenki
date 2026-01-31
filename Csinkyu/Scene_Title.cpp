/*
   - Scene_Title.cpp -
*/
#include "Scene_Title.h"

//依存関係.
#include "GameData.h"
#include "BGManager.h"
#include "Obst_MeteorManager.h"
//参照.
static GameData&      gameData  = GameData::GetInst();
static BGManager&     bgMng     = BGManager::GetInst();
static MeteorManager& meteorMng = MeteorManager::GetInst();

//初期化.
void TitleScene::Init() {
	timer = Timer(TimerMode::CountUp, 0);
}
//リセット.
void TitleScene::Reset() {
	isTitleAnim = false;
}
//入った瞬間.
void TitleScene::Enter() {
	timer.Start();    //タイマー開始.
	bgMng.SetBgNo(1); //背景を設定.
}
//抜けた瞬間.
void TitleScene::Exit() {
	timer.Reset(); //タイマーリセット.
}
//更新.
void TitleScene::Update() {
	//特定の操作でゲーム開始.
	if (InputMng::IsPushActionTime("GameNext") == 1) {
		SceneMng::SetScene("Menu"); //メニューシーンへ.
	}
}
//描画.
void TitleScene::Draw() {

	//操作方法明記.
	DrawStr howPlay(_T(""), { 30, WINDOW_HEI - 30 }, 0x00FFFF);
	{
		const int fontH = gameData.fonts["size18"].GetFont();

#if defined INPUT_CHANGE_ARCADE
		howPlay.text = _T("アーケード操作");
#else
		howPlay.text = _T("コントローラ操作");
#endif
		howPlay.Draw(Anchor::LD, fontH);

		//枠線グラデーション.
		const DBL_XY howPlayPos = howPlay.pos.ToDbl();
		const DBL_XY howPlaySize = howPlay.GetTextSize(fontH).ToDbl();
		const int margin = 5;

		GradLine line;
		line.AddPoint(howPlayPos.Add(-margin, margin), { 0, 255, 255 });
		line.AddPoint(howPlayPos.Add(howPlaySize.x + margin, margin), { 0, 100, 255 });
		line.AddPoint(howPlayPos.Add(howPlaySize.x + margin, -howPlaySize.y - margin), { 0, 255, 255 });
		line.AddPoint(howPlayPos.Add(-margin, -howPlaySize.y - margin), { 0, 100, 255 });
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
		const int    logoY = WINDOW_HEI / 2 - 80;
		const DBL_XY imgSize = { 0.7, 0.7 };

		//切り替え前.
		if (timer.GetPassTime() < delay1) {
			//アニメーション値.
			double anim = Calc::AnimEaseInOut(timer.GetPassTime() / delay1);
			//ロゴ1枚目.
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim);
				DrawImgMng::Get("logo")->DrawExtend({ WINDOW_WID / 2, logoY }, imgSize, Anchor::Mid, true, true);
			}
		}
		//切り替え後.
		else {
			//アニメーション値.
			//1枚目と2枚目の切り替えが自然になるよう、anim2は遅延ありにする.
			double anim1 = Calc::AnimEaseInOut((timer.GetPassTime() - delay1) / 1.8);
			double anim2 = Calc::AnimEaseInOut((timer.GetPassTime() - delay1 - 0.4) / 1.8);
			//ロゴ1枚目.
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * (1 - anim2));
				DrawImgMng::Get("logo")->DrawExtend({ WINDOW_WID / 2, logoY - anim1 * 80 }, imgSize, Anchor::Mid, true, true);
			}
			//ロゴ2枚目.
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim1);
				DrawImgMng::Get("logo_all")->DrawExtend({ WINDOW_WID / 2, logoY - anim1 * 80 }, imgSize, Anchor::Mid, true, true);
			}
		}
	}

	//best score.
	if (timer.GetPassTime() >= delay2) {

		const int drawY = WINDOW_HEI / 2 + 130;

		//アニメーション値.
		double anim1 = Calc::AnimEaseInOut((timer.GetPassTime() - delay3) / 1.5);
		double anim2 = Calc::AnimEaseInOut((timer.GetPassTime() - delay2) / 1.5);
		//テキスト.
		TCHAR text[256];
		_stprintf(text, _T("BEST SCORE: %d"), gameData.bestScore); //ベストスコア.
		DrawStr str(text, { WINDOW_WID / 2, drawY + 1 }, COLOR_BEST_SCORE);
		{
			DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim1);
			str.Draw(Anchor::Mid, gameData.fonts["size30"].GetFont()); //スコア値.
		}
		{
			DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim2);

			//UI
			DrawImgMng::Get("ui_back_best_score")->
				DrawExtend({ WINDOW_WID / 2, drawY + (10 + 18 * anim2) }, { 0.45, 0.4 }, Anchor::Mid, true, true);
			DrawImgMng::Get("ui_back_best_score")->
				DrawExtend({ WINDOW_WID / 2, drawY - (10 + 18 * anim2) }, { 0.45, 0.4 }, Anchor::Mid, true, true);
		}
	}
	//PUSH SPACE.
	if (timer.GetPassTime() >= delay4) {

		const int drawY = WINDOW_HEI / 2 + 310;

		//アニメーション値.
		double anim = Calc::AnimWaveLoop(timer.GetPassTime() - delay4);
		//テキスト.
		DrawStr str(_T("Push SPACE or Ⓐ"), { WINDOW_WID / 2 - 5, drawY }, 0xFFFFFF);
		{
			DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim);
			str.Draw(Anchor::Mid, gameData.fonts["size26"].GetFont()); //テキスト.
		}
	}
	//隕石破壊アニメーション.
	if (!isTitleAnim) {
		if (timer.GetPassTime() >= delay5) {
			//破壊演出.
			meteorMng.BreakMeteor({ 580, 310 }, -130, false, 1.4);
			//一度きり.
			isTitleAnim = true;
		}
	}
}