/*
   - Stage_Tutorial.cpp -
   
   ステージ: チュートリアル.
*/
#include "LaserManager.h"
#include "Obst_NormalLaser.h"
#include "Obst_StraightLaser.h"
#include "Obst_MeteorManager.h"
#include "Obst_Ripples.h"
#include "Obst_Fireworks.h"
#include "Item.h"
#include "EffectManager.h"
#include "GameManager.h"

#include "Stage_Tutorial.h"

//初期化.
void TutorialStage::Init() {
	//実体取得.
	p_data         = GameData::GetPtr();
	p_gameMng      = GameManager::GetPtr();
	p_laserMng     = LaserManager::GetPtr();
	p_meteorMng    = MeteorManager::GetPtr();
	p_ripples      = Ripples::GetPtr();
	p_itemMng      = ItemManager::GetPtr();
	p_fireworksMng = FireworksManager::GetPtr();
	p_effectMng    = EffectManager::GetPtr();
	p_input        = InputMng::GetPtr();
	p_sound        = SoundMng::GetPtr();

	font[0].CreateFontH(_T(""), 20, 1, FONT_ANTI);
	font[1].CreateFontH(_T(""), 26, 1, FONT_ANTI);
}
//リセット.
void TutorialStage::Reset() {
	stepNo = 0; //後からstep1にする.
}
//更新.
void TutorialStage::Update() {

	//ステップ別.
	switch (stepNo)
	{
		case 0: UpdateStep0(); break;
		case 1: UpdateStep1(); break;
		case 2: UpdateStep2(); break;
		case 3: UpdateStep3(); break;
		case 4: UpdateStep4(); break;

		default: assert(FALSE); break;
	}
}
//描画.
void TutorialStage::Draw() {

	//ステップ別.
	switch (stepNo)
	{
		case 0:              break; //描画なし.
		case 1: DrawStep1(); break;
		case 2: DrawStep2(); break;
		case 3: DrawStep3(); break;
		case 4: DrawStep4(); break;

		default: assert(FALSE); break;
	}
}

//更新:step0
void TutorialStage::UpdateStep0() {

	//サウンド.
	p_sound->Play(_T("LevelUp"), false, 100);
	//エフェクト.
	EffectData data{};
	data.type = Effect_Tutorial_Step1;
	data.pos = { WINDOW_WID/2, WINDOW_HEI/2 };
	p_effectMng->SpawnEffect(&data);

	stepNo++; //次のステップ.
}
//更新:step1
void TutorialStage::UpdateStep1() {



	if (p_input->IsPushKeyTime(KEY_0) == 1) {

		//サウンド.
		p_sound->Play(_T("LevelUp"), false, 100);
		//エフェクト.
		EffectData data{};
		data.type = Effect_Tutorial_Step2;		
		data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
		p_effectMng->SpawnEffect(&data);

		stepNo++; //次のステップ.
	}
}
//更新:step2
void TutorialStage::UpdateStep2() {



	if (p_input->IsPushKeyTime(KEY_0) == 1) {

		//サウンド.
		p_sound->Play(_T("LevelUp"), false, 100);
		//エフェクト.
		EffectData data{};
		data.type = Effect_Tutorial_Step3;
		data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
		p_effectMng->SpawnEffect(&data);

		stepNo++; //次のステップ.
	}
}
//更新:step3
void TutorialStage::UpdateStep3() {



	if (p_input->IsPushKeyTime(KEY_0) == 1) {
		
		//サウンド.
		p_sound->Play(_T("LevelUp"), false, 100);
		//エフェクト.
		EffectData data{};
		data.type = Effect_Tutorial_Step4;		
		data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
		p_effectMng->SpawnEffect(&data);

		stepNo++; //次のステップ.
	}
}
//更新:step4
void TutorialStage::UpdateStep4() {

	//チュートリアル終了.
	if (p_input->IsPushKeyTime(KEY_0) == 1) {
		//タイトルへ(全てリセット)
		p_data->scene = SCENE_TITLE;
		GameManager::GetPtr()->Reset();
	}
}

//描画:step1
void TutorialStage::DrawStep1() {

	DrawTopText (_T("プレイヤーを移動させよう"));
	DrawTopText2(_T("キーボード:↑↓←→"));

	//↑↓←→: 移動
}
//描画:step2
void TutorialStage::DrawStep2() {

	DrawTopText(_T(""));

}
//描画:step3
void TutorialStage::DrawStep3() {
	DrawTopText(_T(""));

}
//描画:step4
void TutorialStage::DrawStep4() {
	DrawTopText(_T(""));

}

//画面上にテキストを出す.
void TutorialStage::DrawTopText(MY_STRING text) {

	//テキスト.
	DrawStr str(text, {WINDOW_WID/2, 150}, 0xFFFFFF);
	str.Draw(ANC_MID, font[1].GetFont());
	//枠.
	{
		const int margin = 24;

		DBL_XY pos  = (str.pos - str.GetTextSize(font[1].GetFont())/2).Add(-margin/2, -margin/2).ToDblXY();
		DBL_XY size = (str.GetTextSize(font[1].GetFont()) + margin).ToDblXY();
		//グラデーションをつける.
		GradLine line;
		line.AddPoint(pos,                     0x00FFFF);
		line.AddPoint(pos.Add(size.x,      0), 0x000000);
		line.AddPoint(pos.Add(size.x, size.y), 0xFF00FF);
		line.AddPoint(pos.Add(     0, size.y), 0x000000);
		line.Draw(true);
	}
}
//画面上にテキストを出す(2行目)
void TutorialStage::DrawTopText2(MY_STRING text) {

	//テキスト.
	DrawStr str(text, {WINDOW_WID/2, 210}, 0xFFFFFF);
	str.Draw(ANC_MID, font[0].GetFont());
	//枠.
	{
		const int margin = 24;

		DBL_XY pos  = (str.pos - str.GetTextSize(font[0].GetFont())/2).Add(-margin/2, -margin/2).ToDblXY();
		DBL_XY size = (str.GetTextSize(font[0].GetFont()) + margin).ToDblXY();
		//グラデーションをつける.
		GradLine line;
		line.AddPoint(pos,                     0x00FFFF);
		line.AddPoint(pos.Add(size.x,      0), 0x000000);
		line.AddPoint(pos.Add(size.x, size.y), 0xFF00FF);
		line.AddPoint(pos.Add(     0, size.y), 0x000000);
		line.Draw(true);
	}
}