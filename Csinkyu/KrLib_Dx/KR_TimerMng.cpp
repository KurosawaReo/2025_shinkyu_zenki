/*
   - KR_TimerMng.cpp - (DxLib)
*/
#include "KR_TimerMng.h"

//KrLib名前空間.
namespace KR
{
	//予約実行する.
	void TimerMng::ReservExe(float timer, function<void()> func) {

		//不正な時間は中断.
		if (timer < 0) { return; }

		//予約設定.
		ReservFunc newFunc;
		newFunc.func = func;
		newFunc.time = gameTimer.GetPassTime() + timer; //現在時刻 + 何秒後か.
		//予約リストに追加.
		functions.push_back(newFunc);
	}

	//初期化.
	void TimerMng::Init() {
		gameTimer.Start(); //タイマー開始.
	}

	//更新.
	void TimerMng::Update() {

		//予約がない時は処理しない.
		if (functions.size() <= 0) { return; }

		//現在時刻取得.
		const float nowTime = gameTimer.GetPassTime();
		//予約リスト全ループ.
		for (auto it = functions.begin(); it != functions.end(); ) {
			//予約時間になったら.
			if (it->time <= nowTime) {
				it->func();               //関数実行.
				it = functions.erase(it); //完了したため削除.
			}
			else {
				it++;
			}
		}
	}
}