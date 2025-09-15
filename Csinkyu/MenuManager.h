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
	GameData* p_data{};     // GameDataのポインタ
	SoundMng* p_sound{};    // サウンド管理.

	int selectedIndex = 0;  // 選択中のインデックス

public:
	void Init();
	void Reset();
	void Update();
	void Draw();
};