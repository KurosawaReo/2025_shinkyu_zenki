/*
   - KR_Timer.h - (DxLib)
   ver: 2025/09/10

   タイマー機能を追加します。
*/
#pragma once

//KR_Libに使う用.
namespace KR_Lib
{
	//タイマーモード.
	enum TimerMode
	{
		COUNT_UP,
		COUNT_DOWN,
	};

	//タイマー機能.
	class Timer
	{
	private:
		TimerMode mode{};       //計測モード.
		bool      isMove{};     //計測中か.

		float     tmInit{};     //init : 初期時刻.
		clock_t   tmStart{};    //start: 開始時刻.

		float     tmSavePass{}; //時刻保存用(Stop後にStartしたら再開できるように)

	public:
		//constructor.
		Timer(){}
		Timer(TimerMode _mode, float _init) :
			mode(_mode), tmInit(_init), tmSavePass(_init) //初期化子.
		{}

		void Start() {
			tmStart = clock(); //開始時刻の取得.
			isMove = true;     //計測中.
		}
		void Stop();
		void Reset() {
			tmStart = 0;
			tmSavePass = tmInit; //初期時刻.
			isMove = false;
		}
		bool GetIsMove() const {
			return isMove;
		}

		float GetPassTime();  //時間取得.
		bool  IntervalTime(); //一定時間ごとにtrueを返す.
	};

	//タイマー機能(マイクロ秒)
	class TimerMicro
	{
	private:
		TimerMode     mode{};       //計測モード.
		bool          isMove{};     //計測中か.

		LONGLONG      tmInit{};     //init     : 初期時刻(マイクロ秒)
		LARGE_INTEGER tmStart{};    //start    : 開始時刻(カウント)
		LARGE_INTEGER freq{};       //frequency: 1秒で何カウント進むか.

		LONGLONG      tmSavePass{}; //時刻保存用(Stop後にStartしたら再開できるように)

	public:
		//constructor.
		TimerMicro(){}
		TimerMicro(TimerMode _mode, LONGLONG _init) :
			mode(_mode), tmInit(_init), tmSavePass(_init) //初期化子.
		{
			QueryPerformanceFrequency(&freq); //頻度の取得.
		}

		void Start() {
			QueryPerformanceCounter(&tmStart); //開始時刻の取得.
			isMove = true; //計測中.
		}
		void Stop();
		void Reset() {
			tmStart.QuadPart = 0;
			tmSavePass = tmInit; //初期時刻.
			isMove = false;
		}
		bool GetIsMove() const {
			return isMove;
		}

		LONGLONG GetPassTime (); //時間取得.
		bool     IntervalTime(); //一定時間ごとにtrueを返す.
	};
}