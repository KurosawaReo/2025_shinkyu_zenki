/*
   - TutorialManager.cpp -
   チュートリアルシーン.
*/
#include "GameManager.h"
#include "EffectManager.h"
#include "TutorialManager.h"

//初期化.
void TutorialManager::Init() {
	p_data      = GameData::GetPtr();
	p_effectMng = EffectManager::GetPtr();
	p_input     = InputMng::GetPtr();
	p_sound     = SoundMng::GetPtr();
}
//リセット.
void TutorialManager::Reset() {
	stepNo = 0; //後からstep1にする.
}
//更新.
void TutorialManager::Update() {

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
void TutorialManager::Draw() {

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
void TutorialManager::UpdateStep0() {



	if (p_input->IsPushKeyTime(KEY_0) == 1) {

		//サウンド.
		p_sound->Play(_T("LevelUp"), false, 100);
		//エフェクト.
		EffectData data{};
		data.type = Effect_Tutorial_Step1;		
		data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
		p_effectMng->SpawnEffect(&data);

		stepNo++; //次のステップ.
	}
}
//更新:step1
void TutorialManager::UpdateStep1() {

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
void TutorialManager::UpdateStep2() {



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
void TutorialManager::UpdateStep3() {



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
void TutorialManager::UpdateStep4() {

	//チュートリアル終了.
	if (p_input->IsPushKeyTime(KEY_0) == 1) {
		//タイトルへ(全てリセット)
		GameManager::GetPtr()->Reset();
	}
}

//描画:step1
void TutorialManager::DrawStep1() {


	DrawStr str(_T("↑↓←→: 移動"), {WINDOW_WID/2-500, WINDOW_HEI/2}, 0x00FFFF);
	str.Draw(ANC_MID, p_data->font1);

	//枠.
	Box box = { str.pos.Add(0, 0).ToDblXY(), str.GetTextSize(p_data->font1).ToDblXY()+12, 0x00FFFF};
	DrawBoxST(&box, ANC_MID, false);
}
//描画:step2
void TutorialManager::DrawStep2() {

}
//描画:step3
void TutorialManager::DrawStep3() {

}
//描画:step4
void TutorialManager::DrawStep4() {

}