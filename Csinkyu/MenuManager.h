/*
   - MenuManager.h -
   メニューシーン.
*/
#pragma once

//メニュー[継承不可]
class MenuManager final
{
private:
	GameData* p_data{};     // GameDataのポインタ
	int selectedIndex = 0;  // 選択中のインデックス
public:
	void Init();
	void Reset();
	void Update();
	void Draw();
};