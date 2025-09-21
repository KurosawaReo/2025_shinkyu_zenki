/*
   - KR_Debug.cpp - (DxLib)
   ver: 2025/09/21

   デバッグ機能を追加します。
*/
#pragma once

//KR_Libに使う用.
namespace KR_Lib
{
	//開発中...
	//デバッグ用の関数群.
	namespace Debug {

		void Log(MY_STRING text, int    value);
		void Log(MY_STRING text, float  value);
		void Log(MY_STRING text, double value);
		void Log(MY_STRING text);

		void LogPadID();

		//配列データの表示.
		template<typename T>
		void LogArray(T data[], int maxSize) {

			for (int i = 0; i < maxSize; i++)
			{
				int x = 0 + 8 * (i % 200);
				int y = 100 + 16 * (i / 200);
				DrawString(0, 80, _T("配列データ"), 0xFF00FF);
				DrawFormatString(x, y, 0xFF00FF, _T("%d"), data[i].isActive);
			}
		}
	}
}