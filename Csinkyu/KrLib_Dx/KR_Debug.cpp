/*
   - KR_Debug.cpp - (DxLib)
   ver.2026/01/28
*/
#include "KR_Debug.h"

//[include] cppでのみ使うもの.
#include "KR_App.h"
#include "KR_Camera.h"

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
		void Log(MY_STRING text, bool   value) {
			printfDx(_T("%s: %s\n"), text.c_str(), (value) ? _T("true") : _T("false"));
		}
		void Log(MY_STRING text, INT_XY pos) {
			printfDx(_T("%s: %d %d\n"),     text.c_str(), pos.x, pos.y);
		}
		void Log(MY_STRING text, DBL_XY pos) {
			printfDx(_T("%s: %.2f %.2f\n"), text.c_str(), pos.x, pos.y);
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

		//マウスカーソルに合わせてカメラを動かす.
		void MouseToMoveCamera() {

			static DBL_XY initPos = Camera::GetCameraPos();

			int mx = -1, my = -1;
			GetMousePoint(&mx, &my); //マウス座標取得.

			INT_XY move = {mx, my};
			//カメラを動かす.
			Camera::SetPos(initPos + move.ToDbl());
		}
	}
}