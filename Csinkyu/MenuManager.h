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
	GameData* p_data{};    //GameDataのポインタ.

	Font    fontMenu[2]{}; //メニュー用フォント.

	int   selectedIndex = 0;  // 選択中のインデックス
	float counter = 0;        // 経過時間カウンター.

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