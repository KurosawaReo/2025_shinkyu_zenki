/*
   - KR_Debug.cpp - (DxLib)
   ver: 2025/09/13

   �f�o�b�O�@�\��ǉ����܂��B
*/
#pragma once

#define _debug_log(value)     printfDx(_T("%s: %d\n"), _get_name(value), value); //�ϐ����ƒl��\��(int)
#define _debug_log_f(value)   printfDx(_T("%s: %f\n"), _get_name(value), value); //�ϐ����ƒl��\��(float, double)
#define _debug_log_str(value) printfDx(value);                                   //�������\��.

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	//�J����...

	//�z��f�[�^�̕\��.
	template<typename T>
	void DebugArray(T data[], int maxSize) {

		for (int i = 0; i < maxSize; i++)
		{
			int x = 0 + 8 * (i % 200);
			int y = 100 + 16 * (i / 200);
			DrawString(0, 80, _T("�z��f�[�^"), 0xFF00FF);
			DrawFormatString(x, y, 0xFF00FF, _T("%d"), data[i].isActive);
		}
	}
}