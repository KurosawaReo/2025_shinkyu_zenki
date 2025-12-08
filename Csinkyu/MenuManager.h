/*
   - MenuManager.h -
   メニューシーン.
*/
#pragma once

//メニュー.[継承不可]
class MenuManager final
{
//▼実体関係.
public:
	static MenuManager& GetInst() {
		static MenuManager inst; //自身のインスタンス.
		return inst;
	}

//▼データ.
private:
	GameData* p_data{};           //GameDataのポインタ.

	Font      fontMenu[2]{};      //メニュー用フォント.

	int       selectedIndex = 0;  //カーソルの選択位置 | 0:ゲーム開始 | 1:チュートリアル | 2:タイトルに戻る |
	float     counter = 0;        //経過時間.

	//点滅処理.
	Timer     tmBlink = Timer(TimerMode::CountDown, 0.1f); //点滅間隔.
	Timer     tmTitle = Timer(TimerMode::CountDown, 2.5f); //タイトルアニメ用.
	bool      isBlink = 0;                                 //点滅させる用.

private:
	//constructor(新規作成をできなくする)
	MenuManager(){}

public:
	void Init();
	void Reset();
	void Update();
	void Draw();
	
	//使用禁止.
	MenuManager(const MenuManager&) = delete;
	MenuManager& operator=(const MenuManager&) = delete;
};