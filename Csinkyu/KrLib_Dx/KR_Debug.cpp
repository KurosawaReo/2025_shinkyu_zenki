/*
   - KR_Debug.cpp - (DxLib)
   ver: 2025/11/29
*/
#include "KR_Debug.h"

//KrLib名前空間.
namespace KR
{
	//デバッグ用の関数群.
	namespace Debug 
	{
		//値の表示.
		void Log(MY_STRING text) {
			printfDx(_T("%s\n"),     text.c_str());
		}
		void Log(MY_STRING text, int    value) {
			printfDx(_T("%s: %d\n"), text.c_str(), value);
		}
		void Log(MY_STRING text, float  value) {
			printfDx(_T("%s: %f\n"), text.c_str(), value);
		}
		void Log(MY_STRING text, double value) {
			printfDx(_T("%s: %f\n"), text.c_str(), value);
		}

		//マウス座標の表示(座標調べにおすすめ)
		void LogMousePos() {
			int mx = -1, my = -1;
			GetMousePoint(&mx, &my); //マウス座標取得.
			//表示.
			DrawFormatString(100, 300, 0xFFFFFF, _T("マウス座標: %d, %d"), mx, my);
			//円.
			DrawCircle(mx, my, 10, 0x60FFFF, false, 1);
			DrawCircle(mx, my, 7,  0x30A0A0);
			DrawCircle(mx, my, 5,  0x60FFFF);
			DrawCircle(mx, my, 3,  0xC0FFFF);
		}
		//コントローラIDの表示.
		void LogPadID() {
			DrawFormatString(100, 300, 0xFFFFFF, _T("pad:%d"), GetJoypadInputState(DX_INPUT_PAD1));
		}
	}
}