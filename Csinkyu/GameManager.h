/*
   - GameManager.h -
   ゲーム全体管理.
*/
#pragma once

//ゲームマネージャー.
class GameManager 
{
private:
	GameData data{}; //ゲームデータ.

	Timer tmGame     = Timer(0, CountUp);                //ゲーム時間.
	Timer tmSlowMode = Timer(SLOW_MODE_TIME, CountDown); //スロー継続時間.

public:
	static GameManager* pSelf; //自身のポインタ.

	//メイン処理.
	void Init();
	void Reset();
	void Update();
	void Draw();

	//Update.
	void UpdateTitle();
	void UpdateGame();
	void UpdateEnd();

	//Draw.
	void DrawTitle();
	void DrawGame();
	void DrawEnd();
	void DrawObjests();

	//その他.
	void GameEnd();
};