/*
   - UIManager.h -
   UI管理.
*/
#pragma once

//UI管理.
class UIManager final : public ManagerBase
{
//▼ ===== 変数 ===== ▼.
private:
	int  dispBestScore{}; //表示ベストスコア.

	bool isShowScore{}; //スコアを表示するかどうか.

//▼ ===== 関数 ===== ▼.
public:
	//コンストラクタ.
	UIManager(int order) : ManagerBase(order) {}

	//sign.
	void SignIsShowScore() { isShowScore = true; }
	//set.
	void SetBestScore(int _score) { dispBestScore = _score; }

	void Init()   override;
	void Reset()  override;
	void Update() override;
	void Draw()   override;

	//使用禁止.
	UIManager(const UIManager*) = delete;
	UIManager* operator=(const UIManager*) = delete;
};