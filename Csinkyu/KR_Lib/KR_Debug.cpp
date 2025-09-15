/*
   - KR_Debug.cpp - (DxLib)
   ver: 2025/09/10

   �f�o�b�O�@�\��ǉ����܂��B
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.h�ɓ����ĂȂ���΂����œ���.
#endif
#include "KR_Debug.h"

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	//�f�o�b�O�p�̊֐��Q.
	namespace Debug 
	{
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
	}
}