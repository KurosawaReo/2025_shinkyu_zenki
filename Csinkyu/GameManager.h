/*
   - GameManager.h -
   ゲーム全体管理.
*/
#pragma once

//ゲームマネージャー.
class GameManager 
{
private:
	GameData data{};     //ゲームデータ.

	Timer    tmGame;     //ゲーム時間.
	Timer    tmSlowMode; //スロー継続時間.

public:

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
};