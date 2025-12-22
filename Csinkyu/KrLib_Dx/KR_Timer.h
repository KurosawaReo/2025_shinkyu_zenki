/*
   - KR_Timer.h - (DxLib)
   ver: 2025/12/23

   タイマー機能を追加。
*/
#pragma once
//KR_Globalが入ってなければここで導入.
#if !defined DEF_KR_DX_GLOBAL
  #include "KR_Global.h"
#endif

//KrLib名前空間.
namespace KR
{
	//タイマーモード.
	enum class TimerMode
	{
		CountUp,	//増えるモード.
		CountDown,	//減るモード.
	};
	//タイマー状態.
	enum class TimerState
	{
		Stop,	//停止中.
		Pause,	//ポーズ中.
		Active,	//稼働中.
	};

	//タイマー共通[継承想定]
	class TimerBase
	{
	protected:
		TimerMode  mode{};  //計測モード.
		TimerState state{};	//タイマー状態.

	public:
		//constructor.
		TimerBase() : 
			mode(TimerMode::CountUp), state(TimerState::Stop) 
		{}
		//get.
		TimerState GetState() const { return state; }

		void Stop() {
			if (TimerStop()) {
				state = TimerState::Stop;  //停止できたらStopへ.
			}
		}
		void Pause() {
			if (TimerStop()) {
				state = TimerState::Pause; //停止できたらPauseへ.
			}
		}

		virtual bool TimerStop() = 0; //停止処理.
	};

	//タイマー機能.
	class Timer : public TimerBase
	{
	//▼ ===== 変数 ===== ▼.
	private:
		float      tmInit{};     //init : 初期時刻.
		clock_t    tmStart{};    //start: 開始時刻.

		float      tmSavePass{}; //時刻保存用(Stop後にStartしたら再開できるように)

	//▼ ===== 関数 ===== ▼.
	private:
		bool TimerStop() override; //タイマー停止.

	public:
		//constructor.
		Timer() {
			Timer(TimerMode::CountUp, 0);
		}
		Timer(TimerMode _mode, float _init) :
			tmInit(_init), tmSavePass(_init) //初期化.
		{}

		void Start() {
			tmStart = clock();            //開始時刻の取得.
			state   = TimerState::Active; //タイマー稼働.
		}
		void Reset() {
			tmStart    = 0;
			tmSavePass = tmInit; //初期時刻.
			state      = TimerState::Stop;
		}

		float GetPassTime();  //時間取得.
		bool  IntervalTime(); //一定時間ごとにtrueを返す.
	};

	//タイマー機能(マイクロ秒)
	class TimerMicro : public TimerBase
	{
	//▼ ===== 変数 ===== ▼.
	private:
		LONGLONG      tmInit{};     //init     : 初期時刻(マイクロ秒)
		LARGE_INTEGER tmStart{};    //start    : 開始時刻(カウント)
		LARGE_INTEGER freq{};       //frequency: 1秒で何カウント進むか.

		LONGLONG      tmSavePass{}; //時刻保存用(Stop後にStartしたら再開できるように)

	//▼ ===== 関数 ===== ▼.
	private:
		bool TimerStop() override; //タイマー停止.

	public:
		//constructor.
		TimerMicro() {
			TimerMicro(TimerMode::CountUp, 0);
		}
		TimerMicro(TimerMode _mode, LONGLONG _init) :
			tmInit(_init), tmSavePass(_init) //初期化.
		{
			QueryPerformanceFrequency(&freq); //頻度の取得.
		}

		void Start() {
			QueryPerformanceCounter(&tmStart); //開始時刻の取得.
			state = TimerState::Active;
		}
		void Reset() {
			tmStart.QuadPart = 0;
			tmSavePass = tmInit; //初期時刻.
			state      = TimerState::Stop;
		}

		LONGLONG GetPassTime();  //時間取得.
		double   GetFps();       //fps取得.
		bool     IntervalTime(); //一定時間ごとにtrueを返す.
	};
}