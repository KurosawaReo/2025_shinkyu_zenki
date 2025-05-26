/*
   - myTimerST.h - (original)
   ver.2025/05/20

   DxLibで使う用のオリジナル時間関数.
*/
#pragma once

//タイマー機能.
class Timer
{
private:
	clock_t stTime; //開始時刻.
	clock_t edTime; //終了時刻.
	BOOL    isMove; //計測中か.

public:
	void StartTimer() {
		stTime = clock(); //タイマー開始.
		edTime = 0;
		isMove = TRUE;    //動いた.
	}
	void StopTimer() {
		edTime = clock(); //タイマー終了.
		isMove = FALSE;   //停止した.
	}
	float GetTime() {
		if (!isMove) {
			return (float)(edTime - stTime)/1000; //時間差を返す.
		}
		return 0;
	}
	float GetNowTime() {
		if (isMove) {
			return (float)(clock() - stTime)/1000; //時間差を返す.
		}
		return 0;
	}
};