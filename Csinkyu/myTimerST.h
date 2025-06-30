/*
   - myTimerST.h - (original)
   ver.2025/06/20

   DxLib: オリジナルタイマー機能の追加.
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
	TimerMode mode{};    //計測モード.
	BOOL      isMove{};  //計測中か.

	float     tmInit{};  //init : 初期時刻.
	clock_t   tmStart{}; //start: 開始時刻.
	clock_t   tmEnd{};   //end  : 終了時刻.

public:
	//コンストラクタ.
	Timer(TimerMode _mode, float _init) :
		mode(_mode), tmInit(_init) //初期化子.
	{}

	void Start() {
		tmStart = clock(); //タイマー開始.
		tmEnd = 0;
		isMove = TRUE;     //計測中.
	}
	void Stop() {
		if (isMove) {
			tmEnd = clock(); //タイマー終了.
			isMove = FALSE;  //停止.
		}
	}
	void Reset() {
		tmStart = 0;
		tmEnd = 0;
		isMove = FALSE;
	}
	BOOL GetIsMove() {
		return isMove;
	}

	float GetPassTime(); //時間取得.
};
//タイマー機能(マイクロ秒)
class TimerMicro
{
private:
	TimerMode     mode{};    //計測モード.
	BOOL          isMove{};  //計測中か.

	LONGLONG      tmInit{};  //init     : 初期時刻.
	LARGE_INTEGER tmStart{}; //start    : 開始時刻.
	LARGE_INTEGER tmEnd{};   //end      : 終了時刻.
	LARGE_INTEGER freq{};    //frequency: 頻度.

public:
	//コンストラクタ.
	TimerMicro(TimerMode _mode, LONGLONG _init) :
		mode(_mode), tmInit(_init) //初期化子.
	{
		Init();
	}

	void Init() {
		QueryPerformanceFrequency(&freq); //頻度の取得.
	}
	void Start() {
		QueryPerformanceCounter(&tmStart); //タイマー開始.
		tmEnd.QuadPart = 0;
		isMove = TRUE; //計測中.
	}
	void Stop() {
		if (isMove) {
			QueryPerformanceCounter(&tmEnd); //タイマー終了.
			isMove = FALSE; //停止.
		}
	}
	void Reset() {
		tmStart.QuadPart = 0;
		tmEnd.QuadPart = 0;
		isMove = FALSE;
	}
	BOOL GetIsMove() {
		return isMove;
	}

	LONGLONG GetPassTime ();          //時間取得.
	BOOL     IntervalTime(float sec); //一定時間ごとにTRUEを返す.
};