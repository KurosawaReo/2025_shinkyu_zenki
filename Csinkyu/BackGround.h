/*
   - BackGround.h -
*/
#pragma once

//背景タイル.
class BG_Tile
{
	friend class BackGround; //アクセス許可.
private:
	INT_XY     pos{};
	DBL_XY     sizeRate{};
	DrawImg* img[2]{};

	Timer timer = Timer(COUNT_DOWN, 3); //発光する時間.

	GameData* p_data{};

public:
	void Init(GameData*);                    //初期化.
	void Update();                           //更新.
	void Draw(bool isSlow, double slowTime); //描画.

	void Shine(); //発光.
};

//背景クラス.
class BackGround
{
private:
	vector<BG_Tile> tiles;      //背景タイルデータ.
	DrawImg       imgBG[2]{}; //背景画像.

	TimerMicro tmShine = TimerMicro(COUNT_DOWN, 1000000/60); //光る間隔.

	GameData* p_data{}; //ゲームデータ.
	Calc*     p_calc{}; //計算機能.

public:
	void Init(GameData*);
	void Update();
	void Draw();
};