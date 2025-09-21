/*
   - KR_Debug.cpp - (DxLib)
   ver: 2025/09/21

   �f�o�b�O�@�\��ǉ����܂��B
*/
#pragma once

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	//�J����...
	//�f�o�b�O�p�̊֐��Q.
	namespace Debug {

		void Log(MY_STRING text, int    value);
		void Log(MY_STRING text, float  value);
		void Log(MY_STRING text, double value);
		void Log(MY_STRING text);

		void LogPadID();

		//�z��f�[�^�̕\��.
		template<typename T>
		void LogArray(T data[], int maxSize) {

			for (int i = 0; i < maxSize; i++)
			{
				int x = 0 + 8 * (i % 200);
				int y = 100 + 16 * (i / 200);
				DrawString(0, 80, _T("�z��f�[�^"), 0xFF00FF);
				DrawFormatString(x, y, 0xFF00FF, _T("%d"), data[i].isActive);
			}
		}
	}
}