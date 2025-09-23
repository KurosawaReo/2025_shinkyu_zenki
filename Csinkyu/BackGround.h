/*
   - BackGround.h -
*/
#pragma once

//前方宣言.
class GameData; 
class BackGround;

//背景タイル.
class BG_Tile
{
	friend class BackGround; //アクセス許可.
private:
	INT_XY   pos{};
	DBL_XY   sizeRate{};
	DrawImg* img[2]{};

	Timer timer = Timer(COUNT_DOWN, 3); //発光する時間.

	GameData*   p_data;
	BackGround* p_bg;

public:
	void Init();                //初期化.
	void Update();              //更新.
	void Draw(double slowTime); //描画.

	void Shine(); //発光.
};

//背景クラス.[継承不可]
class BackGround final
{
//▼実体関係.
public:
	//実体取得用.
	static BackGround& GetInst() {
		static BackGround inst; //自身のインスタンス.
		return inst;
	}
	//使用禁止.
	BackGround(const BackGround&) = delete;
	BackGround& operator=(const BackGround&) = delete;
private:
	//constructor(新規作成をできなくする)
	BackGround(){}

//▼データ.
private:
	vector<BG_Tile> tiles;      //背景タイルデータ.
	DrawImg         imgBG[2]{}; //背景画像.

	TimerMicro tmShine = TimerMicro(COUNT_DOWN, 1000000/60); //光る間隔.

	float counter{}; //時間経過計測用.

	GameData* p_data{}; //ゲームデータ.

public:
	//get.
	float GetCounter() const { return counter; }

	void Init();
	void Update();
	void Draw();
};