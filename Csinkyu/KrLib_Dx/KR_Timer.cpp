/*
   - KR_Timer.cpp - (DxLib)
   ver: 2025/11/29
*/
#include "KR_Timer.h"

//KrLib名前空間.
namespace KR
{
// ▼*--=<[ Timer ]>=--*▼ //

	//タイマー停止.
	void Timer::Stop() {

		//計測中なら.
		if (isMove) {

			float elapsed = _flt(clock() - tmStart)/1000; //時間差.

			//経過時間を更新.
			if (mode == TimerMode::CountUp) {
				tmSavePass += elapsed;           //タイマー増加.
			}
			else {
				tmSavePass -= elapsed;           //タイマー減少.
				tmSavePass = max(tmSavePass, 0); //下限は0秒.
			}
			isMove = false; //停止.
		}
	}
	//経過時間取得.
	float Timer::GetPassTime() {

		//計測中なら.
		if (isMove) { 
			float elapsed = _flt(clock() - tmStart)/1000; //時間差.
			float pass = 0; //経過時間.

			if (mode == TimerMode::CountUp) {
				pass = tmSavePass + elapsed; //タイマー増加.
			}
			else {
				pass = tmSavePass - elapsed; //タイマー減少.
				pass = max(pass, 0);         //下限は0秒.
			}
			return pass; //仮で計算した時間差を返す.
		}
		else {
			return tmSavePass; //保存時間を返す.
		}	
	}
	//一定時間ごとにtrueを返す(CountDown専用)
	bool Timer::IntervalTime() {

		//CountDownじゃない場合はfalseを返し続ける.
		if (mode != TimerMode::CountDown) {
			return false;
		}

		//タイマーが0になるまで.
		if (GetPassTime() > 0) {
			return false; //falseを返す.
		}
		Start();     //時間リセット.
		return true; //trueを返す.
	}

// ▼*--=<[ TimerMicro ]>=--*▼ //

	void TimerMicro::Stop() {

		if (isMove) {
		
			LARGE_INTEGER tmEnd;
			QueryPerformanceCounter(&tmEnd); //終了時刻の取得.

			//時間差(freqでカウントをマイクロ秒に変換する)
			LONGLONG elapsed = (tmEnd.QuadPart - tmStart.QuadPart) * 1000000/freq.QuadPart;

			//経過時間を更新.
			if (mode == TimerMode::CountUp) {
				tmSavePass += elapsed;           //タイマー増加.
			}
			else {
				tmSavePass -= elapsed;           //タイマー減少.
				tmSavePass = max(tmSavePass, 0); //下限は0秒.
			}
			isMove = false; //停止.
		}
	}
	//経過時間取得(マイクロ秒)
	LONGLONG TimerMicro::GetPassTime() {

		//計測中なら.
		if (isMove) { 

			LARGE_INTEGER tmEnd;
			QueryPerformanceCounter(&tmEnd); //終了時刻の取得.

			//時間差(freqでカウントをマイクロ秒に変換する)
			LONGLONG elapsed = (tmEnd.QuadPart - tmStart.QuadPart) * 1000000/freq.QuadPart;
			//経過時間.
			LONGLONG pass;

			if (mode == TimerMode::CountUp) {
				pass = tmSavePass + elapsed; //タイマー増加.
			}
			else{
				pass = tmSavePass - elapsed; //タイマー減少.
				pass = max(pass, 0);         //下限は0カウント.
			}
			return pass; //仮で計算した時間差を返す.
		}
		else {
			return tmSavePass; //保存時間を返す.
		}
	}
	//fps取得.
	double TimerMicro::GetFps() {

		//計測中なら.
		if (isMove) {

			LARGE_INTEGER tmEnd;
			QueryPerformanceCounter(&tmEnd); //終了時刻の取得.

			//時間差(freqでカウントをマイクロ秒に変換する)
			LONGLONG elapsed = (tmEnd.QuadPart - tmStart.QuadPart) * 1000000/freq.QuadPart;
			//fpsの計算.
			const double fps = _flt(1000000)/elapsed;

			Start(); //時間リセット.

			return fps; //fpsを返す.
		}
		else {
			return 0; //計測中じゃない時はfps0
		}
	}
	//一定時間ごとにtrueを返す(CountDown専用)
	bool TimerMicro::IntervalTime() {

		//CountDownじゃない場合はfalseを返し続ける.
		if (mode != TimerMode::CountDown) {
			return false;
		}

		//タイマーが0になるまで.
		if (GetPassTime() > 0) {
			return false; //falseを返す.
		}
		Start();     //時間リセット.
		return true; //trueを返す.
	}
}