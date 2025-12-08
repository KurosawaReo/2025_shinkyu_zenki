/*
   - KR_Debug.h - (DxLib)
   ver: 2025/12/07

   デバッグ機能を追加。
*/
#pragma once
//KR_Globalが入ってなければここで導入.
#if !defined DEF_KR_DX_GLOBAL
  #include "KR_Global.h"
#endif

//KrLib名前空間.
namespace KR
{
	//デバッグ用の関数群.
	namespace Debug {

		//表示系.
		void Log        (MY_STRING text);
		void Log        (MY_STRING text, int    value);
		void Log        (MY_STRING text, float  value);
		void Log        (MY_STRING text, double value);
		void Log        (MY_STRING text, INT_XY pos);
		void Log        (MY_STRING text, DBL_XY pos);
		void LogMousePos();
		void LogPadID   ();

		//動作系.
		void MouseToMoveCamera();
	}
}