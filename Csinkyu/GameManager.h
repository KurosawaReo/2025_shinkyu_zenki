/*
   - GameManager.h -
   ゲーム全体管理.
*/
#pragma once

//ゲームマネージャー.
class GameManager 
{
private:
	clock_t  stTime;
	clock_t  nowTime;

	GameData data{}; //ゲームデータ.

public:

	//get.
	float GetTime();

	//その他.
	void Init();
	void Reset();
	void Update();
	void Draw();

	void UpdateTitle();
	void UpdateGame();
	void UpdateEnd();

	void DrawTitle();
	void DrawGame();
	void DrawEnd();
	void DrawObjests();
};