/*
   - GameManager.h -
   ゲーム全体管理.
*/
#pragma once

//ゲームマネージャー.
class GameManager 
{
private: //実体.
	static GameManager inst; //自身のインスタンス.

private: //データ.
	GameData data{}; //ゲームデータ.

	//シーン別に経過時間を記録する.
	Timer tmScene[SCENE_COUNT] = {
		Timer(COUNT_UP, 0), //Titleシーン.
		Timer(COUNT_UP, 0), //Readyシーン.
		Timer(COUNT_UP, 0), //Gameシーン.
		Timer(COUNT_UP, 0), //Endシーン.
		Timer(COUNT_UP, 0), //Pauseシーン.
	};
	Timer tmSlowMode = Timer(COUNT_DOWN, SLOW_MODE_TIME); //スロー継続時間.

	DrawImgST imgLogo[2];   //タイトルロゴ画像.
	DrawImgST imgUI[4];     //UI画像.
	DrawImgST imgNewRecord; //new record.
	DrawImgST imgGameOver;  //gameover.

	bool isTitleAnim{};             //Title:     破片アニメーションを出したか.
	bool isBestScoreSound{};        //BestScore: 音を鳴らしたか.
	bool isItemCountDownSound[3]{}; //Item:      カウントダウンの音を鳴らしたか.

	InputST* p_input{};
	SoundST* p_sound{};

public:
	//実体の取得.
	static GameManager* GetPtr() {
		return &inst;
	}
	//get.
	float GetSlowModeTime() {
		return tmSlowMode.GetPassTime();
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

	void DrawUI();
	void DrawObjects();
	void DrawReflectMode();

	//その他.
	void GameEnd();
	void TakeItem();
};