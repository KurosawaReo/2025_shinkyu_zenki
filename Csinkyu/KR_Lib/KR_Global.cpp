/*
   - KR_Global.h - (DxLib)
   ver: 2025/09/21

   KR_Lib�S�̂Ŏg���ėp�@�\��ǉ����܂��B
*/
#include "KR_Global.h"

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	//constructor.
	MY_COLOR::MY_COLOR(UINT _colorCode) {
		*this = _colorCode;
	}

	//����p.
	inline void MY_COLOR::operator=(const RGBA& rgba) {
		color = rgba; //���̂܂�.
	}
	inline void MY_COLOR::operator=(UINT colorCode) {
		//�J���[�R�[�h��RGB�ɕ���.
		color.r =  colorCode / 0x010000;
		color.g = (colorCode / 0x000100) % 0x100;
		color.b =  colorCode % 0x100;
		color.a = 255;
	}
}