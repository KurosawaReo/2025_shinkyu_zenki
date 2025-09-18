/*
   - UIManager.h -
   UI管理.
*/
#pragma once

class GameManager; //前方宣言.

//UI管理.[継承不可]
class UIManager final
{
public: //実体.
	static UIManager* GetPtr() {
		static UIManager inst; //自身のインスタンス.
		return &inst;
	}

private: //データ.
	DrawImg imgUI[4]{}; //UI画像.

	GameManager* p_gameMng{};
	GameData*    p_gameData{};

public:
	void Init();
	void Reset();
	void Update();
	void Draw();
};