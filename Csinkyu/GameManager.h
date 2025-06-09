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
	//GameManager(); //privateにすることでコンストラクタを使用禁止する.

private: //データ.
	GameData data{}; //ゲームデータ.

	Timer tmGame     = Timer(0, CountUp);                //ゲーム時間.
	Timer tmSlowMode = Timer(SLOW_MODE_TIME, CountDown); //スロー継続時間.

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