/*
   - KR_Debug.h - (DxLib)
   ver: 2025/11/29

   デバッグ機能を追加。
*/
#pragma once
//KR_Globalが入ってなければここで導入.
#if !defined DEF_KR_DXLIB_GLOBAL
  #include "KR_Global.h"
#endif
#include "KR_Input.h"

//KrLib名前空間.
namespace KR
{
	//デバッグ用の関数群.
	namespace Debug {

		void Log(MY_STRING text);
		void Log(MY_STRING text, int    value);
		void Log(MY_STRING text, float  value);
		void Log(MY_STRING text, double value);

		void LogMousePos();
		void LogPadID();
	}
}