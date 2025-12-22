/*
   - BGManager.h -
*/
#pragma once
#include "BG1.h"

//背景クラス.[継承不可]
class BGManager final
{
//▼実体関係.
public:
	static BGManager& GetInst() {
		static BGManager inst; //自身のインスタンス.
		return inst;
	}

//▼変数.
private:
	float counter{}; //経過時間.

	int   useBgNo{}; //何番目の背景を使うか.
	BG1   bg1{};     //背景1.

//▼関数.
private:
	//constructor(新規作成をできなくする)
	BGManager(){}

public:
	//get.
	float GetCounter() const { return counter; }

	void  Init();
	void  Update();
	void  Draw();

	//ポーズ用.
	void  StopAnim();
	void  RestartAnim();

	//使用禁止.
	BGManager(const BGManager&) = delete;
	BGManager& operator=(const BGManager&) = delete;
};