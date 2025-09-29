/*
   - KR_Debug.h - (DxLib)
   ver: 2025/09/23

   デバッグ機能を追加します。
*/
#pragma once

//KR_Libに使う用.
namespace KR_Lib
{
	//デバッグ用の関数群.
	namespace Debug {

		void Log(MY_STRING text);
		void Log(MY_STRING text, int    value);
		void Log(MY_STRING text, float  value);
		void Log(MY_STRING text, double value);

		void LogMousePos();
		void LogPadID();

		//配列データの表示用.
		template<typename T, _type_num_only(T)>
		void LogArray(T num, int maxSize) {

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