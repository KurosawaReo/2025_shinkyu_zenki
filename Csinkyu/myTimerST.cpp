/*
   - myTimerST.cpp - (original)
   ver.2025/06/17

   DxLibで使う用のオリジナル時間関数.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafxがなければここで定義.
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

	switch (mode)
	{
		case CountUp:
			ret = tmInit + tmEnd.QuadPart - tmStart.QuadPart; //タイマー増加.
			break;
		case CountDown:
			ret = tmInit - tmEnd.QuadPart - tmStart.QuadPart; //タイマー減少.
			ret = max(ret, 0); //下限は0μ秒.
			break;

		default: assert(FALSE); break;
	}

	ret *= 1000000;
	ret /= freq.QuadPart;

	return ret; //時間を返す.
}