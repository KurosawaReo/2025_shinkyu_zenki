/*
   - UIManager.h -
   UI管理.
*/
#pragma once

//前方宣言.
class GameManager;
class TutorialStage;

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

	int  disBestScore{}; //表示ベストスコア.
	int  disScore{};     //表示スコア.

	bool isShowScore{}; //スコアを表示するかどうか.

	GameManager*   p_gameMng{};
	GameData*      p_gameData{};
	TutorialStage* p_tutorialStg{};

public:
	//sign.
	void SignIsShowScore() { isShowScore = true; }
	//set.
	void SetDisBestScore(int _score) { disBestScore = _score; }

	void Init();
	void Reset();
	void Update();
	void Draw();
};