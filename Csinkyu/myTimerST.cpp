/*
   - myTimerST.cpp - (original)
   ver.2025/06/09

   DxLibで使う用のオリジナル時間関数.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafxがなければここで定義.
#endif

#include "myTimerST.h"

//時間取得.
float Timer::GetTime() {

	//終わりの時間.
	clock_t ed = (isMove) ? clock() : edTime;
	//時間差.
	float ret = 0;

	switch (mode)
	{
		case CountUp:   
			ret = initTime + (float)(ed - stTime)/1000; //タイマー増加.
			break;
		case CountDown: 
			ret = initTime - (float)(ed - stTime)/1000; //タイマー減少.
			ret = max(ret, 0); //下限は0秒.
			break;

		default: assert(FALSE); break;
	}

	return ret; //時間を返す.
}