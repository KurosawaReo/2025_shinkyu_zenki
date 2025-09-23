/*
   - KR_Debug.cpp - (DxLib)
   ver: 2025/09/23

   �f�o�b�O�@�\��ǉ����܂��B
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.h�ɓ����ĂȂ���΂����œ���.
  #include "KR_Input.h"
#endif
#include "KR_Debug.h"

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	//�f�o�b�O�p�̊֐��Q.
	namespace Debug 
	{
		//�l�̕\��.
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

		//�}�E�X���W�̕\��(���W���ׂɂ�������)
		void LogMousePos() {
			int mx = -1, my = -1;
			GetMousePoint(&mx, &my); //�}�E�X���W�擾.
			//�\��.
			DrawFormatString(100, 300, 0xFFFFFF, _T("�}�E�X���W: %d, %d"), mx, my);
			//�~.
			DrawCircle(mx, my, 7, 0x303030);
			DrawCircle(mx, my, 5, 0xA0A0A0);
			DrawCircle(mx, my, 3, 0xFFFFFF);
		}
		//�R���g���[��ID�̕\��.
		void LogPadID() {
			DrawFormatString(100, 300, 0xFFFFFF, _T("pad:%d"), GetJoypadInputState(DX_INPUT_PAD1));
		}
	}
}