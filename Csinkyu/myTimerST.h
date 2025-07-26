/*
   - myTimerST.h - (original)
   ver.2025/07/25

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
	TimerMode mode{};       //計測モード.
	BOOL      isMove{};     //計測中か.

	float     tmInit{};     //init : 初期時刻.
	clock_t   tmStart{};    //start: 開始時刻.

	float     tmSavePass{}; //時刻保存用(Stop後にStartしたら再開できるように)

public:
	//コンストラクタ.
	Timer(TimerMode _mode, float _init) :
		mode(_mode), tmInit(_init), tmSavePass(_init) //初期化子.
	{}

	void Start() {
		tmStart = clock(); //開始時刻の取得.
		isMove = TRUE;     //計測中.
	}
	void Stop();
	void Reset() {
		tmStart = 0;
		tmSavePass = tmInit; //初期時刻.
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
	TimerMode     mode{};       //計測モード.
	BOOL          isMove{};     //計測中か.

	LONGLONG      tmInit{};     //init     : 初期時刻(マイクロ秒)
	LARGE_INTEGER tmStart{};    //start    : 開始時刻(カウント)
	LARGE_INTEGER freq{};       //frequency: 1秒で何カウント進むか.

	LONGLONG      tmSavePass{}; //時刻保存用(Stop後にStartしたら再開できるように)

public:
	//コンストラクタ.
	TimerMicro(TimerMode _mode, LONGLONG _init) :
		mode(_mode), tmInit(_init), tmSavePass(_init) //初期化子.
	{
		Init();
	}

	void Init() {
		QueryPerformanceFrequency(&freq); //頻度の取得.
	}
	void Start() {
		QueryPerformanceCounter(&tmStart); //開始時刻の取得.
		isMove = TRUE; //計測中.
	}
	void Stop();
	void Reset() {
		tmStart.QuadPart = 0;
		tmSavePass = tmInit; //初期時刻.
		isMove = FALSE;
	}
	BOOL GetIsMove() {
		return isMove;
	}

	LONGLONG GetPassTime (); //時間取得.
	BOOL     IntervalTime(); //一定時間ごとにTRUEを返す.
};