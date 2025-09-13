/*
   - KR_Debug.cpp - (DxLib)
   ver: 2025/09/13

   デバッグ機能を追加します。
*/
#pragma once

#define _debug_log(value)     printfDx(_T("%s: %d\n"), _get_name(value), value); //変数名と値を表示(int)
#define _debug_log_f(value)   printfDx(_T("%s: %f\n"), _get_name(value), value); //変数名と値を表示(float, double)
#define _debug_log_str(value) printfDx(value);                                   //文字列を表示.

//KR_Libに使う用.
namespace KR_Lib
{
	//開発中...

	//配列データの表示.
	template<typename T>
	void DebugArray(T data[], int maxSize) {

		for (int i = 0; i < maxSize; i++)
		{
			int x = 0 + 8 * (i % 200);
			int y = 100 + 16 * (i / 200);
			DrawString(0, 80, _T("配列データ"), 0xFF00FF);
			DrawFormatString(x, y, 0xFF00FF, _T("%d"), data[i].isActive);
		}
	}
}