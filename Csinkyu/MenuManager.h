/*
   - MenuManager.h -
   メニューシーン.
*/
#pragma once

//メニュー.[継承不可]
class MenuManager final
{
public: //実体.
	static MenuManager* GetPtr() {
		static MenuManager inst; //自身のインスタンス.
		return &inst;
	}

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