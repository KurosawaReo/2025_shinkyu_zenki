/*
   - myTimerST.cpp - (original)
   ver.2025/07/19

   DxLib: オリジナルタイマー機能の追加.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx等に入ってなければここで導入.
#endif
#include "myTimerST.h"

//経過時間取得.
float Timer::GetPassTime() {

	//終了時刻のセット.
	if (isMove) { tmEnd = clock(); }
	
	float elapsed = (float)(tmEnd - tmStart)/1000; //時間差.
	float ret;                                     //経過時間.

	if (mode == CountUp) {
		ret = tmInit + elapsed; //タイマー増加.
	}
	else {
		ret = tmInit - elapsed; //タイマー減少.
		ret = max(ret, 0);      //下限は0秒.
	}
	return ret;
}

//経過時間取得(マイクロ秒)
LONGLONG TimerMicro::GetPassTime() {

	//終了時刻のセット.
	if (isMove) { QueryPerformanceCounter(&tmEnd); }

	//時間差(freqでカウントをマイクロ秒に変換する)
	LONGLONG elapsed = (tmEnd.QuadPart - tmStart.QuadPart) * 1000000/freq.QuadPart;
	//経過時間.
	LONGLONG ret;

	if (mode == CountUp) {
		ret = tmInit + elapsed; //タイマー増加.
	}
	else{
		ret = tmInit - elapsed; //タイマー減少.
		ret = max(ret, 0);      //下限は0カウント.
	}
	return ret;
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