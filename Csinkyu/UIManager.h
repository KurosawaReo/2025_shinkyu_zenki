/*
   - UIManager.h -
   UI管理.
*/
#pragma once

//UI管理.
class UIManager : public ManagerBase
{
//▼ ===== 実体 ===== ▼.
private:
	static UIManager inst; //自身のインスタンス.
public:
	static UIManager& GetInst() {
		return inst;
	}

//▼ ===== 変数 ===== ▼.
private:
	int  disBestScore{}; //表示ベストスコア.
	int  disScore{};     //表示スコア.

	bool isShowScore{}; //スコアを表示するかどうか.

//▼ ===== 関数 ===== ▼.
private:
	//コンストラクタ.
	UIManager() : ManagerBase(ORDER_UI_MNG) {}

public:
	//sign.
	void SignIsShowScore() { isShowScore = true; }
	//set.
	void SetDisBestScore(int _score) { disBestScore = _score; }

	void Init()   override;
	void Reset()  override;
	void Update() override;
	void Draw()   override;

	//使用禁止.
	UIManager(const UIManager&) = delete;
	UIManager& operator=(const UIManager&) = delete;
};