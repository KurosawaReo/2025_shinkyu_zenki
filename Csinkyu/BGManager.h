/*
   - BGManager.h -
*/
#pragma once

//背景クラス.[継承不可]
class BGManager final
{
//▼実体関係.
public:
	static BGManager& GetInst() {
		static BGManager inst; //自身のインスタンス.
		return inst;
	}

//▼関数.
private:
	//constructor(新規作成をできなくする)
	BGManager(){}

public:
	void Init();
	void Update();
	void Draw();

	//ポーズ用.
	void StopAnim();
	void RestartAnim();

	//使用禁止.
	BGManager(const BGManager&) = delete;
	BGManager& operator=(const BGManager&) = delete;
};