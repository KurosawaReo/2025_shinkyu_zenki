/*
   - BGManager.h -
*/
#pragma once
#include "BG1.h"
#include "BG2.h"

//背景クラス.
class BGManager : public ManagerBase 
{
//▼実体関係.
public:
	static BGManager& GetInst() {
		static BGManager inst; //自身のインスタンス.
		return inst;
	}

//▼ ===== 変数 ===== ▼.
private:
	float counter{}; //経過時間.

	int   useBgNo{}; //何番目の背景を使うか.
	BG1   bg1{};     //背景1.
	BG2   bg2{};     //背景2.

//▼ ===== 関数 ===== ▼.
private:
	//コンストラクタ.
	BGManager() : ManagerBase(ORDER_BG_MNG) {}

public:
	//set.
	void  SetBgNo(int _no) { useBgNo = _no; }
	//get.
	float GetCounter() const { return counter; }

	void  Init()   override;
	void  Reset()  override;
	void  Update() override;
	void  Draw()   override;

	//ポーズ用.
	void  PauseAnim();
	void  RestartAnim();

	//使用禁止.
	BGManager(const BGManager&) = delete;
	BGManager& operator=(const BGManager&) = delete;
};