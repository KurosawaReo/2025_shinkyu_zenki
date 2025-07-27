/*
   - GameManager.h -
   ゲーム全体管理.
*/
#pragma once

//ゲームマネージャー.
class GameManager 
{
private: //実体.
	static GameManager self; //自身の実体.

private: //データ.
	GameData data{}; //ゲームデータ.

	//シーン別に経過時間を記録する.
	Timer tmScene[SCENE_COUNT] = {
		Timer(CountUp, 0), //Titleシーン.
		Timer(CountUp, 0), //Readyシーン.
		Timer(CountUp, 0), //Gameシーン.
		Timer(CountUp, 0), //Endシーン.
		Timer(CountUp, 0), //Pauseシーン.
	};
	Timer tmSlowMode = Timer(CountDown, SLOW_MODE_TIME); //スロー継続時間.

	DrawImgST imgLogo[2]; //タイトルロゴ画像.
	DrawImgST imgUI;      //UI画像.

	BOOL isFinTitleAnim{}; //タイトルアニメーション用.
	BOOL isFinScoreAnim{}; //最高スコアアニメーション用.
	BOOL isItemCount[3]{}; //アイテムカウントダウンの音を鳴らしたか.

	InputST* p_input{};
	SoundST* p_sound{};

public:
	//実体の取得.
	static GameManager* GetPtr() {
		return &self;
	}

	//メイン処理.
	void Init();
	void Reset();
	void Update();
	void Draw();

	//Reset.
	void ResetNorLaser();
	void ResetStrLaser();

	//Update.
	void UpdateTitle();
	void UpdateReady();
	void UpdateGame();
	void UpdateEnd();
	void UpdatePause();

	void UpdateObjects();

	//Draw.
	void DrawTitle();
	void DrawReady();
	void DrawGame();
	void DrawEnd();
	void DrawPause();

	void DrawBG();
	void DrawUI();
	void DrawObjects();
	void DrawReflectMode();

	//その他.
	void GameEnd();
	void TakeItem();
};