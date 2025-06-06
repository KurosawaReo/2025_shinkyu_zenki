/*
   - myTimerST.h - (original)
   ver.2025/06/02

   DxLibで使う用のオリジナル時間関数.
*/
#pragma once

//タイマーモード.
enum TimerMode
{
	CountUp,
	CountDown,
};
//タイマー機能.
class Timer
{
private:
	float     initTime{}; //初期時間.
	clock_t   stTime{};   //計測開始時刻.
	clock_t   edTime{};   //計測終了時刻.

	BOOL      isMove{};   //計測中か.
	TimerMode mode{};     //計測モード.

public:
	//コンストラクタ.
	Timer(float _init, TimerMode _mode) : 
		initTime(_init), mode(_mode) //初期化子.
	{}

	void Start() {
		stTime = clock(); //タイマー開始.
		edTime = 0;
		isMove = TRUE;    //計測中.
	}
	void Stop() {
		if (isMove) {
			edTime = clock(); //タイマー終了.
			isMove = FALSE;   //停止.
		}
	}
	void Reset() {
		stTime = 0;
		edTime = 0;
		isMove = FALSE;
	}
	BOOL GetIsMove() {
		return isMove;
	}

	float GetTime(); //時間取得.
};