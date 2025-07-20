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

	Timer tmTitle    = Timer(CountUp,   0);              //タイトル用タイマー.
	Timer tmReady    = Timer(CountUp,   0);              //開始用タイマー.
	Timer tmGame     = Timer(CountUp,   0);              //ゲーム時間.
	Timer tmSlowMode = Timer(CountDown, SLOW_MODE_TIME); //スロー継続時間.

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

	//Update.
	void UpdateTitle();
	void UpdateReady();
	void UpdateGame();
	void UpdateEnd();

	void UpdateObjects();

	//Draw.
	void DrawTitle();
	void DrawReady();
	void DrawGame();
	void DrawEnd();

	void DrawBG();
	void DrawUI();
	void DrawObjects();
	void DrawSlowMode();

	//その他.
	void GameEnd();
	void TakeItem();
};