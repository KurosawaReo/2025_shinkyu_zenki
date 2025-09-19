/*
   - KR_Debug.cpp - (DxLib)
   ver: 2025/09/19

   デバッグ機能を追加します。
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.hに入ってなければここで導入.
#endif
#include "KR_Debug.h"

//KR_Libに使う用.
namespace KR_Lib
{
	//デバッグ用の関数群.
	namespace Debug 
	{
		//値の表示.
		void Log(MY_STRING text, int    value) {
			printfDx(_T("%s: %d\n"), text.c_str(), value);
		}
		void Log(MY_STRING text, float  value) {
			printfDx(_T("%s: %f\n"), text.c_str(), value);
		}
		void Log(MY_STRING text, double value) {
			printfDx(_T("%s: %f\n"), text.c_str(), value);
		}
		void Log(MY_STRING text) {
			printfDx(_T("%s\n"),     text.c_str());
		}

		//コントローラIDの表示.
		void LogPadID() {
			DrawFormatString(100, 300, 0xFFFFFF, _T("pad:%d"), GetJoypadInputState(DX_INPUT_PAD1));
		}
	}
}