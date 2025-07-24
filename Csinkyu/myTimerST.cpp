/*
   - myTimerST.cpp - (original)
   ver.2025/07/25

   DxLib: オリジナルタイマー機能の追加.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx等に入ってなければここで導入.
#endif
#include "myTimerST.h"

//タイマー停止.
void Timer::Stop() {

	//計測中なら.
	if (isMove) {

		float elapsed = (float)(clock() - tmStart)/1000; //時間差.

		//経過時間を更新.
		if (mode == CountUp) {
			tmSavePass += elapsed;           //タイマー増加.
		}
		else {
			tmSavePass -= elapsed;           //タイマー減少.
			tmSavePass = max(tmSavePass, 0); //下限は0秒.
		}
		isMove = FALSE; //停止.
	}
}
//経過時間取得.
float Timer::GetPassTime() {

	//計測中なら.
	if (isMove) { 
		float elapsed = (float)(clock() - tmStart)/1000; //時間差.
		float pass = 0; //経過時間.

		if (mode == CountUp) {
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

void TimerMicro::Stop() {

	if (isMove) {
		
		LARGE_INTEGER tmEnd;
		QueryPerformanceCounter(&tmEnd); //終了時刻の取得.

		//時間差(freqでカウントをマイクロ秒に変換する)
		LONGLONG elapsed = (tmEnd.QuadPart - tmStart.QuadPart) * 1000000/freq.QuadPart;

		//経過時間を更新.
		if (mode == CountUp) {
			tmSavePass += elapsed;           //タイマー増加.
		}
		else {
			tmSavePass -= elapsed;           //タイマー減少.
			tmSavePass = max(tmSavePass, 0); //下限は0秒.
		}
		isMove = FALSE; //停止.
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

		if (mode == CountUp) {
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
//一定時間ごとにTRUEを返す(CountDown専用)
BOOL TimerMicro::IntervalTime() {

	//CountDownじゃない場合はFALSEを返し続ける.
	if (mode != CountDown) {
		return FALSE;
	}

	//タイマーが0になるまで.
	if (GetPassTime() > 0) {
		return FALSE; //FALSEを返す.
	}
	Start();     //時間リセット.
	return TRUE; //TRUEを返す.
}