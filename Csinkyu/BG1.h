/*
   - BG1.h -
*/
#pragma once

//前方宣言.
class GameData;
class BGManager;

//背景タイル.
class BG_Tile
{
	friend class BG1; //アクセス許可.
private:
	INT_XY   pos{};
	DBL_XY   sizeRate{};

	Timer timer = Timer(TimerMode::CountDown, 3); //発光する時間.

	GameData* p_data;
	BG1*      p_bg;

public:
	void Init();                //初期化.
	void Update();              //更新.
	void Draw(double slowTime); //描画.

	void Shine(); //発光.
};

//背景1.[継承不可]
class BG1 final
{
//▼実体関係.
public:
	static BG1& GetInst() {
		static BG1 inst; //自身のインスタンス.
		return inst;
	}

//▼変数.
private:
	vector<BG_Tile> tiles; //背景タイルデータ.

	TimerMicro tmShine = TimerMicro(TimerMode::CountDown, 1000000/60); //光る間隔.

	float counter{}; //時間経過計測用.

	GameData* p_data{}; //ゲームデータ.

//▼関数.
private:
	//constructor(新規作成をできなくする)
	BG1(){}

public:
	//get.
	float GetCounter() const { return counter; }

	void Init();
	void Update();
	void Draw();

	//ポーズ用.
	void StopAnim();
	void RestartAnim();

	//使用禁止.
	BG1(const BG1&) = delete;
	BG1& operator=(const BG1&) = delete;
};