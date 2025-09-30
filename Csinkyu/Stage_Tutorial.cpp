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
#include "UIManager.h"
#include "GameManager.h"

#include "Stage_Tutorial.h"

//初期化.
void TutorialStage::Init() {
	//実体取得.
	p_data         = &GameData::GetInst();
	p_gameMng      = &GameManager::GetInst();
	p_laserMng     = &LaserManager::GetInst();
	p_meteorMng    = &MeteorManager::GetInst();
	p_ripples      = &Ripples::GetInst();
	p_itemMng      = &ItemManager::GetInst();
	p_player       = &Player::GetInst();
	p_fireworksMng = &FireworksManager::GetInst();
	p_effectMng    = &EffectManager::GetInst();
	p_uiMng        = &UIManager::GetInst();
	p_input        = &InputMng::GetInst();
	p_sound        = &SoundMng::GetInst();

	font[0].CreateFontH(_T(""), 25, 1, FontTypeID::Anti);
	font[1].CreateFontH(_T(""), 30, 1, FontTypeID::Anti);

	//タイマー
	startTimer = Timer(COUNT_UP, 0);
	endTimer   = Timer(COUNT_UP, 0);
}
//リセット.
void TutorialStage::Reset() {

	startTimer.Reset();
	endTimer.Reset();
	stepNo   = 0;    //後からstep1にする.
	stepInNo = 0;    //0スタート.

	plyMoveSum = 0; 
	ResetSignFlag(); //signフラグoff.
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

//サインフラグのリセット.
void TutorialStage::ResetSignFlag() {
	isTakeItem      = false;
	isReflectLaser  = false;
	isReflectFinish = false;
	isBreakMeteor   = false;
}
//項目が終わる度の処理.
void TutorialStage::StepInEnd() {

	startTimer.Reset(); //リセット.
	endTimer.Reset();   //リセット.
	startTimer.Start(); //開始.

	ResetSignFlag(); //signフラグoff.
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

	startTimer.Start(); //開始.
	stepNo++;           //次のステップ.
	stepInNo = 0;
}
//更新:step1
void TutorialStage::UpdateStep1() {

	//ステップ内項目.
	switch (stepInNo)
	{
		case 0:
		{
			plyMoveSum += p_player->GetMoveDist(); //プレイヤー移動距離を計測.

			//[終了条件] 一定距離移動したら.
			if (!endTimer.GetIsMove() && plyMoveSum >= 1500) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				StepInEnd(); //終了処理.
				stepInNo++;
			}
		}
		break;

		case 1:
		{
			//最初の一定時間は停止.
			if (startTimer.GetPassTime() < TUTORIAL_START_WAIT_TIME) { break; }

			p_laserMng->Update();
			p_gameMng->laserNor1->Update();

			//[終了条件] 一定時間経過したら.
			if (!endTimer.GetIsMove() && startTimer.GetPassTime() >= 9.0) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//サウンド.
				p_sound->Play(_T("LevelUp"), false, 100);
				//エフェクト.
				EffectData data{};
				data.type = Effect_Tutorial_Step2;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				p_effectMng->SpawnEffect(&data);

				//オブジェクトリセット.
				p_laserMng->Reset();
				p_gameMng->ResetNorLaser();
				//アイテム召喚.
				p_itemMng->ItemSpawn(0);

				StepInEnd();  //終了処理.
				stepNo++;     //次のステップ.
				stepInNo = 0;
			}
		}
		break;
	}
}
//更新:step2
void TutorialStage::UpdateStep2() {

	//ステップ内項目.
	switch (stepInNo) 
	{
		case 0:
		{
			//最初の一定時間は停止.
			if (startTimer.GetPassTime() < TUTORIAL_START_WAIT_TIME) { break; }

			p_itemMng->Update();

			//[終了条件] アイテムを取ったら.
			if (!endTimer.GetIsMove() && isTakeItem) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				StepInEnd(); //終了処理.
				stepInNo++;
			}
		}
		break;

		case 1:
		{
			//最初の一定時間は停止.
			if (startTimer.GetPassTime() < TUTORIAL_START_WAIT_TIME) { break; }

			p_itemMng->Update();

			//[終了条件] 反射モードが終わったら.
			if (!endTimer.GetIsMove() && isReflectFinish) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//サウンド.
				p_sound->Play(_T("LevelUp"), false, 100);
				//エフェクト.
				EffectData data{};
				data.type = Effect_Tutorial_Step3;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				p_effectMng->SpawnEffect(&data);

				//アイテム召喚.
				p_itemMng->ItemSpawn(0);

				StepInEnd();  //終了処理.
				stepNo++;     //次のステップ.
				stepInNo = 0;
			}
		}
		break;
	}
}
//更新:step3
void TutorialStage::UpdateStep3() {

	//ステップ内項目.
	switch (stepInNo) 
	{
		case 0:
		{
			//最初の一定時間は停止.
			if (startTimer.GetPassTime() < TUTORIAL_START_WAIT_TIME) { break; }

			p_itemMng->Update();

			//[終了条件] アイテムを取ったら.
			if (!endTimer.GetIsMove() && isTakeItem) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				StepInEnd(); //終了処理.
				stepInNo++;
			}
		}
		break;

		case 1:
		{
			//最初の一定時間は停止.
			if (startTimer.GetPassTime() < TUTORIAL_START_WAIT_TIME) { break; }

			p_itemMng->Update();
			p_laserMng->Update();
			p_gameMng->laserNor1->Update();

			//[終了条件] レーザーを反射した && 反射モードが終わったら.
			if (!endTimer.GetIsMove() && isReflectLaser && isReflectFinish) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//召喚可能に.
				p_meteorMng->SetIsSpawnAble(true);

				StepInEnd(); //終了処理.
				stepInNo++;
			}
		}
		break;

		case 2:
		{
			p_itemMng->Update();
			p_laserMng->Update();
			p_meteorMng->Update();
			p_gameMng->laserNor1->Update();

			//[終了条件] 隕石を壊した & 反射モードが終わったら.
			if (!endTimer.GetIsMove() && isBreakMeteor && isReflectFinish) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				StepInEnd(); //終了処理.
				stepInNo++;
			}
		}
		break;

		case 3:
		{
			p_itemMng->Update();
			p_laserMng->Update();
			p_meteorMng->Update();
			p_gameMng->laserNor1->Update();

			//[終了条件] 一定時間が経過したら.
			if (!endTimer.GetIsMove() && startTimer.GetPassTime() >= 6.0) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//サウンド.
				p_sound->Play(_T("LevelUp"), false, 100);
				//エフェクト.
				EffectData data{};
				data.type = Effect_Tutorial_Step4;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				p_effectMng->SpawnEffect(&data);

				//スコアリセット.
				p_data->scoreBef = p_data->score = 0;
				//スコア表示.
				p_uiMng->SignIsShowScore();
				//召喚可能に.
				p_itemMng->SetIsSpawnAble(true);

				StepInEnd();  //終了処理.
				stepNo++;     //次のステップ.
				stepInNo = 0;
			}
		}
		break;
	}
}
//更新:step4
void TutorialStage::UpdateStep4() {

	//ステップ内項目.
	switch (stepInNo) 
	{
		case 0:
		{
			p_itemMng->Update();
			p_laserMng->Update();
			p_meteorMng->Update();
			p_gameMng->laserNor1->Update();

			//[終了条件] 一定スコアを越える & 反射モードが終わったら.
			if (!endTimer.GetIsMove() && p_data->score >= 2000 && isReflectFinish) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//オブジェクトリセット.
				p_itemMng->Reset();
				p_laserMng->Reset();
				p_meteorMng->Reset();
				p_gameMng->ResetNorLaser();

				StepInEnd(); //終了処理.
				stepInNo++;
			}
		}
		break;

		case 1:
		{
			//[終了条件] 一定時間が経過したら
			if (!endTimer.GetIsMove() && startTimer.GetPassTime() >= 5.0) {
				//BGMフェードアウト.
				p_sound->FadeOutPlay(_T("BGM_Tutorial"), TUTORIAL_END_NEXT_TIME);

				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//チュートリアル終了.
				p_data->scene = SCENE_TITLE;
				p_gameMng->Reset(); //全てリセット.
			}
		}
		break;
	}
}

//描画:step1
void TutorialStage::DrawStep1() {

	//開始タイマーと終了タイマーの組み合わせで透過アニメーションを作る.
	double alpha1 = Calc::CalcNumEaseIn ((startTimer.GetPassTime()-0.5)*2);
	double alpha2 = Calc::CalcNumEaseOut(endTimer.GetPassTime()*2);
	double alpha  = alpha1 * (1-alpha2); //同時に作動しても繋がるように.

    //ステップ内項目.
    switch (stepInNo) 
    {
        case 0:
        {
            DrawTopText1(_T("プレイヤーを移動させる"), alpha);
            DrawTopText2(_T("キーボード操作: WASD / ↑↓←→"), alpha);
            DrawTopText3(_T("コントローラー操作: 左スティック"), alpha);
        }
        break;

        case 1:
        {
            DrawTopText1(_T("攻撃をよける"), alpha);
            DrawTopText2(_T("青いものは敵です。当たると即死します。"), alpha);
            DrawTopText3(_T("灰色:予兆 / 青色:攻撃"), alpha);

            p_gameMng->laserNor1->Draw();
            p_laserMng->Draw();
        }
        break;
    }
}
//描画:step2
void TutorialStage::DrawStep2() {

	//開始タイマーと終了タイマーの組み合わせで透過アニメーションを作る.
	double alpha1 = Calc::CalcNumEaseIn ((startTimer.GetPassTime()-0.5)*2);
	double alpha2 = Calc::CalcNumEaseOut(endTimer.GetPassTime()*2);
	double alpha  = alpha1 * (1-alpha2); //同時に作動しても繋がるように.

    //ステップ内項目.
    switch (stepInNo) 
    {
        case 0:
        {
            DrawTopText1(_T("アイテムをとる"), alpha);
            DrawTopText2(_T("アイテムは画面上から降ってきます。触れると取れます。"), alpha);

			p_itemMng->Draw();
        }
        break;

        case 1:
        {
            DrawTopText1(_T("アイテム発動"), alpha);
            DrawTopText2(_T("触れると自動で効果が発動し、一定時間経つと解除されます。"), alpha);

			p_itemMng->Draw();
        }
        break;
    }
}
//描画:step3
void TutorialStage::DrawStep3() {

	//開始タイマーと終了タイマーの組み合わせで透過アニメーションを作る.
	double alpha1 = Calc::CalcNumEaseIn ((startTimer.GetPassTime()-0.5)*2);
	double alpha2 = Calc::CalcNumEaseOut(endTimer.GetPassTime()*2);
	double alpha  = alpha1 * (1-alpha2); //同時に作動しても繋がるように.

    //ステップ内項目.
    switch (stepInNo) 
    {
        case 0:
        {
            DrawTopText1(_T("反射モード"), alpha);
            DrawTopText2(_T("アイテムを取ると反射モードになります。"), alpha);

			p_itemMng->Draw();
        }
        break;

        case 1:
        {
            DrawTopText1(_T("レーザーを跳ね返す"), alpha);
            DrawTopText2(_T("反射モード中は、レーザーに当たると跳ね返せます。"), alpha);

			p_itemMng->Draw();
			p_laserMng->Draw();
			p_meteorMng->Draw();
			p_gameMng->laserNor1->Draw();
        }
        break;

        case 2:
        {
            DrawTopText1(_T("隕石をこわす"), alpha);
            DrawTopText2(_T("跳ね返したレーザーは、隕石に向かって飛んでいきます。"), alpha);

			p_itemMng->Draw();
			p_laserMng->Draw();
			p_meteorMng->Draw();
			p_gameMng->laserNor1->Draw();
        }
        break;

		case 3:
		{
			DrawTopText1(_T("反射モードの注意"), alpha);
			DrawTopText2(_T("無敵ではないので、レーザー以外に当たると死にます。"), alpha);

			p_itemMng->Draw();
			p_laserMng->Draw();
			p_meteorMng->Draw();
			p_gameMng->laserNor1->Draw();
		}
		break;
    }
}
//描画:step4
void TutorialStage::DrawStep4() {

	//開始タイマーと終了タイマーの組み合わせで透過アニメーションを作る.
	double alpha1 = Calc::CalcNumEaseIn ((startTimer.GetPassTime()-0.5)*2);
	double alpha2 = Calc::CalcNumEaseOut(endTimer.GetPassTime()*2);
	double alpha  = alpha1 * (1-alpha2); //同時に作動しても繋がるように.

    //ステップ内項目.
    switch (stepInNo) 
    {
        case 0:
        {
            DrawTopText2(_T("スコアを稼いで最後に2000点稼いでみましょう。"), alpha);
			DrawTopText3(_T("アイテムを取る:+100, 隕石を壊す:+500"), alpha);

			p_itemMng->Draw();
			p_laserMng->Draw();
			p_meteorMng->Draw();
			p_gameMng->laserNor1->Draw();
        }
        break;

		case 1:
		{
			DrawTopText2(_T("これでチュートリアルは以上です。"), alpha);
			DrawTopText3(_T("自動でタイトルに戻ります..."), alpha);
		}
		break;
    }
} 


//画面上にテキストを出す.
//alphaは0.0～1.0
void TutorialStage::DrawTopText1(MY_STRING text, double alpha) {

	DrawStr str(text, {WINDOW_WID/2, 155}, {0, 255, 255});
	const int useFont = font[1].GetFont();

	{
		const int margin = 24;
		DBL_XY pos  = (str.pos - str.GetTextSize(useFont)/2).Add(-margin/2, -margin/2).ToDblXY();
		DBL_XY size = (str.GetTextSize(useFont) + margin).ToDblXY();
		Box    box  = {pos, size, 0x000000};

		//枠背景.
		SetDrawBlendModeKR(BlendModeID::Alpha, 100*alpha);
		DrawBoxKR(&box, Anchor::LU);
		//テキスト.
		SetDrawBlendModeKR(BlendModeID::Alpha, 255*alpha);
		str.Draw(Anchor::Mid, useFont);
		ResetDrawBlendMode();

		//枠線グラデーション.
		GradLine line;
		line.AddPoint(pos,                     {  0, 255, 255, _int_r(255*alpha)});
		line.AddPoint(pos.Add(size.x,      0), {  0, 100, 255, _int_r(255*alpha)});
		line.AddPoint(pos.Add(size.x, size.y), {  0, 255, 255, _int_r(255*alpha)});
		line.AddPoint(pos.Add(     0, size.y), {  0, 100, 255, _int_r(255*alpha)});
		line.Draw(true);
	}
}
//画面上にテキストを出す(2行目)
//alphaは0.0～1.0
void TutorialStage::DrawTopText2(MY_STRING text, double alpha) {

	DrawStr str(text, {WINDOW_WID/2, 155+70}, {255, 255, 255});
	const int useFont = font[0].GetFont();

	{
		const int margin = 24;
		DBL_XY pos  = (str.pos - str.GetTextSize(useFont)/2).Add(-margin/2, -margin/2).ToDblXY();
		DBL_XY size = (str.GetTextSize(useFont) + margin).ToDblXY();
		Box    box  = {pos, size, 0x000000};

		//枠背景.
		SetDrawBlendModeKR(BlendModeID::Alpha, 100*alpha);
		DrawBoxKR(&box, Anchor::LU);
		//テキスト.
		SetDrawBlendModeKR(BlendModeID::Alpha, 255*alpha);
		str.Draw(Anchor::Mid, useFont);
		ResetDrawBlendMode();

		//枠線グラデーション.
		GradLine line;
		line.AddPoint(pos,                     {  0, 255, 255, _int_r(255*alpha)});
		line.AddPoint(pos.Add(size.x,      0), {  0,   0,   0, _int_r(255*alpha)});
		line.AddPoint(pos.Add(size.x, size.y), {255,   0, 255, _int_r(255*alpha)});
		line.AddPoint(pos.Add(     0, size.y), {  0,   0,   0, _int_r(255*alpha)});
		line.Draw(true);
	}
}
//画面上にテキストを出す(3行目)
//alphaは0.0～1.0
void TutorialStage::DrawTopText3(MY_STRING text, double alpha) {

	DrawStr str(text, {WINDOW_WID/2, 155+70+55}, {255, 255, 255});
	const int useFont = font[0].GetFont();
	
	{
		const int margin = 24;
		DBL_XY pos  = (str.pos - str.GetTextSize(useFont)/2).Add(-margin/2, -margin/2).ToDblXY();
		DBL_XY size = (str.GetTextSize(useFont) + margin).ToDblXY();
		Box    box  = {pos, size, 0x000000};

		//枠背景.
		SetDrawBlendModeKR(BlendModeID::Alpha, 100*alpha);
		DrawBoxKR(&box, Anchor::LU);
		//テキスト.
		SetDrawBlendModeKR(BlendModeID::Alpha, 255*alpha);
		str.Draw(Anchor::Mid, useFont);
		ResetDrawBlendMode();

		//枠線グラデーション.
		GradLine line;
		line.AddPoint(pos,                     {  0, 255, 255, _int_r(255*alpha)});
		line.AddPoint(pos.Add(size.x,      0), {  0,   0,   0, _int_r(255*alpha)});
		line.AddPoint(pos.Add(size.x, size.y), {255,   0, 255, _int_r(255*alpha)});
		line.AddPoint(pos.Add(     0, size.y), {  0,   0,   0, _int_r(255*alpha)});
		line.Draw(true);
	}
}