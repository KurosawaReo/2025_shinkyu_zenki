/*
   - Stage_Tutorial.cpp -
   
   ステージ: チュートリアル.
*/
#include "Stage_Tutorial.h"

//依存関係.
#include "LaserManager.h"
#include "Obst_NormalLaser.h"
#include "Obst_StraightLaser.h"
#include "Obst_MeteorManager.h"
#include "Obst_Ripples.h"
#include "Obst_Fireworks.h"
#include "Item.h"
#include "EffectManager.h"
#include "UIManager.h"
#include "GameData.h"
#include "GameManager.h"
//参照.
static GameData&			gameData		= GameData::GetInst();
static GameManager&			gameMng			= GameManager::GetInst();
static LaserManager&		laserMng		= LaserManager::GetInst();
static MeteorManager&		meteorMng		= MeteorManager::GetInst();
static Ripples&				ripples			= Ripples::GetInst();
static ItemManager&			itemMng			= ItemManager::GetInst();
static Player&				player			= Player::GetInst();
static FireworksManager&	fireworksMng	= FireworksManager::GetInst();
static EffectManager&		effectMng		= EffectManager::GetInst();
static UIManager&			uiMng			= UIManager::GetInst();

//初期化.
void TutorialStage::Init() {

	font[0].CreateFontH(_T(""), 25, 1, FontTypeID::Anti);
	font[1].CreateFontH(_T(""), 30, 1, FontTypeID::Anti);

	//タイマー
	startTimer = Timer(TimerMode::CountUp, 0);
	endTimer   = Timer(TimerMode::CountUp, 0);
}
//リセット.
void TutorialStage::Reset() {

	startTimer.Reset();
	endTimer.Reset();
	stepNo   = 0;    //後からstep1にする.
	stepInNo = 0;    //0スタート.

	plyMoveCntr = 0; 
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

	isPlayerDash    = false;
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
	if (auto i = SoundMng::Get("LevelUp")) {
		i->Play(false, 100); //再生.
	}
	//エフェクト.
	EffectData data{};
	data.type = Effect_Tutorial_Step1;
	data.pos = { WINDOW_WID/2, WINDOW_HEI/2 };
	effectMng.SpawnEffect(&data);

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
			//移動したらカウンターを+1
			if (player.IsMoved()) {
				plyMoveCntr += 1;
			}

			//[終了条件] 一定時間移動したら.
			if (endTimer.GetState() != TimerState::Active && 
				plyMoveCntr >= 50) 
			{
				endTimer.Start();
			}
			//次の説明へ.
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//終了処理.
				StepInEnd();
				stepInNo++;
			}
		}
		break;

		case 1:
		{
			//[終了条件] ダッシュしたら.
			if (endTimer.GetState() != TimerState::Active && isPlayerDash) {
				endTimer.Start();
			}
			//次の説明へ.
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//オブジェクトON.
				ManagerBase::GetMng<LaserManager>()->SetExeState(MngExeState::Active);
				ManagerBase::GetMng<NormalLaser_1>()->SetExeState(MngExeState::Active);
				//終了処理.
				StepInEnd();
				stepInNo++;
			}
		}
		break;

		case 2:
		{
			//最初の一定時間は停止.
			if (startTimer.GetPassTime() < TUTORIAL_START_WAIT_TIME) { break; }

			//[終了条件] 一定時間経過したら.
			if (endTimer.GetState() != TimerState::Active && 
				startTimer.GetPassTime() >= 9.5) 
			{
				endTimer.Start();
			}
			//次の説明へ.
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//サウンド.
				if (auto i = SoundMng::Get("LevelUp")) {
					i->Play(false, 100); //再生.
				}
				//エフェクト.
				EffectData data{};
				data.type = Effect_Tutorial_Step2;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);

				//オブジェクトOFF.
				laserMng.Reset();
				gameMng.ResetNorLaser();
				ManagerBase::GetMng<LaserManager>()->SetExeState(MngExeState::Stop);
				ManagerBase::GetMng<NormalLaser_1>()->SetExeState(MngExeState::Stop);
				//オブジェクトON.
				ManagerBase::GetMng<ItemManager>()->SetExeState(MngExeState::Active);
				//アイテム召喚.
				itemMng.ItemSpawn(0);

				//終了処理.
				StepInEnd();
				stepNo++;
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

			//[終了条件] アイテムを取ったら.
			if (endTimer.GetState() != TimerState::Active && isTakeItem) {
				endTimer.Start();
			}
			//次の説明へ.
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//終了処理.
				StepInEnd();
				stepInNo++;
			}
		}
		break;

		case 1:
		{
			//最初の一定時間は停止.
			if (startTimer.GetPassTime() < TUTORIAL_START_WAIT_TIME) { break; }

			//[終了条件] 反射モードが終わったら.
			if (endTimer.GetState() != TimerState::Active && isReflectFinish) {
				endTimer.Start();
			}
			//次の説明へ.
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//サウンド.
				if (auto i = SoundMng::Get("LevelUp")) {
					i->Play(false, 100); //再生.
				}
				//エフェクト.
				EffectData data{};
				data.type = Effect_Tutorial_Step3;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
				//アイテム召喚.
				itemMng.ItemSpawn(0);
				//終了処理.
				StepInEnd();
				stepNo++;
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

			//[終了条件] アイテムを取ったら.
			if (endTimer.GetState() != TimerState::Active && isTakeItem) {
				endTimer.Start();
			}
			//次の説明へ.
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//終了処理.
				StepInEnd();
				stepInNo++;
			}
		}
		break;

		case 1:
		{
			//最初の一定時間は停止.
			if (startTimer.GetPassTime() < TUTORIAL_START_WAIT_TIME) { break; }

			//[終了条件] レーザーを反射した && 反射モードが終わったら.
			if (endTimer.GetState() != TimerState::Active && isReflectLaser && isReflectFinish) {
				endTimer.Start();
			}
			//次の説明へ.
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//オブジェクトON.
				ManagerBase::GetMng<MeteorManager>()->SetExeState(MngExeState::Active);
				//終了処理.
				StepInEnd();
				stepInNo++;
			}
		}
		break;

		case 2:
		{
			//[終了条件] 隕石を壊した & 反射モードが終わったら.
			if (endTimer.GetState() != TimerState::Active && isBreakMeteor && isReflectFinish) {
				endTimer.Start();
			}
			//次の説明へ.
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//終了処理.
				StepInEnd();
				stepInNo++;
			}
		}
		break;

		case 3:
		{
			//[終了条件] 一定時間が経過したら.
			if (endTimer.GetState() != TimerState::Active && 
				startTimer.GetPassTime() >= 6.0) 
			{
				endTimer.Start();
			}
			//次の説明へ.
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//サウンド.
				if (auto i = SoundMng::Get("LevelUp")) {
					i->Play(false, 100); //再生.
				}
				//エフェクト.
				EffectData data{};
				data.type = Effect_Tutorial_Step4;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);

				//スコアリセット.
				gameData.scoreBef = gameData.score = 0;
				//スコア表示.
				uiMng.SignIsShowScore();
				//召喚可能に.
				ManagerBase::GetMng<ItemManager>()->SetExeState(MngExeState::Active);

				//終了処理.
				StepInEnd();
				stepNo++;
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
			//[終了条件] 一定スコアを越える & 反射モードが終わったら.
			if (endTimer.GetState() != TimerState::Active && 
				gameData.score >= 2000 && isReflectFinish) 
			{
				endTimer.Start();
			}
			//次の説明へ.
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//オブジェクトOFF.
				ManagerBase::GetMng<ItemManager>()->SetExeState(MngExeState::Stop);
				ManagerBase::GetMng<NormalLaser_1>()->SetExeState(MngExeState::Stop);
				ManagerBase::GetMng<LaserManager>()->SetExeState(MngExeState::Stop);
				ManagerBase::GetMng<MeteorManager>()->SetExeState(MngExeState::Stop);
				//終了処理.
				StepInEnd();
				stepInNo++;
			}
		}
		break;

		case 1:
		{
			//[終了条件] 一定時間が経過したら
			if (endTimer.GetState() != TimerState::Active && 
				startTimer.GetPassTime() >= 5.0) 
			{
#if !defined BGM_NONE
				//BGMフェードアウト.
				if (auto i = SoundMng::Get("BGM_Tutorial")) {
					i->FadeOutPlay(TUTORIAL_END_NEXT_TIME); //再生.
				}
#endif
				endTimer.Start();
			}
			//チュートリアル終了.
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				SceneMng::SetScene("Title");
				gameMng.Reset(); //全てリセット.
			}
		}
		break;
	}
}

//描画:step1
void TutorialStage::DrawStep1() {

	//開始タイマーと終了タイマーの組み合わせで透過アニメーションを作る.
	double alpha1 = Calc::AnimEaseIn ((startTimer.GetPassTime()-0.5)*2);
	double alpha2 = Calc::AnimEaseOut(endTimer.GetPassTime()*2);
	double alpha  = alpha1 * (1-alpha2); //同時に作動しても繋がるように.

    //ステップ内項目.
    switch (stepInNo) 
    {
        case 0:
        {
            DrawTopText(1, _T("プレイヤーを移動させる"), alpha);
            DrawTopText(2, _T("キーボード　　 : WASD / ↑↓←→"), alpha);
            DrawTopText(3, _T("コントローラー : 左スティック　 "), alpha);
			DrawTopText(4, _T("アーケード　　 : レバー　　　　 "), alpha);
        }
        break;

		case 1:
		{
			DrawTopText(1, _T("ダッシュする"), alpha);
			DrawTopText(2, _T("キーボード　　 : 移動 + SHIFTキー "), alpha);
			DrawTopText(3, _T("コントローラー : 移動 + Bボタン　 "), alpha);
			DrawTopText(4, _T("アーケード　　 : 移動 + 右上ボタン"), alpha);
		}
		break;

        case 2:
        {
            DrawTopText(1, _T("攻撃をよける"), alpha);
            DrawTopText(2, _T("青いものは敵です。当たると即死します。"), alpha);
            DrawTopText(3, _T("灰色:予告, 青色:攻撃"), alpha);
        }
        break;
    }
}
//描画:step2
void TutorialStage::DrawStep2() {

	//開始タイマーと終了タイマーの組み合わせで透過アニメーションを作る.
	double alpha1 = Calc::AnimEaseIn ((startTimer.GetPassTime()-0.5)*2);
	double alpha2 = Calc::AnimEaseOut(endTimer.GetPassTime()*2);
	double alpha  = alpha1 * (1-alpha2); //同時に作動しても繋がるように.

    //ステップ内項目.
    switch (stepInNo) 
    {
        case 0:
        {
            DrawTopText(1, _T("アイテムをとる"), alpha);
            DrawTopText(2, _T("アイテムは画面上から降ってきます。触れると自動で取れます。"), alpha);
        }
        break;

        case 1:
        {
            DrawTopText(1, _T("アイテム発動"), alpha);
            DrawTopText(2, _T("触れると効果が発動し、一定時間経つと解除されます。"), alpha);
        }
        break;
    }
}
//描画:step3
void TutorialStage::DrawStep3() {

	//開始タイマーと終了タイマーの組み合わせで透過アニメーションを作る.
	double alpha1 = Calc::AnimEaseIn ((startTimer.GetPassTime()-0.5)*2);
	double alpha2 = Calc::AnimEaseOut(endTimer.GetPassTime()*2);
	double alpha  = alpha1 * (1-alpha2); //同時に作動しても繋がるように.

    //ステップ内項目.
    switch (stepInNo) 
    {
        case 0:
        {
            DrawTopText(1, _T("反射モード"), alpha);
            DrawTopText(2, _T("アイテムを取ると反射モードになります。"), alpha);
        }
        break;

        case 1:
        {
            DrawTopText(1, _T("レーザーを跳ね返す"), alpha);
            DrawTopText(2, _T("反射モード中は、レーザーに当たると跳ね返せます。"), alpha);
        }
        break;

        case 2:
        {
            DrawTopText(1, _T("隕石をこわす"), alpha);
            DrawTopText(2, _T("跳ね返したレーザーは、隕石に向かって飛んでいきます。"), alpha);
        }
        break;

		case 3:
		{
			DrawTopText(1, _T("反射モードの注意"), alpha);
			DrawTopText(2, _T("無敵ではないので、レーザー以外には当たると死にます。ご注意ください。"), alpha);
		}
		break;
    }
}
//描画:step4
void TutorialStage::DrawStep4() {

	//開始タイマーと終了タイマーの組み合わせで透過アニメーションを作る.
	double alpha1 = Calc::AnimEaseIn ((startTimer.GetPassTime()-0.5)*2);
	double alpha2 = Calc::AnimEaseOut(endTimer.GetPassTime()*2);
	double alpha  = alpha1 * (1-alpha2); //同時に作動しても繋がるように.

    //ステップ内項目.
    switch (stepInNo) 
    {
        case 0:
        {
            DrawTopText(2, _T("最後に、スコアを2000点稼いでみましょう。"), alpha);
			DrawTopText(3, _T("アイテムを取る:+100, 隕石を壊す:+500"), alpha);
        }
        break;

		case 1:
		{
			DrawTopText(2, _T("これでチュートリアルは以上です。"), alpha);
			DrawTopText(3, _T("ハイスコアを目指して頑張ってください！"), alpha);
		}
		break;
    }
} 

/*
   画面上にテキストを出す.
   alpha: 0.0～1.0
   line : 行数
*/
void TutorialStage::DrawTopText(int line, MY_STRING text, double alpha) {

	//テキスト設定.
	DrawStr str(text, {WINDOW_WID/2, 0}, {});
	switch (line) {
		case 1: 
			str.pos.y = 155;
			str.color = {0, 255, 255};
			break;
		case 2: 
			str.pos.y = 155+70;
			str.color = {255, 255, 255};
			break;
		case 3: 
			str.pos.y = 155+70+55;
			str.color = {255, 255, 255};
			break;
		case 4: 
			str.pos.y = 155+70+55+55; 
			str.color = {255, 255, 255};
			break;
	}
	//フォント.
	const int useFont = (line == 1) ? font[1].GetFont() : font[0].GetFont();

	{
		const int margin = 24;
		DBL_XY pos  = (str.pos - str.GetTextSize(useFont)/2).Add(-margin/2, -margin/2).ToDbl();
		DBL_XY size = (str.GetTextSize(useFont) + margin).ToDbl();
		Box    box  = {pos, size, 0x000000};

		//枠背景.
		{
			DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 100*alpha);
			DrawBoxKR(box, Anchor::LU);
		}
		//テキスト.
		{
			DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255*alpha);
			str.Draw(Anchor::Mid, useFont);
		}
		//枠線グラデーション.
		GradLine gradLine;
		if (line == 1) {
			gradLine.AddPoint(pos,                     {  0, 255, 255, _int_r(255*alpha)});
			gradLine.AddPoint(pos.Add(size.x,      0), {  0, 100, 255, _int_r(255*alpha)});
			gradLine.AddPoint(pos.Add(size.x, size.y), {  0, 255, 255, _int_r(255*alpha)});
			gradLine.AddPoint(pos.Add(     0, size.y), {  0, 100, 255, _int_r(255*alpha)});
		}
		else {
			gradLine.AddPoint(pos,                     {  0, 255, 255, _int_r(255*alpha)});
			gradLine.AddPoint(pos.Add(size.x,      0), {  0,   0,   0, _int_r(255*alpha)});
			gradLine.AddPoint(pos.Add(size.x, size.y), {255,   0, 255, _int_r(255*alpha)});
			gradLine.AddPoint(pos.Add(     0, size.y), {  0,   0,   0, _int_r(255*alpha)});
		}
		gradLine.Draw(true);
	}
}