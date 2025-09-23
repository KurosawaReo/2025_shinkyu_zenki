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
	//実体取得用.
	static MenuManager& GetInst() {
		static MenuManager inst; //自身のインスタンス.
		return inst;
	}
	//使用禁止.
	MenuManager(const MenuManager&) = delete;
	MenuManager& operator=(const MenuManager&) = delete;
private:
	//constructor(新規作成をできなくする)
	MenuManager(){}

//▼データ.
private:
	GameData* p_data{};    //GameDataのポインタ.
	SoundMng* p_sound{};   //サウンド管理.

	DrawImg imgMenu [3]{}; //メニュー用画像.
	Font    fontMenu[2]{}; //メニュー用フォント.

	int   selectedIndex = 0;  // 選択中のインデックス
	float counter = 0;        // 経過時間カウンター.

public:
	void Init();
	void Reset();
	void Update();
	void Draw();
};