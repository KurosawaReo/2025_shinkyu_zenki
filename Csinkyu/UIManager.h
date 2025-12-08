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
//▼実体関係.
public:
	static UIManager& GetInst() {
		static UIManager inst; //自身のインスタンス.
		return inst;
	}

//▼データ.
private:
	int  disBestScore{}; //表示ベストスコア.
	int  disScore{};     //表示スコア.

	bool isShowScore{}; //スコアを表示するかどうか.

	GameManager*   p_gameMng{};
	GameData*      p_gameData{};
	TutorialStage* p_tutorialStg{};

private:
	//constructor(新規作成をできなくする)
	UIManager(){}

public:
	//sign.
	void SignIsShowScore() { isShowScore = true; }
	//set.
	void SetDisBestScore(int _score) { disBestScore = _score; }

	void Init();
	void Reset();
	void Update();
	void Draw();

	//使用禁止.
	UIManager(const UIManager&) = delete;
	UIManager& operator=(const UIManager&) = delete;
};