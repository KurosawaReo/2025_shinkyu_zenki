/*
   - BG1.h -
*/
#pragma once
#include "BG_Base.h"

//背景タイル.
class BG_Tile
{
	friend class BG1; //アクセス許可.
private:
	INT_XY   pos{};
	DBL_XY   sizeRate{};

	Timer    timer = Timer(TimerMode::CountDown, 3); //発光する時間.

	GameData*  p_data{};

public:
	void Init();								//初期化.
	void Update();								//更新.
	void Draw(double slowTime, float counter);	//描画.

	void Shine(); //発光.
};

//背景1.
class BG1 : public BG_Base
{
//▼変数.
private:
	vector<BG_Tile> tiles; //背景タイルデータ.

	TimerMicro tmShine = TimerMicro(TimerMode::CountDown, 1000000/60); //光る間隔.

	GameData* p_data{}; //ゲームデータ.

//▼関数.
public:
	void Init()   override;
	void Update() override;
	void Draw()   override;

	//ポーズ用.
	void StopAnim()    override;
	void RestartAnim() override;
};