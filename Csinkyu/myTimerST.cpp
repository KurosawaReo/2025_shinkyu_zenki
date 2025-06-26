/*
   - myTimerST.cpp - (original)
   ver.2025/06/20

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
	//時間差.
	float ret = 0;

	switch (mode)
	{
		case CountUp:
			ret = tmInit + (float)(tmEnd - tmStart)/1000; //タイマー増加.
			break;
		case CountDown:
			ret = tmInit - (float)(tmEnd - tmStart)/1000; //タイマー減少.
			ret = max(ret, 0); //下限は0秒.
			break;

		default: assert(FALSE); break;
	}

	return ret; //時間を返す.
}

//経過時間取得(マイクロ秒)
LONGLONG TimerMicro::GetPassTime() {

	//終了時刻のセット.
	if (isMove) { QueryPerformanceCounter(&tmEnd); }
	//時間差.
	LONGLONG ret = 0;

	//モード別.
	if (mode == CountUp) {
		ret = tmInit + tmEnd.QuadPart - tmStart.QuadPart; //タイマー増加.
	}
	else{
		ret = tmInit - tmEnd.QuadPart - tmStart.QuadPart; //タイマー減少.
		ret = max(ret, 0); //下限は0μ秒.
	}

	ret *= 1000000;
	ret /= freq.QuadPart;

	return ret; //時間を返す.
}

//一定時間ごとにTRUEを返す(CountUp専用)
BOOL TimerMicro::IntervalTime(float sec) {

	//一定時間経つまで.
	if (GetPassTime() < 1000000/sec) {
		return FALSE; //FALSEを返す.
	}
	Start();     //時間リセット.
	return TRUE; //TRUEを返す.
}